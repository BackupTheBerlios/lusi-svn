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

#include "PackageStatusTestSuite.h"
#include "BuiltPackageStatusTest.h"
#include "ConfiguredPackageStatusTest.h"
#include "InstalledPackageStatusTest.h"
#include "PackedPackageStatusTest.h"
#include "UnknownPackageStatusTest.h"
#include "UnpackedPackageStatusTest.h"

using namespace lusi::package::status;

//public:

PackageStatusTestSuite::PackageStatusTestSuite() {
    //Own namespace Tests
    addTest(BuiltPackageStatusTest::suite());
    addTest(ConfiguredPackageStatusTest::suite());
    addTest(InstalledPackageStatusTest::suite());
    addTest(PackedPackageStatusTest::suite());
    addTest(UnknownPackageStatusTest::suite());
    addTest(UnpackedPackageStatusTest::suite());

    //Direct child namespaces TestSuites
}
