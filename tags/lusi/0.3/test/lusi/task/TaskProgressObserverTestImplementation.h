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

#ifndef LUSI_TASK_TASKPROGRESSOBSERVERTESTIMPLEMENTATION_H
#define LUSI_TASK_TASKPROGRESSOBSERVERTESTIMPLEMENTATION_H

#include <lusi/task/TaskProgressObserver.h>

namespace lusi {
namespace task {

/**
 * Implementation of TaskProgressObserver interface for testing purposes.
 * This class helps testing TaskProgress, as it depends on observers.
 */
class TaskProgressObserverTestImplementation: public TaskProgressObserver {
public:

    /**
     * Creates a new TaskProgressObserverTestImplementation.
     */
    TaskProgressObserverTestImplementation();

    /**
     * Destroys this TaskProgressObserverTestImplementation.
     */
    virtual ~TaskProgressObserverTestImplementation();

    /**
     * Called when some progress is made.
     * The task is copied to mTask and the value is copied to mProgress.
     *
     * @param task A pointer to the Task that made the progress.
     * @param value The percenteage of execution.
     */
    virtual void progress(Task* task, int value);

    /**
     * Returns the last task that sent a progress value.
     * mTask is cleaned, so, if no new progress is notified, it'll return a null
     * pointer.
     *
     * @return The last task that sent a progress value.
     */
    Task* getTask() {
        Task* task = mTask;
        mTask = 0;
        return task;
    }

    /**
     * Returns the last progress value received.
     *
     * @return The last progress value received.
     */
    int getProgress() const {
        return mProgress;
    }

private:

    /**
     * The last task that sent a value.
     */
    Task* mTask;

    /**
     * The last value received.
     */
    int mProgress;

};

}
}

#endif
