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

#include "ConfigurationPathsTest.h"

#define protected public
#define private public
#include "ConfigurationPaths.h"
#undef private
#undef protected

#include "../package/PackageId.h"
#include "../util/User.h"

using std::string;

using lusi::package::PackageId;
using lusi::util::User;

using namespace lusi::configuration;

//public:

void ConfigurationPathsTest::setUp() {
    mConfigurationPaths = new ConfigurationPaths();
}

void ConfigurationPathsTest::tearDown() {
    delete mConfigurationPaths;
}

void ConfigurationPathsTest::testConstructor() {
    //Test with default constructor
    CPPUNIT_ASSERT_EQUAL(User::getCurrentUser().getHome() + ".lusi/",
                         mConfigurationPaths->mBaseDirectory);

    //Test with constructor specifying the user
    delete mConfigurationPaths;
    mConfigurationPaths = new ConfigurationPaths(User(0));

    CPPUNIT_ASSERT_EQUAL(User(0).getHome() + ".lusi/",
                         mConfigurationPaths->mBaseDirectory);
}

void ConfigurationPathsTest::testGetBaseDirectory() {
    mConfigurationPaths->mBaseDirectory = "/home/sweetHome/.lusi/";

    CPPUNIT_ASSERT_EQUAL(mConfigurationPaths->mBaseDirectory,
                         mConfigurationPaths->getBaseDirectory());
}

void ConfigurationPathsTest::testGetPackagesBaseDirectory() {
    mConfigurationPaths->mBaseDirectory = "/home/sweetHome/.lusi/";

    CPPUNIT_ASSERT_EQUAL(mConfigurationPaths->mBaseDirectory + "package/",
                         mConfigurationPaths->getPackagesBaseDirectory());
}

void ConfigurationPathsTest::testGetPackageDirectory() {
    //Test with a PackageId with name and version
    PackageId packageId("kdevelop", "3.4");
    string packageDirectory =
                    mConfigurationPaths->getPackageDirectory(packageId);

    CPPUNIT_ASSERT_EQUAL(mConfigurationPaths->getPackagesBaseDirectory() +
                                                                "kdevelop/3.4/",
                         packageDirectory);

    //Test with a PackageId without version
    PackageId packageId2("kdevelop");
    packageDirectory = mConfigurationPaths->getPackageDirectory(packageId2);

    CPPUNIT_ASSERT_EQUAL(mConfigurationPaths->getPackagesBaseDirectory() +
                                                                "kdevelop/",
                         packageDirectory);
}

void ConfigurationPathsTest::testGetPackageFile() {
    PackageId packageId("testPackage");

    CPPUNIT_ASSERT_EQUAL(mConfigurationPaths->getPackageDirectory(packageId) +
                                                            "package-data.xml",
                         mConfigurationPaths->getPackageFile(packageId));
}

void ConfigurationPathsTest::testGetProfileFile() {
    PackageId packageId("testPackage");

    CPPUNIT_ASSERT_EQUAL(mConfigurationPaths->getPackageDirectory(packageId) +
                                                        "profile.xml",
                         mConfigurationPaths->getProfileFile(packageId));
}

void ConfigurationPathsTest::testGetTaskFile() {
    PackageId packageId("testPackage");
    string taskId("MakeTests");

    CPPUNIT_ASSERT_EQUAL(
        mConfigurationPaths->getPackageDirectory(packageId) + "MakeTests.xml",
        mConfigurationPaths->getTaskFile(taskId, packageId));
}
