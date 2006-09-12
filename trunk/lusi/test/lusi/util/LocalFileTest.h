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

#ifndef LUSI_UTIL_LOCALFILETEST_H
#define LUSI_UTIL_LOCALFILETEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {

/**
 * Test class for LocalFile.
 *
 * @see LocalFile
 */
class LocalFileTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(LocalFileTest);
    CPPUNIT_TEST(testExistsString);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testExists);
    CPPUNIT_TEST(testGetGroup);
    CPPUNIT_TEST(testGetLocalUrl);
    CPPUNIT_TEST(testGetAbsoluteLocalUrl);
    CPPUNIT_TEST(testGetOwner);
    CPPUNIT_TEST(testIsExecutable);
    CPPUNIT_TEST(testIsReadable);
    CPPUNIT_TEST(testIsWritable);
    CPPUNIT_TEST(testGetValidPath);
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
     * Tests if a file that exists returns true and a file that doesn't exist
     * return false (both with relative and absolute URLs).
     */
    void testExistsString();

    /**
     * Tests if a file uses the specifed url, if a directory with a directory
     * url uses that url, and if a directory with a file url uses the same url
     * but changed to directory syntax (with ending "/").
     */
    void testConstructor();

    /**
     * Tests if a file that exists returns true and a file that doesn't exist
     * return false (both with relative and absolute URLs).
     */
    void testExists();

    /**
     * Tests if it returns the group of an existing file and the group of the
     * first existing parent of a file that doesn't exist.
     */
    void testGetGroup();

    /**
     * Tests if it returns mLocalUrl.
     */
    void testGetLocalUrl();

    /**
     * Tests if it returns mLocalUrl for absolute urls, and mLocalUrl appended
     * to the current working directory if it's relative.
     */
    void testGetAbsoluteLocalUrl();

    /**
     * Tests if it returns the owner of an existing file and the owner of the
     * first existing parent of a file that doesn't exist.
     */
    void testGetOwner();

    /**
     * Tests if a file executable by the user returns true and a file not
     * executable by the user returns false. It's checked using files owned
     * and not owned by the user.
     * Also non existent files are tested.
     *
     * @todo Test groups.
     */
    void testIsExecutable();

    /**
     * Tests if a file readable by the user returns true and a file not
     * readable by the user returns false. It's checked using files owned
     * (only readables) and not owned by the user (readables and not).
     * Also non existent files are tested.
     *
     * @todo Test groups.
     */
    void testIsReadable();

    /**
     * Tests if a file writable by the user returns true and a file not
     * writable by the user returns false. It's checked using files owned
     * (only writables) and not owned by the user (writables and not).
     * Also non existent files are tested.
     *
     * @todo Test groups.
     */
    void testIsWritable();

    /**
     * Tests if it returns the path of a file that exists, the path to the first
     * parent of a file that doesn't exist, and the path to the first accesible
     * file in a file without the needed permissions to access to it.
     * It's also tested using relative urls instead of absolute ones.
     */
    void testGetValidPath();

};

}
}

#endif
