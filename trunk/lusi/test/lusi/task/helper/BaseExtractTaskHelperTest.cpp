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

#include "BaseExtractTaskHelperTest.h"

#define protected public
#define private public
#include "BaseExtractTaskHelperTestImplementation.h"
#undef private
#undef protected

#include "../TaskLoggerObserverTestImplementation.h"
#include "../TaskProgressObserverTestImplementation.h"
#include "../TaskTestImplementation.h"
#include "../../configuration/ConfigurationParameterLocalUrl.h"
#include "../../package/Package.h"
#include "../../package/PackageId.h"
#include "../../util/LocalUrl.h"
#include "../../util/SmartPtr.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::package::Package;
using lusi::package::PackageId;
using lusi::task::TaskTestImplementation;
using lusi::task::TaskLoggerObserverTestImplementation;
using lusi::task::TaskProgressObserverTestImplementation;
using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void BaseExtractTaskHelperTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mBaseExtractTaskHelper = new BaseExtractTaskHelperTestImplementation(
                    "BaseExtractTaskHelperTestImplementation", mTask);
    mTaskLoggerObserver = new TaskLoggerObserverTestImplementation();
    mTaskProgressObserver = new TaskProgressObserverTestImplementation();

    mTask->getTaskLogger()->attachObserver(mTaskLoggerObserver);
    mTask->getTaskProgress()->attachObserver(mTaskProgressObserver);
}

void BaseExtractTaskHelperTest::tearDown() {
    delete mTaskProgressObserver;
    delete mTaskLoggerObserver;
    delete mBaseExtractTaskHelper;
    delete mTask;
}

void BaseExtractTaskHelperTest::testExecute() {
    delete mBaseExtractTaskHelper;
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/someFile", LocalUrl("/someFile"))));
    mBaseExtractTaskHelper = new BaseExtractTaskHelperTestImplementation(
                    "BaseExtractTaskHelperTestImplementation", mTask);

    mBaseExtractTaskHelper->execute();

    CPPUNIT_ASSERT_EQUAL(100, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT_EQUAL(true,
                static_cast<BaseExtractTaskHelperTestImplementation*>
                        (mBaseExtractTaskHelper)->isExecutionPrepared());
    CPPUNIT_ASSERT(mTask->getPackage()->getResourceFiles()->
                                                    get("/someFile").isNull());
}

void BaseExtractTaskHelperTest::testConstructor() {
    CPPUNIT_ASSERT_EQUAL(0, mBaseExtractTaskHelper->mNumberOfFilesToExtract);
    CPPUNIT_ASSERT_EQUAL(0, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(string(""),
                         mBaseExtractTaskHelper->mFileToUnpack.getPath());
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterLocalUrl*)0,
                         mBaseExtractTaskHelper->mExtractionDirectory);

    delete mBaseExtractTaskHelper;

    //Test with a ConfigurationParameterMap containing a
    //ConfigurationParameterLocalUrl
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/someFile", LocalUrl("/someFile"))));
    mBaseExtractTaskHelper = new BaseExtractTaskHelperTestImplementation(
                    "BaseExtractTaskHelperTestImplementation", mTask);

    CPPUNIT_ASSERT_EQUAL(string("/someFile"),
                         mBaseExtractTaskHelper->mFileToUnpack.getPath());
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterLocalUrl*)0,
                         mBaseExtractTaskHelper->mExtractionDirectory);
}

void BaseExtractTaskHelperTest::testGetNumberOfFilesToExtract() {
    mBaseExtractTaskHelper->mNumberOfFilesToExtract = 42;

    CPPUNIT_ASSERT_EQUAL(42,
                         mBaseExtractTaskHelper->getNumberOfFilesToExtract());
}

void BaseExtractTaskHelperTest::testSetNumberOfFilesToExtract() {
    mBaseExtractTaskHelper->setNumberOfFilesToExtract(42);

    CPPUNIT_ASSERT_EQUAL(42, mBaseExtractTaskHelper->mNumberOfFilesToExtract);
}

void BaseExtractTaskHelperTest::testFileExtracted() {
    //Test without total number of files set
    mBaseExtractTaskHelper->fileExtracted("/firstFile");

    CPPUNIT_ASSERT_EQUAL((size_t)1,
                mTask->getPackage()->getResourceFiles()->getAll().size());

    SmartPtr<ConfigurationParameter> parameter = mTask->getPackage()->
                                        getResourceFiles()->getAll()[0];

    CPPUNIT_ASSERT_EQUAL(1, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(-1, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT(!parameter.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/firstFile"), parameter->getId());
    CPPUNIT_ASSERT(!parameter.isNull());

    //Test with total number of files set
    mBaseExtractTaskHelper->setNumberOfFilesToExtract(3);
    mBaseExtractTaskHelper->fileExtracted("/secondFile");

    CPPUNIT_ASSERT_EQUAL((size_t)2,
                mTask->getPackage()->getResourceFiles()->getAll().size());

    parameter = mTask->getPackage()->getResourceFiles()->getAll()[1];

    CPPUNIT_ASSERT_EQUAL(2, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(66, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT(!parameter.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/secondFile"), parameter->getId());
    CPPUNIT_ASSERT(!parameter.isNull());


    mBaseExtractTaskHelper->fileExtracted("/thirdFile");

    CPPUNIT_ASSERT_EQUAL((size_t)3,
                mTask->getPackage()->getResourceFiles()->getAll().size());

    parameter = mTask->getPackage()->getResourceFiles()->getAll()[2];

    CPPUNIT_ASSERT_EQUAL(3, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(100, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT(!parameter.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/thirdFile"), parameter->getId());
    CPPUNIT_ASSERT(!parameter.isNull());
}
