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

#ifndef LUSI_UTIL_LOCALFILE_H
#define LUSI_UTIL_LOCALFILE_H

#include <lusi/util/LocalUrl.h>

namespace lusi {
namespace util {
class Group;
class User;
}
}

namespace lusi {
namespace util {

/**
 * @class LocalFile LocalFile.h lusi/util/LocalFile.h
 *
 * A file or directory in the local file system.
 * LocalFile can represent both existent files and non existent files. A file
 * may exist in the file system, but if it can't be accesed due to lack of
 * permissions, it's considered to be non existent.
 *
 * If a file exists, all the operations refer to that file. However, if the file
 * doesn't exist, most of the operations (get user, permissions...) refer to the
 * first parent in the file path that exists.
 *
 * The file is identified by its url. Relative urls aren't solved when creating
 * the file. The stored url is kept relative, although all the operations with
 * the file solve the relative url using the current working directory, so all
 * the operations work with absolute url, no matter how if the real stored url
 * is absolute or relative.
 *
 * The url can be got with getLocalUrl() and getAbsoluteLocalUrl(). The url
 * returned may be different of the url used when creating the file if that url
 * had a file syntax and in the file system it was a directory. In that case,
 * the url stored has an ending "/".
 *
 * A LocalFile can be queried about its user, group and permissions using the
 * appropiate get methods. Also, it can be checked if the user currently running
 * LUSI can read, write and execute it using isReadable(), isWritable() and
 * isExecutable().
 *
 * Class methods can be used to know if a path to a file exists with
 * exists(const string&), and also the current working directory with
 * getCurrentWorkingDirectory().
 *
 * This class should work on any POSIX system. The functions used are stat and
 * getcwd, and the macro S_ISDIR.
 */
class LocalFile {
public:

    /**
     * Enumeration with all the possible permissions of a file.
     */
    enum Permissions {
        OwnerRead = 0400,
        OwnerWrite = 0200,
        OwnerExecute = 0100,
        GroupRead = 0040,
        GroupWrite = 0020,
        GroupExecute = 0010,
        OtherRead = 0004,
        OtherWrite = 0002,
        OtherExecute = 0001,
        None = 0000
    };

    /**
     * Returns true if this file exists in the system, false otherwise.
     * A file that can't be accessed by the current user, even when it may
     * exist, is also reported as non existent, as there is no way to know that
     * it exists.
     *
     * @return True if this file exists in the system, false otherwise.
     */
    static bool exists(const std::string& path);

    /**
     * Returns the path of the current working directory.
     * The path contains the ending "/".
     *
     * @return The path of the current working directory.
     */
    static std::string getCurrentWorkingDirectory();

    /**
     * Creates a new LocalFile.
     * If the local url represents a file (there is no ending "/"), but in the
     * file system it is an existent directory, an ending "/" is added to the
     * stored url.
     *
     * @param localUrl The url to the file.
     */
    LocalFile(const LocalUrl& localUrl);

    /**
     * Destroys this LocalFile.
     */
    virtual ~LocalFile();

    /**
     * Returns true if this file exists in the system, false otherwise.
     * This is only an overloaded version of exists(const string&) provided for
     * convenience.
     *
     * @return True if this file exists in the system, false otherwise.
     * @see exists(const string&)
     */
    bool exists() const;

    /**
     * Returns the group of this file.
     * If the file isn't valid, the file used is the first valid parent of the
     * file.
     *
     * @return The group of this file.
     */
    Group getGroup() const;

    /**
     * Returns the url to this file in the local file system.
     * The url is the same used when creating the file. That is, relative urls
     * aren't resolved.
     * To always get the absolute url, use getAbsoluteLocalUrl.
     *
     * @return The url to this file in the local file system.
     * @see getAbsoluteLocalUrl()
     */
    const LocalUrl& getLocalUrl() const {
        return mLocalUrl;
    }

    /**
     * Returns the absolute url to this file in the local file system.
     * If the local url used when creating the file was absolute, that url is
     * returned. If it was relative, the returned url is the url of the file
     * appended to the current working directory.
     * To get the url used when creating the file, use getLocalUrl.
     *
     * @return The absolute url to this file in the local file system.
     * @see getLocalUrl()
     */
    LocalUrl getAbsoluteLocalUrl() const;

    /**
     * Returns the owner of this file.
     * If the file isn't valid, the file used is the first valid parent of the
     * file.
     *
     * @return The owner of this file.
     */
    User getOwner() const;

    /**
     * Returns the permissions of this file.
     * If the file isn't valid, the file used is the first valid parent of the
     * file.
     * The int returned is a bit OR-ed int with the different permissions of the
     * file. To know if it has a permission, use a bit AND operation like this:
     * value & Permissions::type. If the permission is set, the expression will
     * be != 0. If it is unset, it will be 0.
     *
     * @return The permissions of this file.
     * @see Permissions
     */
    int getPermissions() const;

    /**
     * Returns true if this file is executable by the current user, false
     * otherwise.
     * If the file isn't valid, the file used is the first valid parent of the
     * file.
     *
     * @return True if this file is executable by the current user, false
     *         otherwise.
     */
    bool isExecutable() const;

    /**
     * Returns true if this file is readable by the current user, false
     * otherwise.
     * If the file isn't valid, the file used is the first valid parent of the
     * file.
     *
     * @return True if this file is readable by the current user, false
     *         otherwise.
     */
    bool isReadable() const;

    /**
     * Returns true if this file is writable by the current user, false
     * otherwise.
     * If the file isn't valid, the file used is the first valid parent of the
     * file.
     *
     * @return True if this file is writable by the current user, false
     *         otherwise.
     */
    bool isWritable() const;

private:

    /**
     * Permissions used as mode in hasAccess private method.
     */
    enum PrivatePermissions {
        Read = 0004,
        Write = 0002,
        Execute = 0001
    };

    /**
     * The url to this file in the local file system.
     */
    LocalUrl mLocalUrl;



    /**
     * Returns a valid path to this file.
     * If the file exists and can be accessed, the path to the file is returned.
     * If it doesn't exist or can't be accessed, the path to the first parent
     * directory that exists or can be accessed is returned.
     *
     * @return A valid path to this file.
     */
    std::string getValidPath() const;

    /**
     * Returns true if the current user has the specified access to this file,
     * false otherwise.
     * It is checked if the current user is the owner of the file. In that case,
     * the permissions of the file for the user are checked.
     * Else, it is checked if the group of the current user or any of the
     * supplementary groups of the process are the group of the file. In that
     * case, the permissions of the file for the group are checked.
     * Else, the permissions of the file for others are checked.
     * The mode must be specified using the values for "Other" permissions.
     *
     * Root user is a special case. It can read or write any file, no matter
     * what the permissions of the file are. It also can execute any file,
     * provided at least one of the execution bits is set.
     *
     * The access mode to check must be an or combination of the literals in
     * PrivatePermissions enumeration.
     *
     * @param mode The access mode to check.
     * @return True if the current user has the specified access to this file,
     *         false otherwise.
     */
    bool LocalFile::hasAccess(int mode) const;

};

}
}

#endif
