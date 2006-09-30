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

#include "TaskHelperUsingMake.h"
#include "../../configuration/ConfigurationParameterMap.h"
#include "../../package/LocalFileResource.h"
#include "../../package/Package.h"
#include "../../package/ResourceMap.h"
#include "../../task/Task.h"
#include "../../util/LocalFile.h"
#include "../../util/LocalUrl.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameterMap;
using lusi::package::LocalFileResource;
using lusi::task::Task;
using lusi::util::LocalFile;
using lusi::util::LocalUrl;
using lusi::util::Process;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

TaskHelperUsingMake::~TaskHelperUsingMake() {
    delete mPackageDirectory;
}

bool TaskHelperUsingMake::hasValidResourceMap() {
    if (mPackageDirectory->getPath() == "") {
        return false;
    }

    if (mTask->getPackage()->getResourceMap()->get(
                    mPackageDirectory->getDirectory() + "Makefile") != 0) {
        return true;
    }

    if (LocalFile(mPackageDirectory->getDirectory() + "Makefile").exists()) {
        return true;
    }

    return false;
}

void TaskHelperUsingMake::receivedStderr(Process* process, const string& data) {
    mReceivedStderrData += data;

    while (mReceivedStderrData.find('\n') != string::npos) {
        string newLine = mReceivedStderrData.substr(0,
                                        mReceivedStderrData.find('\n') + 1);
        mReceivedStderrData.erase(0, newLine.size());

        if (newLine.find("warning:") != string::npos) {
            notifyTaskLogger(newLine, warning);
        } else {
            TaskHelperUsingProcess::receivedStderr(process, newLine);
        }
    }
}

//protected:

TaskHelperUsingMake::TaskHelperUsingMake(const string& name, Task* task):
            TaskHelperUsingProcess(name, task), mReceivedStderrData("") {
    vector< SmartPtr<LocalFileResource> > localFileResources = mTask->
                getPackage()->getResourceMap()->
                        getAllResourcesByType<LocalFileResource>();
    if (localFileResources.size() == 0 ||
                !LocalUrl(localFileResources[0]->getId()).isDirectory()) {
        mPackageDirectory = new LocalUrl("");
    } else {
        mPackageDirectory = new LocalUrl(localFileResources[0]->getId());
    }
}
