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
#include "../../configuration/ConfigurationParameterLocalUrl.h"
#include "../../configuration/ConfigurationParameterMap.h"
#include "../../package/Package.h"
#include "../../util/i18n.h"
#include "../../util/Process.h"
#include "../../util/SmartPtr.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::configuration::InvalidConfigurationException;
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

    mTask->getPackage()->getResourceFiles()->remove(mFileToUnpack.getPath());
    mFileToUnpack = LocalUrl();
}

void BaseExtractTaskHelper::initConfigurationParameterMap() {
    mExtractionDirectory =
        new ConfigurationParameterLocalUrl("extractionDirectory",
            _("Extraction directory"), ConfigurationParameter::OptionalPriority,
            _("The directory to extract the package to"),
            mFileToUnpack.getParent(),
            ConfigurationParameterLocalUrl::DirectoryType);

    mConfigurationParameterMap->add(
                    SmartPtr<ConfigurationParameter>(mExtractionDirectory));
}

//protected:

BaseExtractTaskHelper::BaseExtractTaskHelper(const string& name, Task* task):
                        TaskHelperUsingProcess(name, task) {
    vector< SmartPtr<ConfigurationParameter> > resourceFiles =
            mTask->getPackage()->getResourceFiles()->getAll();
    if (resourceFiles.size() != 1) {
        mFileToUnpack = LocalUrl("");
    } else {
        mFileToUnpack = LocalUrl(resourceFiles[0]->getId());
    }

    mNumberOfFilesToExtract = 0;
    mNumberOfFilesExtracted = 0;

    mExtractionDirectory = 0;
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

    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            fileName, LocalUrl(fileName))));
}
