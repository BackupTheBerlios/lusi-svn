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

#include "Profile.h"
#include "Package.h"
#include "PackageManager.h"
#include "status/BuiltPackageStatus.h"
#include "status/ConfiguredPackageStatus.h"
#include "status/InstalledPackageStatus.h"
#include "status/PackedPackageStatus.h"
#include "status/UnknownPackageStatus.h"
#include "status/UnpackedPackageStatus.h"
#include "../configuration/ConfigurationCloner.h"
#include "../configuration/ConfigurationLoader.h"
#include "../configuration/ConfigurationParameterBool.h"
#include "../configuration/ConfigurationParameterMap.h"
#include "../configuration/ConfigurationParameterString.h"
#include "../configuration/ConfigurationPaths.h"
#include "../configuration/ConfigurationSaver.h"
#include "../util/LocalFile.h"
#include "../util/LocalUrl.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationCloner;
using lusi::configuration::ConfigurationLoader;
using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterBool;
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
using lusi::task::Task;
using lusi::util::LocalFile;
using lusi::util::SmartPtr;

using namespace lusi::package;

//public:

Profile::Profile(Package* package) {
    mPackage = package;
    mConfiguration = new ConfigurationParameterMap("profile");

    load();
}

Profile::~Profile() {
    delete mConfiguration;
}

/*
inline Package* Profile::getPackage() {
    return mPackage;
}
*/

vector<const PackageStatus*> Profile::getAllPackageStatus() {
    vector<const PackageStatus*> packageStatus;
    vector< SmartPtr<ConfigurationParameter> > configurations =
                                                    mConfiguration->getAll();

    typedef vector< SmartPtr<ConfigurationParameter> >::const_iterator
    Iterator;

    Iterator it = configurations.begin();
    for (; (*it) != mCurrentConfiguration; ++it) {
        packageStatus.push_back(getPackageStatusFromId((*it)->getId()));
    }
    packageStatus.push_back(getPackageStatusFromId((*it)->getId()));

    return packageStatus;
}

const PackageStatus* Profile::getPackageStatus() {
    return getPackageStatusFromId(mCurrentConfiguration->getId());
}

SmartPtr<ConfigurationParameterMap> Profile::getResources() {
    return mCurrentConfiguration->get("resources");
}

string Profile::getTaskId() {
    return ((SmartPtr<ConfigurationParameterString>)
                mCurrentConfiguration->get("taskId"))->getValue();
}

void Profile::setResources(SmartPtr<ConfigurationParameterMap> resources) {
    mCurrentConfiguration->remove("resources");

    SmartPtr<ConfigurationParameterMap> resourcesCopy(
        ConfigurationCloner().clone(getPtr(resources)));
    mCurrentConfiguration->add(resourcesCopy);

    save();
}

void Profile::setTaskId(const string& taskId) {
    ((SmartPtr<ConfigurationParameterString>)
                mCurrentConfiguration->get("taskId"))->setValue(taskId);

    save();
}

void Profile::addPackageStatus(const PackageStatus* packageStatus) {
    vector< SmartPtr<ConfigurationParameter> > configurations =
        mConfiguration->getAll();

    uint i = 1;
    while (i < configurations.size() &&
            configurations[i-1] != mCurrentConfiguration) {
        ++i;
    }

    string packageStatusId = getIdForPackageStatus(packageStatus);

    if (i < configurations.size() &&
            configurations[i]->getId() == packageStatusId) {
        mCurrentConfiguration = configurations[i];
        save();

        return;
    }

    if (i < configurations.size() &&
            configurations[i]->getId() != packageStatusId) {
        for (; i < configurations.size(); ++i) {
            mConfiguration->remove(configurations[i]->getId());
        }
    }

    mCurrentConfiguration = SmartPtr<ConfigurationParameterMap>(
        new ConfigurationParameterMap(getIdForPackageStatus(packageStatus)));
    mCurrentConfiguration->add(SmartPtr<ConfigurationParameterString>(
                            new ConfigurationParameterString("taskId", "")));
    mCurrentConfiguration->add(SmartPtr<ConfigurationParameterMap>(
                            new ConfigurationParameterMap("resources")));

    mConfiguration->add(mCurrentConfiguration);

    save();
}

void Profile::revertPackageStatus(const PackageStatus* packageStatus) {
    vector< SmartPtr<ConfigurationParameter> > configurations =
        mConfiguration->getAll();
    string packageStatusId = getIdForPackageStatus(packageStatus);

    uint i = 0;
    while (i < configurations.size() &&
            configurations[i]->getId() != mCurrentConfiguration->getId() &&
            configurations[i]->getId() != packageStatusId) {
        ++i;
    }

    if (configurations[i]->getId() != packageStatusId) {
        return;
    }

    mCurrentConfiguration = configurations[i];

    for (++i; i < configurations.size(); ++i) {
        SmartPtr<ConfigurationParameterMap> configuration(
                                                    configurations[i]);
        configuration->remove("resources");
        configuration->add(SmartPtr<ConfigurationParameterMap>(
                            new ConfigurationParameterMap("resources")));
    }

    mPackage->revertPackageStatus(packageStatus);

    save();
}

//private:

vector<string> Profile::getVersionsWithProfile() {
    ConfigurationPaths configurationPaths;
    PackageId packageIdNoVersion(mPackage->getPackageId().getName());
    LocalFile packageDirectory(
                configurationPaths.getPackageDirectory(packageIdNoVersion));

    vector<string> packageFiles = packageDirectory.list();
    vector<string> packageVersions;

    for (uint i=0; i<packageFiles.size(); ++i) {
        string fileName = packageFiles[i];
        if (fileName[fileName.size() - 1] == '/') {
            PackageId packageId(mPackage->getPackageId().getName(), fileName);
            if (LocalFile(configurationPaths.getProfileFile(packageId)).
                                                                    exists()) {
                packageVersions.push_back(
                        fileName.substr(0, fileName.size() - 1));
            }
        }
    }

    return packageVersions;
}

