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

#ifndef LUSI_PACKAGE_PROFILE_H
#define LUSI_PACKAGE_PROFILE_H

#include <string>
#include <vector>

#include <lusi/util/SmartPtr.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterMap;
}
}

namespace lusi {
namespace package {
class Package;
class PackageId;
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
namespace task {
class Task;
}
}

namespace lusi {
namespace package {

/**
 * @class Profile Profile.h lusi/package/Profile.h
 *
 * Profile contains all the information about the PackageStatus a Package had.
 * This includes the order of the PackageStatus, the Task executed in each
 * PackageStatus to evolve to the next, and the resources the Package had in
 * each PackageStatus.
 *
 * The PackageStatus of the Package is the "current PackageStatus" of the
 * Profile. The resources associated with the current PackageStatus can be got
 * with getResources(). The Profile may contain the id of the Task used to go
 * from the current PackageStatus to the next in a previous execution. That id
 * can be got using getTaskId().
 *
 * The resources and the Task id for the current PackageStatus can also be set
 * using setResources(SmartPtr<ConfigurationParameterMap>) and setTaskId(const
 * string*).
 *
 * When the Package advances to a new PackageStatus, it can be set with
 * addPackageStatus(const PackageStatus*). When a new PackageStatus is set, its
 * resources and Task id are empty, so they must be set as needed.
 *
 * As the Profile contains the history of all the PackageStatus of the Package,
 * the current PackageStatus can be reverted to a previous one using
 * reverPackageStatus(const PackageStatus*). The resources of all the
 * PackageStatus from the next to the reverted to the end are cleared (as
 * they are no longer valid). The Task ids, however, are kept, as they can
 * suggest the Tasks to be executed.
 *
 * The available PackageStatus to revert to can be known using
 * getAllPackageStatus().
 *
 * When a change is made in the Profile (a PackageStatus is added, resources
 * are set, and so on), it is saved automatically.
 */
class Profile {
public:

    /**
     * Creates a new Profile of the specified Package.
     *
     * @param package The Package of this Profile.
     */
    explicit Profile(Package* package);

    /**
     * Destroys this profile.
     */
    virtual ~Profile();

    /**
     * Returns the Package of this Profile.
     *
     * @return The Package of this Profile.
     */
    Package* getPackage() {
        return mPackage;
    }

    /**
     * Returns the list with all the PackageStatus.
     * The list contains the PackageStatus from the first to the current in the
     * same order they were added.
     *
     * @return The list with all the PackageStatus.
     */
    std::vector<const lusi::package::status::PackageStatus*>
    getAllPackageStatus();

    /**
     * Returns the current PackageStatus.
     *
     * @return The current PackageStatus.
     */
    const lusi::package::status::PackageStatus* getPackageStatus();

    /**
     * Returns the current resources.
     * The current resources are those associated with the current
     * PackageStatus. If there are no associated resources, an empty
     * ConfigurationParameterMap is returned.
     *
     * The id of the returned ConfigurationParameterMap is "resources".
     *
     * @return The current resources.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    getResources();

    /**
     * Returns the id of a suggested Task to be executed based on the Package
     * status.
     * If there's no suitable Task to be executed, an empty string is returned.
     *
     * @return The id of the suggested Task to execute.
     */
    std::string getTaskId();

    /**
     * Sets the current resources.
     * The current resources are removed and substituted with the new ones.
     * The configuration itself isn't added, but a copy of it. All the child
     * parameters are also copied.
     *
     * @param resources The resources to set.
     */
    void setResources(lusi::util::SmartPtr<
                lusi::configuration::ConfigurationParameterMap> resources);

    /**
     * Sets the current Task id.
     *
     * @param taskId The Task id to set.
     */
    void setTaskId(const std::string& taskId);

    /**
     * Adds a new package status after the current one.
     * After adding the new status it is set as the current one.
     *
     * If the current PackageStatus is the last in the list of PackageStatus,
     * the new PackageStatus is added at the end. An empty string is added as
     * the Task id, and an empty ConfigurationParameterMap is added as the
     * resources.
     *
     * If the current PackageStatus isn't the last and the new one to add is
     * equal to the next PackageStatus, the next PackageStatus is set as the
     * current one. No changes are made in the Task ids or resources, as if the
     * PackageStatus wasn't the last, the Profile was reverted, so no more
     * changes are needed.
     *
     * If the new one to add is different, the next PackageStatus and all the
     * others until the end are removed, and the PackageStatus is added like in
     * the first case (the current being the last, as all the others are
     * removed).
     *
     * @param packageStatus The PackageStatus to add.
     */
    void addPackageStatus(
                const lusi::package::status::PackageStatus* packageStatus);

