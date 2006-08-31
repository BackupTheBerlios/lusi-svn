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

#ifndef LUSI_UTIL_SUPROCESSTEST_H
#define LUSI_UTIL_SUPROCESSTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {
class SuProcess;
}
}

namespace lusi {
namespace util {

/**
 * Test class for SuProcess.
 *
 * @see SuProcess
 */
class SuProcessTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SuProcessTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetUserName);
    CPPUNIT_TEST(testSetUserName);
    CPPUNIT_TEST(testSetPassword);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the SuProcess.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if the user name and the password are set to "".
     */
    void testConstructor();

    /**
     * Tests if getUserName returns mUserName.
     */
    void testGetUserName();

    /**
     * Tests if setUserName sets mUserName.
     */
    void testSetUserName();

    /**
     * Tests if setPassword sets mPassword.
     */
    void testSetPassword();

private:

    /**
     * SuProcess to be tested.
     */
    SuProcess* mSuProcess;

};

}
}

#endif
