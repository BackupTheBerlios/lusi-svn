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

#ifndef LUSI_PACKAGE_PROFILETEST_H
#define LUSI_PACKAGE_PROFILETEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace package {
class Package;
class Profile;
}
}

namespace lusi {
namespace package {

/**
 * Test class for Profile.
 *
 * @see Profile
 */
class ProfileTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ProfileTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetAllPackageStatus);
    CPPUNIT_TEST(testGetPackageStatus);
    CPPUNIT_TEST(testGetResources);
    CPPUNIT_TEST(testGetTaskId);
    CPPUNIT_TEST(testSetResources);
    CPPUNIT_TEST(testSetTaskId);
    CPPUNIT_TEST(testAddPackageStatus);
    CPPUNIT_TEST(testRevertPackageStatus);
    CPPUNIT_TEST(testLoadSave);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     * Removes the files created by the tests.
     */
    virtual void tearDown();

    /**
     * Tests if a previously saved Profile is loaded. It is also loaded that,
     * if no saved Profile existed, a new Profile is created with
     * UnknownPackageStatus, and an empty Task id and empty resources.
     */
    void testConstructor();

    /**
     * Tests if all the PackageStatus from first to current are returned.
     */
    void testGetAllPackageStatus();

    /**
     * Tests if the PackageStatus got from the id of mCurrentConfiguration is
     * returned.
     */
    void testGetPackageStatus();

    /**
     * Tests if the resources returned are those of mCurrentConfiguration.
     */
    void testGetResources();

    /**
     * Tests if the Task id returned is the one saved in mCurrentConfiguration.
     */
    void testGetTaskId();

    /**
     * Tests if the specified resources are copied to the resources in
     * mCurrentConfiguration, and that the previous resources are removed.
     */
    void testSetResources();

    /**
     * Tests if the Task id in mCurrentConfiguration is set.
     */
    void testSetTaskId();

    /**
     * Tests if the PackageStatus is added and set as current PackageStatus.
     * It is also tested that an empty Task id and empty resources are set if
     * the current PackageStatus was the last.
     * If the next PackageStatus was different from the one set, it is tested
     * that all the next PackageStatus are removed and a new one added.
     * If the PackageStatus is the same as the next, it is tested thatthe next
     * is set as current.
     */
    void testAddPackageStatus();

    /**
     * Tests if the PackageStatus specified is set as the current one, and the
     * resources of all the next PackageStatus are cleaned. It is also tested
     * that, if the PackageStatus wasn't in the list of previous PackageStatus
     * (because it wasn't at all, or because it was after the current one)
     * nothing is done.
     */
    void testRevertPackageStatus();

    /**
     * Tests if the previously saved resources can be loaded. It is also tested
     * with a reverted PackageStatus.
     */
    void testLoadSave();

private:

    /**
     * The Profile to test.
     */
    Profile* mProfile;

    /**
     * The Package of mProfile.
     */
    Package* mPackage;

};

}
}

#endif
