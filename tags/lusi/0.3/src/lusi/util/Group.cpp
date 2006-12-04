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

#include <grp.h>

#include "Group.h"

using std::string;
using std::vector;

using namespace lusi::util;

//public:

vector<Group> Group::getCurrentGroups() {
    vector<Group> groups;

    int numberOfGroups = getgroups(0, NULL);
    gid_t* groupIds = new gid_t[numberOfGroups];
    getgroups(numberOfGroups, groupIds);

    for (int i=0; i<numberOfGroups; ++i) {
        groups.push_back(Group(groupIds[i]));
    }

    delete []groupIds;

    return groups;
}

Group::Group(int id /*= -1*/) {
    init(getgrgid(id));
}

Group::Group(const std::string& name) {
    init(getgrnam(name.c_str()));
}

Group::Group(const Group& group) {
    mId = group.mId;
    mName = group.mName;
}

Group::~Group() {
}

/*
inline bool Group::exists() const {
    return mId != -1;
}

inline int Group::getId() const {
    return mId;
}

inline const string& Group::getName() const {
    return mName;
}

inline bool Group::isRoot() const {
    return mId == 0;
}
*/

Group& Group::operator=(const Group& group) {
    if (&group == this) {
        return *this;
    }

    mId = group.mId;
    mName = group.mName;

    return *this;
}

bool Group::operator==(const Group& group) const {
    return mId == group.mId && mName == group.mName;
}

bool Group::operator!=(const Group& group) const {
    return !(*this == group);
}

//private:

void Group::init(struct group* groupData) {
    if (groupData == NULL) {
        mId = -1;
        mName = "";
    } else {
        mId = groupData->gr_gid;
        mName = groupData->gr_name;
    }
}
