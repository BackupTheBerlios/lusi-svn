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

#include "TaskHelperManager.h"
#include "../Task.h"

//TODO remove functions register when automatic registering is done
#include "ConfigureConfigureTaskHelper.h"
#include "MakeBuildTaskHelper.h"
#include "MakeInstallTaskHelper.h"
#include "TarExtractTaskHelper.h"

using std::multimap;
using std::pair;
using std::string;
using std::vector;

using lusi::task::Task;

using namespace lusi::task::helper;

//public:

TaskHelperManager::~TaskHelperManager() {
}

TaskHelperManager* TaskHelperManager::getInstance() {
    if (sInstance == 0) {
        sInstance = new TaskHelperManager();
    }

    return sInstance;
}

vector<TaskHelper*> TaskHelperManager::getTaskHelpers(Task* task) const {
    vector<TaskHelper*> taskHelpers;

    typedef multimap<string, TaskHelper* (*)(Task*)>::const_iterator iterator;
    for (pair<iterator, iterator> range =
                    mTaskHelperFactories.equal_range(task->getId());
            range.first != range.second; ++range.first) {
       taskHelpers.push_back(range.first->second(task));
    }

    return taskHelpers;
}

void TaskHelperManager::registerTaskHelper(
                                TaskHelper* (*taskHelperFactory)(Task*),
                                const string& taskId) {
    mTaskHelperFactories.insert(make_pair(taskId, taskHelperFactory));
}

//private:

TaskHelperManager* TaskHelperManager::sInstance = 0;

//TODO remove functions register when automatic registering is done
TaskHelperManager::TaskHelperManager(): mTaskHelperFactories() {
    registerTaskHelper(createConfigureConfigureTaskHelper, "ConfigureTask");
    registerTaskHelper(createMakeBuildTaskHelper, "BuildTask");
    registerTaskHelper(createMakeInstallTaskHelper, "InstallTask");
    registerTaskHelper(createTarExtractTaskHelper, "ExtractTask");
    registerTaskHelper(createUndoMakeInstallTaskHelper, "UndoInstallTask");
}
