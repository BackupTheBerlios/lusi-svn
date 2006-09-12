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

#ifndef LUSI_UTIL_USER_H
#define LUSI_UTIL_USER_H

#include <string>

#include <lusi/util/Group.h>

namespace lusi {
namespace util {

/**
 * @class User User.h lusi/util/User.h
 *
 * Represents a user of the file system.
 * This is only a wrapper class for system calls to get (but not
 * change) information about system users, using an object oriented approach
 * and abstracting the interaction with the system.
 *
 * Each user stores its id, its name and the primary group it belongs to.
 *
 * Users are created using their user id or their name. When creating a user,
 * the parameters not set are got from the system. If a user doesn't exist, the
 * id and name are set to -1 and "", and the group to the invalid group (-1).
 *
 * The user currently executing LUSI can be got with getCurrentUser.
 *
 * This class should work on any POSIX compliant system. It uses geteuid,
 * getpwuid and getpwnam system calls.
 */
class User {
public:

    /**
     * Returns the current user executing LUSI.
     *
     * @return The current user executing LUSI.
     */
    static User getCurrentUser();

    /**
     * Creates a new user from the specified user id.
     * User name and groups are got from the system.
     *
     * @param id The id of the user to create.
     */
    User(int id = -1);

    /**
     * Creates a new user from the specified user name.
     * User id and groups are got from the system.
     *
     * @param name The name of the user to create.
     */
    User(const std::string& name);

    /**
     * Copy constructor.
     *
     * @param user The user to copy.
     */
    User(const User& user);

    /**
     * Destroys this User.
     */
    virtual ~User();

    /**
     * Returns true if the user exists in the system, false otherwise.
     *
     * @return True if the user exists in the system, false otherwise.
     */
    bool exists() const {
        return mId != -1;
    }

    /**
     * Returns the group of the user.
     *
     * @return The group of the user.
     */
    const Group& getGroup() {
        return mGroup;
    }

    /**
     * Returns the id of this user.
     *
     * @return The id of this user.
     */
    int getId() const {
        return mId;
    }

    /**
     * Returns the name of this user.
     *
     * @return The name of this user.
     */
    const std::string& getName() const {
        return mName;
    }

    /**
     * Returns true if the user is root, false otherwise.
     *
     * @return True if the user is root, false otherwise.
     */
    bool isRoot() const {
        return mId == 0;
    }

    /**
     * Assignment operator.
     *
     * @param user The user to assign.
     * @return A reference to this User.
     */
    User& operator=(const User& user);

    /**
     * Returns true if the user is equal to this user, false otherwise.
     *
     * @return True if the user is equal to this user, false otherwise.
     */
    bool operator==(const User& user) const;

    /**
     * Returns true if the user is different to this user, false otherwise.
     *
     * @return True if the user is different to this user, false otherwise.
     */
    bool operator!=(const User& user) const;

private:

    /**
     * The id of the user.
     */
    int mId;

    /**
     * The name of the user.
     */
    std::string mName;

    /**
     * The group of the user.
     */
    Group mGroup;



    /**
     * Initializes this User using the information in the passwd structure
     * provided.
     * If the structure is NULL, the user doesn't exist. Non existent users have
     * -1 as id and "" as name.
     *
     * @param userData The user information to initialize this User.
     */
    void init(struct passwd* userData);

};

}
}

#endif
