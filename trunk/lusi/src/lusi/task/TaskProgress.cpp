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

#include "TaskProgress.h"
#include "TaskProgressObserver.h"

using std::string;
using std::vector;

using namespace lusi::task;

//public:

TaskProgress::TaskProgress(Task* task) {
    mTask = task;
    mTaskProgressObservers = vector<TaskProgressObserver*>();
    mExtendedProgress = false;
}

TaskProgress::~TaskProgress() {
}

/*
inline bool TaskProgress::isExtendedProgress() {
    return mExtendedProgress;
}

inline void TaskProgress::setExtendedProgress(bool extendedProgress) {
    mExtendedProgress = extendedProgress;
}
*/

void TaskProgress::attachObserver(TaskProgressObserver* observer) {
    if (find(mTaskProgressObservers.begin(), mTaskProgressObservers.end(),
                    observer) != mTaskProgressObservers.end()) {
        return;
    }

    mTaskProgressObservers.push_back(observer);
}

void TaskProgress::detachObserver(TaskProgressObserver* observer) {
    vector<TaskProgressObserver*>::iterator iterator =
                    find(mTaskProgressObservers.begin(),
                         mTaskProgressObservers.end(),
                         observer);

    if (iterator != mTaskProgressObservers.end()) {
        mTaskProgressObservers.erase(iterator);
    }
}

//private:

void TaskProgress::notifyProgress(int value) {
    vector<TaskProgressObserver*>::iterator it;
    for (it = mTaskProgressObservers.begin();
                it != mTaskProgressObservers.end(); ++it) {
        (*it)->progress(mTask, value);
    }
}
