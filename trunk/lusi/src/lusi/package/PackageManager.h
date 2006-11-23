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

#ifndef LUSI_PACKAGE_PACKAGEMANAGER_H
#define LUSI_PACKAGE_PACKAGEMANAGER_H

#include <vector>

#include <lusi/package/PackageId.h>

namespace lusi {
namespace package {
class Package;
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
namespace util {
template<typename T>
class SmartPtr;
}
}

namespace lusi {
namespace package {

/**
 * @class PackageManager PackageManager.h lusi/package/PackageManager.h
 *
 * Manager for Packages.
 * PackageManager handles the Packages used in this and previous executions of
 * LUSI. It contains the information to associate a PackageId with their
 * PackageStatus, so it can be queried about what PackageIds are associated with
 * a specific PackageStatus through getPackageIds(PackageStatus*).
 *
 * Packages shouldn't be created directly. Instead, they should always be got
 * using this class through getPackage(const PackageId&). The Package is saved
 * automatically each time its status is set.
 *
 * This class follows the Singleton Design Pattern. Only one instance is
 * created, and it can be got with getInstance() method.
 *
 * A static method, getPackageNames(), is provided to know the name of all the
 * saved Packages in the hard disk.
 */
class PackageManager {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static PackageManager* getInstance();

    /**
     * Returns all the available names of Packages.
     * The available names are the direct child directories of the Packages
     * base configuration directory. The returned strings are the names,
     * not the directory names, so the ending '/' is already removed.
     *
     * @return All the available names of Packages.
     */
    static std::vector<std::string> getPackageNames();

    /**
     * Destroys this PackageManager.
     */
    virtual ~PackageManager();

    /**
     * Returns all the registered PackageIds for the specified PackageStatus.
     * The returned PackageIds can be used to get the registered Packages
     * through getPackage(const PackageId&).
     *
     * @return All the registered PackageIds for the specified PackageStatus.
     * @see getPackage(const PackageId&)
     */
    std::vector<PackageId> getPackageIds(
                    const lusi::package::status::PackageStatus* packageStatus);

    /**
     * Gets a Package for the specified PackageId.
     * The PackageId can have been got using getPackageIds(PackageStatus*), or
     * be a new PackageId different from all the returned by
     * getPackageIds(PackageStatus*).
     *
     * If the PackageId was returned by getPackageIds(PackageStatus), the
     * returned Package will be initialized with that PackageId and its
     * associated PackageStatus.
     *
     * If the PackageId was new, the returned Package will be initialized with
     * the PackageId and the default PackageStatus.
     *
     * @param packageId The PackageId to get the Package.
     * @return A Package for the specified PackageId initialized with the
     *         available information.
     * @see getPackageIds(PackageStatus*)
     */
    lusi::util::SmartPtr<Package> getPackage(const PackageId& packageId);

    /**
     * Updates the status associated with the PackageId of the Package and saves
     * the Package.
     * The Package must have been got using getPackage(const PackageId&).
     * This method is called automatically when the PackageStatus of a Package
     * is set.
     *
     * @param package The Package to update.
     * @return True if the Package was successfully saved, false otherwise.
     */
    bool updatePackage(Package* package);

private:

    /**
     * Container to hold a PackageId and its associated PackageStatus.
     */
    struct PackageData {

        /**
         * Creates a new PackageData with trivial attributes.
         */
        PackageData(): packageId("") {
        }

        /**
         * The PackageId.
         */
        PackageId packageId;

        /**
         * The PackageStatus associated to the PackageId.
         */
        const lusi::package::status::PackageStatus* packageStatus;

    };

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static PackageManager* sInstance;

    /**
     * The data of all the registered packages.
     * It contains the loaded Packages and the ones created through
     * getPackage(const PackageId&).
     */
    std::vector<PackageData> mPackageDatas;



    /**
     * Creates a new PackageManager.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    PackageManager();

    /**
     * Loads all the saved PackageIds and their associated PackageStatus.
     * All the saved Packages and each of their versions are loaded. Also, it is
     * loaded the PackageId without any version (if it was saved).
     *
     * @see loadPackage(const PackageId&)
     */
    void load();

    /**
     * Loads the saved Package identified by the PackageId.
     * Loading a Package in this context doesn't mean creating a new Package.
     * Instead, the PackageId is added to mPackageDatas with its associated
     * PackageStatus.
     *
     * @param packageId The PackageId of the Package to load.
     * @return True if the Package was loaded, false otherwise.
     * @see lusi::configuration::ConfigurationLoader
     */
    bool loadPackage(const PackageId& packageId);

    /**
     * Saves the Package.
     * The status of the Package is saved in the configuration file for the
     * specified Package.
     *
     * @param package The Package to save.
     * @return True if the Package was saved, false otherwise.
     * @see lusi::configuration::ConfigurationSaver
     */
    bool savePackage(Package* package);

    /**
     * Copy constructor disabled.
     */
    PackageManager(const PackageManager& packageManager);

    /**
     * Assignment disabled.
     */
    PackageManager& operator=(const PackageManager& packageManager);

};

}
}

#endif
