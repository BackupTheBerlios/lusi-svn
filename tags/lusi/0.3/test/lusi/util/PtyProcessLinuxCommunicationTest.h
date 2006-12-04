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

#ifndef LUSI_UTIL_PTYPROCESSLINUXCOMMUNICATIONTEST_H
#define LUSI_UTIL_PTYPROCESSLINUXCOMMUNICATIONTEST_H

#include "BaseProcessLinuxCommunicationTest.h"

namespace lusi {
namespace util {

/**
 * Test class for PtyProcessLinuxCommunication.
 * Uses BasePipeProcessLinuxCommunication. The test executed are an extended
 * version of testOpenCommunicationChannels and the base version of
 * testCloseCommunicationChannels.
 *
 * @see PtyProcessLinuxCommunication
 */
class PtyProcessLinuxCommunicationTest:
                public BaseProcessLinuxCommunicationTest {
    CPPUNIT_TEST_SUITE(PtyProcessLinuxCommunicationTest);
    CPPUNIT_TEST(testOpenCommunicationChannels);
    CPPUNIT_TEST(testCloseCommunicationChannels);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the PipeProcessLinuxCommunication.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Executes base tests and then checks that the file descriptors are ptys.
     */
    virtual void testOpenCommunicationChannels();

};

}
}

#endif
