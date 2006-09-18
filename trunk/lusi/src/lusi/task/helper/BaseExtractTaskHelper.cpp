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

#include "BaseExtractTaskHelper.h"
#include "../../configuration/ConfigurationParameterMap.h"
#include "../../configuration/ConfigurationParameterSimple.h"
#include "../../package/LocalFileResource.h"
#include "../../package/Package.h"
#include "../../package/ResourceMap.h"
#include "../../util/LocalFile.h"
#include "../../util/Process.h"
#include "../../util/SmartPtr.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationParameterSimple;
using lusi::configuration::InvalidConfigurationException;
using lusi::package::LocalFileResource;
using lusi::package::Resource;
using lusi::task::Task;
using lusi::util::LocalUrl;
using lusi::util::Process;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

BaseExtractTaskHelper::~BaseExtractTaskHelper() {
}

void BaseExtractTaskHelper::execute() throw (ExecuteTaskHelperException,
                                             InvalidConfigurationException) {
    TaskHelperUsingProcess::execute();

    mTask->getPackage()->getResourceMap()->remove(mFileToUnpack->getId());
    //TODO add release method to smartptr instead of assign an empty one
    mFileToUnpack = SmartPtr<LocalFileResource>(0);
}

void BaseExtractTaskHelper::initConfigurationParameterMap() {
    ConfigurationParameterSimple* extractionDirectory =
        new ConfigurationParameterSimple("extractionDirectory",
            "Extraction directory", ConfigurationParameter::OptionalPriority,
                "The directory to extract the package to",
                    LocalUrl(mFileToUnpack->getId()).getParent());

    mConfigurationParameterMap.add(
                    SmartPtr<ConfigurationParameter>(extractionDirectory));
}

//protected:

BaseExtractTaskHelper::BaseExtractTaskHelper(const string& name, Task* task):
                        TaskHelperUsingProcess(name, task) {
    vector< SmartPtr<LocalFileResource> > localFileResources = mTask->
            getPackage()->getResourceMap()->
                    getAllResourcesByType<LocalFileResource>();
    if (localFileResources.size() != 1) {
        mFileToUnpack = SmartPtr<LocalFileResource>(new LocalFileResource(""));
    } else {
        mFileToUnpack = localFileResources[0];
    }

    mNumberOfFilesToExtract = 0;
    mNumberOfFilesExtracted = 0;
}

/*
inline int BaseExtractTaskHelper::getNumberOfFilesToExtract() {
    return mNumberOfFilesToExtract;
}

inline void BaseExtractTaskHelper::setNumberOfFilesToExtract(
                                    int numberOfFilesToExtract) {
    mNumberOfFilesToExtract = numberOfFilesToExtract;
}
*/

void BaseExtractTaskHelper::fileExtracted(const string& fileName) {
    mNumberOfFilesExtracted++;

    if (mNumberOfFilesToExtract != 0) {
        notifyTaskProgress((mNumberOfFilesExtracted * 100) /
                                            mNumberOfFilesToExtract);
    }

    mTask->getPackage()->getResourceMap()->add(
                        SmartPtr<Resource>(new LocalFileResource(fileName)));
}
