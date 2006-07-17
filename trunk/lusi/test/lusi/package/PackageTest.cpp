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

#include "PackageTest.h"
#include "Package.h"
#include "PackageId.h"
#include "status/BuiltPackageStatus.h"
#include "status/UnknownPackageStatus.h"

using lusi::package::status::BuiltPackageStatus;
using lusi::package::status::PackageStatus;
using lusi::package::status::UnknownPackageStatus;

using namespace lusi::package;

//public:

void PackageTest::setUp() {
    mPackageId = new PackageId("Scorched3D");
    mPackage = new Package(mPackageId);
}

void PackageTest::tearDown() {
    delete mPackage;
    delete mPackageId;
}

void PackageTest::testGetPackageId() {
    CPPUNIT_ASSERT_EQUAL(mPackageId, mPackage->getPackageId());
}

//TODO Check getProfile
void PackageTest::testGetProfile() {
}

//TODO Check getResourceMap
void PackageTest::testGetResourceMap() {
}

void PackageTest::testGetPackageStatus() {
    //Test constructor with default PackageStatus
    CPPUNIT_ASSERT_EQUAL(static_cast<const PackageStatus*>
                                (UnknownPackageStatus::getInstance()),
                         mPackage->getPackageStatus());

    delete mPackage;
    mPackage = new Package(mPackageId, BuiltPackageStatus::getInstance());

    //Test constructor with explicit PackageStatus
    CPPUNIT_ASSERT_EQUAL(static_cast<const PackageStatus*>
                                (BuiltPackageStatus::getInstance()),
                         mPackage->getPackageStatus());
}

void PackageTest::testSetPackageStatus() {
    mPackage->setPackageStatus(BuiltPackageStatus::getInstance());
    CPPUNIT_ASSERT_EQUAL(static_cast<const PackageStatus*>
                                (BuiltPackageStatus::getInstance()),
                         mPackage->getPackageStatus());
}
