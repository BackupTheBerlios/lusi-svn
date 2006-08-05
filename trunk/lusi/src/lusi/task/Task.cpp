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

using lusi::task::helper::TaskHelper;
using lusi::task::helper::TaskHelperManager;
using lusi::package::Package;
using lusi::package::status::PackageStatus;

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

    //mName must be set before calling getTaskHelpers, as it uses getName()
    mTaskHelpers = TaskHelperManager::getInstance()->getTaskHelpers(this);
    mCurrentTaskHelper = mTaskHelpers.begin();

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

inline Package* Task::getPackage() {
    return mPackage;
}

inline TaskConfiguration* Task::getTaskConfiguration() {
    return mTaskConfiguration;
}

inline TaskLogger* Task::getTaskLogger() {
    return mTaskLogger;
}

inline TaskProgress* Task::getTaskProgress() {
    return mTaskProgress;
}
*/

//TODO implement a better test logic
bool Task::test() {
    return mTaskHelpers.size() > 0;
}

//TODO throw exception if Task couldn't be done? Return false?
//TODO add configuration checkings
//TODO add support for several suitable TaskHelpers
void Task::redo() {
    TaskHelper* taskHelper = getRedoTaskHelper();
    if (taskHelper != 0) {
        mTaskLogger->notifyEvent(mName + ": executing " + taskHelper->getName() +
                                            '\n', message);
        taskHelper->execute();

        mPackage->setPackageStatus(mProvidedPackageStatus);
    }
}

//TODO throw exception if Task couldn't be undone? Return false?
void Task::undo() {
    TaskHelper* taskHelper = getUndoTaskHelper();
    if (taskHelper != 0) {
        taskHelper->revert();

        mPackage->setPackageStatus(mNeededPackageStatus);
    }
}

//private:

TaskHelper* Task::getRedoTaskHelper() {
    //TODO get TaskHelper from TaskConfiguration

    TaskHelper* taskHelper = 0;
    bool validTaskHelper = false;
    for (; !validTaskHelper && mCurrentTaskHelper != mTaskHelpers.end();
            ++mCurrentTaskHelper) {
        taskHelper = *mCurrentTaskHelper;
        if (taskHelper->hasValidResourceMap()) {
            validTaskHelper = true;
        }
    }

    return taskHelper;
}

TaskHelper* Task::getUndoTaskHelper() {
    //TODO get TaskHelper from TaskConfiguration
    return 0;
}
