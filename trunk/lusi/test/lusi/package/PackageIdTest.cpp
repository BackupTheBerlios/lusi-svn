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

#include "PackageIdTest.h"
#include "PackageId.h"

using std::string;

using namespace lusi::package;

//public:

void PackageIdTest::setUp() {
}

void PackageIdTest::tearDown() {
}

void PackageIdTest::testCompareVersions() {
    //Test only with major versions
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1", "2"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("01", "2"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("10", "2"));
    CPPUNIT_ASSERT(0 == PackageId::compareVersions("0", "0"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("", "0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1", ""));

    //Test with major versions that have subversions
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1", "2.0"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("01.1", "2.0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("10.0", "2.0"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("", "0.1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1", ""));

    //Test with subversions (and the same number of subversions)
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.0", "1.0.1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.01", "1.0.2"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.10", "1.0.20"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.2", "1.0.1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.10", "1.0.1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.10", "1.0.2"));
    CPPUNIT_ASSERT(0 == PackageId::compareVersions("1.0.1", "1.0.1"));

    //Test with subversions (and different number of subversions)
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.0", "1.0.0.1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.10", "1.1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.1.1", "1.0.1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.2", "1.1.10"));

    //Test with non numerical versions
    //Test with alpha
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-alpha1", "1.1-alpha2"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-alpha01", "1.1-alpha2"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-alpha2", "1.1-alpha1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-alpha10", "1.1-alpha2"));
    CPPUNIT_ASSERT(0 == PackageId::compareVersions("1.1-alpha1", "1.1-alpha1"));

    //Test with beta
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-beta1", "1.1-beta2"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-beta01", "1.1-beta2"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-beta2", "1.1-beta1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-beta10", "1.1-beta2"));
    CPPUNIT_ASSERT(0 == PackageId::compareVersions("1.1-beta1", "1.1-beta1"));

    //Test with rc
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-rc1", "1.1-rc2"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-rc01", "1.1-rc2"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-rc2", "1.1-rc1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-rc10", "1.1-rc2"));
    CPPUNIT_ASSERT(0 == PackageId::compareVersions("1.1-rc1", "1.1-rc1"));

    //Test mixing alpha, beta and rc
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-alpha1", "1.1-beta1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-alpha2", "1.1-beta1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-alpha1", "1.1-rc1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-alpha2", "1.1-rc1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-beta1", "1.1-rc1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.1-beta2", "1.1-rc1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-beta1", "1.1-alpha1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-beta1", "1.1-alpha2"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-rc1", "1.1-alpha1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-rc1", "1.1-alpha2"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-rc1", "1.1-beta1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.1-rc1", "1.1-beta2"));

    //Test mixing alpha, beta, rc and numerical versions
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.1-alpha1", "1.0.1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.1-beta1", "1.0.1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.1-rc1", "1.0.1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.1-alpha1", "1.1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.1-beta1", "1.1"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.1-rc1", "1.1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.1-alpha1", "1.0.0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.1-beta1", "1.0.0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.1-rc1", "1.0.0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.1-alpha1", "1.0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.1-beta1", "1.0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("1.0.1-rc1", "1.0"));

    //Test with versions not following the default regular expression
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.0.1-gamma1", "2.0.0"));
    CPPUNIT_ASSERT(0 > PackageId::compareVersions("1.-gamma1", "2.0.0"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("2.0.0", "1.0.1-gamma1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("2.0.0", "1.-gamma1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("2.0.0", "2.0.0-gamma1"));
    CPPUNIT_ASSERT(0 < PackageId::compareVersions("2.0.0", "2.0.-gamma1"));
}

void PackageIdTest::testGetName() {
    PackageId packageId("wesnoth");
    CPPUNIT_ASSERT_EQUAL(string("wesnoth"), packageId.getName());
}

void PackageIdTest::testGetVersion() {
    PackageId packageIdDefault("wesnoth");
    CPPUNIT_ASSERT_EQUAL(string(""), packageIdDefault.getVersion());

    PackageId packageId("wesnoth", "1.0");
    CPPUNIT_ASSERT_EQUAL(string("1.0"), packageId.getVersion());
}
