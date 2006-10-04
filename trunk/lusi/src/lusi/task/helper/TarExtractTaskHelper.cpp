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

#include <sstream>

#include "TarExtractTaskHelper.h"
#include "../../configuration/ConfigurationParameterLocalUrl.h"
#include "../../package/LocalFileResource.h"
#include "../../util/LocalFile.h"
#include "../../util/LocalUrl.h"
#include "../../util/Process.h"
#include "../../util/ProcessRunner.h"

using std::istringstream;
using std::string;

using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::package::ResourceMap;
using lusi::task::Task;
using lusi::util::LocalFile;
using lusi::util::LocalUrl;
using lusi::util::Process;
using lusi::util::ProcessRunner;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

TaskHelper* lusi::task::helper::createTarExtractTaskHelper(
                                        Task* task) {
    return new TarExtractTaskHelper(task);
}

//public:

TarExtractTaskHelper::TarExtractTaskHelper(Task* task):
                        BaseExtractTaskHelper("TarExtractTaskHelper", task),
                        mReceivedData("") {
    mTarFormat = inferTarFormat();
}

TarExtractTaskHelper::~TarExtractTaskHelper() {
}

bool TarExtractTaskHelper::hasValidResourceMap() {
    if (mTarFormat == "?") {
        return false;
    }

    return true;
}

void TarExtractTaskHelper::receivedStdout(Process* process,
                                           const string& data) {
    BaseExtractTaskHelper::receivedStdout(process, data);

    mReceivedData += data;

    while (mReceivedData.find('\n') != string::npos) {
        string fileName = mReceivedData.substr(0, mReceivedData.find('\n'));
        mReceivedData.erase(0, fileName.size() + 1);

        fileExtracted(mExtractionDirectory->getValue().getPath() + fileName);
    }
}

//protected:

Process* TarExtractTaskHelper::getProcess() {
    setNumberOfFilesToExtract(calculateNumberOfFilesToExtract());

    Process* process = Process::newProcess(Process::PipeCommunication);
    process->setWorkingDirectory(
                    LocalUrl(mFileToUnpack->getId()).getDirectory());

    string extractCommand;

    if (!LocalFile(mExtractionDirectory->getValue()).exists()) {
        extractCommand = "mkdir -p " +
                            mExtractionDirectory->getValue().getPath() + " && ";
    }

    extractCommand += "tar -vx" + (mTarFormat!=""?" "+mTarFormat:"") +
                      " -f " + LocalUrl(mFileToUnpack->getId()).getFileName();

    if (!mExtractionDirectory->isDefaultValue()) {
        extractCommand += " -C " + mExtractionDirectory->getValue().getPath();
    }

    (*process) << "/bin/sh" << "-c" << extractCommand;


    if (getNumberOfFilesToExtract() > 0) {
        mTask->getTaskProgress()->setExtendedProgress(true);
    }

    return process;
}

//private:

std::string TarExtractTaskHelper::inferTarFormat() {
    string extension = LocalUrl(mFileToUnpack->getId()).getExtension();

    if (extension == "gzip" || extension == "gz") {
        return "-z";
    }

    if (extension == "bzip2" || extension == "bz2") {
        return "-j";
    }

    if (extension == "tar") {
        return "";
    }

    //unknown format
    return "?";
}

int TarExtractTaskHelper::calculateNumberOfFilesToExtract() {
    ProcessRunner processRunner;
    Process* process = processRunner.getProcess();
    (*process) << "/bin/sh" << "-c" <<
                  "tar -t " + mTarFormat + " -f " + mFileToUnpack->getId() +
                  " | wc -l" ;

    notifyTaskLogger("Calculating number of files to extract (" +
                            process->getArgumentsAsString() + ")\n", message);

    process->start();

    if (!processRunner.getStderrData().empty()) {
        notifyTaskLogger("Error while calculating number of files to extract:" +
                                processRunner.getStderrData(), error);
        return 0;
    }

    istringstream toInt(processRunner.getStdoutData());
    int numberOfFilesToExtract;
    toInt >> numberOfFilesToExtract;

    notifyTaskLogger("Done: " + processRunner.getStdoutData(), message);

    return numberOfFilesToExtract;
}
