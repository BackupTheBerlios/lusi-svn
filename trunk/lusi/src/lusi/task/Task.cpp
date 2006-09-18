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
#include "../package/Package.h"

using std::string;
using std::vector;

using lusi::configuration::InvalidConfigurationException;
using lusi::configuration::ConfigurationParameterMap;
using lusi::package::Package;
using lusi::package::status::PackageStatus;
using lusi::task::helper::ExecuteTaskHelperException;
using lusi::task::helper::TaskHelper;
using lusi::task::helper::TaskHelperManager;

using namespace lusi::task;

//public:

Task::Task(const string& name, Package* package,
           TaskConfiguration* taskConfiguration,
           const PackageStatus* neededPackageStatus,
           const PackageStatus* providedPackageStatus) {
    mName = name;
    mPackage = package;
    mTaskConfiguration = taskConfiguration;
    mNeededPackageStatus = neededPackageStatus;
    mProvidedPackageStatus = providedPackageStatus;
    mCurrentTaskHelper = 0;

    //mName must be set before calling getTaskHelpers, as it uses getName()
    mTaskHelpers = TaskHelperManager::getInstance()->getTaskHelpers(this);
    mTaskHelpersIterator = mTaskHelpers.begin();
    nextTaskHelper();

    mTaskLogger = new TaskLogger(this);
    mTaskProgress = new TaskProgress(this);
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

ConfigurationParameterMap Task::getTaskHelperConfiguration() const {
    if (mCurrentTaskHelper != 0) {
        return mCurrentTaskHelper->getConfigurationParameterMap();
    }

    return ConfigurationParameterMap();
}


ConfigurationParameterMap Task::getInvalidConfiguration() const {
    if (mCurrentTaskHelper != 0) {
        return mCurrentTaskHelper->getInvalidConfiguration();
    }

    return ConfigurationParameterMap();
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
    mTaskConfiguration->merge(
                        mCurrentTaskHelper->getConfigurationParameterMap());

    nextTaskHelper();

    mTaskProgress->setExtendedProgress(false);
}

//private:

void Task::nextTaskHelper() {

    //TODO get TaskHelper from TaskConfiguration

    TaskHelper* taskHelper = 0;
    bool validTaskHelper = false;
    for (; !validTaskHelper && mTaskHelpersIterator != mTaskHelpers.end();
            ++mTaskHelpersIterator) {
        taskHelper = *mTaskHelpersIterator;
        if (taskHelper->hasValidResourceMap()) {
            validTaskHelper = true;
        }
    }

    if (taskHelper != 0) {
        taskHelper->initConfigurationParameterMap();
        taskHelper->getConfigurationParameterMap().merge(*mTaskConfiguration);
    }

    mCurrentTaskHelper = taskHelper;
}