//TODO refactor with code in TaskConfiguration
void Profile::load() {
    PackageId packageId = mPackage->getPackageId();

    if (packageId.getVersion() != "") {
        if (load(packageId)) {
            return;
        }

        vector<string> packageVersions = getVersionsWithProfile();
        packageVersions.push_back(packageId.getVersion());
        sort(packageVersions.begin(), packageVersions.end(),
             versionsWeakOrdering);

        if (loadPreviousVersion(packageVersions)) {
            revertPackageStatus(getAllPackageStatus()[0]);
            return;
        }

        if (loadNextVersion(packageVersions)) {
            revertPackageStatus(getAllPackageStatus()[0]);
            return;
        }
    }

    PackageId noVersionPackageId(packageId.getName());
    if (load(noVersionPackageId)) {
        revertPackageStatus(getAllPackageStatus()[0]);
        return;
    }

    createDefaultProfile();
}

bool Profile::loadPreviousVersion(vector<string>& packageVersions) {
    PackageId packageId = mPackage->getPackageId();
    string previousVersion;

    //Versions prior to 4.1 of libstdc++ don't compile if the reverse
    //iterator is set as const.
    //See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=11729
    vector<string>::reverse_iterator rIt = find(packageVersions.rbegin(),
                                                packageVersions.rend(),
                                                packageId.getVersion());
    if ((++rIt) != packageVersions.rend()) {
        previousVersion = *rIt;
    }

    if (previousVersion != "" &&
            previousVersion != packageId.getVersion()) {
        PackageId previousPackageId(packageId.getName(), previousVersion);
        if (load(previousPackageId)) {
            return true;
        }
    }

    return false;
}

bool Profile::loadNextVersion(const vector<string>& packageVersions) {
    PackageId packageId = mPackage->getPackageId();
    string nextVersion;

    vector<string>::const_iterator it = find(packageVersions.begin(),
                                             packageVersions.end(),
                                             packageId.getVersion());
    if ((++it) != packageVersions.end()) {
        nextVersion = *it;
    }

    if (nextVersion != "" && nextVersion != packageId.getVersion()) {
        PackageId nextPackageId(packageId.getName(), nextVersion);
        if (load(nextPackageId)) {
            return true;
        }
    }

    return false;
}

bool Profile::load(const PackageId& packageId) {
    try {
        mConfiguration = ConfigurationLoader().load(
                ConfigurationPaths().getProfileFile(packageId));
    } catch (PersistenceException e) {
        return false;
    }

    typedef vector< SmartPtr<ConfigurationParameter> >::const_iterator
    Iterator;

    vector< SmartPtr<ConfigurationParameter> > configurations =
            mConfiguration->getAll();

    for (Iterator it=configurations.begin(); it != configurations.end(); ++it) {
        SmartPtr<ConfigurationParameterBool> selected =
            (SmartPtr<ConfigurationParameterMap>(*it))->get("selected");
        if (!selected.isNull()) {
            mCurrentConfiguration = (*it);
            mCurrentConfiguration->remove("selected");
        }
    }

    return true;
}

void Profile::createDefaultProfile() {
    mCurrentConfiguration = SmartPtr<ConfigurationParameterMap>(
        new ConfigurationParameterMap(getIdForPackageStatus(
            UnknownPackageStatus::getInstance())));
    mCurrentConfiguration->add(SmartPtr<ConfigurationParameterString>(
                        new ConfigurationParameterString("taskId", "")));
    mCurrentConfiguration->add(SmartPtr<ConfigurationParameterMap>(
                            new ConfigurationParameterMap("resources")));
    mConfiguration->add(mCurrentConfiguration);
}

void Profile::save() {
    mCurrentConfiguration->add(SmartPtr<ConfigurationParameterBool>(
            new ConfigurationParameterBool("selected", true)));

    try {
        ConfigurationSaver().save(mConfiguration,
            ConfigurationPaths().getProfileFile(mPackage->getPackageId()));
    } catch (PersistenceException e) {
    }

    mCurrentConfiguration->remove("selected");
}

const PackageStatus* Profile::getPackageStatusFromId(const string& id) {
    if (id == "built") {
        return BuiltPackageStatus::getInstance();
    } else if (id == "configured") {
        return ConfiguredPackageStatus::getInstance();
    } else if (id == "installed") {
        return InstalledPackageStatus::getInstance();
    } else if (id == "packed") {
        return PackedPackageStatus::getInstance();
    } else if (id == "unknown") {
        return UnknownPackageStatus::getInstance();
    } else if (id == "unpacked") {
        return UnpackedPackageStatus::getInstance();
    }

    return UnknownPackageStatus::getInstance();
}

string Profile::getIdForPackageStatus(const PackageStatus* packageStatus) {
    if (packageStatus == BuiltPackageStatus::getInstance()) {
        return "built";
    } else if (packageStatus == ConfiguredPackageStatus::getInstance()) {
        return "configured";
    } else if (packageStatus == InstalledPackageStatus::getInstance()) {
        return "installed";
    } else if (packageStatus == PackedPackageStatus::getInstance()) {
        return "packed";
    } else if (packageStatus == UnknownPackageStatus::getInstance()) {
        return "unknown";
    } else if (packageStatus == UnpackedPackageStatus::getInstance()) {
        return "unpacked";
    }

    return "unknown";
}
