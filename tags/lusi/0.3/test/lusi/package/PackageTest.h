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

#ifndef LUSI_PACKAGE_PACKAGETEST_H
#define LUSI_PACKAGE_PACKAGETEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace package {
class Package;
class PackageId;
}
}

namespace lusi {
namespace package {

/**
 * Test class for Package.
 *
 * @see Package
 */
class PackageTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(PackageTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetPackageId);
    CPPUNIT_TEST(testGetProfile);
    CPPUNIT_TEST(testGetResources);
    CPPUNIT_TEST(testGetResourceFiles);
    CPPUNIT_TEST(testGetPackageStatus);
    CPPUNIT_TEST(testSetPackageStatus);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Checks if the values are initialized in constructor as they should. It is
     * tested with a default PackageStatus and an explicit PackageStatus.
     */
    void testConstructor();

    /**
     * Checks if getPackageId() returns mPackageId.
     */
    void testGetPackageId();

    /**
     * Checks if getProfile() initializes the profile when it is called for
     * first time, and then it returns mProfile (always the same object).
     */
    void testGetProfile();

    /**
     * Checks if getResources() initializes the resources when it is called for
     * first time, and then it returns mResources (always the same object).
     */
    void testGetResources();

    /**
     * Checks if getResourceFiles() initializes the resource files when it is
     * called for first time, and then it returns mResourceFiles (always the
     * same object).
     */
    void testGetResourceFiles();

    /**
     * Checks if getPackageStatus() returns mPackageStatus.
     */
    void testGetPackageStatus();

    /**
     * Checks if setPackageStatus() sets mPackageStatus.
     */
    void testSetPackageStatus();

private:

    /**
     * The Package to test.
     */
    Package* mPackage;

    /**
     * The PackageId for the Package.
     */
    PackageId* mPackageId;

};

}
}

#endif
