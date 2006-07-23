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

#include <string>

#include "ProcessTest.h"

#define protected public
#define private public
#include "ProcessTestImplementation.h"
#undef private
#undef protected

#include "ProcessObserverTestImplementation.h"

using std::string;

using namespace lusi::util;

//public:

void ProcessTest::setUp() {
    mProcessObserver1 = new ProcessObserverTestImplementation();
    mProcessObserver2 = new ProcessObserverTestImplementation();
    mProcessObserver3 = new ProcessObserverTestImplementation();
    mProcess = new ProcessTestImplementation();

    mProcess->attachObserver(mProcessObserver1);
    mProcess->attachObserver(mProcessObserver2);
    mProcess->attachObserver(mProcessObserver3);
}

void ProcessTest::tearDown() {
    delete mProcessObserver1;
    delete mProcessObserver2;
    delete mProcessObserver3;
    delete mProcess;
}

void ProcessTest::testAttachObserver() {
    CPPUNIT_ASSERT(mProcess->mProcessObservers.size() == 3);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver1, mProcess->mProcessObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver2, mProcess->mProcessObservers[1]);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver3, mProcess->mProcessObservers[2]);

    //Adding repeated elements
    mProcess->attachObserver(mProcessObserver2);

    CPPUNIT_ASSERT(mProcess->mProcessObservers.size() == 3);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver1, mProcess->mProcessObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver2, mProcess->mProcessObservers[1]);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver3, mProcess->mProcessObservers[2]);
}

void ProcessTest::testDetachObserver() {
    mProcess->detachObserver(mProcessObserver2);

    CPPUNIT_ASSERT(mProcess->mProcessObservers.size() == 2);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver1, mProcess->mProcessObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver3, mProcess->mProcessObservers[1]);

    //Detaching an already detached observer
    mProcess->detachObserver(mProcessObserver2);

    CPPUNIT_ASSERT(mProcess->mProcessObservers.size() == 2);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver1, mProcess->mProcessObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mProcessObserver3, mProcess->mProcessObservers[1]);

    //Detaching all the observers
    mProcess->detachObserver(mProcessObserver1);
    mProcess->detachObserver(mProcessObserver3);

    CPPUNIT_ASSERT(mProcess->mProcessObservers.size() == 0);
}

void ProcessTest::testNotifyReceivedStdout() {
    ProcessObserverTestImplementation* processObserver1 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver1);
    ProcessObserverTestImplementation* processObserver2 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver2);
    ProcessObserverTestImplementation* processObserver3 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver3);

    mProcess->notifyReceivedStdout("Kwai");

    CPPUNIT_ASSERT_EQUAL(string("Kwai"),
            processObserver1->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Kwai"),
            processObserver2->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Kwai"),
            processObserver3->getStdoutLastData());

    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver1->getStdoutLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver2->getStdoutLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver3->getStdoutLastProcess());

    mProcess->detachObserver(processObserver1);
    mProcess->notifyReceivedStdout("Caine");

    CPPUNIT_ASSERT_EQUAL(string("Kwai"),
            processObserver1->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Caine"),
            processObserver2->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Caine"),
            processObserver3->getStdoutLastData());

    CPPUNIT_ASSERT_EQUAL((Process*)0,
            processObserver1->getStdoutLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver2->getStdoutLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver3->getStdoutLastProcess());

    mProcess->detachObserver(processObserver3);
    mProcess->notifyReceivedStdout("Chang");

    CPPUNIT_ASSERT_EQUAL(string("Kwai"),
            processObserver1->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Chang"),
            processObserver2->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Caine"),
            processObserver3->getStdoutLastData());

    CPPUNIT_ASSERT_EQUAL((Process*)0,
            processObserver1->getStdoutLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver2->getStdoutLastProcess());
    CPPUNIT_ASSERT_EQUAL((Process*)0,
            processObserver3->getStdoutLastProcess());
}

