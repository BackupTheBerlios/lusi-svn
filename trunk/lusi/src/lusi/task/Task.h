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

#ifndef LUSI_TASK_TASK_H
#define LUSI_TASK_TASK_H

#include <string>
#include <vector>

#include <lusi/configuration/InvalidConfigurationException.h>
#include <lusi/task/ExecuteTaskException.h>

namespace lusi {
namespace package {
class Package;
}
}

namespace lusi {
namespace package {
namespace status {
class PackageStatus;
}
}
}

namespace lusi {
namespace task {
class TaskConfiguration;
class TaskLogger;
class TaskProgress;
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
 * @class Task Task.h lusi/task/Task.h
 *
 * A task to be executed in the process of installing or uninstalling a package.
 * Tasks are actions which have a concrete mission in the process of installing
 * or uninstalling a package. Each task is used in combination with other tasks
 * to fulfill those process. Extract the package, configure it, build it... are
 * all examples of tasks.
 *
 * Tasks are generic elements. They describe what can be done (extract,
 * build...), but not how it can be done (extract using tar or zip, build with
 * make or jam...). When a task is executed, it uses a helper class which
 * defines how things can be done. The task looks for the right implementation
 * for the package used and executes it.
 *
 * The task executes each TaskHelper set by nextTaskHelper() method until
 * the Task is done or there are no more TaskHelpers availables. If a
 * TaskHelper is executed successfully, the type of the TaskHelper is saved in
 * the configuration, so it will be tried the first if the Task is executed
 * again with the same Package. TaskHelpers that can be undone have a
 * counterpart TaskHelper that, when executed, reverts the original TaskHelper.
 *
 * TaskHelpers are registered with a task name using TaskHelperManager. A Task
 * can, therefore, know which TaskHelpers it can use.
 * Task and TaskHelper are similar to Bridge Design Pattern, although not
 * follow exactly that design pattern. In fact, they're more like a Task
 * composed (not in the sense of Composite Design Pattern) with TaskHelpers
 * (which follow Strategy Design Pattern).
 *
 * The task is executed using execute() method, and the changes made by that
 * method may be revertable using the UndoTask for this Task, if any. Reverting
 * a task doesn't need to be done just after it was done, other tasks can be
 * done an undone before reverting this task. In fact, it can even be undone
 * long time since when it was done (think, for example, on uninstalling an
 * installed package).
 *
 * Prior to execute a task, it can be tested if the Package and
 * TaskConfiguration to use are valid with this Task using test() method.
 * Moreover, the configuration to be used by the current TaskHelper (which is
 * different than the one for the Task) can be got with
 * getTaskHelperConfiguration(). Also, the invalid values in that configuration
 * can be checked using getInvalidConfiguration(). If the Task is executed with
 * an invalid task helper configuration, an exception is thrown.
 *
 * The Task can also notify the operations executed and the progress when
 * executing the task. There are Loggers for both events, which can be got
 * with getTaskLogger() and getTaskProgress() methods.
 *
 * Tasks are identified by their name, so it must be unique. Two different tasks
 * can't both need and provide the same PackageStatus. Tasks should be
 * registered with TaskManager using the name and the needed and provided
 * PackageStatus.
 *
 * Task shouldn't be created directly. Instead, use
 * TaskManager::getTask(lusi::package::Package*).
 *
 * @see helper::TaskHelper
 * @see TaskLogger
 * @see TaskManager
 * @see TaskProgress
 */
class Task {
public:

    /**
     * Creates a new Task.
     * It sets the first TaskHelper to be executed, if any.
     *
     * @param name The name of the Task.
     * @param package The Package to use.
     * @param taskConfiguration The TaskConfiguration to use.
     * @param neededPackageStatus The PackageStatus needed to execute this Task.
     * @param providedPackageStatus The PackageStatus this Task provides once
     *                              it was executed.
     */
    Task(const std::string& name, lusi::package::Package* package,
         TaskConfiguration* taskConfiguration,
         const lusi::package::status::PackageStatus* neededPackageStatus,
         const lusi::package::status::PackageStatus* providedPackageStatus);

    /**
     * Destroys this Task.
     * The Package and TaskConfiguration used aren't deleted when destroying
     * the Task.
     */
    virtual ~Task();

    /**
     * Returns the name of this Task.
     * The name is read only, and this is an accessor method.
     *
     * @return The name of this Task.
     */
    const std::string& getName() const {
        return mName;
    }

    /**
     * Returns the Package used by this Task.
     *
     * @return The Package of this Task.
     */
    lusi::package::Package* getPackage() const {
        return mPackage;
    }

    /**
     * Returns the TaskConfiguration used by this Task.
     *
     * @return The TaskConfiguration used by this Task.
     */
    TaskConfiguration* getTaskConfiguration() const {
        return mTaskConfiguration;
    }

    /**
     * Returns the PackageStatus needed to execute this Task.
     * The status is read only, and this is an accessor method.
     *
     * @return The PackageStatus needed.
     */
    const lusi::package::status::PackageStatus* getNeededPackageStatus() const {
        return mNeededPackageStatus;
    }

