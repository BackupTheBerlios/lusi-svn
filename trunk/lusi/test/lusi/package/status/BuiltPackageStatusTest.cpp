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

#include "BuiltPackageStatusTest.h"
#include "BuiltPackageStatus.h"

using namespace lusi::package::status;

//public:

void BuiltPackageStatusTest::setUp() {
}

void BuiltPackageStatusTest::tearDown() {
}

void BuiltPackageStatusTest::testSingleton() {
    CPPUNIT_ASSERT(BuiltPackageStatus::getInstance() != 0);

    CPPUNIT_ASSERT_EQUAL(BuiltPackageStatus::getInstance(),
            BuiltPackageStatus::getInstance());
}
