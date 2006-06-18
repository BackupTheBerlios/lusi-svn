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

#ifndef LUSI_PACKAGE_PACKAGE_H
#define LUSI_PACKAGE_PACKAGE_H

#include <lusi/package/status/UnknownPackageStatus.h>

namespace lusi {
namespace package {
class PackageId;
class Profile;
class ResourceMap;
}
}

namespace lusi {
namespace package {
namespace status {
    class PackageStatus;
}
}
}

namespace lusi {
namespace package {

/**
 * @class Package Package.h lusi/package/Package.h
 *
 * The Package class represents a software package.
 * Packages are identified by its name and version. They also have a Profile
 * which contains information about the Tasks executed over the Package. A
 * Package is composed by different Resources, all grouped in a ResourceMap.
 * Packages have also a specific PackageStatus, used to describe which Tasks
 * can be executed over the Package.
 *
 * The only property of a Package that can be set is the PackageStatus, which
 * is updated by Tasks when they finish their execution. However, an initial
 * PackageStatus should be provided by classes which creates Packages. If not
 * specified, default PackageStatus is set to UnknownPackageStatus.
 *
 * A Package with an empty ResourceMap represents a Package already used by the
 * library. Resources are then got from the Profile.
 * @todo Better design for Packages already used.
 */
class Package {
public:

    /**
     * Creates a new Package using the specified PackageId and PackageStatus.
     * If no PackageStatus is specified, it uses UnkwnonPackageStatus. You're
     * encouraged to set it, however.
     */
    Package(PackageId* packageId, status::PackageStatus* packageStatus =
                    status::UnknownPackageStatus::getInstance());

    /**
     * Destroys this package.
     */
    virtual ~Package();

    /**
     * Returns the PackageId.
     *
     * @return The PackageId.
     */
    PackageId* getPackageId() {
        return mPackageId;
    }

    /**
     * Returns the Profile.
     *
     * @return The Profile.
     */
    Profile* getProfile() {
        return mProfile;
    }

    /**
     * Returns the ResourceMap.
     *
     * @return The ResourceMap.
     */
    ResourceMap* getResourceMap() {
        return mResourceMap;
    }

    /**
     * Returns the PackageStatus.
     *
     * @return The PackageStatus.
     */
    status::PackageStatus* getPackageStatus() {
        return mPackageStatus;
    }

    /**
     * Sets the PackageStatus.
     *
     * @param packageStatus The PackageStatus.
     */
    void setPackageStatus(status::PackageStatus* packageStatus) {
        mPackageStatus = packageStatus;
    }

protected:

private:

    /**
     * The PackageId.
     */
    PackageId* mPackageId;

    /**
     * The Profile.
     */
    Profile* mProfile;

    /**
     * The ResourceMap.
     */
    ResourceMap* mResourceMap;

    /**
     * The PackageStatus.
     */
    status::PackageStatus* mPackageStatus;




    /**
     * Copy constructor disabled.
     */
    Package(const Package &package);

    /**
     * Assignment disabled.
     */
    Package& operator=(const Package &package);

};

}
}

#endif
