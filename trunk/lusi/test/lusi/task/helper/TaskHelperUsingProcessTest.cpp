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

#include "TaskHelperUsingProcessTest.h"

#define protected public
#define private public
#include "TaskHelperUsingProcessTestImplementation.h"
#undef private
#undef protected

#include "../TaskConfiguration.h"
#include "../TaskLoggerObserverTestImplementation.h"
#include "../TaskProgressObserverTestImplementation.h"
#include "../TaskTestImplementation.h"
#include "../../package/Package.h"
#include "../../package/PackageId.h"

using std::string;

using lusi::package::Package;
using lusi::package::PackageId;
using lusi::task::TaskTestImplementation;
using lusi::task::TaskConfiguration;
using lusi::task::TaskLoggerObserverTestImplementation;
using lusi::task::TaskProgressObserverTestImplementation;

using namespace lusi::task::helper;

//public:

void TaskHelperUsingProcessTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mTaskHelperUsingProcess = new TaskHelperUsingProcessTestImplementation(
                    "TaskHelperUsingProcessTestImplementation", mTask);
    mTaskLoggerObserver = new TaskLoggerObserverTestImplementation();
    mTaskProgressObserver = new TaskProgressObserverTestImplementation();

    mTask->getTaskLogger()->attachObserver(mTaskLoggerObserver);
    mTask->getTaskProgress()->attachObserver(mTaskProgressObserver);
}

void TaskHelperUsingProcessTest::tearDown() {
    delete mTaskProgressObserver;
    delete mTaskLoggerObserver;
    delete mTaskHelperUsingProcess;
    delete mTask;
}

void TaskHelperUsingProcessTest::testExecute() {
    mTaskHelperUsingProcess->execute();

    CPPUNIT_ASSERT_EQUAL(100, mTaskProgressObserver->getProgress());
    CPPUNIT_ASSERT_EQUAL(true,
                static_cast<TaskHelperUsingProcessTestImplementation*>
                        (mTaskHelperUsingProcess)->isExecutionPrepared());
    CPPUNIT_ASSERT_EQUAL(string("TaskHelperUsingProcessTestImplementation: ") +
            string("executing process\n") +
            string("echo TaskHelperUsingProcessTestImplementation\n") +
            string("TaskHelperUsingProcessTestImplementation\n") +
            string("TaskHelperUsingProcessTestImplementation: end process\n"),
            mTaskLoggerObserver->getAllMessages());
}

void TaskHelperUsingProcessTest::testReceivedStdout() {
    mTaskHelperUsingProcess->receivedStdout(0, "Spared no expense");

    CPPUNIT_ASSERT_EQUAL(string("Spared no expense"),
                         mTaskLoggerObserver->getMessage());
    CPPUNIT_ASSERT_EQUAL(message, mTaskLoggerObserver->getEventType());
}

void TaskHelperUsingProcessTest::testReceivedStderr() {
    mTaskHelperUsingProcess->receivedStderr(0,
                                "Ah, ah, ah, you didn't say the magic word");

    CPPUNIT_ASSERT_EQUAL(string("Ah, ah, ah, you didn't say the magic word"),
                         mTaskLoggerObserver->getMessage());
    CPPUNIT_ASSERT_EQUAL(error, mTaskLoggerObserver->getEventType());
}

void TaskHelperUsingProcessTest::testProcessExited() {
    mTaskHelperUsingProcess->processExited(0);

    CPPUNIT_ASSERT_EQUAL(100, mTaskProgressObserver->getProgress());
}
