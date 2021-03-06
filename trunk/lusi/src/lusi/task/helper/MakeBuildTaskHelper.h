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

#ifndef LUSI_TASK_HELPER_MAKEBUILDTASKHELPER_H
#define LUSI_TASK_HELPER_MAKEBUILDTASKHELPER_H

#include <lusi/task/helper/TaskHelperUsingMake.h>

namespace lusi {
namespace task {
namespace helper {

/**
 * Returns a new MakeBuildTaskHelper.
 * Used to register MakeBuildTaskHelpers with Task names.
 *
 * @param task The Task to help.
 * @return The new MakeBuildTaskHelper created.
 * @see TaskHelperManager
 */
TaskHelper* createMakeBuildTaskHelper(lusi::task::Task* task);

/**
 * @class MakeBuildTaskHelper MakeBuildTaskHelper.h \
 * lusi/task/helper/MakeBuildTaskHelper.h
 *
 * BuildTaskHelper for make command.
 * This BuildTask implementation adds support for make command. This command
 * reads the macros in a file called Makefile. When it's executed, it builds
 * the package or cleans the files created when building it. It uses no
 * parameters.
 *
 * Resources that can be used with MakeBuildTaskHelper are those with a
 * "Makefile" file in the base directory of the package. The package
 * directory must be the first ConfigurationParameterLocalUrl in the
 * resource files.
 *
 * No configuration is needed.
 */
class MakeBuildTaskHelper: public TaskHelperUsingMake {
public:

    /**
     * Creates a new MakeBuildTaskHelper.
     * The package directory is the first ConfigurationParameterLocalUrl in the
     * resource files.
     * If there's no ConfigurationParameterLocalUrl, or the first it's not a
     * directory, an empty LocalUrl is used.
     * No checks about, for example, more than one package directory, are made.
     *
     * @param task The Task to help.
     */
    MakeBuildTaskHelper(lusi::task::Task* task);

    /**
     * Destroys this MakeBuildTaskHelper.
     */
    virtual ~MakeBuildTaskHelper();

protected:

    /**
     * Creates a new Process with PipeCommunication and sets the arguments and
     * the working directory to call make command.
     *
     * @return The Process to be executed.
     */
    virtual lusi::util::Process* getProcess();

private:

    /**
     * Copy constructor disabled.
     */
    MakeBuildTaskHelper(const MakeBuildTaskHelper& makeBuild);

    /**
     * Assignment disabled.
     */
    MakeBuildTaskHelper& operator=(const MakeBuildTaskHelper& makeBuild);

};

}
}
}

#endif
