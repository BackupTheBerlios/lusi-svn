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

#ifndef LUSI_TASK_TASKLOGGERTEST_H
#define LUSI_TASK_TASKLOGGERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace task {
class Task;
class TaskLogger;
class TaskLoggerObserver;
}
}

namespace lusi {
namespace task {

/**
 * Test class for TaskLogger.
 *
 * @see TaskLogger
 */
class TaskLoggerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TaskLoggerTest);
    CPPUNIT_TEST(testAttachObserver);
    CPPUNIT_TEST(testDetachObserver);
    CPPUNIT_TEST(testNotifyEvent);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates all the observers and the TaskLogger, and attachs the
     * observers to the TaskLogger.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if TaskLoggerObservers are attached as they should.
     */
    void testAttachObserver();

    /**
     * Tests if TaskLoggerObservers are detached as they should.
     */
    void testDetachObserver();

    /**
     * Tests if the registered observers are notified when events is sent.
     */
    void testNotifyEvent();

private:

    /**
     * First TaskLoggerObserver.
     */
    TaskLoggerObserver* mTaskLoggerObserver1;

    /**
     * Second TaskLoggerObserver.
     */
    TaskLoggerObserver* mTaskLoggerObserver2;

    /**
     * Third TaskLoggerObserver.
     */
    TaskLoggerObserver* mTaskLoggerObserver3;

    /**
     * TaskLogger to be tested.
     */
    TaskLogger* mTaskLogger;

    /**
     * The Task to associate the TaskLogger with.
     */
    Task* mTask;

};

}
}

#endif
