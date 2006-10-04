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

#include "MakeInstallTaskHelper.h"
#include "../../configuration/ConfigurationParameterAnd.h"
#include "../../configuration/ConfigurationParameterString.h"
#include "../../util/LocalFile.h"
#include "../../util/ProcessRunner.h"
#include "../../util/SuProcess.h"
#include "../../util/User.h"

using std::string;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterAnd;
using lusi::configuration::ConfigurationParameterString;
using lusi::util::LocalFile;
using lusi::util::Process;
using lusi::util::ProcessException;
using lusi::util::ProcessRunner;
using lusi::util::SmartPtr;
using lusi::util::SuProcess;

using namespace lusi::task::helper;

TaskHelper* lusi::task::helper::createMakeInstallTaskHelper(
                                        Task* task) {
    return new MakeInstallTaskHelper(task);
}

//public:

MakeInstallTaskHelper::MakeInstallTaskHelper(Task* task):
                        TaskHelperUsingMake("MakeInstallTaskHelper", task),
                        mUserName(0), mPassword(0) {
}

MakeInstallTaskHelper::~MakeInstallTaskHelper() {
}

void MakeInstallTaskHelper::initConfigurationParameterMap() {
    string prefixString = getInstallationPrefix();

    if (prefixString == "") {
        //The prefix can't be determined
        return;
    }

    LocalFile prefix(prefixString);
    if (prefix.isWritable() && prefix.isExecutable()) {
        return;
    }

    mUserName = new ConfigurationParameterString("userName", "User name",
        ConfigurationParameter::RequiredPriority,
        "The name of the owner of the directory to install the package to",
        prefix.getOwner().getName());
    mPassword = new ConfigurationParameterString("password", "Password",
        ConfigurationParameter::RequiredPriority,
        "The password of the owner of the directory to install the package to",
        ConfigurationParameterString::PasswordType);

    ConfigurationParameterAnd* login = new ConfigurationParameterAnd("login",
                            "Login", ConfigurationParameter::RequiredPriority,
        "Login data of the owner of the directory to install the package to");
    login->addConfigurationParameter(mUserName);
    login->addConfigurationParameter(mPassword);

    mConfigurationParameterMap.add(SmartPtr<ConfigurationParameter>(login));
}

//protected:

Process* MakeInstallTaskHelper::getProcess() {
    SuProcess* suProcess = SuProcess::newSuProcess(Process::PtyCommunication);
    if (mUserName != 0) {
        suProcess->setUserName(mUserName->getValue());
        suProcess->setPassword(mPassword->getValue());
    }

    suProcess->setWorkingDirectory(mPackageDirectory->getDirectory());
    (*suProcess) << "make" << "install";
    return suProcess;
}

//private:

std::string MakeInstallTaskHelper::getInstallationPrefix() {
    ProcessRunner processRunner;
    Process* process = processRunner.getProcess();

    process->setWorkingDirectory(mPackageDirectory->getDirectory());
    (*process) << "sed" << "--posix" << "-n" << "-e" <<
                  "s/^prefix[ \\t]*=[ \\t]*//p" << "Makefile";

    try {
        process->start();
    } catch (ProcessException e) {
        return "";
    }

    string installPrefix = processRunner.getStdoutData();
    installPrefix = installPrefix.substr(0, installPrefix.find('\n'));
    return installPrefix;
}
