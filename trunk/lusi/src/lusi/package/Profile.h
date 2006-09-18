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

namespace lusi {
namespace package {
    class Package;
}
}

namespace lusi {
namespace task {
    class Task;
    class TaskConfiguration;
}
}

namespace lusi {
namespace package {

/**
 * @class Profile Profile.h lusi/package/Profile.h
 *
 * Profile contains all the information about the Task executed over a Package,
 * including order of execution and configuration of each Task.
 * Based on this information and the status of the Package, a Profile can
 * suggest a Task to be executed. The suggested Task isn't tested to verify if
 * it can be executed.
 *
 * New TaskConfigurations can be added using
 * addTaskConfiguration(TaskConfiguration). The order used to add them is kept
 * for future use. Added TaskConfigurations lifespan is handled by Profile.
 *
 * Profiles can be saved in a persistent way, so they can be later retrieved
 * for future use. Due to this, Profiles should be got through
 * ProfileManager::getProfile(PackageId*). This method takes care of adding
 * the needed TaskConfigurations.
 *
 * @see ProfileManager
 */
class Profile {
public:

    /**
     * Creates a new Profile of the specified Package.
     * ProfileManager::getProfile(PackageId*) should be used instead of
     * creating a new Profile explicitly.
     *
     * @param package The Package of this Profile.
     */
    explicit Profile(Package* package);

    /**
     * Destroys this profile.
     */
    virtual ~Profile();

    /**
     * Adds a new TaskConfiguration to the Profile.
     * The order used to add the TaskConfigurations is taken into account. Once
     * added, the TaskConfiguration lifespan is handled by this Profile (it's
     * destroyed when this Profile is destroyed).
     *
     * @param taskConfiguration The TaskConfiguration to add.
     */
    void addTaskConfiguration(
                lusi::task::TaskConfiguration* taskConfiguration);

    /**
     * Returns the Package of this Profile.
     *
     * @return The Package of this Profile.
     */
    Package* getPackage() {
        return mPackage;
    }

    /**
     * Returns a suggested Task to be executed based on the status of the
     * Package.
     * The TaskConfiguration selected is the newest version of the one for the
     * Task that needs the current PackageStatus.
     * If there's no suitable Task to be executed, a null pointer is returned.
     *
     * @return The suggested Task to execute.
     */
    lusi::task::Task* getTask();

    /**
     * Saves the profile in a persistent way.
     * This method commits the changes made in the Profile to the configuration
     * file from where it was loaded (or a new one if it's a fresh profile).
     */
    void save();

protected:

private:

    /**
     * The Package of this Profile.
     */
    Package* mPackage;




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
