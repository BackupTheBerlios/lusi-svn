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

#ifndef LUSI_UTIL_LOCALURLTEST_H
#define LUSI_UTIL_LOCALURLTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {

class LocalUrlTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(LocalUrlTest);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testIsDirectory);
    CPPUNIT_TEST(testIsRelative);
    CPPUNIT_TEST(testGetDirectory);
    CPPUNIT_TEST(testGetExtension);
    CPPUNIT_TEST(testGetFileName);
    CPPUNIT_TEST(testGetPath);
    CPPUNIT_TEST(testAppendRelativePathToDirectory);
    CPPUNIT_TEST(testOperatorAssignment);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorDifferent);
    CPPUNIT_TEST(testCleanPath);
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
     * Tests if the copy constructor copies all the fields.
     */
    void testCopyConstructor();

    /**
     * Tests if the path represents a directory.
     */
    void testIsDirectory();

    /**
     * Tests if the path is relative.
     */
    void testIsRelative();

    /**
     * Tests if the string returned is the directory in the path.
     */
    void testGetDirectory();

    /**
     * Tests if the string returned is the extension in the path.
     */
    void testGetExtension();

    /**
     * Tests if the string returned is the file name in the path.
     */
    void testGetFileName();

    /**
     * Tests if the string returned is the path stored.
     */
    void testGetPath();

    /**
     * Tests if relative paths are appended to the directory path.
     */
    void testAppendRelativePathToDirectory();

    /**
     * Tests if the assignment copies all the fields.
     */
    void testOperatorAssignment();

    /**
     * Tests if the LocalUrl is equal to other LocalUrls.
     */
    void testOperatorEqual();

    /**
     * Tests if the LocalUrl is different to other LocalUrls.
     */
    void testOperatorDifferent();

    /**
     * Tests if the paths are cleaned of self and parent references.
     */
    void testCleanPath();

};

}
}

#endif
