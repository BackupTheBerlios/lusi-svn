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

#ifndef LUSI_PACKAGE_STATUS_UNPACKEDPACKAGESTATUS_H
#define LUSI_PACKAGE_STATUS_UNPACKEDPACKAGESTATUS_H

#include <lusi/package/status/PackageStatus.h>

namespace lusi {
namespace package {
namespace status {

/**
 * @class UnpackedPackageStatus UnpackedPackageStatus.h \
 * lusi/package/status/UnpackedPackageStatus.h
 *
 * PackageStatus which represents unpackaged packages.
 * This status is meant to be used whenever the Package is unpacked, so all the
 * files that belong to the package can be accessed directly.
 *
 * This class follows the Singleton Design Pattern. Only one instance is
 * created, and it can be got with getInstance() method.
 */
class UnpackedPackageStatus: public PackageStatus {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static const UnpackedPackageStatus* getInstance();

    /**
     * Destroys this UnpackedPackageStatus.
     */
    virtual ~UnpackedPackageStatus();

protected:

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static UnpackedPackageStatus* sInstance;

    /**
     * Creates a new UnpackedPackageStatus.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    UnpackedPackageStatus();

    /**
     * Copy constructor disabled.
     */
    UnpackedPackageStatus(const UnpackedPackageStatus& unpackedPackageStatus);

    /**
     * Assignment disabled.
     */
    UnpackedPackageStatus& operator=(
            const UnpackedPackageStatus& unpackedPackageStatus);

};

}
}
}

#endif
