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

#ifndef LUSI_UTIL_PROCESSLINUXTEST_H
#define LUSI_UTIL_PROCESSLINUXTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {
class ProcessLinux;
class ProcessObserverTestImplementation;
}
}

namespace lusi {
namespace util {

/**
 * Test class for ProcessLinux.
 *
 * @see ProcessLinux
 */
class ProcessLinuxTest: public CppUnit::TestFixture {
public:
    CPPUNIT_TEST_SUITE(ProcessLinuxTest);
    CPPUNIT_TEST(testOperatorAppend);
    CPPUNIT_TEST(testNotifyReceivedStdout);
    CPPUNIT_TEST(testNotifyReceivedStderr);
    CPPUNIT_TEST(testNotifyProcessExited);
    CPPUNIT_TEST(testSetWorkingDirectory);
    CPPUNIT_TEST(testStart);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates all the observers and the Process, and attachs the observers to
     * the Process.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if the operator << appends arguments to the arguments list.
     */
    void testOperatorAppend();

    /**
     * Tests if the registered observers are notified when new data is received
     * in stdout.
     */
    void testNotifyReceivedStdout();

    /**
     * Tests if the registered observers are notified when new data is received
     * in stderr.
     */
    void testNotifyReceivedStderr();

    /**
     * Tests if the registered observers are notified when the Process exits.
     */
    void testNotifyProcessExited();

    /**
     * Tests if the working directory is taken into account when executing the
     * process.
     */
    void testSetWorkingDirectory();

    /**
     * Tests start method with bad process (non existent, without full path...).
     */
    void testStart();

private:

    /**
     * ProcessLinux to be tested.
     */
    ProcessLinux* mProcessLinux;

    /**
     * ProcessObserver for updates in the ProcessLinux.
     */
    ProcessObserverTestImplementation* mProcessObserver;



    /**
     * Calls tearDown and setUp.
     */
    void restartTestObjects();
};

}
}

#endif
