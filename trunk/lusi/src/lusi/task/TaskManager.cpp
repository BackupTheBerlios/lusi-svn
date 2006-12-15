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

#include "TaskManager.h"
#include "Task.h"
#include "../package/Package.h"
#include "../package/Profile.h"
#include "../package/status/BuiltPackageStatus.h"
#include "../package/status/ConfiguredPackageStatus.h"
#include "../package/status/InstalledPackageStatus.h"
#include "../package/status/PackedPackageStatus.h"
#include "../package/status/UnpackedPackageStatus.h"

using std::make_pair;
using std::multimap;
using std::pair;
using std::string;
using std::vector;

using lusi::package::Package;
using lusi::package::status::PackageStatus;
using lusi::package::status::BuiltPackageStatus;
using lusi::package::status::ConfiguredPackageStatus;
using lusi::package::status::InstalledPackageStatus;
using lusi::package::status::PackedPackageStatus;
using lusi::package::status::UnpackedPackageStatus;

using namespace lusi::task;

//public:

TaskManager* TaskManager::getInstance() {
    if (sInstance == 0) {
        sInstance = new TaskManager();
    }

    return sInstance;
}

TaskManager::~TaskManager() {
}

//TODO handle several valid Tasks registered with the same needed status
Task* TaskManager::getTask(Package* package) {
    Task* task = getTaskFromProfile(package);

    if (task) {
        return task;
    }

    vector<TaskData> tasks = getTasksByPackageStatus(
                    package->getPackageStatus(), mTasksByNeededPackageStatus);
    for (vector<TaskData>::const_iterator iterator = tasks.begin();
                iterator != tasks.end() && task == 0; ++iterator) {
        task = new Task((*iterator).id, package,
                (*iterator).neededPackageStatus,
                (*iterator).providedPackageStatus);
        if (!task->test()) {
            delete task;
            task = 0;
        }
    }

    return task;
}

void TaskManager::registerTask(const string& id,
                               const PackageStatus* neededPackageStatus,
                               const PackageStatus* providedPackageStatus) {
    TaskData taskData;
    taskData.id = id;
    taskData.neededPackageStatus = neededPackageStatus;
    taskData.providedPackageStatus = providedPackageStatus;

    mTasksByNeededPackageStatus.insert(make_pair(neededPackageStatus,
                                                 taskData));
    mTasksByProvidedPackageStatus.insert(make_pair(providedPackageStatus,
                                                   taskData));
}

//private:

TaskManager* TaskManager::sInstance = 0;

TaskManager::TaskManager(): mTasksByNeededPackageStatus(),
                    mTasksByProvidedPackageStatus() {
    registerTask("BuildTask", ConfiguredPackageStatus::getInstance(),
                 BuiltPackageStatus::getInstance());
    registerTask("ConfigureTask", UnpackedPackageStatus::getInstance(),
                 ConfiguredPackageStatus::getInstance());
    registerTask("ExtractTask", PackedPackageStatus::getInstance(),
                 UnpackedPackageStatus::getInstance());
    registerTask("InstallTask", BuiltPackageStatus::getInstance(),
                 InstalledPackageStatus::getInstance());
    registerTask("UndoInstallTask", InstalledPackageStatus::getInstance(),
                 BuiltPackageStatus::getInstance());
}

vector<TaskManager::TaskData> TaskManager::getTasksByPackageStatus(
                                    const PackageStatus* packageStatus,
                                    const multimap<const PackageStatus*,
                                                   TaskData>& tasksMultimap) {
    vector<TaskData> taskDatas;

    typedef multimap<const PackageStatus*, TaskData>::const_iterator iterator;
    for (pair<iterator, iterator> range =
                    tasksMultimap.equal_range(packageStatus);
            range.first != range.second; ++range.first) {
       taskDatas.push_back(range.first->second);
    }

    return taskDatas;
}

Task* TaskManager::getTaskFromProfile(Package* package) {
    string taskId = package->getProfile()->getTaskId();
    if (taskId == "") {
        return 0;
    }

    //TODO index Tasks also by name, instead of traversing the other maps
    typedef multimap<const PackageStatus*, TaskData>::const_iterator iterator;
    for (iterator it = mTasksByNeededPackageStatus.begin();
            it != mTasksByNeededPackageStatus.end(); ++it) {
        if (it->second.id == taskId) {
            Task* task = new Task(it->second.id, package,
                                 it->second.neededPackageStatus,
                                 it->second.providedPackageStatus);
            if (task->test()) {
                return task;
            }
            delete task;
        }
    }

    return 0;
}
