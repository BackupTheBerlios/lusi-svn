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

#include <vector>

#include "ConfigureConfigureTaskHelper.h"
#include "../../configuration/ConfigurationParameterLocalUrl.h"
#include "../../configuration/ConfigurationParameterMap.h"
#include "../../package/Package.h"
#include "../../task/Task.h"
#include "../../util/i18n.h"
#include "../../util/LocalUrl.h"
#include "../../util/Process.h"
#include "../../util/ProcessRunner.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::configuration::ConfigurationParameterMap;
using lusi::task::Task;
using lusi::util::LocalUrl;
using lusi::util::Process;
using lusi::util::ProcessException;
using lusi::util::ProcessRunner;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

TaskHelper* lusi::task::helper::createConfigureConfigureTaskHelper(
                                        Task* task) {
    return new ConfigureConfigureTaskHelper(task);
}

//public:

ConfigureConfigureTaskHelper::ConfigureConfigureTaskHelper(Task* task):
                TaskHelperUsingProcess("ConfigureConfigureTaskHelper", task) {
    //TODO refactor with same code in other TaskHelpers
    vector< SmartPtr<ConfigurationParameter> > resourceFiles = mTask->
                getPackage()->getResourceFiles()->getAll();
    if (resourceFiles.size() == 0 ||
                !LocalUrl(resourceFiles[0]->getId()).isDirectory()) {
        mPackageDirectory = new LocalUrl("");
    } else {
        mPackageDirectory = new LocalUrl(resourceFiles[0]->getId());
    }
}

ConfigureConfigureTaskHelper::~ConfigureConfigureTaskHelper() {
    delete mPackageDirectory;
}

//TODO check if the script is executable. Log error information?
bool ConfigureConfigureTaskHelper::hasValidResources() {
    if (mPackageDirectory->getPath() == "") {
        return false;
    }

    if (mTask->getPackage()->getResourceFiles()->get(
                    mPackageDirectory->getDirectory() + "configure") == 0) {
        return false;
    }

    return true;
}

void ConfigureConfigureTaskHelper::initConfigurationParameterMap() {
    ConfigurationParameterLocalUrl* prefix;

    string defaultPrefix = getDefaultPrefix();
    if (defaultPrefix != "") {
        prefix = new ConfigurationParameterLocalUrl("prefix", _("Prefix"),
            ConfigurationParameter::RecommendedPriority,
            _("The prefix directory to install the package to"), defaultPrefix,
            ConfigurationParameterLocalUrl::DirectoryType);
    } else {
        prefix = new ConfigurationParameterLocalUrl("prefix", _("Prefix"),
            ConfigurationParameter::RecommendedPriority,
            _("The prefix directory to install the package to"),
            ConfigurationParameterLocalUrl::DirectoryType);
        prefix->setValue(LocalUrl("/usr/local/"));
    }

    mConfigurationParameterMap->add(SmartPtr<ConfigurationParameter>(prefix));
}

//protected:

Process* ConfigureConfigureTaskHelper::getProcess() {
    Process* process = Process::newProcess(Process::PipeCommunication);
    process->setWorkingDirectory(mPackageDirectory->getDirectory());
    (*process) << "/bin/sh" << "-c" << "./configure" +
                                            getConfigureParameters(process);
    return process;
}

//private:

//TODO implement it
string ConfigureConfigureTaskHelper::getConfigureParameters(Process* process) {
    string configureParameters;

    SmartPtr<ConfigurationParameterLocalUrl> prefix =
        static_cast< SmartPtr<ConfigurationParameterLocalUrl> >(
            mConfigurationParameterMap->get("prefix"));

    if (!prefix->isDefaultValue()) {
        configureParameters += " --" + prefix->getId() + "=" +
                               prefix->getValue().getPath();
    }

    return configureParameters;
}

string ConfigureConfigureTaskHelper::getDefaultPrefix() {
    ProcessRunner processRunner;
    Process* process = processRunner.getProcess();

    process->setWorkingDirectory(mPackageDirectory->getDirectory());
    string searchPrefixCommand =
            "sed -n \"s/^[ \\t]*ac_default_prefix=//p\" configure | tail -n 1";
    (*process) << "/bin/sh" << "-c" << "export prefix=`" + searchPrefixCommand +
                  "` && /bin/sh -c \"echo $prefix\"";

    try {
        process->start();
    } catch (ProcessException e) {
        return "";
    }

    string defaultPrefix = processRunner.getStdoutData();
    defaultPrefix = defaultPrefix.substr(0, defaultPrefix.find('\n'));
    return defaultPrefix;
}
