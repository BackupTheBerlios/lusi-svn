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

#include <string>

#include <lusi/task/helper/BuildTaskHelper.h>

namespace lusi {
namespace package {
class ResourceMap;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * @class MakeBuildTaskHelper MakeBuildTaskHelper.h \
 * lusi/task/helper/MakeBuildTaskHelper.h
 *
 * BuildTaskHelper for make command.
 * This BuildTask implementation adds support for make command. This command
 * reads the macros in a file called Makefile. When it's executed, it builds
 * the package or cleans the files created when building it. It uses no
 * parameters (apart from the objetive of the Makefile to execute).
 *
 * ResourceMaps that can be used with MakeBuildTaskHelper are those
 * with a "Makefile" file in the base directory of the package.
 *
 * No configuration is needed.
 */
class MakeBuildTaskHelper: public BuildTaskHelper {
public:

    /**
     * Creates a new MakeBuildTaskHelper.
     */
    MakeBuildTaskHelper();

    /**
     * Destroys this MakeBuildTaskHelper.
     */
    virtual ~MakeBuildTaskHelper();

    /**
     * Returns True if this ResourceMap contains a Makefile that contains
     * macros to be executed by make command.
     *
     * @param resourceMap The ResourceMap to check.
     * @return bool True if the ResourceMap contains a Makefile.
     */
    bool isValidResourceMap(lusi::package::ResourceMap* resourceMap);

protected:

    /**
     * Returns the name of the "make" command.
     *
     * @return The name of "make" command to be invoked.
     */
    virtual std::string buildCommand();

    /**
     * Returns the name of the "make clean" command to invoke to revert the
     * changes made executing this TaskHelper.
     *
     * @return The "make clean" command to be invoked.
     */
    virtual std::string cleanCommand();

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
