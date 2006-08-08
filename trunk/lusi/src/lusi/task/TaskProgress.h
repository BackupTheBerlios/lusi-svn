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

#ifndef LUSI_TASK_TASKPROGRESS_H
#define LUSI_TASK_TASKPROGRESS_H

#include <string>
#include <vector>

namespace lusi {
namespace task {
class Task;
class TaskProgressObserver;
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
 * @class TaskProgress TaskProgress.h lusi/util/TaskProgress.h
 *
 * A TaskProgress which notifies the progress in the execution of a Task.
 * This class notifies all the observers when some progress happens in the
 * associated Task. It's responsability of the Task to call the notifyProgress
 * method, as this class only handles the notifications and the observers. The
 * Task itself must "warn" this class about progress made.
 *
 * Observers can be registered using attachObserver(TaskProgressObserver*) and
 * deregistered with detachObserver(TaskProgressObserver*).
 *
 * TaskProgress can be marked as basic or extended, depending on the values they
 * notify: only UNSTARTED and FINISHED, or all the range between them. By
 * default, they are basic.
 * This value is only a hint, and TaskProgress marked as basic can do extended
 * notifications, and viceversa. However, Task and TaskHelpers are encouraged
 * to respect it ;)
 *
 * @see TaskProgressObserver
 */
class TaskProgress {
friend class lusi::task::helper::TaskHelper;
public:

    /**
     * This value represents the progress of a Task which hasn't been started
     * yet.
     */
    static const int UNSTARTED = 0;

    /**
     * This value represents the progress of a Task which has been finished.
     */
    static const int FINISHED = 100;

    /**
     * Creates a new TaskProgress.
     * ExtendedProgress is false.
     *
     * @param task The Task which mades the progress.
     */
    TaskProgress(Task* task);

    /**
     * Destroys this TaskProgress.
     */
    virtual ~TaskProgress();

    /**
     * Returns true if the Progress notifications are extended, false if they
     * are basic.
     *
     * @return True if the Progress notifications are extended, false if they
     *         are basic.
     * @see mExtendedProgress
     */
    bool isExtendedProgress() {
        return mExtendedProgress;
    }

    /**
     * Sets if the Progress notifications are basic or extended.
     *
     * @param extendedProgress True if the notifications are extended, false if
     *                         they are basic.
     * @see mExtendedProgress
     */
    void setExtendedProgress(bool extendedProgress) {
        mExtendedProgress = extendedProgress;
    }

    /**
     * Adds a new observer to be notified when some progress in the execution of
     * the Task is made.
     * If the observer was already added, it's not added again.
     *
     * @param observer The TaskProgressObserver to add.
     */
    void attachObserver(TaskProgressObserver* observer);

    /**
     * Removes an observer, so it will no longer be notified when progress in
     * the execution of the Task is made.
     *
     * @param observer The TaskProgressObserver to remove.
     */
    void detachObserver(TaskProgressObserver* observer);

protected:

private:

    /**
     * The Task which makes the progress to be notified.
     */
    Task* mTask;

    /**
     * A vector containing all the TaskProgressObservers registered.
     */
    std::vector<TaskProgressObserver*> mTaskProgressObservers;

    /**
     * If the Progress notifications are extended or basic.
     * Basic notifications refers to simply notifying UNSTARTED progress and
     * FINISHED progress. Extended, on the other hand, can notify any value in
     * that range.
     *
     * This value is only a hint. A TaskProgress marked as basic can do extended
     * notifications, and a TaskProgress marked as extended can do only basic
     * notifications.
     */
    bool mExtendedProgress;



    /**
     * Notifies all the observers about the progress value.
     * It must be an integer in the range from 0 to 100.
     *
     * @param value The progress value.
     */
    void notifyProgress(int value);

};

}
}

#endif
