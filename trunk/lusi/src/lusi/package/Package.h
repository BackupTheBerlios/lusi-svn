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

#include <string>
#include <vector>

#include <lusi/package/PackageId.h>
#include <lusi/package/status/UnknownPackageStatus.h>
#include <lusi/util/SmartPtr.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterMap;
}
}

namespace lusi {
namespace package {
class Profile;
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
 * Packages are identified by its name and version. A Package is composed by
 * different resources (files, for example), grouped in a
 * ConfigurationParameterMap.
 * Packages have also a specific PackageStatus, used to describe which Tasks
 * can be executed over the Package.
 * They also have a Profile which contains information about the Tasks executed
 * over the Package, the resources and the PackageStatus (it is like the
 * historial of the Package).
 *
 * Packages shouldn't be created directly. Instead, they should always be got
 * through PackageManager.
 *
 * The configuration of the Package is composed of the different resources that
 * form the Package in the current PackageStatus. They are added directly under
 * the root ConfigurationParameterMap of the configuration, returned by
 * getResources().
 *
 * The most common resource are files. All the files that are part of the
 * Package are added under the "files" ConfigurationParameterMap, direct child
 * of the root ConfigurationParameterMap. As it is the most common
 * ConfigurationParameter needed, it can be got directly through
 * getResourceFiles(). All the children of the "files" ConfigurationParameterMap
 * are ConfigurationParameterLocalUrl with an id equal to the path of the
 * default LocalUrl.
 *
 * The resources are updated by Tasks when they are executed to reflect the
 * changes made, if any.
 *
 * The only property of a Package that can be set is the PackageStatus, which
 * is updated by Tasks when they finish their execution. An initial
 * PackageStatus is provided by the PackageManager with the last PackageStatus
 * the Package was in the last execution of LUSI. If not specified, default
 * PackageStatus is set to UnknownPackageStatus.
 *
 * This class follows a Proxy Design Pattern. The Profile and the resources are
 * only loaded on demand, when their get method is called. Resource files also
 * load the general resources when they are got. This approach makes possible
 * to have a long list of Packages which only contains their PackageId and
 * their PackageStatus instead of the full data of the class.
 *
 * Resources are got initially from the Profile, and depth copied to the
 * Package, to avoid changes in the resources of the Package to modify also the
 * Profile.
 *
 * @see PackageManager
 */
class Package {
friend class Profile;
public:

    /**
     * Returns all the available versions of the Package with the specified
     * name.
     * The available versions are the direct child directories of the root
     * Package configuration directory. The returned strings are the versions,
     * not the directory names, so the ending '/' is already removed.
     *
     * @param packageName The name of the package.
     * @return All the available versions of the Package with the specified
     *         name.
     */
    static std::vector<std::string> getPackageVersions(
                                            const std::string& packageName);

    /**
     * Creates a new Package using the specified PackageId and PackageStatus.
     * If no PackageStatus is specified, it uses UnknownPackageStatus.
     *
     * @param packageId The PackageId.
     * @param packageStatus The PackageStatus, UnknownPackageStatus by default.
     */
    Package(const PackageId& packageId,
            const status::PackageStatus* packageStatus =
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
    const PackageId& getPackageId() {
        return mPackageId;
    }

    /**
     * Returns the Profile.
     *
     * @return The Profile.
     */
    Profile* getProfile();

    /**
     * Returns the resources in a ConfigurationParameterMap.
     *
     * @return The resources in a ConfigurationParameterMap.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    getResources();

    /**
     * Returns the ConfigurationParameterMap containing the files of this
     * Package.
     *
     * @return The ConfigurationParameterMap containing the files of this
     *         Package.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    getResourceFiles();

    /**
     * Returns the PackageStatus.
     *
     * @return The PackageStatus.
     */
    const status::PackageStatus* getPackageStatus() {
        return mPackageStatus;
    }

    /**
     * Sets the PackageStatus.
     * The Profile and the the PackageManager are also updated.
     *
     * @param packageStatus The PackageStatus.
     */
    void setPackageStatus(const status::PackageStatus* packageStatus);

protected:

private:

    /**
     * The PackageId.
     */
    PackageId mPackageId;

    /**
     * The Profile.
     */
    Profile* mProfile;

    /**
     * The ConfigurationParameterMap.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    mResources;

    /**
     * The ConfigurationParameterMap containing the files of this Package.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    mResourceFiles;

    /**
     * The PackageStatus.
     */
    const status::PackageStatus* mPackageStatus;



    /**
     * Reverts the PackageStatus to a previous one.
     * This method is called by Profile to update the PackageStatus in the
     * Package and in the PackageManager. It also sets to null the resources of
     * this Package, so they are got again from the Profile when needed.
     *
     * @param packageStatus The PackageStatus to revert to.
     */
    void revertPackageStatus(const status::PackageStatus* packageStatus);

    /**
     * Copy constructor disabled.
     */
    Package(const Package& package);

    /**
     * Assignment disabled.
     */
    Package& operator=(const Package& package);

};

}
}

#endif
