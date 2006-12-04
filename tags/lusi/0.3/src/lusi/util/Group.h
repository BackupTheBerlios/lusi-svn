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

#ifndef LUSI_UTIL_GROUP_H
#define LUSI_UTIL_GROUP_H

#include <string>
#include <vector>

namespace lusi {
namespace util {

/**
 * @class Group Group.h lusi/util/Group.h
 *
 * Represents a group of the file system.
 * This is only a wrapper class for system calls to get (but not
 * change) information about system groups, using an object oriented approach
 * and abstracting the interaction with the system.
 *
 * Each group stores its id and its name. The list of users of this group is
 * not stored.
 *
 * Groups are created using their group id or their name. When creating a group,
 * the parameter not set is got from the system. If a group doesn't exist, the
 * id and name are set to -1 and "".
 *
 * The supplementary groups of the user currently executing LUSI can be got
 * with getCurrentGroups.
 *
 * This class should work on any POSIX compliant system. It uses getgroups,
 * getgrgid and getgrnam system calls.
 */
class Group {
public:

    /**
     * Returns the current suplmenetary groups of the process executing LUSI.
     *
     * @return The current suplmenetary groups of the process executing LUSI.
     */
    static std::vector<Group> getCurrentGroups();

    /**
     * Creates a new group from the specified group id.
     * Group name is got from the system.
     *
     * @param id The id of the group to create.
     */
    Group(int id = -1);

    /**
     * Creates a new group from the specified group name.
     * Group id is got from the system.
     *
     * @param name The name of the group to create.
     */
    Group(const std::string& name);

    /**
     * Copy constructor.
     *
     * @param group The group to copy.
     */
    Group(const Group& group);

    /**
     * Destroys this Group.
     */
    virtual ~Group();

    /**
     * Returns true if the group exists in the system, false otherwise.
     *
     * @return True if the group exists in the system, false otherwise.
     */
    bool exists() const {
        return mId != -1;
    }

    /**
     * Returns the id of this group.
     *
     * @return The id of this group.
     */
    int getId() const {
        return mId;
    }

    /**
     * Returns the name of this group.
     *
     * @return The name of this group.
     */
    const std::string& getName() const {
        return mName;
    }

    /**
     * Returns true if the group is root, false otherwise.
     *
     * @return True if the group is root, false otherwise.
     */
    bool isRoot() const {
        return mId == 0;
    }

    /**
     * Assignment operator.
     *
     * @param group The group to assign.
     * @return A reference to this Group.
     */
    Group& operator=(const Group& group);

    /**
     * Returns true if the group is equal to this group, false otherwise.
     *
     * @return True if the group is equal to this group, false otherwise.
     */
    bool operator==(const Group& group) const;

    /**
     * Returns true if the user is different to this user, false otherwise.
     *
     * @return True if the user is different to this user, false otherwise.
     */
    bool operator!=(const Group& group) const;

private:

    /**
     * The id of the group.
     */
    int mId;

    /**
     * The name of the group.
     */
    std::string mName;



    /**
     * Initializes this Group using the information in the group structure
     * provided.
     * If the structure is NULL, the group doesn't exist. Non existent groups
     * have -1 as id and "" as name.
     *
     * @param groupData The group information to initialize this Group.
     */
    void init(struct group* groupData);

};

}
}

#endif
