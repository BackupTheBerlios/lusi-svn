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

#ifndef LUSI_TASK_HELPER_TASKHELPER_H
#define LUSI_TASK_HELPER_TASKHELPER_H

#include <string>

#include <lusi/task/Task.h>
#include <lusi/task/TaskLogger.h>
#include <lusi/task/TaskProgress.h>

namespace lusi {
namespace configuration {
class ConfigurationParametersSet;
}
}

namespace lusi {
namespace package {
class ResourceMap;
}
}

namespace lusi {
namespace task {
class Task;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * @class TaskHelper TaskHelper.h lusi/task/helper/TaskHelper.h
 *
 * Real implementation for a Task.
 * TaskHelper contains the real behaviour that executes or reverts a Task. Each
 * TaskHelper is an implementation of a Task, and a Task can have various
 * TaskHelpers.
 *
 * A Task can use a TaskHelper only if the ResourceMap of the Package of the
 * Task is valid for the TaskHelper. It can be checked with
 * hasValidResourceMap().
 * This way, for the same Task, different TaskHelpers could be executed
 * depending on the Package being used.
 *
 * As each TaskHelper does different things, each TaskHelper needs different
 * configuration parameters. Those are specified with the method
 * checkConfiguration, which returns the configuration parameters the TaskHelper
 * accepts but weren't already set in the TaskConfiguration of the Task.
 *
 * TaskHelpers must be registered with the Tasks they can help. This can be done
 * using TaskHelperManager. Further information can be seen in the documentation
 * of that class.
 *
 * TaskHelpers of the same class share the same name. Therefore, the name
 * identifies classes, not individual objects. The name is equal to the name
 * of the class.
 *
 * The TaskHelpers must log what they're doing. To do this, subclasses can use
 * the protected methods notifyTaskLogger(std::string, LoggedEventType) and
 * notifyTaskProgress(int), which notifies all the observers of TaskLogger and
 * TaskProgress of the Task.
 *
 * @see lusi::task::Task
 * @see TaskHelperManager
 */
class TaskHelper {
public:

    /**
     * Destroys this TaskHelper.
     */
    virtual ~TaskHelper();

    /**
     * Returns True if this TaskHelper can be executed using the ResourceMap of
     * the Package of the Task.
     * The ResourceMap isn't checked when reverting, as the Task takes care of
     * reverting only previously executed TaskHelpers.
     * Must be implemented in derived classes.
     *
     * @return bool True if the ResourceMap is valid, false otherwise.
     */
    virtual bool hasValidResourceMap() = 0;

    /**
     * Returns the Configuration needed by this TaskHelper.
     * The Configuration contains all the configurable values accepted by the
     * TaskHelper which weren't already set in the TaskConfiguration of the
     * Task.
     * Must be implemented in derived classes.
     *
     * @return Returns the Configuration needed by this TaskHelper.
     * @todo Move checkConfiguration to Task and create getNeededConfiguration
     *       in this class?
     */
    virtual lusi::configuration::ConfigurationParametersSet
                                            checkConfiguration() = 0;

    /**
     * Executes this TaskHelper.
     * Must be implemented in derived classes.
     *
     * @see revert()
     */
    virtual void execute() = 0;

    /**
     * Reverts the changes made executing this TaskHelper.
     * Must be implemented in derived classes.
     *
     * @see execute()
     */
    virtual void revert() = 0;

    /**
     * Returns the name of the TaskHelper.
     *
     * @return The name of the TaskHelper.
     */
    const std::string& getName() {
        return mName;
    }

protected:

    /**
     * Task to help.
     */
    lusi::task::Task* mTask;



    /**
     * Creates a new TaskHelper.
     * The name of the TaskHelper identifies classes of TaskHelpers, not
     * individual objects.
     *
     * @param name The name of the TaskHelper.
     * @param task The task to help.
     */
    TaskHelper(const std::string& name, lusi::task::Task* task);

    /**
     * Notifies the TaskLogger of the Task with a new event.
     *
     * @param message The message of the event.
     * @param type The type of the event.
     */
    void notifyTaskLogger(const std::string& message, LoggedEventType type) {
        mTask->getTaskLogger()->notifyEvent(message, type);
    }

    /**
     * Notifies the TaskProgress of the Task that progress happened.
     *
     * @param value The progress of the TaskHelper.
     */
    void notifyTaskProgress(int value) {
        mTask->getTaskProgress()->notifyProgress(value);
    }

private:

    /**
     * The name of the TaskHelper.
     */
    std::string mName;



    /**
     * Copy constructor disabled.
     */
    TaskHelper(const TaskHelper& taskHelper);

    /**
     * Assignment disabled.
     */
    TaskHelper& operator=(const TaskHelper& taskHelper);

};

}
}
}

#endif
