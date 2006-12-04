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

#include "ProcessRunnerTest.h"

#define protected public
#include "ProcessTestImplementation.h"
#undef protected

#include "ProcessRunner.h"

using std::string;

using namespace lusi::util;

//public:

void ProcessRunnerTest::setUp() {
    mProcess = new ProcessTestImplementation();
    mProcessRunner = new ProcessRunner(mProcess);
}

void ProcessRunnerTest::tearDown() {
    delete mProcessRunner;
}

void ProcessRunnerTest::testGetProcess() {
    CPPUNIT_ASSERT_EQUAL(mProcess, mProcessRunner->getProcess());
    delete mProcessRunner;


    //Test default value
    mProcessRunner = new ProcessRunner();
    CPPUNIT_ASSERT(mProcessRunner->getProcess() != 0);
    CPPUNIT_ASSERT(mProcessRunner->getProcess()->getArguments().size() == 0);
}

void ProcessRunnerTest::testGetStdoutData() {
    mProcess->notifyReceivedStdout("Worst. ");
    mProcess->notifyReceivedStdout("Library. ");
    mProcess->notifyReceivedStdout("Ever.\n");

    CPPUNIT_ASSERT_EQUAL(string("Worst. Library. Ever.\n"),
                         mProcessRunner->getStdoutData());
}

void ProcessRunnerTest::testGetStderrData() {
    mProcess->notifyReceivedStderr("D'oh! ");
    mProcess->notifyReceivedStderr("D'oh? ");
    mProcess->notifyReceivedStderr("D'oh.\n");

    CPPUNIT_ASSERT_EQUAL(string("D'oh! D'oh? D'oh.\n"),
                         mProcessRunner->getStderrData());
}

void ProcessRunnerTest::testGetProcessExitedNumber() {
    mProcess->notifyProcessExited();

    CPPUNIT_ASSERT_EQUAL(1, mProcessRunner->getProcessExitedNumber());
}
