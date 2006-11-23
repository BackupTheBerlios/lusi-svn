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

#ifndef LUSI_TASK_HELPER_BASEEXTRACTTASKHELPERTESTIMPLEMENTATION_H
#define LUSI_TASK_HELPER_BASEEXTRACTTASKHELPERTESTIMPLEMENTATION_H

#include <lusi/task/helper/BaseExtractTaskHelper.h>

namespace lusi {
namespace util {
class Process;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Implementation of BaseExtractTaskHelper for testing purposes.
 * This class helps testing BaseExtractTaskHelper class non-abstract methods.
 */
class BaseExtractTaskHelperTestImplementation: public BaseExtractTaskHelper {
public:

    /**
     * Creates a new BaseExtractTaskHelperTestImplementation.
     *
     * @param name The name of the BaseExtractTaskHelperTestImplementation.
     * @param task The Task to use.
     */
    BaseExtractTaskHelperTestImplementation(const std::string& name,
                                            lusi::task::Task* task);

    /**
     * Destroys this BaseExtractTaskHelperTestImplementation.
     */
    virtual ~BaseExtractTaskHelperTestImplementation();

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
     * @return process The Process to execute.
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
