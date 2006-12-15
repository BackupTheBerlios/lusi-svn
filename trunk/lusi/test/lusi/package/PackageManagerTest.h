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

#ifndef LUSI_PACKAGE_PACKAGEMANAGERTEST_H
#define LUSI_PACKAGE_PACKAGEMANAGERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace package {
class Package;
class PackageManager;
}
}

namespace lusi {
namespace package {

/**
 * Test class for PackageManager.
 *
 * @see PackageManager
 */
class PackageManagerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(PackageManagerTest);
    CPPUNIT_TEST(testSingleton);
    CPPUNIT_TEST(testGetPackages);
    CPPUNIT_TEST(testGetPackagesPackageStatus);
    CPPUNIT_TEST(testGetPackage);
    CPPUNIT_TEST(testRemovePackage);
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
     * Checks if getInstance() always returns the same not null reference.
     */
    void testSingleton();

    /**
     * Tests if getPackages() returns mPackages.
     */
    void testGetPackages();

    /**
     * Tests if all the Packages associated with the specified status are
     * returned. It is tested with a status without registered Packages, a
     * status with one Package and a status with two Packages.
     */
    void testGetPackagesPackageStatus();

    /**
     * Tests if the Package associated with the specified PackageId is
     * returned. It is also tested that, if the PackageId isn't
     * registered yet, a new Package is registered and returned.
     */
    void testGetPackage();

    /**
     * Tests if the Package data is removed from disk, if the PackageStatus is
     * removed from the Packages list and if the Profile is reverted to its
     * first PackageStatus.
     */
    void testRemovePackage();

private:

    /**
     * The PackageManager to test.
     * The tested PackageManager isn't the one got through getInstance. It's
     * created for each test.
     */
    PackageManager* mPackageManager;

    /**
     * The first Package registered with mPackageManager.
     */
    Package* mPackage1;

    /**
     * The second Package registered with mPackageManager.
     */
    Package* mPackage2;

    /**
     * The third Package registered with mPackageManager.
     */
    Package* mPackage3;

};

}
}

#endif
