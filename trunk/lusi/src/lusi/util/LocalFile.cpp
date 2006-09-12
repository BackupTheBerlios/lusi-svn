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

#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>

#include "LocalFile.h"
#include "Group.h"
#include "User.h"

using std::string;
using std::vector;

using namespace lusi::util;

//public:

bool LocalFile::exists(const string& path) {
    LocalUrl url(path);
    if (url.isRelative()) {
        url = LocalUrl(getCurrentWorkingDirectory());
        url.appendRelativePathToDirectory(path);
    }

    struct stat fileStat;
    if (stat(url.getPath().c_str(), &fileStat) < 0 &&
            (errno == ENOENT || errno == ENOTDIR || errno == EACCES)) {
        return false;
    }

    return true;
}

//TODO test it
std::string LocalFile::getCurrentWorkingDirectory() {
    size_t size = 100;

    while (true) {
        char* buffer = new char[size];

        if (getcwd(buffer, size) == buffer) {
            string workingDirectory = string(buffer);
            delete []buffer;

            if (LocalUrl(workingDirectory).isDirectory()) {
                return workingDirectory;
            } else {
                return workingDirectory + "/";
            }
        } else if (errno == ERANGE) {
            size *= 2;
        }

        delete []buffer;
    }
}

LocalFile::LocalFile(const LocalUrl& localUrl): mLocalUrl(localUrl) {
    if (mLocalUrl.getPath() != "" && exists()) {
        struct stat fileStat;
        //TODO check errors
        stat(getValidPath().c_str(), &fileStat);
        if (!mLocalUrl.isDirectory() && S_ISDIR(fileStat.st_mode)) {
            mLocalUrl = LocalUrl(mLocalUrl.getPath() + "/");
        }
    }
}

LocalFile::~LocalFile() {
}

bool LocalFile::exists() const {
    return exists(mLocalUrl.getPath());
}

Group LocalFile::getGroup() const{
    struct stat fileStat;
    //TODO check errors
    stat(getValidPath().c_str(), &fileStat);

    return fileStat.st_gid;
}

/*
inline const LocalUrl& LocalFile::getLocalUrl() const {
    return mLocalUrl;
}
*/

LocalUrl LocalFile::getAbsoluteLocalUrl() const {
    if (!mLocalUrl.isRelative()) {
        return mLocalUrl;
    }

    LocalUrl absoluteUrl(getCurrentWorkingDirectory());
    absoluteUrl.appendRelativePathToDirectory(mLocalUrl);
    return absoluteUrl;
}

User LocalFile::getOwner() const{
    struct stat fileStat;
    //TODO check errors
    stat(getValidPath().c_str(), &fileStat);

    return fileStat.st_uid;
}

//TODO test it
int LocalFile::getPermissions() const {
    int permissions = None;

    struct stat fileStat;
    //TODO check errors
    stat(getValidPath().c_str(), &fileStat);

    //Owner permissions
    permissions |= (fileStat.st_mode & S_IRUSR)?OwnerRead:None;
    permissions |= (fileStat.st_mode & S_IWUSR)?OwnerWrite:None;
    permissions |= (fileStat.st_mode & S_IXUSR)?OwnerExecute:None;

    //Group permissions
    permissions |= (fileStat.st_mode & S_IRGRP)?GroupRead:None;
    permissions |= (fileStat.st_mode & S_IWGRP)?GroupWrite:None;
    permissions |= (fileStat.st_mode & S_IXGRP)?GroupExecute:None;

    //Other permissions
    permissions |= (fileStat.st_mode & S_IROTH)?OtherRead:None;
    permissions |= (fileStat.st_mode & S_IWOTH)?OtherWrite:None;
    permissions |= (fileStat.st_mode & S_IXOTH)?OtherExecute:None;

    return permissions;
}

bool LocalFile::isExecutable() const {
    return hasAccess(Execute);
}

bool LocalFile::isReadable() const {
    return hasAccess(Read);
}

bool LocalFile::isWritable() const {
    return hasAccess(Write);
}

//private:

string LocalFile::getValidPath() const {
    LocalUrl localUrl = getAbsoluteLocalUrl();

    while (!exists(localUrl.getPath())) {
        localUrl = localUrl.getParent();
    }

    return localUrl.getPath();
}

//Based in the code of eaccess in GNU test command, from shell utils package
bool LocalFile::hasAccess(int mode) const {
    int permissions = getPermissions();

    User user = User::getCurrentUser();

    if (user.isRoot()) {
        //Root can read or write any file
        if (mode != Execute) {
            return true;
        }

        //Root can execute any file that has any one of the execute bits set
        if (permissions & OwnerExecute || permissions & GroupExecute ||
                permissions & OtherExecute) {
           return true;
        }
    }

    vector<Group> currentGroups = Group::getCurrentGroups();
    Group fileGroup = getGroup();

    if (getOwner() == user) {
        mode <<= 6;
    } else if (fileGroup == user.getGroup() ||
            find(currentGroups.begin(), currentGroups.end(), fileGroup) !=
                currentGroups.end()) {
        mode <<= 3;
    }

    if (permissions & mode) {
        return true;
    }

    return false;
}
