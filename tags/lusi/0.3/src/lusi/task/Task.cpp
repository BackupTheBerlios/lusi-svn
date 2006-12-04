/***************************************************************************
 *   Copyright (C) 2006 by Daniel Calviño Sánchez                          *
 *   kalvy@users.berlios.de                                                *
 *                                                                         *
 *   This library is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This library is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this library; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "Task.h"
#include "TaskConfiguration.h"
#include "TaskLogger.h"
#include "TaskProgress.h"
#include "helper/TaskHelper.h"
#include "helper/TaskHelperManager.h"
#include "../configuration/ConfigurationMerger.h"
#include "../package/Package.h"
#include "../util/SmartPtr.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationMerger;
using lusi::configuration::InvalidConfigurationException;
using lusi::package::Package;
using lusi::package::status::PackageStatus;
using lusi::task::helper::ExecuteTaskHelperException;
using lusi::task::helper::TaskHelper;
using lusi::task::helper::TaskHelperManager;
using lusi::util::SmartPtr;

using namespace lusi::task;

//public:

Task::Task(const string& name, Package* package,
           const PackageStatus* neededPackageStatus,
           const PackageStatus* providedPackageStatus) {
    mName = name;
    mPackage = package;
    mTaskConfiguration = new TaskConfiguration(this);
    mNeededPackageStatus = neededPackageStatus;
    mProvidedPackageStatus = providedPackageStatus;
    mCurrentTaskHelper = 0;

    //mName must be set before calling getTaskHelpers, as it uses getName()
    mTaskHelpers = TaskHelperManager::getInstance()->getTaskHelpers(this);
    mTaskHelpersIterator = mTaskHelpers.begin();
    nextTaskHelper();

    mTaskLogger = new TaskLogger(this);
    mTaskProgress = new TaskProgress(this);

    sortTaskHelpers();
}

Task::~Task() {
    for (vector<TaskHelper*>::const_iterator iterator = mTaskHelpers.begin();
            iterator != mTaskHelpers.end(); ++iterator) {
        delete *iterator;
    }

    delete mTaskConfiguration;
    delete mTaskLogger;
    delete mTaskProgress;
}

/*
inline const string& Task::getName() const {
    return mName;
}

inline Package* Task::getPackage() const {
    return mPackage;
}

inline TaskConfiguration* Task::getTaskConfiguration() const {
    return mTaskConfiguration;
}

inline const PackageStatus* Task::getNeededPackageStatus() const {
    return mNeededPackageStatus;
}

inline const PackageStatus* Task::getProvidedPackageStatus() const {
    return mProvidedPackageStatus;
}

inline TaskLogger* Task::getTaskLogger() const {
    return mTaskLogger;
}

inline TaskProgress* Task::getTaskProgress() const {
    return mTaskProgress;
}
*/

SmartPtr<ConfigurationParameterMap> Task::getTaskHelperConfiguration() const {
    if (mCurrentTaskHelper != 0) {
        return mCurrentTaskHelper->getConfigurationParameterMap();
    }

    return SmartPtr<ConfigurationParameterMap>();
}

SmartPtr<ConfigurationParameterMap> Task::getInvalidConfiguration() const {
    if (mCurrentTaskHelper != 0) {
        return mCurrentTaskHelper->getInvalidConfiguration();
    }

    return SmartPtr<ConfigurationParameterMap>();
}

//TODO implement a better test logic
bool Task::test() const {
    return mTaskHelpers.size() > 0 && mCurrentTaskHelper != 0;
}

//TODO add support for several suitable TaskHelpers
void Task::execute() throw (ExecuteTaskException,
                            InvalidConfigurationException) {
    if (!test()) {
        throw ExecuteTaskException("There are no available task helpers");
    }

    mTaskLogger->notifyEvent(mName + ": executing " +
                             mCurrentTaskHelper->getName() + '\n', message);

    try {
        mCurrentTaskHelper->execute();
    } catch (ExecuteTaskHelperException e) {
        mTaskLogger->notifyEvent("An exception happened when executing " +
            mCurrentTaskHelper->getName() + ": " + e.what() + '\n', error);
        throw ExecuteTaskException("An exception happened when executing " +
            mCurrentTaskHelper->getName() + ": " + e.what());
    }

    mPackage->setPackageStatus(mProvidedPackageStatus);
    mTaskConfiguration->addTaskHelperConfiguration(
                            mCurrentTaskHelper->getConfigurationParameterMap());
    //If it fails to save... well, bad luck :P, as it will likely be due to
    //external factors that can't be corrected (for example, lack of
    //permissions in the configuration directory)
    mTaskConfiguration->save();

    nextTaskHelper();

    mTaskProgress->setExtendedProgress(false);
}

//private:

void Task::nextTaskHelper() {
    TaskHelper* taskHelper = 0;
    bool validTaskHelper = false;
    for (; !validTaskHelper && mTaskHelpersIterator != mTaskHelpers.end();
            ++mTaskHelpersIterator) {
        taskHelper = *mTaskHelpersIterator;
        if (taskHelper->hasValidResources()) {
            validTaskHelper = true;
        } else {
            taskHelper = 0;
        }
    }

    if (taskHelper != 0) {
        //The advantage of having the call to init here instead of in
        //TaskHelperManager::getTaskHelpers() is that it is only called when
        //the TaskHelper is going to be executed. Having it in getTaskHelpers,
        //every TaskHelper configuration would be inited.
        taskHelper->initConfigurationParameterMap();

        SmartPtr<ConfigurationParameterMap> savedTaskHelperConfiguration =
                mTaskConfiguration->getTaskHelperConfiguration(
                        taskHelper->getName());
        if (!savedTaskHelperConfiguration.isNull()) {
            ConfigurationMerger().merge(
                    getPtr(taskHelper->getConfigurationParameterMap()),
                    getPtr(savedTaskHelperConfiguration));
        }
    }

    mCurrentTaskHelper = taskHelper;
}

void Task::sortTaskHelpers() {
    vector< SmartPtr<ConfigurationParameterMap> > loadedTaskHelpers =
                        mTaskConfiguration->getAllTaskHelperConfigurations();

    for (vector< SmartPtr<ConfigurationParameterMap> >::reverse_iterator rIt =
                                                    loadedTaskHelpers.rbegin();
            rIt != loadedTaskHelpers.rend(); ++rIt) {
        bool found = false;
        vector<TaskHelper*>::iterator it = mTaskHelpers.begin();

        while (!found && it != mTaskHelpers.end()) {
            if ((*it)->getName() == (*rIt)->getId()) {
                TaskHelper* taskHelper = *it;
                mTaskHelpers.erase(it);
                mTaskHelpers.insert(mTaskHelpers.begin(), taskHelper);

                found = true;
            }
            ++it;
        }
    }
}
