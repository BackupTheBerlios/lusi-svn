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
    CPPUNIT_TEST_SUITE(ProcessLinuxTest);
    CPPUNIT_TEST(testNotifyReceivedStdout);
    CPPUNIT_TEST(testNotifyReceivedStderr);
    CPPUNIT_TEST(testNotifyProcessExited);
    CPPUNIT_TEST(testSetWorkingDirectory);
    CPPUNIT_TEST(testStart);
    CPPUNIT_TEST(testWriteData);
    CPPUNIT_TEST(testNormalExit);
    CPPUNIT_TEST(testGetExitStatus);
    CPPUNIT_TEST(testGetProcessLinuxCommunication);
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

    /**
     * Tests if writing data to an unstarted process and a finished process
     * returns false.
     * TODO: test if a running process receives well the sent data (it wasn't
     * done due to the need of threads).
     */
    void testWriteData();

    /**
     * Tests if a process not executed and one failed return false, and if a
     * process exited cleanly and a process exited with errors return true.
     */
    void testNormalExit();

    /**
     * Tests if a process exited cleanly returns 0 and if a process exited with
     * errors returns a status != 0.
     */
    void testGetExitStatus();

    /**
     * Tests if getProcessLinuxCommunication returns mProcessLinuxCommunication.
     */
    void testGetProcessLinuxCommunication();

private:

    /**
     * ProcessLinux using pipe communication to be tested.
     */
    ProcessLinux* mPipeProcessLinux;

    /**
     * ProcessLinux using pty communication to be tested.
     */
    ProcessLinux* mPtyProcessLinux;

    /**
     * ProcessObserver for updates in the ProcessLinux using pipe communication.
     */
    ProcessObserverTestImplementation* mPipeProcessObserver;

    /**
     * ProcessObserver for updates in the ProcessLinux using pty communication.
     */
    ProcessObserverTestImplementation* mPtyProcessObserver;



    /**
     * Calls tearDown and setUp.
     */
    void restartTestObjects();
};

}
}

#endif