    /**
     * Returns the PackageStatus this Task provides once it was executed.
     * The status is read only, and this is an accessor method.
     *
     * @return The PackageStatus provided.
     */
    const lusi::package::status::PackageStatus* getProvidedPackageStatus()
                                                            const {
        return mProvidedPackageStatus;
    }

    /**
     * Returns the TaskLogger which notifies all the operations made when
     * executing the Task.
     *
     * @return The TaskLogger for the operations made executing the Task.
     */
    TaskLogger* getTaskLogger() const {
        return mTaskLogger;
    }

    /**
     * Returns the TaskProgress which notifies all the changes in the progress
     * made executing this Task.
     *
     * @return The TaskProgress which notifies the progress made executing this
     *         Task.
     */
    TaskProgress* getTaskProgress() const {
        return mTaskProgress;
    }

    /**
     * Returns the configuration parameterss needed by the current TaskHelper.
     * The parameters contain all the values that can and, in some cases, need,
     * to be customized when executing a TaskHelper (the real implementations of
     * Tasks).
     *
     * Note that the returned parameters may also exist in this Task
     * configuration. However, when checking the configuration before executing
     * the Task, you must always use this method instead. This configuration
     * is added automatically to the configuration of the Task when it is
     * executed successfully.
     *
     * This method should be called only with Tasks that can be executed (which
     * can be known using test()).
     *
     * @return The configuration parameterss needed by the current TaskHelper.
     */
    lusi::configuration::ConfigurationParameterMap getTaskHelperConfiguration()
                                                                        const;

    /**
     * Returns the invalid configuration parameters of the current TaskHelper.
     * The invalid parameters must be fixed before the Task can be executed. If
     * executed with invalid parameters, an exception is thrown.
     *
     * Although the ConfigurationParameterMap object changes every time, the
     * parameters it contains will always be a subset of those returned by
     * getTaskHelperConfiguration(). The parameters are shared by both maps.
     *
     * This method should be called only with Tasks that can be executed (which
     * can be known using test()).
     *
     * @return The invalid configuration parameters of this TaskHelper.
     */
    lusi::configuration::ConfigurationParameterMap getInvalidConfiguration()
                                                                        const;

    /**
     * Checks if the Task can be executed using the Package and
     * TaskConfiguration specified.
     *
     * @return True if it can be executed, false otherwise.
     */
    bool test() const;

    /**
     * Executes this Task.
     * The current TaskHelper, which is the real implementation of the Task, is
     * executed. Once finished, the package status is updated and the
     * configuration of the TaskHelper merged with the Task configuration to
     * save the parameters used.
     *
     * This method can only be called when all the parameters are valid. If
     * there are any invalid parameters, an exception is thrown.
     *
     * Also, if it is called when there are no more available TaskHelpers, an
     * exception is thrown. The same exception is thrown if the execution of the
     * TaskHelper used failed.
     *
     * @throw ExecuteTaskException If a problem happened when executing this
     *                             Task.
     * @throws InvalidConfigurationException If the parameters are incomplete or
     *                                       invalid.
     * @todo Add support to execute several TaskHelpers
     */
    void execute() throw (ExecuteTaskException,
                          lusi::configuration::InvalidConfigurationException);

protected:

private:

    /**
     * The name of this Task.
     */
    std::string mName;

    /**
     * The package to use in this Task.
     */
    lusi::package::Package* mPackage;

    /**
     * The task configuration to use in this Task.
     */
    TaskConfiguration* mTaskConfiguration;

    /**
     * The PackageStatus needed to execute this Task.
     */
    const lusi::package::status::PackageStatus* mNeededPackageStatus;

    /**
     * The PackageStatus this Task provides once it was executed.
     */
    const lusi::package::status::PackageStatus* mProvidedPackageStatus;

    /**
     * The TaskHelpers for this Task.
     */
    std::vector<lusi::task::helper::TaskHelper*> mTaskHelpers;

    /**
     * The current iterator in mTaskHelpers which contains the next TaskHelper
     * to be used.
     */
    std::vector<lusi::task::helper::TaskHelper*>::const_iterator
    mTaskHelpersIterator;

    /**
     * The current task helper, null if there is none available.
     */
    lusi::task::helper::TaskHelper* mCurrentTaskHelper;

    /**
     * The TaskLogger which notifies all the operations made when executing the
     * Task.
     */
    TaskLogger* mTaskLogger;

    /**
     * The TaskProgress which notifies all the changes in the progress made
     * executing this Task.
     */
    TaskProgress* mTaskProgress;



    /**
     * Sets the next TaskHelper to use in mCurrentTaskHelper.
     * If there are no more available TaskHelpers suitable to be executed with
     * the Package, a null pointer is set.
     *
     * The TaskHelper set is the next suitable TaskHelper to be executed from
     * the vector of TaskHelpers. A TaskHelper is suitable if the ResourceMap
     * is valid for that TaskHelper.
     * Once the TaskHelper is set, its configuration is initialized and the
     * TaskConfiguration merged with it.
     */
    void nextTaskHelper();

    /**
     * Copy constructor disabled.
     */
    Task(const Task& task);

    /**
     * Assignment disabled.
     */
    Task& operator=(const Task& task);

};

}
}

#endif