void ProcessTest::testNotifyReceivedStderr() {
    ProcessObserverTestImplementation* processObserver1 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver1);
    ProcessObserverTestImplementation* processObserver2 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver2);
    ProcessObserverTestImplementation* processObserver3 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver3);

    mProcess->notifyReceivedStderr("Master");

    CPPUNIT_ASSERT_EQUAL(string("Master"),
            processObserver1->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Master"),
            processObserver2->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Master"),
            processObserver3->getStderrLastData());

    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver1->getStderrLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver2->getStderrLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver3->getStderrLastProcess());

    mProcess->detachObserver(processObserver1);
    mProcess->notifyReceivedStderr("Mei");

    CPPUNIT_ASSERT_EQUAL(string("Master"),
            processObserver1->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Mei"),
            processObserver2->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Mei"),
            processObserver3->getStderrLastData());

    CPPUNIT_ASSERT_EQUAL((Process*)0,
            processObserver1->getStderrLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver2->getStderrLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver3->getStderrLastProcess());

    mProcess->detachObserver(processObserver3);
    mProcess->notifyReceivedStderr("Pai");

    CPPUNIT_ASSERT_EQUAL(string("Master"),
            processObserver1->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Pai"),
            processObserver2->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Mei"),
            processObserver3->getStderrLastData());

    CPPUNIT_ASSERT_EQUAL((Process*)0,
            processObserver1->getStderrLastProcess());
    CPPUNIT_ASSERT_EQUAL(mProcess,
            processObserver2->getStderrLastProcess());
    CPPUNIT_ASSERT_EQUAL((Process*)0,
            processObserver3->getStderrLastProcess());
}

void ProcessTest::testNotifyProcessExited() {
    ProcessObserverTestImplementation* processObserver1 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver1);
    ProcessObserverTestImplementation* processObserver2 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver2);
    ProcessObserverTestImplementation* processObserver3 =
        static_cast<ProcessObserverTestImplementation*>(mProcessObserver3);

    mProcess->notifyProcessExited();

    CPPUNIT_ASSERT_EQUAL(1, processObserver1->getProcessExitedNumber());
    CPPUNIT_ASSERT_EQUAL(1, processObserver2->getProcessExitedNumber());
    CPPUNIT_ASSERT_EQUAL(1, processObserver3->getProcessExitedNumber());

    CPPUNIT_ASSERT_EQUAL(mProcess, processObserver1->getLastProcessExited());
    CPPUNIT_ASSERT_EQUAL(mProcess, processObserver2->getLastProcessExited());
    CPPUNIT_ASSERT_EQUAL(mProcess, processObserver3->getLastProcessExited());

    mProcess->detachObserver(processObserver1);
    mProcess->notifyProcessExited();

    CPPUNIT_ASSERT_EQUAL(1, processObserver1->getProcessExitedNumber());
    CPPUNIT_ASSERT_EQUAL(2, processObserver2->getProcessExitedNumber());
    CPPUNIT_ASSERT_EQUAL(2, processObserver3->getProcessExitedNumber());

    CPPUNIT_ASSERT_EQUAL((Process*)0, processObserver1->getLastProcessExited());
    CPPUNIT_ASSERT_EQUAL(mProcess, processObserver2->getLastProcessExited());
    CPPUNIT_ASSERT_EQUAL(mProcess, processObserver3->getLastProcessExited());

    mProcess->detachObserver(processObserver3);
    mProcess->notifyProcessExited();

    CPPUNIT_ASSERT_EQUAL(1, processObserver1->getProcessExitedNumber());
    CPPUNIT_ASSERT_EQUAL(3, processObserver2->getProcessExitedNumber());
    CPPUNIT_ASSERT_EQUAL(2, processObserver3->getProcessExitedNumber());

    CPPUNIT_ASSERT_EQUAL((Process*)0, processObserver1->getLastProcessExited());
    CPPUNIT_ASSERT_EQUAL(mProcess, processObserver2->getLastProcessExited());
    CPPUNIT_ASSERT_EQUAL((Process*)0, processObserver3->getLastProcessExited());
}
