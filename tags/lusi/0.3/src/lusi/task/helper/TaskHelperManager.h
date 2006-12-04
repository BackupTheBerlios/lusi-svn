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

#ifndef LUSI_TASK_HELPER_TASKHELPERMANAGER_H
#define LUSI_TASK_HELPER_TASKHELPERMANAGER_H

#include <map>
#include <string>
#include <vector>

namespace lusi {
namespace task {
class Task;
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
namespace helper {

/**
 * @class TaskHelperManager TaskHelperManager.h \
 * lusi/task/helper/TaskHelperManager.h
 *
 * Manager for TaskHelpers.
 * Registers TaskHelpers with Task names, so each Task can know which
 * TaskHelpers can use.
 *
 * In order to register a TaskHelper, a function which takes a Task as
 * parameter and returns a pointer to a new TaskHelper (including any derived
 * class) must be used. This function is like a simplified Factory Design
 * Pattern, as it has the same philosophy, although without using specific
 * Factory classes.
 *
 * A instance of all the TaskHelpers registered with a Task name can be got
 * using getTaskHelpers.
 */
class TaskHelperManager {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static TaskHelperManager* getInstance();

    /**
     * Destroys this TaskHelperManager.
     */
    virtual ~TaskHelperManager();

    /**
     * Returns a vector with instances of all the TaskHelpers registered with
     * the name of the task.
     * The vector contains pointers to TaskHelpers initialized with the Task.
     * All the elements in the vector must be deleted when they're no longer
     * being used.
     *
     * @param task The task to get the helpers for.
     * @return A vector containing pointers to instances of all the TaskHelpers
     *         availables for the Task.
     * @see registerTaskHelper(TaskHelper* (*)(lusi::task::Task*), std::string)
     */
    std::vector<TaskHelper*> getTaskHelpers(lusi::task::Task* task) const;

    /**
     * Register a TaskHelper with a task name.
     * The TaskHelper is registered using a factory function which creates a new
     * instance of a TaskHelper (or any derived class) when called, using the
     * Task that the TaskHelper will be registered with.
     *
     * TaskHelpers for each Task name can be got using getTaskHelpers(Task).
     *
     * @param taskHelperFactory A function returning a pointer to a new
     *                          TaskHelper, created with the specified Task.
     * @param taskName The name of the Task to register the TaskHelper with.
     * @see getTaskHelpers(lusi::task::Task)
     */
    void registerTaskHelper(TaskHelper* (*taskHelperFactory)(lusi::task::Task*),
                            const std::string& taskName);

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static TaskHelperManager* sInstance;

    /**
     * Multimap containing the TaskHelper factories for each Task name.
     * TaskHelper factories are functions returning a pointer to an instance of
     * a TaskHelper.
     */
    std::multimap<std::string, TaskHelper* (*)(lusi::task::Task*)>
    mTaskHelperFactories;



    /**
     * Creates a new TaskHelperManager.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    TaskHelperManager();

    /**
     * Copy constructor disabled.
     */
    TaskHelperManager(const TaskHelperManager& taskHelperManager);

    /**
     * Assignment disabled.
     */
    TaskHelperManager& operator=(const TaskHelperManager& taskHelperManager);

};

}
}
}

#endif
