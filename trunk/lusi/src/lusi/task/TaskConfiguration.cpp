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

#include <algorithm>

#include "TaskConfiguration.h"
#include "Task.h"
#include "../configuration/ConfigurationLoader.h"
#include "../configuration/ConfigurationParameterMap.h"
#include "../configuration/ConfigurationPaths.h"
#include "../configuration/ConfigurationSaver.h"
#include "../package/PackageId.h"
#include "../package/Package.h"
#include "../util/LocalUrl.h"
#include "../util/LocalFile.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationLoader;
using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationPaths;
using lusi::configuration::ConfigurationSaver;
using lusi::configuration::PersistenceException;
using lusi::package::Package;
using lusi::package::PackageId;
using lusi::util::LocalFile;
using lusi::util::SmartPtr;

using namespace lusi::task;

/**
 * Wrapper function for PackageId::compareVersions static method to adjust to
 * weak ordering interface used by stdlib algorithms.
 * It simply returns true if version1 is smaller than version2, false otherwise.
 *
 * @param version1 The first version to compare.
 * @param version2 The second version to compare.
 * @return True if version1 is smaller than version2, false otherwise.
 */
bool versionsWeakOrdering(const string& version1, const string& version2) {
    if (PackageId::compareVersions(version1, version2) < 0) {
        return true;
    }

    return false;
}

//public:

TaskConfiguration::TaskConfiguration(Task* task) {
    mTask = task;
    mConfiguration = 0;
    mConfigurationToSave = new ConfigurationParameterMap(mTask->getId());

    load();
}

TaskConfiguration::~TaskConfiguration() {
    delete mConfiguration;
    delete mConfigurationToSave;
}

SmartPtr<ConfigurationParameterMap>
TaskConfiguration::getTaskHelperConfiguration(const string& taskHelperId) {
    if (!mConfiguration) {
        return SmartPtr<ConfigurationParameterMap>();
    }

    return mConfiguration->get(taskHelperId);
}

vector< SmartPtr<ConfigurationParameterMap> >
TaskConfiguration::getAllTaskHelperConfigurations() {
    if (!mConfiguration) {
        return vector< SmartPtr<ConfigurationParameterMap> >();
    }

    vector< SmartPtr<ConfigurationParameter> > configurations =
                                                    mConfiguration->getAll();
    vector< SmartPtr<ConfigurationParameterMap> > configurationMaps;
    for (uint i=0; i<configurations.size(); ++i) {
        SmartPtr<ConfigurationParameterMap> configurationMap =
                                                    configurations[i];
        if (!configurationMap.isNull()) {
            configurationMaps.push_back(configurationMap);
        }
    }

    return configurationMaps;
}

void TaskConfiguration::addTaskHelperConfiguration(
                SmartPtr<ConfigurationParameterMap> taskHelperConfiguration) {
    mConfigurationToSave->add(taskHelperConfiguration);
}

bool TaskConfiguration::save() {
    const string taskId = mTask->getId();
    PackageId packageId = mTask->getPackage()->getPackageId();

    try {
        ConfigurationSaver().save(mConfigurationToSave,
                        ConfigurationPaths().getTaskFile(taskId, packageId));
        return true;
    } catch (PersistenceException e) {
        return false;
    }
}

//private:

void TaskConfiguration::load() {
    PackageId packageId = mTask->getPackage()->getPackageId();

    if (packageId.getVersion() != "") {
        if (load(packageId)) {
            return;
        }

        vector<string> packageVersions =
                            Package::getPackageVersions(packageId.getName());
        packageVersions.push_back(packageId.getVersion());
        sort(packageVersions.begin(), packageVersions.end(),
             versionsWeakOrdering);

        //Get previous saved version, if any
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
                return;
            }
        }

        //Get next saved version, if any
        string nextVersion;

        vector<string>::const_iterator it = find(packageVersions.begin(),
                                packageVersions.end(), packageId.getVersion());
        if ((++it) != packageVersions.end()) {
            nextVersion = *it;
        }

        if (nextVersion != "" && nextVersion != packageId.getVersion()) {
            PackageId nextPackageId(packageId.getName(), nextVersion);
            if (load(nextPackageId)) {
                return;
            }
        }
    }

    PackageId noVersionPackageId(packageId.getName());
    if (load(noVersionPackageId)) {
        return;
    }
}

bool TaskConfiguration::load(const PackageId& packageId) {
    string taskId = mTask->getId();
    if (taskId.find("Undo") != string::npos) {
        taskId.erase(taskId.find("Undo"), string("Undo").size());
    }

    try {
        mConfiguration = ConfigurationLoader().load(
                ConfigurationPaths().getTaskFile(taskId, packageId));
        return true;
    } catch (PersistenceException e) {
    }

    return false;
}
