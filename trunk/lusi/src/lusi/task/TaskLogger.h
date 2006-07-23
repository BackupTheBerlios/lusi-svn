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

#ifndef LUSI_TASK_TASKLOGGER_H
#define LUSI_TASK_TASKLOGGER_H

#include <string>
#include <vector>

#include <lusi/task/LoggedEventType.h>

namespace lusi {
namespace task {
class Task;
class TaskLoggerObserver;
}
}

namespace lusi {
namespace task {
namespace helper {
class TaskHelper;
}
}
}

namespace lusi {
namespace task {

/**
 * @class TaskLogger TaskLogger.h lusi/util/TaskLogger.h
 *
 * A TaskLogger which notifies events in the execution of a Task.
 * This class notifies all the observers when some event happens in the
 * associated Task. It's responsability of the Task to call the notifyEvent
 * method, as this class only handles the notifications and the observers. The
 * Task itself must "warn" this class about events happened.
 *
 * Observers can be registered using attachObserver(TaskLoggerObserver*) and
 * deregistered with detachObserver(TaskLoggerObserver*).
 *
 * @see TaskLoggerObserver
 */
class TaskLogger {
friend class lusi::task::helper::TaskHelper;
public:

    /**
     * Creates a new TaskLogger.
     */
    TaskLogger(Task* task);

    /**
     * Destroys this TaskLogger.
     */
    virtual ~TaskLogger();

    /**
     * Adds a new observer to be notified when some event in the execution of
     * the Task happens.
     * If the observer was already added, it's not added again.
     *
     * @param observer The TaskLoggerObserver to add.
     */
    void attachObserver(TaskLoggerObserver* observer);

    /**
     * Removes an observer, so it will no longer be notified when events in
     * the execution of the Task happen.
     *
     * @param observer The TaskLoggerObserver to remove.
     */
    void detachObserver(TaskLoggerObserver* observer);

protected:

private:

    /**
     * The Task which notifies the events.
     */
    Task* mTask;

    /**
     * A vector containing all the TaskLoggerObservers registered.
     */
    std::vector<TaskLoggerObserver*> mTaskLoggerObservers;



    /**
     * Notifies all the observers about the event.
     * The event is the information message and the type of it (message,
     * warning or error).
     *
     * @param message The message of the event.
     * @param type The type of the event.
     */
    void notifyEvent(const std::string& message, LoggedEventType type);

};

}
}

#endif
