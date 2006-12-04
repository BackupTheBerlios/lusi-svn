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

#include <memory>

#include "ProcessLinuxCommunicationTest.h"

#define protected public
#define private public
#include "ProcessLinuxCommunicationTestImplementation.h"
#undef private
#undef protected

#include "PipeProcessLinuxCommunication.h"
#include "PtyProcessLinuxCommunication.h"

using std::auto_ptr;

using namespace lusi::util;

//public:

void ProcessLinuxCommunicationTest::setUp() {
     mProcessLinuxCommunication =
                        new ProcessLinuxCommunicationTestImplementation();
}

void ProcessLinuxCommunicationTest::tearDown() {
    delete mProcessLinuxCommunication;
}

void ProcessLinuxCommunicationTest::testNewProcessLinuxCommunication() {
    auto_ptr<ProcessLinuxCommunication> processLinuxCommunication =
            auto_ptr<ProcessLinuxCommunication>(
                    ProcessLinuxCommunication::newProcessLinuxCommunication(
                            Process::PipeCommunication));
    CPPUNIT_ASSERT(0 != dynamic_cast<PipeProcessLinuxCommunication*>
                            (processLinuxCommunication.get()));

    processLinuxCommunication = auto_ptr<ProcessLinuxCommunication>(
            ProcessLinuxCommunication::newProcessLinuxCommunication(
                    Process::PtyCommunication));
    CPPUNIT_ASSERT(0 != dynamic_cast<PtyProcessLinuxCommunication*>
                            (processLinuxCommunication.get()));
}

void ProcessLinuxCommunicationTest::testConstructor() {
    CPPUNIT_ASSERT_EQUAL(false,
            mProcessLinuxCommunication->mOpenCommunicationChannels);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mChildStdin);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mChildStdout);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mChildStderr);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mParentStdin);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mParentStdout);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mParentStderr);
}

void ProcessLinuxCommunicationTest::testOpenCommunicationChannels() {
    mProcessLinuxCommunication->openCommunicationChannels();

    CPPUNIT_ASSERT_EQUAL(true,
            mProcessLinuxCommunication->mOpenCommunicationChannels);
    CPPUNIT_ASSERT_EQUAL(false,
            mProcessLinuxCommunication->mCloseCommunicationChannelsCalled);

    //Test with already opened channels
    mProcessLinuxCommunication->openCommunicationChannels();

    CPPUNIT_ASSERT_EQUAL(true,
            mProcessLinuxCommunication->mOpenCommunicationChannels);
    CPPUNIT_ASSERT_EQUAL(true,
            mProcessLinuxCommunication->mCloseCommunicationChannelsCalled);
}

void ProcessLinuxCommunicationTest::testCloseCommunicationChannels() {
    mProcessLinuxCommunication->mOpenCommunicationChannels = true;
    mProcessLinuxCommunication->mChildStdin = 4;
    mProcessLinuxCommunication->mChildStdout = 8;
    mProcessLinuxCommunication->mChildStderr = 15;
    mProcessLinuxCommunication->mParentStdin = 16;
    mProcessLinuxCommunication->mParentStdout = 23;
    mProcessLinuxCommunication->mParentStderr = 42;
    mProcessLinuxCommunication->closeCommunicationChannels();

    CPPUNIT_ASSERT_EQUAL(false,
            mProcessLinuxCommunication->mOpenCommunicationChannels);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mChildStdin);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mChildStdout);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mChildStderr);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mParentStdin);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mParentStdout);
    CPPUNIT_ASSERT_EQUAL(-1, mProcessLinuxCommunication->mParentStderr);
}

void ProcessLinuxCommunicationTest::testGetChildStdin() {
    mProcessLinuxCommunication->mChildStdin = 4;

    CPPUNIT_ASSERT_EQUAL(4, mProcessLinuxCommunication->getChildStdin());
}

void ProcessLinuxCommunicationTest::testGetChildStdout() {
    mProcessLinuxCommunication->mChildStdout = 8;

    CPPUNIT_ASSERT_EQUAL(8, mProcessLinuxCommunication->getChildStdout());
}

void ProcessLinuxCommunicationTest::testGetChildStderr() {
    mProcessLinuxCommunication->mChildStderr = 15;

    CPPUNIT_ASSERT_EQUAL(15, mProcessLinuxCommunication->getChildStderr());
}

void ProcessLinuxCommunicationTest::testGetParentStdin() {
    mProcessLinuxCommunication->mParentStdin = 16;

    CPPUNIT_ASSERT_EQUAL(16, mProcessLinuxCommunication->getParentStdin());
}

void ProcessLinuxCommunicationTest::testGetParentStdout() {
    mProcessLinuxCommunication->mParentStdout = 23;

    CPPUNIT_ASSERT_EQUAL(23, mProcessLinuxCommunication->getParentStdout());
}

void ProcessLinuxCommunicationTest::testGetParentStderr() {
    mProcessLinuxCommunication->mParentStderr = 42;

    CPPUNIT_ASSERT_EQUAL(42, mProcessLinuxCommunication->getParentStderr());
}
