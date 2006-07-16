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
#include "TaskLogger.h"
#include "TaskProgress.h"
#include "helper/TaskHelper.h"
#include "helper/TaskHelperManager.h"

using std::string;
using std::vector;

using lusi::task::helper::TaskHelper;
using lusi::task::helper::TaskHelperManager;
using lusi::package::Package;

using namespace lusi::task;

//public:

Task::~Task() {
    for (vector<TaskHelper*>::const_iterator iterator = mTaskHelpers.begin();
            iterator != mTaskHelpers.end(); ++iterator) {
        delete *iterator;
    }
}

const string& Task::getName() const {
    return mName;
}

Package* Task::getPackage() {
}

TaskConfiguration* Task::getTaskConfiguration() {
}

TaskLogger Task::getTaskLogger() {
}

TaskProgress Task::getProgress() {
}

bool Task::test() {
}

void Task::redo() {
}

void Task::undo() {
}

//protected:

Task::Task(const string& name, Package* package,
            TaskConfiguration* taskConfiguration) {
    mName = name;

    //mName must be set before calling getTaskHelpers, as it uses getName()
    mTaskHelpers = TaskHelperManager::getInstance()->getTaskHelpers(this);
}

//private:

TaskHelper* Task::getRedoHelper() {
}

TaskHelper* Task::getUndoHelper() {
}
