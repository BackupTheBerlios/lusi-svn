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

#ifndef LUSI_TASK_TASKLOGGEROBSERVERTESTIMPLEMENTATION_H
#define LUSI_TASK_TASKLOGGEROBSERVERTESTIMPLEMENTATION_H

#include <lusi/task/TaskLoggerObserver.h>

namespace lusi {
namespace task {

/**
 * Implementation of TaskLoggerObserver interface for testing purposes.
 * This class helps testing TaskLogger, as it depends on observers.
 */
class TaskLoggerObserverTestImplementation: public TaskLoggerObserver {
public:

    /**
     * Creates a new TaskLoggerObserverTestImplementation.
     */
    TaskLoggerObserverTestImplementation();

    /**
     * Destroys this TaskLoggerObserverTestImplementation.
     */
    virtual ~TaskLoggerObserverTestImplementation();

    /**
     * Called when a new message is sent.
     * The task is copied to mTask, the message is copied to mMessage and the
     * event type is copied to mEventType.
     *
     * @param task A pointer to the Task that sent the message.
     * @param message The message sent.
     * @param type The type of the message.
     */
    virtual void event(Task* task, const std::string& message,
                       LoggedEventType type);

    /**
     * Returns the last task that sent a message.
     * mTask is cleaned, so, if no new message is notified, it'll return a null
     * pointer.
     *
     * @return The last task that sent a message.
     */
    Task* getTask() {
        Task* task = mTask;
        mTask = 0;
        return task;
    }

    /**
     * Returns the last message received.
     *
     * @return The last message received.
     */
    const std::string& getMessage() const {
        return mMessage;
    }

    /**
     * Returns the type of the last event received.
     *
     * @return The type of the last event received.
     */
    const LoggedEventType& getEventType() const {
        return mEventType;
    }

private:

    /**
     * The last task that sent a value.
     */
    Task* mTask;

    /**
     * The last message received.
     */
    std::string mMessage;

    /**
     * The last type of the last event received.
     */
    LoggedEventType mEventType;

};

}
}

#endif