    /**
     * Reverts this Profile to the specified PackageStatus.
     * The current PackageStatus is set as the one specified. If the specified
     * PackageStatus isn't any of the PackageStatus before the current one in
     * the list, nothing is done.
     *
     * All the resources of the PackageStatus from the next PackageStatus (the
     * next of the new current PackageStatus) to the end are cleared, although
     * the Task ids are kept.
     *
     * The Package of this Profile is also reverted, so its PackageStatus is
     * changed and the resources cleared to be got again.
     *
     * @param packageStatus The PackageStatus to revert to.
     */
    void revertPackageStatus(
                const lusi::package::status::PackageStatus* packageStatus);

protected:

private:

    /**
     * The Package of this Profile.
     */
    Package* mPackage;

    /**
     * The configuration with all the PackageStatus, resources and Task ids.
     */
    lusi::configuration::ConfigurationParameterMap* mConfiguration;

    /**
     * The configuration for the current PackageStatus.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    mCurrentConfiguration;



    /**
     * Returns the versions of the Package that have a saved Profile.
     *
     * @return The versions of the Package that have a saved Profile.
     */
    std::vector<std::string> getVersionsWithProfile();

    /**
     * Loads the Profile.
     * First, the Profile for the exact version of the Package is used. If it
     * can't be loaded, the greatest smaller version than the current version
     * is used. If it can't be loaded, the smaller greatest version than the
     * current version is used. It it can't be loaded, a Package without
     * version is used. If it can't be loaded, a default Profile is created.
     *
     * If the loaded Profile isn't that for the exact version of the Package, it
     * is reverted to its first PackageStatus, so the information about the Task
     * ids is kept, but all the resources are removed (as they aren't valid with
     * the new Package).
     */
    void load();

    /**
     * Loads the Profile for the greatest smaller version of the PackageId.
     *
     * @param packageVersions All the versions of the Package.
     * @return True if the Profile was loaded, false otherwise.
     */
    bool loadPreviousVersion(std::vector<std::string>& packageVersions);

    /**
     * Loads the Profile for the smaller greatest version of the PackageId.
     *
     * @param packageVersions All the versions of the Package.
     * @return True if the Profile was loaded, false otherwise.
     */
    bool loadNextVersion(const std::vector<std::string>& packageVersions);

    /**
     * Loads the Profile for a specific PackageId.
     * The current PackageStatus is that with the "selected"
     * ConfigurationParameterBool. That parameter is removed in the
     * configuration.
     *
     * @return True if the Profile was loaded, false otherwise.
     */
    bool load(const PackageId& packageId);

    /**
     * Creates a new default profile.
     * The default Profile contains an empty ConfigurationParameterMap called
     * "resources", an empty Task id and an UnknownPackageStatus.
     */
    void createDefaultProfile();

    /**
     * Saves the profile in a persistent way.
     * This method commits the changes made in the Profile to the configuration
     * file from where it was loaded (or a new one if it's a fresh profile).
     *
     * The current PackageStatus is marked in the saved file with a
     * ConfigurationParameterBool called "selected".
     */
    void save();

    /**
     * Returns the PackageStatus from its id.
     * Temporal method until redesign of PackageStatus is made.
     *
     * @param id The id to get the PackageStatus from.
     * @return The PackageStatus from its id.
     */
    const lusi::package::status::PackageStatus* getPackageStatusFromId(
                                                        const std::string& id);

    /**
     * Returns the id for the PackageStatus.
     * Temporal method until redesign of PackageStatus is made.
     *
     * @param packageStatus The PackageStatus to get its id.
     * @return The id for the PackageStatus.
     */
    std::string getIdForPackageStatus(
                    const lusi::package::status::PackageStatus* packageStatus);

    /**
     * Copy constructor disabled.
     */
    Profile(const Profile& profile);

    /**
     * Assignment disabled.
     */
    Profile& operator=(const Profile& profile);

};

}
}

#endif
