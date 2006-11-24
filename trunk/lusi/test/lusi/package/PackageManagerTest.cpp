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

using std::vector;

using lusi::package::status::PackageStatus;
using lusi::package::status::PackedPackageStatus;
using lusi::package::status::UnknownPackageStatus;
using lusi::package::status::UnpackedPackageStatus;

using namespace lusi::package;

//public:

void PackageManagerTest::setUp() {
    mPackageManager = new PackageManager();

    //Remove the packages loaded from disk, if any
    for (uint i=0; i<mPackageManager->mPackages.size(); ++i) {
        delete mPackageManager->mPackages[i];
    }
    mPackageManager->mPackages.clear();

    mPackage1 = new Package(PackageId("1"),
                                    UnpackedPackageStatus::getInstance());
    mPackageManager->mPackages.push_back(mPackage1);

    mPackage2 = new Package(PackageId("2"),
                                    PackedPackageStatus::getInstance());
    mPackageManager->mPackages.push_back(mPackage2);

    mPackage3 = new Package(PackageId("3"),
                                    UnpackedPackageStatus::getInstance());
    mPackageManager->mPackages.push_back(mPackage3);
}

void PackageManagerTest::tearDown() {
    delete mPackageManager;
}

void PackageManagerTest::testSingleton() {
    CPPUNIT_ASSERT(PackageManager::getInstance() != 0);

    CPPUNIT_ASSERT_EQUAL(PackageManager::getInstance(),
                         PackageManager::getInstance());
}

void PackageManagerTest::testGetPackages() {
    CPPUNIT_ASSERT(mPackageManager->mPackages ==
                   mPackageManager->getPackages());
}

void PackageManagerTest::testGetPackagesPackageStatus() {
    vector<Package*> packages;

    //Test with a status without registered Packages
    packages =
        mPackageManager->getPackages(UnknownPackageStatus::getInstance());

    CPPUNIT_ASSERT_EQUAL((size_t)0, packages.size());

    //Test with a status with one registered Package
    packages =
        mPackageManager->getPackages(PackedPackageStatus::getInstance());

    CPPUNIT_ASSERT_EQUAL((size_t)1, packages.size());
    CPPUNIT_ASSERT_EQUAL(mPackage2, packages[0]);

    //Test with a status with two registered Packages
    packages =
        mPackageManager->getPackages(UnpackedPackageStatus::getInstance());

    CPPUNIT_ASSERT_EQUAL((size_t)2, packages.size());
    CPPUNIT_ASSERT_EQUAL(mPackage1, packages[0]);
    CPPUNIT_ASSERT_EQUAL(mPackage3, packages[1]);
}

void PackageManagerTest::testGetPackage() {
    //Test with a PackageId already registered
    Package* package = mPackageManager->getPackage(mPackage1->getPackageId());

    CPPUNIT_ASSERT_EQUAL(mPackage1, package);
    CPPUNIT_ASSERT_EQUAL(
                    (const PackageStatus*)UnpackedPackageStatus::getInstance(),
                    package->getPackageStatus());
    CPPUNIT_ASSERT_EQUAL((size_t)3, mPackageManager->mPackages.size());

    //Test with a PackageId not registered
    PackageId packageId("4");
    package = mPackageManager->getPackage(packageId);

    CPPUNIT_ASSERT(packageId == package->getPackageId());
    CPPUNIT_ASSERT_EQUAL(
                    (const PackageStatus*)UnknownPackageStatus::getInstance(),
                    package->getPackageStatus());
    CPPUNIT_ASSERT_EQUAL((size_t)4, mPackageManager->mPackages.size());
    CPPUNIT_ASSERT(packageId == mPackageManager->mPackages[3]->getPackageId());
}
