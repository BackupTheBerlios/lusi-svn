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

#ifndef LUSI_PACKAGE_STATUS_CONFIGUREDPACKAGESTATUS_H
#define LUSI_PACKAGE_STATUS_CONFIGUREDPACKAGESTATUS_H

#include <lusi/package/status/PackageStatus.h>

namespace lusi {
namespace package {
namespace status {

/**
 * @class ConfiguredPackageStatus ConfiguredPackageStatus.h \
 * lusi/package/status/ConfiguredPackageStatus.h
 *
 * PackageStatus which represents configured packages.
 * This status is meant to be used whenever the Package is configured and ready
 * to be built.
 *
 * This class follows the Singleton Design Pattern. Only one instance is
 * created, and it can be got with getInstance() method.
 */
class ConfiguredPackageStatus: public PackageStatus {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static const ConfiguredPackageStatus* getInstance();

    /**
     * Destroys this ConfiguredPackageStatus.
     */
    virtual ~ConfiguredPackageStatus();

protected:

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static ConfiguredPackageStatus* sInstance;

    /**
     * Creates a new ConfiguredStatus.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    ConfiguredPackageStatus();

    /**
     * Copy constructor disabled.
     */
    ConfiguredPackageStatus(const ConfiguredPackageStatus &configuredPackageStatus);

    /**
     * Assignment disabled.
     */
    ConfiguredPackageStatus& operator=(const ConfiguredPackageStatus &configuredPackageStatus);

};

}
}
}

#endif
