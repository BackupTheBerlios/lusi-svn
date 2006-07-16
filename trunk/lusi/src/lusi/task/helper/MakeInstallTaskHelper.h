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

#ifndef LUSI_TASK_HELPER_MAKEINSTALLTASKHELPER_H
#define LUSI_TASK_HELPER_MAKEINSTALLTASKHELPER_H

#include <string>

#include <lusi/task/helper/InstallTaskHelper.h>

namespace lusi {
namespace package {
class ResourceMap;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Returns a new MakeInstallTaskHelper.
 * Used to register MakeInstallTaskHelpers with Task names.
 *
 * @param task The Task to help.
 * @return The new MakeInstallTaskHelper created.
 * @see TaskHelperManager
 */
TaskHelper* createMakeInstallTaskHelper(lusi::task::Task* task);

/**
 * @class MakeInstallTaskHelper MakeInstallTaskHelper.h \
 * lusi/task/helper/MakeInstallTaskHelper.h
 *
 * InstallTaskHelper for make command.
 * This InstallTask implementation adds support for make command. This command
 * reads the macros in a file called Makefile. When it's executed, it installs
 * the package or uninstalls it removing the files created when building it. It
 * uses no parameters (apart from the objetive of the Makefile to execute).
 *
 * ResourceMaps that can be used with MakeInstallTaskHelper are those
 * with a "Makefile" file in the base directory of the package.
 *
 * No configuration is needed.
 */
class MakeInstallTaskHelper: public InstallTaskHelper {
public:

    /**
     * Creates a new MakeInstallTaskHelper.
     */
    MakeInstallTaskHelper(lusi::task::Task* task);

    /**
     * Destroys this MakeInstallTaskHelper.
     */
    virtual ~MakeInstallTaskHelper();

    /**
     * Returns True if the ResourceMap contains a Makefile that contains
     * macros to be executed by make command.
     *
     * @return bool True if the ResourceMap contains a Makefile.
     * @todo Check for install objective in Makefile?
     */
    virtual bool hasValidResourceMap();

protected:

    /**
     * Returns the name of the "make install" command.
     *
     * @return The name of "make install" command to be invoked.
     */
    virtual std::string installCommand();

    /**
     * Returns the name of the "make uninstall" command to invoke to revert the
     * changes made executing this TaskHelper.
     *
     * @return The "make uninstall" command to be invoked.
     */
    virtual std::string uninstallCommand();

private:

    /**
     * Copy constructor disabled.
     */
    MakeInstallTaskHelper(const MakeInstallTaskHelper& makeInstall);

    /**
     * Assignment disabled.
     */
    MakeInstallTaskHelper& operator=(const MakeInstallTaskHelper& makeInstall);

};

}
}
}

#endif
