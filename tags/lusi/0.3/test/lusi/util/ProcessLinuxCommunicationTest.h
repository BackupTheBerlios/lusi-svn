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

#ifndef LUSI_UTIL_PROCESSLINUXCOMMUNICATIONTEST_H
#define LUSI_UTIL_PROCESSLINUXCOMMUNICATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {
class ProcessLinuxCommunicationTestImplementation;
}
}

namespace lusi {
namespace util {

/**
 * Test class for ProcessLinuxCommunication.
 *
 * @see ProcessLinuxCommunication
 */
class ProcessLinuxCommunicationTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ProcessLinuxCommunicationTest);
    CPPUNIT_TEST(testNewProcessLinuxCommunication);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testOpenCommunicationChannels);
    CPPUNIT_TEST(testCloseCommunicationChannels);
    CPPUNIT_TEST(testGetChildStdin);
    CPPUNIT_TEST(testGetChildStdout);
    CPPUNIT_TEST(testGetChildStderr);
    CPPUNIT_TEST(testGetParentStdin);
    CPPUNIT_TEST(testGetParentStdout);
    CPPUNIT_TEST(testGetParentStderr);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the ProcessLinuxCommunicationTestImplementation.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if the returned ProcessLinuxCommunication is of the class it
     * should.
     */
    void testNewProcessLinuxCommunication();

    /**
     * Tests if mOpenCommunicationChannels is set to false and all the channels
     * to -1.
     */
    void testConstructor();

    /**
     * Tests if closeCommunicationChannels is called if the communication
     * channels are opened, and if mOpenCommunicationChannels is set to true.
     */
    void testOpenCommunicationChannels();

    /**
     * Tests if mOpenCommunicationChannels is set to false and all the channels
     * to -1.
     */
    void testCloseCommunicationChannels();

    /**
     * Tests if getChildStdin returns mChildStdin.
     */
    void testGetChildStdin();

    /**
     * Tests if getChildStdout returns mChildStdout.
     */
    void testGetChildStdout();

    /**
     * Tests if getChildStderr returns mChildStderr.
     */
    void testGetChildStderr();

    /**
     * Tests if getParentStdin returns mParentStdin.
     */
    void testGetParentStdin();

    /**
     * Tests if getParentStdout returns mParentStdout.
     */
    void testGetParentStdout();

    /**
     * Tests if getParentStderr returns mParentStderr.
     */
    void testGetParentStderr();

private:

    /**
     * The ProcessLinuxCommunication to test.
     */
    ProcessLinuxCommunicationTestImplementation* mProcessLinuxCommunication;

};

}
}

#endif
