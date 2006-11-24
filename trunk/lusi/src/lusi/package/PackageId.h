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
     * Compares two package versions.
     * The versions are expected to follow this regular expression:
     * "[0-9]+(\.[0-9]+)*(-(alpha|beta|rc)[0-9]+)?".
     * The versions are compared based on their subversions, not
     * lexicographically. For example, "0.16" is greater than "0.4".
     *
     * If the compared versions doesn't have the same number of subversions,
     * and the common parts are equal, the version with more subversions numbers
     * is the greatest. For example, "0.23.4" is greater than "0.23".
     *
     * The non numerical part of the subversions is ordered as follows:
     * rc > beta > alpha. The number that follows the text is also compared as
     * numbers, not lexicographically. For example, "0.8.15" > "0.8" >
     * "0.8-rc10" > "0.8-rc8" > "0.8-beta4" > "0.8-alpha2".
     *
     * If any of the specified versions doesn't follow the expected regular
     * expression, the versions are compared as much as possible. If which
     * version is greater can't be determined before reaching the part of the
     * string that doesn't follows the regular expression, the first version is
     * set as greater than the second.
     *
     * @param version1 The first version to compare.
     * @param version2 The second version to compare.
     * @return An integer less than 0 if the first version is smaller than the
     *         second, 0 if they are equal, or an integer greater than 0 if the
     *         first version is greater than the second.
     */
    static int compareVersions(const std::string& version1,
                               const std::string& version2);

    /**
     * Creates a new PackageId using the specified name and version.
     * If no version is specified, it's set to an empty string.
     *
     * @param name The name of the PackageId.
     * @param version The version of the PackageId, empty by default.
     */
    PackageId(const std::string& name,
            const std::string& version = std::string());

    /**
     * Copy constructor.
     *
     * @param packageId The PackageId to copy.
     */
    PackageId(const PackageId& packageId);

    /**
     * Destroys this PackageId.
     */
    virtual ~PackageId();

    /**
     * Returns the name of this PackageId.
     *
     * @return The name of this PackageId.
     */
    const std::string& getName() const {
        return mName;
    }

    /**
     * Returns the version of this PackageId.
     *
     * @return The name of this PackageId.
     */
    const std::string& getVersion() const {
        return mVersion;
    }

    /**
     * Assignment operator.
     *
     * @param packageId The PackageId to assign.
     * @return A reference to this PackageId.
     */
    PackageId& operator=(const PackageId& packageId);

    /**
     * Returns true if the PackageId is equal to this PackageId, false
     * otherwise.
     *
     * @param packageId The PackageId to compare to.
     * @return True if the PackageId is equal to this PackageId, false
     *         otherwise.
     */
    bool operator==(const PackageId& packageId) const;

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

};

}
}

#endif
