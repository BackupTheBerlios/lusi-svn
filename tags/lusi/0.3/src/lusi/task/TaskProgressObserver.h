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

#ifndef LUSI_TASK_TASKPROGRESSOBSERVER_H
#define LUSI_TASK_TASKPROGRESSOBSERVER_H

namespace lusi {
namespace task {
class Task;
}
}

namespace lusi {
namespace task {

/**
 * @class TaskProgressObserver TaskProgressObserver.h \
 * lusi/util/TaskProgressObserver.h
 *
 * Interface to observe progress in the execution of a Task.
 * Updates values are integers in the range from TaskProgress::UNSTARTED (0) to
 * TaskProgress::FINISHED (100). They represent the percenteage of execution of
 * the Task.
 *
 * @see TaskProgress
 */
class TaskProgressObserver {
public:

    /**
     * Destroys this TaskProgressObserver.
     */
    virtual ~TaskProgressObserver() {
    }

    /**
     * Called when some progress is made.
     * The value is an integer in the range from 0 to 100, representing the
     * percenteage of execution of the Task.
     *
     * @param task A pointer to the Task that made the progress.
     * @param value The percenteage of execution.
     */
    virtual void progress(Task* task, int value) = 0;

protected:

    /**
     * Creates a new TaskProgressObserver.
     * Protected to avoid classes other than derived to create
     * TaskProgressObserver objects.
     */
    TaskProgressObserver() {
    }

private:

    /**
     * Copy constructor disabled.
     */
    TaskProgressObserver(const TaskProgressObserver& taskProgressObserver);

    /**
     * Assignment disabled.
     */
    TaskProgressObserver& operator=(const TaskProgressObserver&
                                taskProgressObserver);

};

}
}

#endif
