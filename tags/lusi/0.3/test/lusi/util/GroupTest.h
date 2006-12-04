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

#ifndef LUSI_UTIL_GROUPTEST_H
#define LUSI_UTIL_GROUPTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {

/**
 * Test class for Group.
 *
 * @see Group
 */
class GroupTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(GroupTest);
    CPPUNIT_TEST(testConstructorId);
    CPPUNIT_TEST(testConstructorName);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testExists);
    CPPUNIT_TEST(testGetId);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST(testIsRoot);
    CPPUNIT_TEST(testOperatorAssignment);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorDifferent);
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
     * Tests if the constructor using the id sets all the fields.
     */
    void testConstructorId();

    /**
     * Tests if the constructor using the name sets all the fields.
     */
    void testConstructorName();

    /**
     * Tests if the copy constructor copies all the fields.
     */
    void testCopyConstructor();

    /**
     * Tests if a valid group exists and an invalid group doesn't exist.
     */
    void testExists();

    /**
     * Tests if it returns mId.
     */
    void testGetId();

    /**
     * Tests if it returns mName.
     */
    void testGetName();

    /**
     * Tests if for root group returns true and for other group returns false.
     */
    void testIsRoot();

    /**
     * Tests if the operator assignment copies all the fields and returns the
     * Group. It also checks against self assignment.
     */
    void testOperatorAssignment();

    /**
     * Tests if the operator equal returns true for equal groups and false for
     * different groups.
     */
    void testOperatorEqual();

    /**
     * Tests if the operator different returns true for different groups and
     * false for equal groups.
     */
    void testOperatorDifferent();

};

}
}

#endif
