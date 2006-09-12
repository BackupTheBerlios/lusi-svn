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

#include <pwd.h>

#include "User.h"

using std::string;

using namespace lusi::util;

//public:

User User::getCurrentUser() {
    return User(geteuid());
}

User::User(int id /*= -1*/) {
    init(getpwuid(id));
}

User::User(const std::string& name) {
    init(getpwnam(name.c_str()));
}

User::User(const User& user) {
    mId = user.mId;
    mName = user.mName;
    mGroup = user.mGroup;
}

User::~User() {
}

/*
inline bool User::exists() const {
    return mId != -1;
}

inline const Group& User::getGroup() {
    return mGroup;
}

inline int User::getId() const {
    return mId;
}

inline const string& User::getName() const {
    return mName;
}

inline bool User::isRoot() const {
    return mId == 0;
}
*/

User& User::operator=(const User& user) {
    if (&user == this) {
        return *this;
    }

    mId = user.mId;
    mName = user.mName;
    mGroup = user.mGroup;

    return *this;
}

bool User::operator==(const User& user) const {
    return mId == user.mId && mName == user.mName && mGroup == user.mGroup;
}

bool User::operator!=(const User& user) const {
    return !(*this == user);
}

//private:

void User::init(struct passwd* userData) {
    if (userData == NULL) {
        mId = -1;
        mName = "";
        mGroup = Group(-1);
    } else {
        mId = userData->pw_uid;
        mName = userData->pw_name;
        mGroup = Group(userData->pw_gid);
    }
}
