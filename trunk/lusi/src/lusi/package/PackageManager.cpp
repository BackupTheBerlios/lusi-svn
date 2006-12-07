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

#include "PackageManager.h"
#include "Package.h"
#include "PackageId.h"
#include "status/BuiltPackageStatus.h"
#include "status/ConfiguredPackageStatus.h"
#include "status/InstalledPackageStatus.h"
#include "status/PackedPackageStatus.h"
#include "status/UnknownPackageStatus.h"
#include "status/UnpackedPackageStatus.h"
#include "../configuration/ConfigurationLoader.h"
#include "../configuration/ConfigurationParameterMap.h"
#include "../configuration/ConfigurationParameterString.h"
#include "../configuration/ConfigurationPaths.h"
#include "../configuration/ConfigurationSaver.h"
#include "../util/LocalFile.h"
#include "../util/LocalUrl.h"
#include "../util/SmartPtr.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationLoader;
using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationParameterString;
using lusi::configuration::ConfigurationPaths;
using lusi::configuration::ConfigurationSaver;
using lusi::configuration::PersistenceException;
using lusi::package::status::BuiltPackageStatus;
using lusi::package::status::ConfiguredPackageStatus;
using lusi::package::status::InstalledPackageStatus;
using lusi::package::status::PackageStatus;
using lusi::package::status::PackedPackageStatus;
using lusi::package::status::UnknownPackageStatus;
using lusi::package::status::UnpackedPackageStatus;
using lusi::util::LocalFile;
using lusi::util::SmartPtr;

using namespace lusi::package;

//public:

PackageManager* PackageManager::getInstance() {
    if (sInstance == 0) {
        sInstance = new PackageManager();
    }

    return sInstance;
}

vector<string> PackageManager::getPackageNames() {
    LocalFile packagesBaseDirectory(
                    ConfigurationPaths().getPackagesBaseDirectory());

    vector<string> packagesBaseFiles = packagesBaseDirectory.list();
    vector<string> packageNames;

    for (uint i=0; i<packagesBaseFiles.size(); ++i) {
        string fileName = packagesBaseFiles[i];
        if (fileName[fileName.size() - 1] == '/') {
            packageNames.push_back(fileName.substr(0, fileName.size() - 1));
        }
    }

    return packageNames;
}

PackageManager::~PackageManager() {
    for (uint i=0; i<mPackages.size(); ++i) {
        delete mPackages[i];
    }
}

/*
inline vector<Package*> PackageManager::getPackages() {
    return mPackages;
}
*/

vector<Package*> PackageManager::getPackages(
                                        const PackageStatus* packageStatus) {
    vector<Package*> packages;

    for (uint i=0; i<mPackages.size(); ++i) {
        if (mPackages[i]->getPackageStatus() == packageStatus) {
            packages.push_back(mPackages[i]);
        }
    }

    return packages;
}

Package* PackageManager::getPackage(const PackageId& packageId) {
    for (uint i=0; i<mPackages.size(); ++i) {
        if (mPackages[i]->getPackageId() == packageId) {
            return mPackages[i];
        }
    }

    Package* package = new Package(packageId);
    mPackages.push_back(package);

    return package;
}

bool PackageManager::updatePackage(Package* package) {
    return savePackage(package);
}

//private:

PackageManager* PackageManager::sInstance = 0;

PackageManager::PackageManager() {
    load();
}

void PackageManager::load() {
    vector<string> packageNames = getPackageNames();

    for (uint i=0; i<packageNames.size(); ++i) {
        vector<string> packageVersions =
                            Package::getPackageVersions(packageNames[i]);

        for (uint j=0; j<packageVersions.size(); ++j) {
            PackageId packageId(packageNames[i], packageVersions[j]);
            loadPackage(packageId);
        }

        //Loads the package without version data, if any
        PackageId packageId(packageNames[i]);
        loadPackage(packageId);
    }
}

bool PackageManager::loadPackage(const PackageId& packageId) {
    SmartPtr<ConfigurationParameterMap> configuration;

    try {
        configuration = SmartPtr<ConfigurationParameterMap>(
            ConfigurationLoader().load(
                ConfigurationPaths().getPackageFile(packageId)));
    } catch (PersistenceException e) {
        return false;
    }

    SmartPtr<ConfigurationParameterString> statusConfiguration(
                                                configuration->get("status"));
    const PackageStatus* packageStatus = UnknownPackageStatus::getInstance();

    if (statusConfiguration->getValue() == "built") {
        packageStatus = BuiltPackageStatus::getInstance();
    } else if (statusConfiguration->getValue() == "configured") {
        packageStatus = ConfiguredPackageStatus::getInstance();
    } else if (statusConfiguration->getValue() == "installed") {
        packageStatus = InstalledPackageStatus::getInstance();
    } else if (statusConfiguration->getValue() == "packed") {
        packageStatus = PackedPackageStatus::getInstance();
    } else if (statusConfiguration->getValue() == "unknown") {
        packageStatus = UnknownPackageStatus::getInstance();
    } else if (statusConfiguration->getValue() == "unpacked") {
        packageStatus = UnpackedPackageStatus::getInstance();
    }

    Package* package = new Package(packageId, packageStatus);
    mPackages.push_back(package);

    return true;
}

//TODO The string of each status should be returned by each status. Not modified
//yet as I'm planing to modify the status mechanism.
bool PackageManager::savePackage(Package* package) {
    SmartPtr<ConfigurationParameterMap> configuration(
        new ConfigurationParameterMap("package"));

    SmartPtr<ConfigurationParameterString> statusConfiguration(
        new ConfigurationParameterString("status"));
    configuration->add(statusConfiguration);

    if (package->getPackageStatus() == BuiltPackageStatus::getInstance()) {
        statusConfiguration->setValue("built");
    } else if (package->getPackageStatus() ==
                                    ConfiguredPackageStatus::getInstance()) {
        statusConfiguration->setValue("configured");
    } else if (package->getPackageStatus() ==
                                    InstalledPackageStatus::getInstance()) {
        statusConfiguration->setValue("installed");
    } else if (package->getPackageStatus() ==
                                    PackedPackageStatus::getInstance()) {
        statusConfiguration->setValue("packed");
    } else if (package->getPackageStatus() ==
                                    UnknownPackageStatus::getInstance()) {
        statusConfiguration->setValue("unknown");
    } else if (package->getPackageStatus() ==
                                    UnpackedPackageStatus::getInstance()) {
        statusConfiguration->setValue("unpacked");
    }

    try {
        ConfigurationSaver().save(getPtr(configuration),
            ConfigurationPaths().getPackageFile(package->getPackageId()));
    } catch (PersistenceException e) {
        return false;
    }

    return true;
}
