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
#include "../../package/LocalFileResource.h"
#include "../../package/Package.h"
#include "../../package/PackageId.h"
#include "../../package/ResourceMap.h"
#include "../../util/SmartPtr.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::package::LocalFileResource;
using lusi::package::Package;
using lusi::package::PackageId;
using lusi::package::Resource;
using lusi::task::TaskTestImplementation;
using lusi::task::TaskLoggerObserverTestImplementation;
using lusi::task::TaskProgressObserverTestImplementation;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void BaseExtractTaskHelperTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mPackage = mTask->getPackage();
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
    mPackage->getResourceMap()->add(
                        SmartPtr<Resource>(new LocalFileResource("/someFile")));
    mBaseExtractTaskHelper = new BaseExtractTaskHelperTestImplementation(
                    "BaseExtractTaskHelperTestImplementation", mTask);

    mBaseExtractTaskHelper->execute();

    CPPUNIT_ASSERT_EQUAL(100, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT_EQUAL(true,
                static_cast<BaseExtractTaskHelperTestImplementation*>
                        (mBaseExtractTaskHelper)->isExecutionPrepared());
    CPPUNIT_ASSERT(
            mTask->getPackage()->getResourceMap()->get("/someFile").isNull());
}

void BaseExtractTaskHelperTest::testConstructor() {
    CPPUNIT_ASSERT_EQUAL(0, mBaseExtractTaskHelper->mNumberOfFilesToExtract);
    CPPUNIT_ASSERT_EQUAL(0, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(string(""),
                         mBaseExtractTaskHelper->mFileToUnpack->getId());
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterLocalUrl*)0,
                         mBaseExtractTaskHelper->mExtractionDirectory);

    delete mBaseExtractTaskHelper;

    //Test with a ResourceMap containing a LocalResource
    mPackage->getResourceMap()->add(
                        SmartPtr<Resource>(new LocalFileResource("/someFile")));
    mBaseExtractTaskHelper = new BaseExtractTaskHelperTestImplementation(
                    "BaseExtractTaskHelperTestImplementation", mTask);

    CPPUNIT_ASSERT_EQUAL(string("/someFile"),
                         mBaseExtractTaskHelper->mFileToUnpack->getId());
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
                        mTask->getPackage()->getResourceMap()->getAll().size());

    SmartPtr<Resource> resource = mTask->getPackage()->
                                                getResourceMap()->getAll()[0];

    CPPUNIT_ASSERT_EQUAL(1, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(-1, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT(!resource.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/firstFile"), resource->getId());
    CPPUNIT_ASSERT(!((SmartPtr<LocalFileResource>)resource).isNull());

    //Test with total number of files set
    mBaseExtractTaskHelper->setNumberOfFilesToExtract(3);
    mBaseExtractTaskHelper->fileExtracted("/secondFile");

    CPPUNIT_ASSERT_EQUAL((size_t)2,
                        mTask->getPackage()->getResourceMap()->getAll().size());

    resource = mTask->getPackage()->getResourceMap()->getAll()[1];

    CPPUNIT_ASSERT_EQUAL(2, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(66, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT(!resource.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/secondFile"), resource->getId());
    CPPUNIT_ASSERT(!((SmartPtr<LocalFileResource>)resource).isNull());


    mBaseExtractTaskHelper->fileExtracted("/thirdFile");

    CPPUNIT_ASSERT_EQUAL((size_t)3,
                        mTask->getPackage()->getResourceMap()->getAll().size());

    resource =mTask->getPackage()->getResourceMap()->getAll()[2];

    CPPUNIT_ASSERT_EQUAL(3, mBaseExtractTaskHelper->mNumberOfFilesExtracted);
    CPPUNIT_ASSERT_EQUAL(100, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT(!resource.isNull());
    CPPUNIT_ASSERT_EQUAL(string("/thirdFile"), resource->getId());
    CPPUNIT_ASSERT(!((SmartPtr<LocalFileResource>)resource).isNull());
}
