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

#include "TaskProgressTest.h"

#define protected public
#define private public
#include "TaskProgress.h"
#undef private
#undef protected

#include "TaskTestImplementation.h"
#include "TaskProgressObserverTestImplementation.h"

using namespace lusi::task;

//public:

void TaskProgressTest::setUp() {
    mTask = new TaskTestImplementation("One, two, three... testing...", 0, 0);
    mTaskProgressObserver1 = new TaskProgressObserverTestImplementation();
    mTaskProgressObserver2 = new TaskProgressObserverTestImplementation();
    mTaskProgressObserver3 = new TaskProgressObserverTestImplementation();
    mTaskProgress = new TaskProgress(mTask);

    mTaskProgress->attachObserver(mTaskProgressObserver1);
    mTaskProgress->attachObserver(mTaskProgressObserver2);
    mTaskProgress->attachObserver(mTaskProgressObserver3);
}

void TaskProgressTest::tearDown() {
    delete mTask;
    delete mTaskProgressObserver1;
    delete mTaskProgressObserver2;
    delete mTaskProgressObserver3;
    delete mTaskProgress;
}

void TaskProgressTest::testConstructor() {
    delete mTaskProgress;
    mTaskProgress = new TaskProgress(mTask);

    CPPUNIT_ASSERT_EQUAL(mTask, mTaskProgress->mTask);
    CPPUNIT_ASSERT_EQUAL(true, mTaskProgress->mTaskProgressObservers.empty());
    CPPUNIT_ASSERT_EQUAL(false, mTaskProgress->mExtendedProgress);
}

void TaskProgressTest::testIsExtendedProgress() {
    mTaskProgress->mExtendedProgress = true;
    CPPUNIT_ASSERT_EQUAL(mTaskProgress->mExtendedProgress,
                         mTaskProgress->isExtendedProgress());

    mTaskProgress->mExtendedProgress = false;
    CPPUNIT_ASSERT_EQUAL(mTaskProgress->mExtendedProgress,
                         mTaskProgress->isExtendedProgress());
}

void TaskProgressTest::testSetExtendedProgress() {
    mTaskProgress->setExtendedProgress(true);
    CPPUNIT_ASSERT_EQUAL(true,
                         mTaskProgress->mExtendedProgress);

    mTaskProgress->setExtendedProgress(false);
    CPPUNIT_ASSERT_EQUAL(false,
                         mTaskProgress->mExtendedProgress);
}

void TaskProgressTest::testAttachObserver() {
    CPPUNIT_ASSERT(mTaskProgress->mTaskProgressObservers.size() == 3);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver1,
                         mTaskProgress->mTaskProgressObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver2,
                         mTaskProgress->mTaskProgressObservers[1]);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver3,
                         mTaskProgress->mTaskProgressObservers[2]);

    //Adding repeated elements
    mTaskProgress->attachObserver(mTaskProgressObserver2);

    CPPUNIT_ASSERT(mTaskProgress->mTaskProgressObservers.size() == 3);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver1,
                         mTaskProgress->mTaskProgressObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver2,
                         mTaskProgress->mTaskProgressObservers[1]);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver3,
                         mTaskProgress->mTaskProgressObservers[2]);
}

void TaskProgressTest::testDetachObserver() {
    mTaskProgress->detachObserver(mTaskProgressObserver2);

    CPPUNIT_ASSERT(mTaskProgress->mTaskProgressObservers.size() == 2);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver1,
                         mTaskProgress->mTaskProgressObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver3,
                         mTaskProgress->mTaskProgressObservers[1]);

    //Detaching an already detached observer
    mTaskProgress->detachObserver(mTaskProgressObserver2);

    CPPUNIT_ASSERT(mTaskProgress->mTaskProgressObservers.size() == 2);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver1,
                         mTaskProgress->mTaskProgressObservers[0]);
    CPPUNIT_ASSERT_EQUAL(mTaskProgressObserver3,
                         mTaskProgress->mTaskProgressObservers[1]);

    //Detaching all the observers
    mTaskProgress->detachObserver(mTaskProgressObserver1);
    mTaskProgress->detachObserver(mTaskProgressObserver3);

    CPPUNIT_ASSERT(mTaskProgress->mTaskProgressObservers.size() == 0);
}

void TaskProgressTest::testNotifyProgress() {
    TaskProgressObserverTestImplementation* taskProgressObserver1 =
        static_cast<TaskProgressObserverTestImplementation*>
            (mTaskProgressObserver1);
    TaskProgressObserverTestImplementation* taskProgressObserver2 =
        static_cast<TaskProgressObserverTestImplementation*>
            (mTaskProgressObserver2);
    TaskProgressObserverTestImplementation* taskProgressObserver3 =
        static_cast<TaskProgressObserverTestImplementation*>
            (mTaskProgressObserver3);

    mTaskProgress->notifyProgress(1);

    CPPUNIT_ASSERT_EQUAL(1,
            taskProgressObserver1->getProgress());
    CPPUNIT_ASSERT_EQUAL(1,
            taskProgressObserver2->getProgress());
    CPPUNIT_ASSERT_EQUAL(1,
            taskProgressObserver3->getProgress());

    CPPUNIT_ASSERT_EQUAL(mTask,
            taskProgressObserver1->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskProgressObserver2->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskProgressObserver3->getTask());

    mTaskProgress->detachObserver(taskProgressObserver1);
    mTaskProgress->notifyProgress(26);

    CPPUNIT_ASSERT_EQUAL(1,
            taskProgressObserver1->getProgress());
    CPPUNIT_ASSERT_EQUAL(26,
            taskProgressObserver2->getProgress());
    CPPUNIT_ASSERT_EQUAL(26,
            taskProgressObserver3->getProgress());

    CPPUNIT_ASSERT_EQUAL((Task*)0,
            taskProgressObserver1->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskProgressObserver2->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskProgressObserver3->getTask());

    mTaskProgress->detachObserver(taskProgressObserver3);
    mTaskProgress->notifyProgress(66);

    CPPUNIT_ASSERT_EQUAL(1,
            taskProgressObserver1->getProgress());
    CPPUNIT_ASSERT_EQUAL(66,
            taskProgressObserver2->getProgress());
    CPPUNIT_ASSERT_EQUAL(26,
            taskProgressObserver3->getProgress());

    CPPUNIT_ASSERT_EQUAL((Task*)0,
            taskProgressObserver1->getTask());
    CPPUNIT_ASSERT_EQUAL(mTask,
            taskProgressObserver2->getTask());
    CPPUNIT_ASSERT_EQUAL((Task*)0,
            taskProgressObserver3->getTask());
}
