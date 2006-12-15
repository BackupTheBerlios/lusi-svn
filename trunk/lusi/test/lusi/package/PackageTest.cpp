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

#include <sys/stat.h>

#include "PackageTest.h"

#define protected public
#define private public
#include "Package.h"
#undef private
#undef protected

#include "PackageId.h"
#include "Profile.h"
#include "status/BuiltPackageStatus.h"
#include "status/UnknownPackageStatus.h"
#include "../configuration/ConfigurationParameterMap.h"
#include "../configuration/ConfigurationPaths.h"

using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationPaths;
using lusi::package::status::BuiltPackageStatus;
using lusi::package::status::PackageStatus;
using lusi::package::status::UnknownPackageStatus;

using namespace lusi::package;

//public:

void PackageTest::setUp() {
    mPackageId = new PackageId("aPackageNameThatCanBeDeletedAfterEachTest");
    mPackage = new Package(*mPackageId);
}

void PackageTest::tearDown() {
    ConfigurationPaths paths;

    struct stat fileStat;
    if (!stat(paths.getPackageDirectory(*mPackageId).c_str(), &fileStat)) {
        unlink(paths.getPackageFile(*mPackageId).c_str());
        unlink(paths.getProfileFile(*mPackageId).c_str());
        rmdir(paths.getPackageDirectory(*mPackageId).c_str());
    }

    delete mPackage;
    delete mPackageId;
}

void PackageTest::testConstructor() {
    //Test constructor with default PackageStatus
    CPPUNIT_ASSERT(*mPackageId == mPackage->mPackageId);
    CPPUNIT_ASSERT(UnknownPackageStatus::getInstance() ==
                   mPackage->getPackageStatus());
    CPPUNIT_ASSERT_EQUAL((Profile*)0, mPackage->mProfile);
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResources.isNull());
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResourceFiles.isNull());

    //Test constructor with explicit PackageStatus
    delete mPackage;
    mPackage = new Package(*mPackageId, BuiltPackageStatus::getInstance());

    CPPUNIT_ASSERT(BuiltPackageStatus::getInstance() ==
                   mPackage->getPackageStatus());
    CPPUNIT_ASSERT_EQUAL((Profile*)0, mPackage->mProfile);
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResources.isNull());
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResourceFiles.isNull());
}

void PackageTest::testGetPackageId() {
    CPPUNIT_ASSERT(mPackage->mPackageId == mPackage->getPackageId());
}

void PackageTest::testGetProfile() {
    CPPUNIT_ASSERT_EQUAL((Profile*)0, mPackage->mProfile);

    CPPUNIT_ASSERT_EQUAL(mPackage->mProfile, mPackage->getProfile());
    CPPUNIT_ASSERT_EQUAL(mPackage->getProfile(), mPackage->getProfile());
}

void PackageTest::testGetResources() {
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResources.isNull());

    CPPUNIT_ASSERT_EQUAL(false, mPackage->getResources().isNull());
    CPPUNIT_ASSERT(mPackage->mResources == mPackage->getResources());
    CPPUNIT_ASSERT(mPackage->getResources() == mPackage->getResources());
}

void PackageTest::testGetResourceFiles() {
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResourceFiles.isNull());

    CPPUNIT_ASSERT(mPackage->mResourceFiles == mPackage->getResourceFiles());
    CPPUNIT_ASSERT(mPackage->mResources->get("files") ==
                   mPackage->mResourceFiles);
    CPPUNIT_ASSERT(mPackage->getResourceFiles() ==
                   mPackage->getResourceFiles());
}

void PackageTest::testGetPackageStatus() {
    CPPUNIT_ASSERT_EQUAL(mPackage->mPackageStatus,
                         mPackage->getPackageStatus());
}

void PackageTest::testSetPackageStatus() {
    mPackage->mPackageStatus = UnknownPackageStatus::getInstance();

    mPackage->setPackageStatus(BuiltPackageStatus::getInstance());
    CPPUNIT_ASSERT_EQUAL(static_cast<const PackageStatus*>
                                (BuiltPackageStatus::getInstance()),
                         mPackage->mPackageStatus);
    CPPUNIT_ASSERT_EQUAL(static_cast<const PackageStatus*>
                                (BuiltPackageStatus::getInstance()),
                         mPackage->getProfile()->getPackageStatus());
}

void PackageTest::testRevertPackageStatus() {
    mPackage->setPackageStatus(BuiltPackageStatus::getInstance());
    mPackage->revertPackageStatus(UnknownPackageStatus::getInstance());

    CPPUNIT_ASSERT_EQUAL(static_cast<const PackageStatus*>(
                            UnknownPackageStatus::getInstance()),
                         mPackage->mPackageStatus);
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResources.isNull());
    CPPUNIT_ASSERT_EQUAL(true, mPackage->mResourceFiles.isNull());
}
