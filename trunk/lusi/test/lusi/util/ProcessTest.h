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

#ifndef LUSI_UTIL_PROCESSTEST_H
#define LUSI_UTIL_PROCESSTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {
class Process;
class ProcessObserver;
}
}

namespace lusi {
namespace util {

/**
 * Test class for Process.
 *
 * @see Process
 */
class ProcessTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ProcessTest);
    CPPUNIT_TEST(testGetArguments);
    CPPUNIT_TEST(testGetArgumentsAsString);
    CPPUNIT_TEST(testGetWorkingDirectory);
    CPPUNIT_TEST(testSetWorkingDirectory);
    CPPUNIT_TEST(testAttachObserver);
    CPPUNIT_TEST(testDetachObserver);
    CPPUNIT_TEST(testOperatorAppend);
    CPPUNIT_TEST(testNotifyReceivedStdout);
    CPPUNIT_TEST(testNotifyReceivedStderr);
    CPPUNIT_TEST(testNotifyProcessExited);
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
     * Tests if the arguments returned are the same as the added with
     * operator<<.
     */
    void testGetArguments();

    /**
     * Tests if the arguments returned as a string contains all the arguments with
     * a blank space between them.
     */
    void testGetArgumentsAsString();

    /**
     * Tests if mWorkingDirectory is returned.
     */
    void testGetWorkingDirectory();

    /**
     * Tests if the working directory is set in the mWorkingDirectory attribute.
     */
    void testSetWorkingDirectory();

    /**
     * Tests if ProcessObservers are attached as they should.
     */
    void testAttachObserver();

    /**
     * Tests if ProcessObservers are detached as they should.
     */
    void testDetachObserver();

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

private:

    /**
     * First ProcessObserver.
     */
    ProcessObserver* mProcessObserver1;

    /**
     * Second ProcessObserver.
     */
    ProcessObserver* mProcessObserver2;

    /**
     * Third ProcessObserver.
     */
    ProcessObserver* mProcessObserver3;

    /**
     * Process to be tested.
     */
    Process* mProcess;

};

}
}

#endif
