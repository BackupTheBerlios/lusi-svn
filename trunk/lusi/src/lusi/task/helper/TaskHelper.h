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
namespace helper {

/**
 * @class TaskHelper TaskHelper.h lusi/task/helper/TaskHelper.h
 *
 * Real implementation for a Task.
 * TaskHelper contains the real behaviour that executes or reverts a Task. Each
 * TaskHelper is an implementation of a Task, and a Task can have various
 * TaskHelpers.
 *
 * A TaskHelper can be used with a Task only if the ResourceMap of the Package
 * of the Task is valid for the TaskHelper. That is, for the same Task,
 * different TaskHelpers could be executed depending on the Package being used.
 *
 * As each TaskHelper does different things, each TaskHelper needs different
 * configuration parameters. Those are specified with the method
 * checkConfiguration, which returns the configuration parameters the TaskHelper
 * accepts but weren't already set in the TaskConfiguration of the Task.
 *
 * TaskHelpers can be registered with a specific Task using
 * registerWithTask(string). This will likely change when dynamic modules are
 * used.
 *
 * @see lusi::task::Task
 */
class TaskHelper {
public:

    /**
     * Creates a new TaskHelper.
     */
    TaskHelper();

    /**
     * Destroys this TaskHelper.
     */
    virtual ~TaskHelper();

    /**
     * Returns True if this TaskHelper can be executed or reverted using the
     * specified ResourceMap.
     * Must be implemented in derived classes.
     *
     * @param resourceMap The ResourceMap to check.
     * @return bool True if the ResourceMap is valid, false otherwise.
     */
    virtual bool isValidResourceMap(
                        lusi::package::ResourceMap* resourceMap) = 0;

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

protected:

    /**
     * Registers a TaskHelper with the Task with the specified taskName.
     * When a TaskHelper is registered with a Task, the TaskHelper can be used
     * by the Task when getting an implementation to be executed or reverted.
     *
     * @param taskName The task to register this TaskHelper with.
     * @todo Design a better approach to register TaskHelpers with Tasks.
     */
    void registerWithTask(const std::string& taskName);

private:

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
