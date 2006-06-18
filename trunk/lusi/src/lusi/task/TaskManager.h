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

#ifndef LUSI_TASK_TASKMANAGER_H
#define LUSI_TASK_TASKMANAGER_H

#include <string>

namespace lusi {
namespace package {
class Package;
}
}

namespace lusi {
namespace task {
class Task;
}
}

namespace lusi {
namespace task {

/**
 * @class TaskManager TaskManager.h lusi/task/TaskManager.h
 *
 * Manager for Tasks.
 * TaskManager handles the selection of Task to be executed or reverted. It
 * first tries with the Profile and, if that fails, it uses the PackageStatus.
 *
 * Task shouldn't be created directly. Instead, they should always be got
 * using this class.
 *
 * This class follows the Singleton Design Pattern. Only one instance is
 * created, and it can be got with getInstance() method.
 */
class TaskManager {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static TaskManager* getInstance();

    /**
     * Destroys this TaskManager.
     */
    virtual ~TaskManager();

    /**
     * Returns a Task to be done over the Package.
     * It first tries with the Task suggested by the Profile and, if that
     * fails, it returns a suitable Task based on the PackageStatus.
     *
     * @param package The Package to do the Task over.
     * @return The Task to be done.
     * @todo rename to getRedoTask?
     */
    Task* getTask(lusi::package::Package* package);

    /**
     * Returns a Task to be undone over the Package.
     * It first tries with the Task suggested by the Profile and, if that
     * fails, it returns a suitable Task based on the PackageStatus.
     *
     * @param package The Package to undo the Task over.
     * @return The Task to be undone.
     */
    Task* getUndoTask(lusi::package::Package* package);

protected:

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static TaskManager* sInstance;




    /**
     * Creates a new TaskManager.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    TaskManager();

    /**
     * Copy constructor disabled.
     */
    TaskManager(const TaskManager& taskManager);

    /**
     * Assignment disabled.
     */
    TaskManager& operator=(const TaskManager& taskManager);

};

}
}

#endif
