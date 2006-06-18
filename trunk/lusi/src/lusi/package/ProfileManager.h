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

#ifndef LUSI_PACKAGE_PROFILEMANAGER_H
#define LUSI_PACKAGE_PROFILEMANAGER_H

namespace lusi {
namespace package {
    class PackageId;
    class Profile;
}
}

namespace lusi {
namespace package {

/**
 * @class ProfileManager ProfileManager.h lusi/package/ProfileManager.h
 *
 * Manager for Profiles.
 * ProfileManager handles the creation of Profiles. getProfile(PackageId)
 * method returns a specific Profile depending on the PackageId used.
 *
 * This class follows the Singleton Design Pattern. Only one instance is
 * created, and it can be got with getInstance() method.
 */
class ProfileManager {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static ProfileManager* getInstance();

    /**
     * Destroys this ProfileManager.
     */
    virtual ~ProfileManager();

    /**
     * Returns the Profile for the specified Package using its PackageId.
     * If the version of the PackageId wasn't used before, the Profile for the
     * newest version available is used.
     * If the PackageId has an unspecified version, the Profile will contain
     * the TaskConfiguration for all the versions of the Package.
     * If there's no Profile for that Package, a new empty Profile is returned.
     *
     * The packageId must be linked to a valid Package.
     *
     * @param packageId The PackageId of the Package.
     * @return The Profile for the specified Package.
     */
    Profile* getProfile(const PackageId* packageId);

protected:

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static ProfileManager* sInstance;




    /**
     * Creates a new ProfileManager.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    ProfileManager();

    /**
     * Copy constructor disabled.
     */
    ProfileManager(const ProfileManager &profileManager);

    /**
     * Assignment disabled.
     */
    ProfileManager& operator=(const ProfileManager &profileManager);

};

}
}

#endif
