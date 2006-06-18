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

#ifndef LUSI_PACKAGE_STATUS_UNKNOWNPACKAGESTATUS_H
#define LUSI_PACKAGE_STATUS_UNKNOWNPACKAGESTATUS_H

#include <lusi/package/status/PackageStatus.h>

namespace lusi {
namespace package {
namespace status {

/**
 * @class UnknownPackageStatus UnknownPackageStatus.h \
 * lusi/package/status/UnknownPackageStatus.h
 *
 * PackageStatus which represents an unespecified status.
 * This status is meant to be used whenever the status of the Package isn't
 * known for whatever reason.
 *
 * This class follows the Singleton Design Pattern. Only one instance is
 * created, and it can be got with getInstance() method.
 */
class UnknownPackageStatus: public PackageStatus {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static const UnknownPackageStatus* getInstance();

    /**
     * Destroys this UnknownPackageStatus.
     */
    virtual ~UnknownPackageStatus();

protected:

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static UnknownPackageStatus* sInstance;

    /**
     * Creates a new UnknownPackageStatus.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    UnknownPackageStatus();

    /**
     * Copy constructor disabled.
     */
    UnknownPackageStatus(const UnknownPackageStatus &unknownPackageStatus);

    /**
     * Assignment disabled.
     */
    UnknownPackageStatus& operator=(const UnknownPackageStatus &unknownPackageStatus);

};

}
}
}

#endif
