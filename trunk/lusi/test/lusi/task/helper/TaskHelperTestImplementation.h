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

#ifndef LUSI_TASK_HELPER_TASKHELPERTESTIMPLEMENTATION_H
#define LUSI_TASK_HELPER_TASKHELPERTESTIMPLEMENTATION_H

#include <lusi/task/helper/TaskHelper.h>

namespace lusi {
namespace task {
namespace helper {

/**
 * Returns a new TaskHelperTestImplementation with name "1" and valid resource
 * map.
 *
 * @param task The Task to help.
 * @return The TaskHelperTestImplementation created.
 */
TaskHelper* createTaskHelperTestImplementation1(lusi::task::Task* task);

/**
 * Returns a new TaskHelperTestImplementation with name "2".
 *
 * @param task The Task to help.
 * @return The TaskHelperTestImplementation created.
 */
TaskHelper* createTaskHelperTestImplementation2(lusi::task::Task* task);

/**
 * Returns a new TaskHelperTestImplementation with name "3".
 *
 * @param task The Task to help.
 * @return The TaskHelperTestImplementation created.
 */
TaskHelper* createTaskHelperTestImplementation3(lusi::task::Task* task);

/**
 * Implementation of TaskHelper for testing purposes.
 * This class helps testing TaskHelper class non-abstract methods, and also to
 * be used where TaskHelper objects are needed.
 */
class TaskHelperTestImplementation: public TaskHelper {
public:

    /**
     * Creates a new TaskHelperTestImplementation.
     *
     * @param task The task to help.
     * @param name The name of the TaskHelper.
     * @param validResourceMap The value to return by hasValidResourceMap().
     */
    TaskHelperTestImplementation(Task* task, const std::string& name,
                                 bool validResourceMap = false);

    /**
     * Destroys this TaskHelperTestImplementation.
     */
    virtual ~TaskHelperTestImplementation();

    /**
     * Returns the value set in the constructor.
     *
     * @param resourceMap A ResourceMap.
     */
    virtual bool hasValidResourceMap() {
        return mValidResourceMap;
    }

private:

    /**
     * The value to return in hasValidResourceMap().
     */
    bool mValidResourceMap;

};

}
}
}

#endif
