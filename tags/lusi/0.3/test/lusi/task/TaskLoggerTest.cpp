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

#include "TaskLoggerTest.h"

#define protected public
#define private public
#include "TaskLogger.h"
#undef private
#undef protected

#include "TaskTestImplementation.h"
#include "TaskLoggerObserverTestImplementation.h"

using std::string;

using namespace lusi::task;

//public:

void TaskLoggerTest::setUp() {
    mTask = new TaskTestImplementation("One, two, three... testing...");
    mTaskLoggerObserver1 = new TaskLoggerObserverTestImplementation();
    mTaskLoggerObserver2 = new TaskLoggerObserverTestImplementation();
    mTaskLoggerObserver3 = new TaskLoggerObserverTestImplementation();
    mTaskLogger = new TaskLogger(mTask);

    mTaskLogger->attachObserver(mTaskLoggerObserver1);
    mTaskLogger->attachObserver(mTaskLoggerObserver2);
    mTaskLogger->attachObserver(mTaskLoggerObserver3);
}

void TaskLoggerTest::tearDown() {
    delete mTask;
    delete mTaskLoggerObserver1;
    delete mTaskLoggerObserver2;
    delete mTaskLoggerObserver3;
    delete mTaskLogger;
}

void TaskLoggerTest::testAttachObserver() {
    CPPUNIT_ASSERT(mTaskLogger->mTaskLoggerObservers.size() == 3);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver1,
                         mTaskLogger->mTaskLoggerObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver2,
                         mTaskLogger->mTaskLoggerObservers[1]);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver3,
                         mTaskLogger->mTaskLoggerObservers[2]);

    //Adding repeated elements
    mTaskLogger->attachObserver(mTaskLoggerObserver2);

    CPPUNIT_ASSERT(mTaskLogger->mTaskLoggerObservers.size() == 3);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver1,
                         mTaskLogger->mTaskLoggerObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver2,
                         mTaskLogger->mTaskLoggerObservers[1]);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver3,
                         mTaskLogger->mTaskLoggerObservers[2]);
}

void TaskLoggerTest::testDetachObserver() {
    mTaskLogger->detachObserver(mTaskLoggerObserver2);

    CPPUNIT_ASSERT(mTaskLogger->mTaskLoggerObservers.size() == 2);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver1,
                         mTaskLogger->mTaskLoggerObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver3,
                         mTaskLogger->mTaskLoggerObservers[1]);

    //Detaching an already detached observer
    mTaskLogger->detachObserver(mTaskLoggerObserver2);

    CPPUNIT_ASSERT(mTaskLogger->mTaskLoggerObservers.size() == 2);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver1,
                         mTaskLogger->mTaskLoggerObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskLoggerObserver3,
                         mTaskLogger->mTaskLoggerObservers[1]);

    //Detaching all the observers
    mTaskLogger->detachObserver(mTaskLoggerObserver1);
    mTaskLogger->detachObserver(mTaskLoggerObserver3);

    CPPUNIT_ASSERT(mTaskLogger->mTaskLoggerObservers.size() == 0);
}

void TaskLoggerTest::testNotifyEvent() {
    TaskLoggerObserverTestImplementation* taskLoggerObserver1 =
        static_cast<TaskLoggerObserverTestImplementation*>
            (mTaskLoggerObserver1);
    TaskLoggerObserverTestImplementation* taskLoggerObserver2 =
        static_cast<TaskLoggerObserverTestImplementation*>
            (mTaskLoggerObserver2);
    TaskLoggerObserverTestImplementation* taskLoggerObserver3 =
        static_cast<TaskLoggerObserverTestImplementation*>
            (mTaskLoggerObserver3);

    mTaskLogger->notifyEvent("Code quickly", message);

    CPPUNIT_ASSERT_EQUAL(string("Code quickly"),
            taskLoggerObserver1->getMessage());
    CPPUNIT_ASSERT_EQUAL(string("Code quickly"),
            taskLoggerObserver2->getMessage());
    CPPUNIT_ASSERT_EQUAL(string("Code quickly"),
            taskLoggerObserver3->getMessage());

    CPPUNIT_ASSERT_EQUAL(message,
            taskLoggerObserver1->getEventType());
    CPPUNIT_ASSERT_EQUAL(message,
            taskLoggerObserver2->getEventType());
    CPPUNIT_ASSERT_EQUAL(message,
            taskLoggerObserver3->getEventType());

    CPPUNIT_ASSERT_EQUAL(mTask,
            taskLoggerObserver1->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskLoggerObserver2->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskLoggerObserver3->getTask());

    mTaskLogger->detachObserver(taskLoggerObserver1);
    mTaskLogger->notifyEvent("Time's up!", error);

    CPPUNIT_ASSERT_EQUAL(string("Code quickly"),
            taskLoggerObserver1->getMessage());
    CPPUNIT_ASSERT_EQUAL(string("Time's up!"),
            taskLoggerObserver2->getMessage());
    CPPUNIT_ASSERT_EQUAL(string("Time's up!"),
            taskLoggerObserver3->getMessage());

    CPPUNIT_ASSERT_EQUAL((Task*)0,
            taskLoggerObserver1->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskLoggerObserver2->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskLoggerObserver3->getTask());

    CPPUNIT_ASSERT_EQUAL(message,
            taskLoggerObserver1->getEventType());
    CPPUNIT_ASSERT_EQUAL(error,
            taskLoggerObserver2->getEventType());
    CPPUNIT_ASSERT_EQUAL(error,
            taskLoggerObserver3->getEventType());

    mTaskLogger->detachObserver(taskLoggerObserver3);
    mTaskLogger->notifyEvent("Hurry up!", warning);

    CPPUNIT_ASSERT_EQUAL(string("Code quickly"),
            taskLoggerObserver1->getMessage());
    CPPUNIT_ASSERT_EQUAL(string("Hurry up!"),
            taskLoggerObserver2->getMessage());
    CPPUNIT_ASSERT_EQUAL(string("Time's up!"),
            taskLoggerObserver3->getMessage());

    CPPUNIT_ASSERT_EQUAL((Task*)0,
            taskLoggerObserver1->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskLoggerObserver2->getTask());
    CPPUNIT_ASSERT_EQUAL((Task*)0,
            taskLoggerObserver3->getTask());

    CPPUNIT_ASSERT_EQUAL(message,
            taskLoggerObserver1->getEventType());
    CPPUNIT_ASSERT_EQUAL(warning,
            taskLoggerObserver2->getEventType());
    CPPUNIT_ASSERT_EQUAL(error,
            taskLoggerObserver3->getEventType());
}
