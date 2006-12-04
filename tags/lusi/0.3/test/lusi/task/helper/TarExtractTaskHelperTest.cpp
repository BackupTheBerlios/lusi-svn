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

#include <memory>
#include <vector>

#include "TarExtractTaskHelperTest.h"

#define protected public
#define private public
#include "TarExtractTaskHelper.h"
#undef private
#undef protected

#include "../TaskLoggerObserverTestImplementation.h"
#include "../TaskProgressObserverTestImplementation.h"
#include "../TaskTestImplementation.h"
#include "../../configuration/ConfigurationParameterLocalUrl.h"
#include "../../package/Package.h"
#include "lusi/util/Process.h"
#include "../../util/SmartPtr.h"

using std::auto_ptr;
using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::configuration::ConfigurationParameterMap;
using lusi::task::TaskTestImplementation;
using lusi::task::TaskLoggerObserverTestImplementation;
using lusi::task::TaskProgressObserverTestImplementation;
using lusi::util::LocalUrl;
using lusi::util::Process;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void TarExtractTaskHelperTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mTarExtractTaskHelper = new TarExtractTaskHelper(mTask);
    mTaskLoggerObserver = new TaskLoggerObserverTestImplementation();
    mTaskProgressObserver = new TaskProgressObserverTestImplementation();

    mTask->getTaskLogger()->attachObserver(mTaskLoggerObserver);
    mTask->getTaskProgress()->attachObserver(mTaskProgressObserver);
}

void TarExtractTaskHelperTest::tearDown() {
    delete mTaskProgressObserver;
    delete mTaskLoggerObserver;
    delete mTarExtractTaskHelper;
    delete mTask;
}

void TarExtractTaskHelperTest::testHasValidResources() {
    //Test the empty resource files used by default
    CPPUNIT_ASSERT_EQUAL(false, mTarExtractTaskHelper->hasValidResources());

    //Test with resource files with more than one compressed file
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(
            new ConfigurationParameterLocalUrl("/firstFile.tar.gz",
                LocalUrl("/firstFile.tar.gz"))));
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(
            new ConfigurationParameterLocalUrl("/secondFile.tar.gz",
                LocalUrl("/secondFile.tar.gz"))));
    delete mTarExtractTaskHelper;
    mTarExtractTaskHelper = new TarExtractTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(false, mTarExtractTaskHelper->hasValidResources());

    //Test with resource files with a not compressed file
    mTask->getPackage()->getResourceFiles()->remove("/firstFile.tar.gz");
    mTask->getPackage()->getResourceFiles()->remove("/secondFile.tar.gz");
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(
            new ConfigurationParameterLocalUrl("/firstFile.ogg",
                LocalUrl("/firstFile.ogg"))));
    delete mTarExtractTaskHelper;
    mTarExtractTaskHelper = new TarExtractTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(false, mTarExtractTaskHelper->hasValidResources());

    //Test with resource files with a compressed file
    mTask->getPackage()->getResourceFiles()->remove("/firstFile.ogg");
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(
            new ConfigurationParameterLocalUrl("/firstFile.tar.bz2",
                LocalUrl("/firstFile.tar.bz2"))));
    delete mTarExtractTaskHelper;
    mTarExtractTaskHelper = new TarExtractTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(true, mTarExtractTaskHelper->hasValidResources());
}

