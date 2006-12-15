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

#include "ConfigurationPaths.h"
#include "../package/Package.h"
#include "../package/PackageId.h"
#include "../task/Task.h"
#include "../util/User.h"

using std::string;

using lusi::package::PackageId;
using lusi::task::Task;
using lusi::util::User;

using namespace lusi::configuration;

//public:

ConfigurationPaths::ConfigurationPaths(
                            const User& user /*= User::getCurrentUser()*/) {
    mBaseDirectory = user.getHome() + ".lusi/";
}

ConfigurationPaths::~ConfigurationPaths() {
}

string ConfigurationPaths::getBaseDirectory() {
    return mBaseDirectory;
}

string ConfigurationPaths::getPackagesBaseDirectory() {
    return mBaseDirectory + "package/";
}

string ConfigurationPaths::getPackageDirectory(const PackageId& packageId) {
    string packageDirectory = getPackagesBaseDirectory() + packageId.getName() +
                                                                            '/';

    if (packageId.getVersion() != "") {
        packageDirectory += packageId.getVersion() + '/';
    }

    return packageDirectory;
}

string ConfigurationPaths::getPackageFile(const PackageId& packageId) {
    return getPackageDirectory(packageId) + "package-data.xml";
}

string ConfigurationPaths::getProfileFile(const PackageId& packageId) {
    return getPackageDirectory(packageId) + "profile.xml";
}

string ConfigurationPaths::getTaskFile(const string& taskId,
                                       const PackageId& packageId) {
    return getPackageDirectory(packageId) + taskId + ".xml";
}
