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
 * A task to be done or undone in the process of installing or uninstalling a
 * package.
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
 * The task executes each TaskHelper returned by getRedoHelper() method until
 * the Task is done or the TaskHelper returned is a null pointer. If a
 * TaskHelper is executed successfully, the type of the TaskHelper is saved in
 * the configuration, so it will be tried the first if the Task is executed
 * again with the same Package. This TaskHelper will be the one used to undo the
 * Task.
 * TaskHelpers are registered with a task name using TaskHelperManager. A Task
 * can, therefore, know which TaskHelpers it can use.
 * Task and TaskHelper are similar to Bridge Design Pattern, although not
 * follow exactly that design pattern. In fact, they're more like a Task
 * composed (not in the sense of Composite Design Pattern) with TaskHelpers
 * (which follow Strategy Design Pattern).
 *
 * The task is executed using redo() method, and the changes made by that
 * method can be reverted with undo(). Reverting a task doesn't need to be done
 * just after it was done, other tasks can be done an undone before reverting
 * this task. In fact, it can even be undone long time since when it was done
 * (think, for example, on uninstalling an installed package).
 *
 * Prior to do or undo a task, it can be tested if the Package and
 * TaskConfiguration to use are valid with this Task.
 *
 * The Task can also notify the operations executed and the progress when doing
 * or undoing the task. There are Loggers for both events, which can be got
 * with getTaskLogger() and getProgress() methods.
 *
 * Tasks are identified by their name, so it must be unique. Two different tasks
 * can't both need and provide the same PackageStatus. The methods that return
 * the needed and provided PackageStatus must be implemented in derived
 * classes.
 *
 * Task shouldn't be created directly. Instead, use
 * TaskManager::getTask(lusi::package::Package*) and
 * TaskManager::getUndoTask(lusi::package::Package*), depending on the desired
 * Task.
 *
 * @see helper::TaskHelper
 * @see TaskLogger
 * @see TaskManager
 * @see TaskProgress
 */
class Task {
public:

    /**
     * Destroys this Task.
     * The Package and TaskConfiguration used aren't deleted when destroying
     * the Task.
     */
    virtual ~Task();

    /**
     * Returns the PackageStatus needed to execute this Task.
     * The status is read only, and this is an accessor method.
     * Must be implemented in derived classes.
     *
     * @return The PackageStatus needed.
     */
    virtual const lusi::package::status::PackageStatus* needsPackageStatus()
                                                            const = 0;

    /**
     * Returns the PackageStatus this Task provides once it was executed.
     * The status is read only, and this is an accessor method.
     * Must be implemented in derived classes.
     *
     * @return The PackageStatus provided.
     */
    virtual const lusi::package::status::PackageStatus* providesPackageStatus()
                                                            const = 0;

    /**
     * Returns the name of this Task.
     * The name is read only, and this is an accessor method.
     *
     * @return The name of this Task.
     */
    const std::string& getName() const;

    /**
     * Returns the Package used by this Task.
     *
     * @return The Package of this Task.
     */
    lusi::package::Package* getPackage();

    /**
     * Returns the TaskConfiguration used by this Task.
     *
     * @return The TaskConfiguration used by this Task.
     */
    TaskConfiguration* getTaskConfiguration();

    /**
     * Returns the TaskLogger which notifies all the operations made when
     * executing the Task.
     *
     * @return The TaskLogger for the operations made executing the Task.
     */
    TaskLogger getTaskLogger();

    /**
     * Returns the TaskProgress which notifies all the changes in the progress
     * made executing this Task.
     *
     * @return The TaskProgress which notifies the progress made executing this
     *         Task.
     */
    TaskProgress getProgress();

    /**
     * Checks if the Task can be executed using the Package and
     * TaskConfiguration specified.
     *
     * @return True if it can be executed, false otherwise.
     */
    bool test();

    /**
     * Executes this Task.
     * Selects the right implementations of this Task from all the availables,
     * using getRedoHelper(), and executes them. Once the Task is completed,
     * this method finishes, even if there are more implementations that could
     * be executed.
     * All the operations done can be reverted using undo().
     *
     * @see undo()
     */
    void redo();

    /**
     * Reverts the changes made executing this Task.
     * Selects the right implementation of this Task from all the availables,
     * using getUndoHelper(), and reverts the changes made when it was executed.
     *
     * @see redo()
     */
    void undo();

protected:

    /**
     * Creates a new Task.
     *
     * @param name The name of the Task.
     * @param package The Package to use.
     * @param taskConfiguration The TaskConfiguration to use.
     */
    Task(const std::string& name, lusi::package::Package* package,
         TaskConfiguration* taskConfiguration);

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
     * The TaskHelpers for this Task.
     */
    std::vector<lusi::task::helper::TaskHelper*> mTaskHelpers;



    /**
     * Returns a TaskHelper to be executed.
     * If there are no more available TaskHelpers suitable to be executed with
     * the Package, returns a null pointer.
     *
     * The TaskHelper returned is, in first case, a TaskHelper previously
     * executed with the Package in the current status. If there isn't any, the
     * suitable TaskHelpers from the vector of TaskHelpers are returned, one
     * at a time each time the method is called, until there're no more
     * suitable TaskHelpers left.
     *
     * @return A TaskHelper to be executed, or a null pointer if there are no
     *         more suitable TaskHelpers.
     */
    lusi::task::helper::TaskHelper* getRedoHelper();

    /**
     * Returns a TaskHelper to be reverted.
     * If there is no available TaskHelper suitable to be reverted with
     * the Package, returns a null pointer.
     *
     * The TaskHelper returned is a TaskHelper previously successfully executed
     * with the Package in the current status.
     *
     * @return A TaskHelper to be reverted, or a null pointer if there is no
     *         suitable TaskHelper.
     */
    lusi::task::helper::TaskHelper* getUndoHelper();

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
