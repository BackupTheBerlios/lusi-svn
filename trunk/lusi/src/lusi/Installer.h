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

#ifndef LUSI_INSTALLER_H
#define LUSI_INSTALLER_H

#include <lusi/Module.h>

namespace lusi {
namespace package {
class Package;
}
}

namespace lusi {

/**
 * @class Installer Installer.h lusi/Installer.h
 *
 * Installer for packages.
 * This module installs the specified Package.
 *
 * @see Uninstaller
 */
class Installer: public Module {
public:

    /**
     * Creates a new installer.
     */
    Installer();

    /**
     * Destroys this installer.
     */
    virtual ~Installer();

    /**
     * Installs the specified package.
     * Executes the needed tasks (through TaskManager) and updates the profile,
     * if needed.
     *
     * @param package The package to install.
     * @see task::TaskManager::getTask(lusi::package::Package*)
     */
    void execute(lusi::package::Package* package);

protected:

private:

    /**
     * Copy constructor disabled.
     */
    Installer(const Installer &installer);

    /**
     * Assignment disabled.
     */
    Installer& operator=(const Installer &installer);

};

}

#endif
