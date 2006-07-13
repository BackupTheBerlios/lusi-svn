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

#ifndef LUSI_PACKAGE_PACKAGEID_H
#define LUSI_PACKAGE_PACKAGEID_H

#include <string>

namespace lusi {
namespace package {

/**
 * @class PackageId PackageId.h lusi/package/PackageId.h
 *
 * Identifier for Packages.
 * A Package is identified by its name and version. Name and version can't be
 * modified once the PackageId is created.
 *
 * PackageId may have unset version. In this case, a default empty version is
 * automatically set. Name can't be empty.
 */
class PackageId {
public:

    /**
     * Creates a new PackageId using the specified name and version.
     * If no version is specified, it's set to an empty string.
     */
    PackageId(const std::string& name,
            const std::string& version = std::string());

    /**
     * Destroys this PackageId.
     */
    virtual ~PackageId();

    /**
     * Returns the name of this PackageId.
     * The name is read only, and this is an accessor method.
     *
     * @return The name of this PackageId.
     */
    const std::string& getName() const {
        return mName;
    }

    /**
     * Returns the version of this PackageId.
     * The version is read only, and this is an accessor method.
     *
     * @return The name of this PackageId.
     */
    const std::string& getVersion() const {
        return mVersion;
    }

protected:

private:

    /**
     * The name of the PackageId.
     */
    std::string mName;

    /**
     * The version of the PackageId.
     */
    std::string mVersion;




    /**
     * Copy constructor disabled.
     */
    PackageId(const PackageId& packageId);

    /**
     * Assignment disabled.
     */
    PackageId& operator=(const PackageId& packageId);

};

}
}

#endif
