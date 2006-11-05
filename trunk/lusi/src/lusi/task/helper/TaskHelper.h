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

#include <lusi/configuration/ConfigurationParameterMap.h>
#include <lusi/configuration/InvalidConfigurationException.h>
#include <lusi/task/Task.h>
#include <lusi/task/TaskLogger.h>
#include <lusi/task/TaskProgress.h>
#include <lusi/task/helper/ExecuteTaskHelperException.h>

namespace lusi {
namespace package {
class ResourceMap;
}
}

namespace lusi {
namespace util {
template<typename T>
class SmartPtr;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * @class TaskHelper TaskHelper.h lusi/task/helper/TaskHelper.h
 *
 * Real implementation for a Task.
 * TaskHelper contains the real behaviour that executes a Task. Each TaskHelper
 * is an implementation of a Task, and a Task can have various TaskHelpers.
 *
 * A Task can use a TaskHelper only if the ResourceMap of the Package of the
 * Task is valid for the TaskHelper. It can be checked with
 * hasValidResourceMap().
 * This way, for the same Task, different TaskHelpers could be executed
 * depending on the Package being used.
 *
 * As each TaskHelper does different things, each TaskHelper needs different
 * configuration parameters. The configuration is stored in a
 * ConfigurationParameterMap, with id "[mName]Configuration". Name and
 * information are empty and priority is set to recommended. Those parameters
 * aren't used, as it is a special case for the ConfigurationParameterMap.
 * The configuration of the TaskHelper is initialized through
 * initConfigurationParameterMap(). This method must be called in the Task
 * before using the TaskHelper.
 * The configuration can be checked using getInvalidConfiguration(). This method
 * returns a ConfigurationParameterMap with all the invalid parameters in the
 * configuration. A TaskHelper can't be executed if there are invalid
 * parameters. An InvalidConfigurationException is thrown in those cases.
 *
 * TaskHelpers must be registered with the Tasks they can help. This can be done
 * using TaskHelperManager. Further information can be seen in the documentation
 * of that class.
 *
 * TaskHelpers of the same class share the same name. Therefore, the name
 * identifies classes, not individual objects. The name is equal to the name
 * of the class.
 *
 * The TaskHelpers must log what they are doing. To do this, subclasses can use
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
     * Must be implemented in derived classes.
     *
     * @return bool True if the ResourceMap is valid, false otherwise.
     */
    virtual bool hasValidResourceMap() = 0;

    /**
     * Executes this TaskHelper.
     * This method must be called only on TaskHelpers with a valid resource map.
     * If the resource map is invalid, the behaviour of this method is
     * undefined.
     *
     * Configuration has been already initialized when this method is called.
     *
     * Default implementation checks if there are any invalid parameters and, in
     * that case, throws an InvalidConfigurationException containing all the
     * invalid parameters.
     *
     * If a problem (different than executing the TaskHelper with an invalid
     * configuration) happens, an ExecuteTaskHelperException is thrown. The
     * message explains the problem happened.
     *
     * Derived classes must extend this method with a full implementation.
     *
     * @throws ExecuteTaskHelperException If a problem happened when executing
     *                                    this TaskHelper.
     * @throws InvalidConfigurationException If the parameters are incomplete or
     *                                       invalid.
     */
    virtual void execute() throw (ExecuteTaskHelperException,
                            lusi::configuration::InvalidConfigurationException);

    /**
     * Inits the configuration parameters for this TaskHelper.
     * When a TaskHelper is selected to be used with a task, this method is
     * called.
     *
     * Default implementation is empty (no parameters needed).
     *
     * This method can be overriden in derived classes if default implementation
     * doesn't suit their needs.
     */
    virtual void initConfigurationParameterMap();

    /**
     * Returns the invalid configuration parameters of this TaskHelper.
     * If all the parameters are valid, the returned map will be empty.
     * A parameter is invalid if it is incomplete (a mandatory parameter not
     * set) or if its value isn't suitable for the TaskHelper.
     *
     * Default implementation returns a ConfigurationParameterMap with all the
     * incomplete parameters. The id of the map is
     * "[mName]InvalidConfiguration", name and information are empty, and
     * priority is set to required.
     *
     * This method can be overriden in derived classes if default implementation
     * doesn't suit their needs.
     *
     * @return Returns the invalid configuration parameters of this TaskHelper.
     */
    virtual lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    getInvalidConfiguration();

    /**
     * Returns the name of the TaskHelper.
     *
     * @return The name of the TaskHelper.
     */
    const std::string& getName() const {
        return mName;
    }

    /**
     * Returns the configuration parameters for this TaskHelper.
     *
     * @return The configuration parameters for this TaskHelper.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    getConfigurationParameterMap() {
        return mConfigurationParameterMap;
    }

protected:

    /**
     * Task to help.
     */
    lusi::task::Task* mTask;

    /**
     * The configuration parameters for this TaskHelper.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    mConfigurationParameterMap;




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
