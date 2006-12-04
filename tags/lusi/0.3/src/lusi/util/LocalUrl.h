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

#ifndef LUSI_UTIL_LOCALURL_H
#define LUSI_UTIL_LOCALURL_H

#include <string>

namespace lusi {
namespace util {

/**
 * @class LocalUrl LocalUrl.h lusi/util/LocalUrl.h
 *
 * A url in a local file system.
 * This class represents urls, but only in a Linux file system. No protocol
 * (http, ftp...) is specified, as all the urls are local. The url doesn't
 * represent real files in the file system, only urls.
 *
 * Directory representations end always with "/". If the path doesn't end with
 * "/", the path represents a file. isDirectory() checks if the url is a
 * directory, and getDirectory() returns the directory in the path, if any.
 *
 * Files can have or not to have an extension. The extension are all the
 * characters after the last "." in the file name (that is, dots in the
 * directory name aren't taken into account). The extension can be got with
 * getExtension().
 *
 * Absolute urls start with "/", which designs the root directory, while
 * relative urls start with any other character. Self and parent directories
 * syntax ("./" and "../") can also be used. isRelative() checks if the url is
 * relative.
 *
 * LocalUrls are cleaned of self and parent directories syntax as much as
 * possible. For example, when creating a LocalUrl using "/../usr/" only "/usr/"
 * would be stored. However, "../etc/" would be stored as "../etc/", as the
 * leading parent reference can't be resolved.
 * Also, when appending relative LocalUrl to another LocalUrl which represents a
 * directory, the relative path appended is cleaned.
 *
 * The parent directory can be got using getParent().
 */
class LocalUrl {
public:

    /**
     * Creates a new LocalUrl.
     * The path stored is cleaned.
     *
     * @param path The path, empty by default.
     * @see cleanPath(std::string)
     */
    LocalUrl(const std::string& path = "");

    /**
     * Copy constructor.
     *
     * @param localUrl The LocalUrl to copy.
     */
    LocalUrl(const LocalUrl& localUrl);

    /**
     * Destroys this LocalUrl.
     */
    virtual ~LocalUrl();

    /**
     * Returns true if the url represents a directory, false if it represents a
     * file.
     * A url is a directory if the last character in the path is a "/".
     *
     * @return True if the url represents a directory, false if it represents a
     * file.
     */
    bool isDirectory() const;

    /**
     * Returns true if the url is relative, false if it's absolute.
     * A url is relative if the first character in the path isn't "/".
     *
     * @return True if the url is relative, false if it's absolute.
     */
    bool isRelative() const;

    /**
     * Returns the directory, if any.
     * The directory is all the path before the last "/". The directory returned
     * also includes the last "/". If there's no directory, an empty string is
     * returned.
     *
     * @return The directory, if any.
     */
    std::string getDirectory() const;

    /**
     * Returns the extension of the file, if any.
     * The extension returned doesn't include the ".". An empty string can be
     * returned both if the file has no extension, or if the url represents a
     * directory.
     *
     * @return The extension of the file, if any.
     */
    std::string getExtension() const;

    /**
     * Returns the file name, if any.
     * The file name is all the path after the last "/". The file name returned
     * doesn't include the last "/". If there's no file name, an empty string is
     * returned.
     *
     * @return The file name, if any.
     */
    std::string getFileName() const;

    /**
     * Returns the path to the parent directory.
     * The directory returned also includes the last "/".
     *
     * If this LocalUrl is a file, the returned path will be equal to the path
     * returned by directory (provided it's not empty. In that case, "../" is
     * returned). If this LocalUrl is a directory, the returned path will be
     * the parent directory of this directory.
     *
     * If the current directory is the root directory, this returns the root
     * directory itself.
     * Also, if the current directory is the base of a relative directory which
     * can't be resolved, the current directory itself is returned (for example,
     * "../").
     *
     * @return The path to the parent directory.
     */
    std::string getParent() const;

    /**
     * Returns the full path.
     *
     * @return The full path.
     */
    std::string getPath() const {
        return mPath;
    }

    /**
     * Appends a relative path to the end of this directory url.
     * If this LocalUrl doesn't represent a directory or the LocalUrl to add
     * isn't relative, nothing is done.
     * Once the relative path is added to the directory, the path is cleaned.
     *
     * @param localUrl The relative path to append.
     * @see cleanPath(std::string)
     */
    void appendRelativePathToDirectory(const LocalUrl& localUrl);

    /**
     * Assignment operator.
     *
     * @param localUrl The LocalUrl to assign.
     * @return This LocalUrl.
     */
    LocalUrl& operator=(const LocalUrl& localUrl);

    /**
     * Checks if this LocalUrl is equal to the one given.
     * They're equal if their path is equal.
     *
     * @param localUrl The localUrl to compare to.
     * @return True if they are equal, false otherwise.
     */
    bool operator==(const LocalUrl& localUrl) const;

    /**
     * Checks if this LocalUrl is different to the one given.
     * They're different if their path is different.
     *
     * @param localUrl The localUrl to compare to.
     * @return True if they are different, false otherwise.
     */
    bool operator!=(const LocalUrl& localUrl) const;

private:

    /**
     * The path.
     */
    std::string mPath;



    /**
     * Cleans the path as much as possible of self and parent directories
     * syntax.
     * References to self ("./") are removed, and parent directories are solved,
     * if possible. Root directory is a special case, as its parent is itself.
     *
     * For example, once cleaned, "/../usr/" becomes "/usr/", "./etc/fstab"
     * becomes "etc/fstab" and "usr/bin/../lib/" becomes "usr/lib/". However,
     * "../etc/" becomes "../etc/", as the leading parent reference can't be
     * resolved. The same goes for "usr/../../etc/ which becomes "../etc/" (note
     * that there's no leading "/" in "usr/").
     *
     * @param path The path to be cleaned.
     * @return The cleaned path.
     */
    std::string cleanPath(const std::string& path);

};

}
}

#endif
