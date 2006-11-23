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

#include "PackageManagerTest.h"

#define protected public
#define private public
#include "Package.h"
#include "PackageManager.h"
#undef private
#undef protected

#include "PackageId.h"
#include "status/PackedPackageStatus.h"
#include "status/UnknownPackageStatus.h"
#include "status/UnpackedPackageStatus.h"
#include "../util/SmartPtr.h"

using std::vector;

using lusi::package::status::PackageStatus;
using lusi::package::status::PackedPackageStatus;
using lusi::package::status::UnknownPackageStatus;
using lusi::package::status::UnpackedPackageStatus;
using lusi::util::SmartPtr;

using namespace lusi::package;

//public:

void PackageManagerTest::setUp() {
    mPackageManager = new PackageManager();
    mPackageManager->mPackageDatas.clear();

    mPackageId1 = new PackageId("1");
    mPackageId2 = new PackageId("2");
    mPackageId3 = new PackageId("3");

    struct PackageManager::PackageData packageData;
    packageData.packageId = *mPackageId1;
    packageData.packageStatus = UnpackedPackageStatus::getInstance();
    mPackageManager->mPackageDatas.push_back(packageData);

    packageData.packageId = *mPackageId2;
    packageData.packageStatus = PackedPackageStatus::getInstance();
    mPackageManager->mPackageDatas.push_back(packageData);

    packageData.packageId = *mPackageId3;
    packageData.packageStatus = UnpackedPackageStatus::getInstance();
    mPackageManager->mPackageDatas.push_back(packageData);
}

void PackageManagerTest::tearDown() {
    delete mPackageManager;
    delete mPackageId1;
    delete mPackageId2;
    delete mPackageId3;
}

void PackageManagerTest::testSingleton() {
    CPPUNIT_ASSERT(PackageManager::getInstance() != 0);

    CPPUNIT_ASSERT_EQUAL(PackageManager::getInstance(),
                         PackageManager::getInstance());
}

void PackageManagerTest::testGetPackageIds() {
    vector<PackageId> packageIds;

    //Test with a status without registered PackageIds
    packageIds =
        mPackageManager->getPackageIds(UnknownPackageStatus::getInstance());

    CPPUNIT_ASSERT_EQUAL((size_t)0, packageIds.size());

    //Test with a status with one registered PackageId
    packageIds =
        mPackageManager->getPackageIds(PackedPackageStatus::getInstance());

    CPPUNIT_ASSERT_EQUAL((size_t)1, packageIds.size());
    CPPUNIT_ASSERT(*mPackageId2 == packageIds[0]);

    //Test with a status with two registered PackageIds
    packageIds =
        mPackageManager->getPackageIds(UnpackedPackageStatus::getInstance());

    CPPUNIT_ASSERT_EQUAL((size_t)2, packageIds.size());
    CPPUNIT_ASSERT(*mPackageId1 == packageIds[0]);
    CPPUNIT_ASSERT(*mPackageId3 == packageIds[1]);
}

void PackageManagerTest::testGetPackage() {
    //Test with a PackageId already registered
    SmartPtr<Package> package = mPackageManager->getPackage(*mPackageId1);

    CPPUNIT_ASSERT(*mPackageId1 == package->getPackageId());
    CPPUNIT_ASSERT_EQUAL(
                    (const PackageStatus*)UnpackedPackageStatus::getInstance(),
                    package->getPackageStatus());
    CPPUNIT_ASSERT_EQUAL((size_t)3, mPackageManager->mPackageDatas.size());

    //Test with a PackageId not registered
    PackageId packageId("4");
    package = mPackageManager->getPackage(packageId);

    CPPUNIT_ASSERT(packageId == package->getPackageId());
    CPPUNIT_ASSERT_EQUAL(
                    (const PackageStatus*)UnknownPackageStatus::getInstance(),
                    package->getPackageStatus());
    CPPUNIT_ASSERT_EQUAL((size_t)4, mPackageManager->mPackageDatas.size());
    CPPUNIT_ASSERT(packageId == mPackageManager->mPackageDatas[3].packageId);
}

void PackageManagerTest::testUpdatePackage() {
    SmartPtr<Package> package = mPackageManager->getPackage(*mPackageId1);
    package->mPackageStatus = PackedPackageStatus::getInstance();

    mPackageManager->updatePackage(getPtr(package));

    CPPUNIT_ASSERT_EQUAL((size_t)3, mPackageManager->mPackageDatas.size());
    CPPUNIT_ASSERT(*mPackageId1 == mPackageManager->mPackageDatas[0].packageId);
    CPPUNIT_ASSERT_EQUAL(
                    (const PackageStatus*)PackedPackageStatus::getInstance(),
                    mPackageManager->mPackageDatas[0].packageStatus);
}
