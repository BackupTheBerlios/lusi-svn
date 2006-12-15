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
namespace package {

/**
 * @class PackageManager PackageManager.h lusi/package/PackageManager.h
 *
 * Manager for Packages.
 * PackageManager handles the Packages used in this and previous executions of
 * LUSI. Each Package is associated with only one PackageId. However, several
 * Packages can be in the same status.
 *
 * This class can be queried about what Packages are associated with a specific
 * PackageStatus through getPackages(PackageStatus*). This is only an overloaded
 * version of getPackages(), provided for convenience.
 *
 * Packages shouldn't be created directly. Instead, they should always be got
 * using this class through getPackage(const PackageId&) or
 * getPackages(PackageStatus*). The former can be used to get registered
 * Packages or register new Packages, while the latter can only be used to get
 * already registered Packages.
 *
 * The Packages are updated automatically each time their status is set.
 *
 * Any Package can be removed from LUSI control using remove(Package*).
 *
 * This class follows the Singleton Design Pattern. Only one instance is
 * created, and it can be got with getInstance() method.
 *
 * A static method, getPackageNames(), is provided to know the name of all the
 * saved Packages in the hard disk.
 *
 * The PackageManager loads and save the PackageStatus of each Package in a
 * specific file. The PackageStatus of the Package can also be known using the
 * Profile, but the PackageManager saves its own copy of that information due to
 * efficency reasons: this way, only the PackageStatus must be loaded, but if
 * the PackageStatus were got from the Profile, the whole Profile with all the
 * resources would need to be loaded for each Package, even when they weren't
 * going to be used.
 */
class PackageManager {
friend class Package;
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
     * Returns all the registered Packages.
     *
     * @return All the registered Packages.
     */
    std::vector<Package*> getPackages() {
        return mPackages;
    }

    /**
     * Returns all the registered Packages in the specified PackageStatus.
     * This is only an overloaded version of getPackages(), provided for
     * convenience.
     *
     * @param packageStatus The PackageStatus.
     * @return All the registered Packages in the specified PackageStatus.
     */
    std::vector<Package*> getPackages(
                    const lusi::package::status::PackageStatus* packageStatus);

    /**
     * Gets the Package with the specified PackageId.
     * The PackageId can be the one of an already registered Package, or
     * be a new PackageId.
     *
     * If the PackageId is from an already registered Package, that Package is
     * returned.
     *
     * If the PackageId was new, a new Package is registered and returned. The
     * Package will use UnknownPackageStatus.
     *
     * @param packageId The PackageId to get the Package.
     * @return The Package with the specified PackageId.
     */
    Package* getPackage(const PackageId& packageId);

    /**
     * Removes a Package.
     * The Package data saved by the PackageManager is removed from disk, the
     * Package is removed from the list of Packages and the Profile is reverted
     * to its first PackageStatus (this way, the information about the Task is
     * kept, but all the resources are removed).
     *
     * Note that this only removes the Package from LUSI, but the files of the
     * Package aren't removed, it isn't uninstalled automatically... This only
     * affects to LUSI control over the Package.
     *
     * The Package must have been got using this class (not creating it
     * "manually"). It can't be used after calling this method, as it is
     * deleted in it.
     *
     * @param package The Package to remove.
     */
    void removePackage(Package* package);

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static PackageManager* sInstance;

    /**
     * The registered packages.
     * It contains the loaded Packages and the ones created through
     * getPackage(const PackageId&).
     */
    std::vector<Package*> mPackages;



    /**
     * Creates a new PackageManager.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    PackageManager();

    /**
     * Loads all the saved Packages.
     * All the saved Packages and each of their versions are loaded. Also, it is
     * loaded the Package without any version (if it was saved).
     *
     * @see loadPackage(const PackageId&)
     */
    void load();

    /**
     * Loads the saved Package identified by the PackageId.
     * Loading a Package in this context only means creating the new Package,
     * but not initializing its Profile nor resources.
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
