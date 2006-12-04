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

#ifndef LUSI_PACKAGE_PACKAGEIDTEST_H
#define LUSI_PACKAGE_PACKAGEIDTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace package {
class PackageId;
}
}

namespace lusi {
namespace package {

/**
 * Test class for PackageId.
 *
 * @see PackageId
 */
class PackageIdTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(PackageIdTest);
    CPPUNIT_TEST(testCompareVersions);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST(testGetVersion);
    CPPUNIT_TEST(testOperatorAssignment);
    CPPUNIT_TEST(testOperatorEqual);
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
     * Checks if the versions are compared as they should. That is checked with
     * two versions with the same number of subversions and with two versions
     * with different number of subversions. The checks are also made with
     * a string lexicographically greater than other but smaller in version
     * terms, and with all the non numerical values.
     */
    void testCompareVersions();

    /**
     * Checks if all the values are well set in the constructor. It is tested
     * also using the default version.
     */
    void testConstructor();

    /**
     * Checks if the copy constructor copies all the fields.
     */
    void testCopyConstructor();

    /**
     * Checks if getName() returns mName.
     */
    void testGetName();

    /**
     * Checks if getVersion() returns mVersion.
     */
    void testGetVersion();

    /**
     * Tests if the operator assignment copies all the fields and returns the
     * PackageId. It also checks against self assignment.
     */
    void testOperatorAssignment();

    /**
     * Tests if the operator equal returns true for equal PackageIds and false
     * for different PackageIds.
     */
    void testOperatorEqual();

private:

    /**
     * The PackageId to test.
     */
    PackageId* mPackageId;

};

}
}

#endif
