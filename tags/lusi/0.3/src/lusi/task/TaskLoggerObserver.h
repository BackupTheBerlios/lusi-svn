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

#ifndef LUSI_TASK_TASKLOGGEROBSERVER_H
#define LUSI_TASK_TASKLOGGEROBSERVER_H

#include <string>

#include <lusi/task/LoggedEventType.h>

namespace lusi {
namespace task {
class Task;
}
}

namespace lusi {
namespace task {

/**
 * @class TaskLoggerObserver TaskLoggerObserver.h lusi/util/TaskLoggerObserver.h
 *
 * Interface to observe updates in the execution of a Task.
 * The updates observed are messages sent by the Task telling what it's doing.
 * Messages can be, for example, the output of an executed Process, or
 * information about "decisions" took by the Task about executed helpers.
 * The messages are from one of the types specified in LoggedEventType.
 *
 * @see TaskLogger
 */
class TaskLoggerObserver {
public:

    /**
     * Destroys this TaskLoggerObserver.
     */
    virtual ~TaskLoggerObserver() {
    }

    /**
     * Called when a new message is sent.
     *
     * @param task A pointer to the Task that sent the message.
     * @param message The message sent.
     * @param type The type of the message.
     */
    virtual void event(Task* task, const std::string& message,
                       LoggedEventType type) = 0;

protected:

    /**
     * Creates a new TaskLoggerObserver.
     * Protected to avoid classes other than derived to create
     * TaskLoggerObserver objects.
     */
    TaskLoggerObserver() {
    }

private:

    /**
     * Copy constructor disabled.
     */
    TaskLoggerObserver(const TaskLoggerObserver& taskLoggerObserver);

    /**
     * Assignment disabled.
     */
    TaskLoggerObserver& operator=(const TaskLoggerObserver& taskLoggerObserver);

};

}
}

#endif
