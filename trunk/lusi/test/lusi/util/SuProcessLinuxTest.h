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

#ifndef LUSI_UTIL_SUPROCESSLINUXTEST_H
#define LUSI_UTIL_SUPROCESSLINUXTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {
class ProcessObserverTestImplementation;
class SuProcessLinux;
}
}

namespace lusi {
namespace util {

/**
 * Test class for SuProcessLinux.
 * Asserts involving another user and a right password are disabled, as the
 * user name and password to test change depending on the computer where
 * the tests are run. To enable them, set mValidUserName and mValidPassword.
 *
 * @see SuProcessLinux
 */
class SuProcessLinuxTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SuProcessLinuxTest);
    CPPUNIT_TEST(testStart);
    CPPUNIT_TEST(testNormalExit);
    CPPUNIT_TEST(testGetExitStatus);
    CPPUNIT_TEST(testCheckUserName);
    CPPUNIT_TEST(testCheckPassword);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the observer and the SuProcessLinux, and attachs the observer to
     * the SuProcessLinux.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if a wrong user or password fails when trying to execute a process,
     * if trying to execute a process with the current user doesn't need
     * password and trying to execute a process with another user with a right
     * password.
     *
     * Asserts involving another user and a right password are disabled, as the
     * user name and password to test change depending on the computer where
     * the tests are run. To enable them, set mValidUserName and mValidPassword.
     * Those asserts are also run ten times to check, at least to some degree,
     * that there are no race conditions. It makes the whole tests very slow.
     */
    void testStart();

    /**
     * Tests if a process not executed (one not started and one not switched)
     * returns false, and if a process exited cleanly and a process exited with
     * errors return true (both switching and without switching).
     */
    void testNormalExit();

    /**
     * Tests if a process exited cleanly returns 0 and if a process exited with
     * errors returns a status != 0 (both switching and without switching).
     */
    void testGetExitStatus();

    /**
     * Tests if a wrong user throws an exception and if a right user doesn't.
     */
    void testCheckUserName();

    /**
     * Tests if a wrong password throws an exception, if a right user doesn't,
     * and, in both cases, if mProcessLinux is restored after executing the
     * check.
     *
     * Assert involving another user and a right password is disabled, as the
     * user name and password to test change depending on the computer where
     * the tests are run. To enable them, set mValidUserName and mValidPassword.
     */
    void testCheckPassword();

private:

    /**
     * SuProcessLinux to be tested.
     */
    SuProcessLinux* mSuProcessLinux;

    /**
     * ProcessObserver for updates in the SuProcessLinux.
     */
    ProcessObserverTestImplementation* mProcessObserver;

    /**
     * The user name to use when testing switching to a valid user.
     */
    std::string mValidUserName;

    /**
     * The password to use when testing switching to a valid user.
     */
    std::string mValidPassword;



    /**
     * Calls tearDown and setUp.
     */
    void restartTestObjects();

};

}
}

#endif
