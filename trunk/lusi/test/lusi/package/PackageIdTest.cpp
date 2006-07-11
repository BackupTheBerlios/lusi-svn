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
