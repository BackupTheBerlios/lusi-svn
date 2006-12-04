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

#ifndef LUSI_UTIL_PROCESSRUNNERTEST_H
#define LUSI_UTIL_PROCESSRUNNERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {
class Process;
class ProcessRunner;
}
}

namespace lusi {
namespace util {

/**
 * Test class for ProcessRunner.
 *
 * @see ProcessRunner
 */
class ProcessRunnerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ProcessRunnerTest);
    CPPUNIT_TEST(testGetProcess);
    CPPUNIT_TEST(testGetStdoutData);
    CPPUNIT_TEST(testGetStderrData);
    CPPUNIT_TEST(testGetProcessExitedNumber);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the ProcessRunner and the Process.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if the Process set in the constructor is returned.
     */
    void testGetProcess();

    /**
     * Tests if all the data received in stdout is returned.
     */
    void testGetStdoutData();

    /**
     * Tests if all the data received in stderr is returned.
     */
    void testGetStderrData();

    /**
     * Tests if all the number of times the process exited is returned.
     */
    void testGetProcessExitedNumber();

private:

    /**
     * ProcessRunner to be tested.
     */
    ProcessRunner* mProcessRunner;

    /**
     * Process to use.
     */
    Process* mProcess;

};

}
}

#endif
