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

#include "LocalUrl.h"

using std::string;

using namespace lusi::util;

LocalUrl::LocalUrl(const string& path) {
    mPath = cleanPath(path);
}

LocalUrl::LocalUrl(const LocalUrl& localUrl) {
    mPath = localUrl.mPath;
}

LocalUrl::~LocalUrl() {
}

bool LocalUrl::isDirectory() const {
    return mPath[mPath.size() - 1] == '/';
}

bool LocalUrl::isRelative() const {
    return mPath[0] != '/';
}

std::string LocalUrl::getDirectory() const {
    string::size_type separatorPosition = mPath.rfind("/");
    if (separatorPosition == string::npos) {
        return string("");
    }

    return mPath.substr(0, separatorPosition + 1);
}

std::string LocalUrl::getExtension() const {
    string::size_type dotPosition = mPath.rfind(".");

    if (dotPosition == string::npos || dotPosition == 0) {
        return string("");
    }

    string::size_type separatorPosition = mPath.rfind("/");

    if (separatorPosition != string::npos &&
            (separatorPosition > dotPosition ||
             dotPosition == separatorPosition + 1)) {
        return string("");
    }

    return mPath.substr(dotPosition+1);
}

std::string LocalUrl::getFileName() const {
    string::size_type separatorPosition = mPath.rfind("/");
    if (separatorPosition == string::npos) {
        return mPath;
    }

    return mPath.substr(separatorPosition + 1);
}

/*
inline std::string getPath() const {
    return mPath;
}
*/

void LocalUrl::appendRelativePathToDirectory(const LocalUrl& localUrl) {
    if (!isDirectory() || !localUrl.isRelative()) {
        return;
    }

    mPath = cleanPath(mPath + localUrl.mPath);
}

LocalUrl& LocalUrl::operator=(const LocalUrl& localUrl) {
    if (this != &localUrl) {
        mPath = localUrl.mPath;
    }

    return *this;
}

bool LocalUrl::operator==(const LocalUrl& localUrl) {
    return mPath == localUrl.mPath;
}

bool LocalUrl::operator!=(const LocalUrl& localUrl) {
    return mPath != localUrl.mPath;
}

string LocalUrl::cleanPath(const string& path) {
    string cleanedPath("");

    string::size_type separatorPosition = 0;
    string::size_type currentPosition = 0;
    int length = 0;
    int parentDirectories = 0;
    while ((separatorPosition = path.find("/", currentPosition))
                        != string::npos) {
        length = separatorPosition - currentPosition + 1;

        if (length == 3 && path[currentPosition] == '.' &&
                           path[currentPosition + 1] == '.') {
            if (cleanedPath.size() != 1 || cleanedPath[0] != '/') {
                //Handle parent directory, only if we're not in root
                string::size_type thisSeparatorPosition =
                                cleanedPath.rfind("/", cleanedPath.size() - 2);
                string::size_type thisLength = (cleanedPath.size() - 1 ) -
                                                        thisSeparatorPosition;

                if (parentDirectories > 0) {
                    cleanedPath.erase(thisSeparatorPosition + 1, thisLength);
                    parentDirectories--;
                } else {
                    cleanedPath += "../";
                }
            }
        } else if (length == 2 && path[currentPosition] == '.') {
            //Ignore self
        } else {
            //Otherwise, add the current directory
            cleanedPath += path.substr(currentPosition, length);
            if (cleanedPath != "/") {
                parentDirectories++;
            }
        }

        currentPosition = separatorPosition + 1;
    }

    cleanedPath += path.substr(currentPosition);

    return cleanedPath;
}