void TarExtractTaskHelperTest::testReceivedStdout() {
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(
            new ConfigurationParameterLocalUrl("/package.tar.bz2",
                LocalUrl("/package.tar.bz2"))));
    delete mTarExtractTaskHelper;
    mTarExtractTaskHelper = new TarExtractTaskHelper(mTask);
    mTarExtractTaskHelper->initConfigurationParameterMap();

    mTarExtractTaskHelper->receivedStdout(0, "package/File1\n");

    //Test parent method implementation
    CPPUNIT_ASSERT_EQUAL(string("package/File1\n"),
                         mTaskLoggerObserver->getMessage());
    CPPUNIT_ASSERT_EQUAL(message, mTaskLoggerObserver->getEventType());

    //Test if the file is added to the resource files
    CPPUNIT_ASSERT_EQUAL((size_t)2,
                    mTask->getPackage()->getResourceFiles()->getAll().size());

    SmartPtr<ConfigurationParameter> resource = mTask->getPackage()->
                                                getResourceFiles()->getAll()[1];

    CPPUNIT_ASSERT_EQUAL(1, mTarExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT(!resource.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/package/File1"), resource->getId());
    CPPUNIT_ASSERT(!resource.isNull());


    //Test with data without ending new line
    mTarExtractTaskHelper->receivedStdout(0, "package/Fi");

    //Test parent method implementation
    CPPUNIT_ASSERT_EQUAL(string("package/Fi"),
                         mTaskLoggerObserver->getMessage());
    CPPUNIT_ASSERT_EQUAL(message, mTaskLoggerObserver->getEventType());

    //Test that the file wasn't added to the resource files
    CPPUNIT_ASSERT_EQUAL((size_t)2,
                    mTask->getPackage()->getResourceFiles()->getAll().size());


    //Test with the missing data
    mTarExtractTaskHelper->receivedStdout(0, "le2\n");

    //Test parent method implementation
    CPPUNIT_ASSERT_EQUAL(string("le2\n"),
                         mTaskLoggerObserver->getMessage());
    CPPUNIT_ASSERT_EQUAL(message, mTaskLoggerObserver->getEventType());

    //Test if the file is added to the resource files
    CPPUNIT_ASSERT_EQUAL((size_t)3,
                    mTask->getPackage()->getResourceFiles()->getAll().size());

    resource = mTask->getPackage()->getResourceFiles()->getAll()[2];

    CPPUNIT_ASSERT_EQUAL(2, mTarExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT(!resource.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/package/File2"), resource->getId());
    CPPUNIT_ASSERT(!resource.isNull());


    //Test with various files extracted in the same output sent
    mTarExtractTaskHelper->receivedStdout(0, "package/File3\npackage/File4\n");

    //Test parent method implementation
    CPPUNIT_ASSERT_EQUAL(string("package/File3\npackage/File4\n"),
                         mTaskLoggerObserver->getMessage());
    CPPUNIT_ASSERT_EQUAL(message, mTaskLoggerObserver->getEventType());

    //Test if the file is added to the resource files
    CPPUNIT_ASSERT_EQUAL((size_t)5,
                    mTask->getPackage()->getResourceFiles()->getAll().size());
    CPPUNIT_ASSERT_EQUAL(4, mTarExtractTaskHelper->mNumberOfFilesExtracted);

    resource = mTask->getPackage()->getResourceFiles()->getAll()[3];
    CPPUNIT_ASSERT(!resource.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/package/File3"), resource->getId());
    CPPUNIT_ASSERT(!resource.isNull());

    resource = mTask->getPackage()->getResourceFiles()->getAll()[4];
    CPPUNIT_ASSERT(!resource.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/package/File4"), resource->getId());
    CPPUNIT_ASSERT(!resource.isNull());
}

void TarExtractTaskHelperTest::testGetProcess() {
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(
            new ConfigurationParameterLocalUrl("/directory/file.tar.bz2",
                LocalUrl("/directory/file.tar.bz2"))));
    delete mTarExtractTaskHelper;
    mTarExtractTaskHelper = new TarExtractTaskHelper(mTask);
    mTarExtractTaskHelper->initConfigurationParameterMap();

    auto_ptr<Process> process(mTarExtractTaskHelper->getProcess());

    CPPUNIT_ASSERT_EQUAL(0, mTarExtractTaskHelper->mNumberOfFilesToExtract);
    CPPUNIT_ASSERT_EQUAL(string("/directory/"), process->getWorkingDirectory());
    CPPUNIT_ASSERT_EQUAL(string("/bin/sh"), process->getArguments()[0]);
    CPPUNIT_ASSERT_EQUAL(string("-c"), process->getArguments()[1]);
    CPPUNIT_ASSERT_EQUAL(
                string("mkdir -p /directory/ && tar -vx -j -f file.tar.bz2"),
                process->getArguments()[2]);
    CPPUNIT_ASSERT_EQUAL(vector<string>::size_type(3),
                         process->getArguments().size());
    //As /directory/file.tar.bz2 doesn't exist, files to be extracted can't be
    //calculated
    CPPUNIT_ASSERT_EQUAL(false, mTask->getTaskProgress()->isExtendedProgress());


    //Test with a tar file (no format argument should be added)
    mTask->getPackage()->getResourceFiles()->remove("/directory/file.tar.bz2");
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(
            new ConfigurationParameterLocalUrl("/directory/file.tar",
                LocalUrl("/directory/file.tar"))));
    delete mTarExtractTaskHelper;
    mTarExtractTaskHelper = new TarExtractTaskHelper(mTask);
    mTarExtractTaskHelper->initConfigurationParameterMap();

    process = auto_ptr<Process>(mTarExtractTaskHelper->getProcess());

    CPPUNIT_ASSERT_EQUAL(0, mTarExtractTaskHelper->mNumberOfFilesToExtract);
    CPPUNIT_ASSERT_EQUAL(string("/directory/"), process->getWorkingDirectory());
    CPPUNIT_ASSERT_EQUAL(string("/bin/sh"), process->getArguments()[0]);
    CPPUNIT_ASSERT_EQUAL(string("-c"), process->getArguments()[1]);
    CPPUNIT_ASSERT_EQUAL(
                string("mkdir -p /directory/ && tar -vx -f file.tar"),
                process->getArguments()[2]);
    CPPUNIT_ASSERT_EQUAL(vector<string>::size_type(3),
                         process->getArguments().size());
    //As /directory/file.tar.bz2 doesn't exist, files to be extracted can't be
    //calculated
    CPPUNIT_ASSERT_EQUAL(false, mTask->getTaskProgress()->isExtendedProgress());
}

void TarExtractTaskHelperTest::testInferTarFormat() {
    //Test the empty ConfigurationParameterLocalUrl used by default
    CPPUNIT_ASSERT_EQUAL(string("?"), mTarExtractTaskHelper->inferTarFormat());

    //Test with tar files
    mTarExtractTaskHelper->mFileToUnpack = LocalUrl("/file.tar");

    CPPUNIT_ASSERT_EQUAL(string(""), mTarExtractTaskHelper->inferTarFormat());

    //Test with gzip files
    mTarExtractTaskHelper->mFileToUnpack = LocalUrl("/file.gzip");

    CPPUNIT_ASSERT_EQUAL(string("-z"), mTarExtractTaskHelper->inferTarFormat());

    mTarExtractTaskHelper->mFileToUnpack = LocalUrl("/file.tar.gz");

    CPPUNIT_ASSERT_EQUAL(string("-z"), mTarExtractTaskHelper->inferTarFormat());

    //Test with bzip2 files
    mTarExtractTaskHelper->mFileToUnpack = LocalUrl("/file.bzip2");

    CPPUNIT_ASSERT_EQUAL(string("-j"), mTarExtractTaskHelper->inferTarFormat());

    mTarExtractTaskHelper->mFileToUnpack = LocalUrl("/file.tar.bz2");

    CPPUNIT_ASSERT_EQUAL(string("-j"), mTarExtractTaskHelper->inferTarFormat());
}
