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

#ifndef LUSI_TASK_HELPER_TASKHELPERUSINGPROCESSTESTIMPLEMENTATION_H
#define LUSI_TASK_HELPER_TASKHELPERUSINGPROCESSTESTIMPLEMENTATION_H

#include <lusi/task/helper/TaskHelperUsingProcess.h>
#include <lusi/util/Process.h>

namespace lusi {
namespace task {
namespace helper {

/**
 * Implementation of TaskHelperUsingProcess for testing purposes.
 * This class helps testing TaskHelperUsingProcess class non-abstract methods.
 */
class TaskHelperUsingProcessTestImplementation: public TaskHelperUsingProcess {
public:

    /**
     * Creates a new TaskHelperUsingProcessTestImplementation.
     *
     * @param name The name of the TaskHelperUsingProcessTestImplementation.
     * @param task The Task to use.
     */
    TaskHelperUsingProcessTestImplementation(const std::string& name,
                                             lusi::task::Task* task);

    /**
     * Destroys this TaskHelperUsingProcessTestImplementation.
     */
    virtual ~TaskHelperUsingProcessTestImplementation();

    /**
     * Returns true.
     *
     * @return bool True.
     */
    virtual bool hasValidResources() {
        return true;
    }

    /**
     * Returns True if getProcess method was called, false otherwise.
     */
    bool isExecutionPrepared() const {
        return mExecutionPrepared;
    }

protected:

    /**
     * Sets mExecutionPrepared to true.
     * Returns a Process which executes an echo with the name of this class.
     *
     * @return The Process to execute.
     */
    virtual lusi::util::Process* getProcess();

private:

    /**
     * True if getProcess method was called, false otherwise.
     */
    bool mExecutionPrepared;

};

}
}
}

#endif
