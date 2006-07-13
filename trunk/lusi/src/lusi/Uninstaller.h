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

#ifndef LUSI_UNINSTALLER_H
#define LUSI_UNINSTALLER_H

#include <lusi/Module.h>

namespace lusi {
namespace package {
class Package;
}
}

namespace lusi {

/**
 * @class Uninstaller Uninstaller.h lusi/Uninstaller.h
 *
 * Uninstaller for packages.
 * This module uninstalls the specified Package.
 *
 * @see Installer
 */
class Uninstaller: public Module {
public:

    /**
     * Creates a new uninstaller.
     */
    Uninstaller();

    /**
     * Destroys this uninstaller.
     */
    virtual ~Uninstaller();

    /**
     * Uninstalls the specified package.
     * Reverts the needed tasks (through TaskManager) and updates the profile,
     * if needed.
     *
     * @param package The package to uninstall.
     * @see task::TaskManager::getUndoTask(lusi::package::Package*)
     */
    void execute(lusi::package::Package* package);

protected:

private:

    /**
     * Copy constructor disabled.
     */
    Uninstaller(const Uninstaller& uninstaller);

    /**
     * Assignment disabled.
     */
    Uninstaller& operator=(const Uninstaller& uninstaller);

};

}

#endif
