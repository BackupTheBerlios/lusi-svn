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

#ifndef LUSI_TASK_TASKPROGRESSTEST_H
#define LUSI_TASK_TASKPROGRESSTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace task {
class Task;
class TaskProgress;
class TaskProgressObserver;
}
}

namespace lusi {
namespace task {

/**
 * Test class for TaskProgress.
 *
 * @see TaskProgress
 */
class TaskProgressTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TaskProgressTest);
    CPPUNIT_TEST(testAttachObserver);
    CPPUNIT_TEST(testDetachObserver);
    CPPUNIT_TEST(testNotifyProgress);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates all the observers and the TaskProgress, and attachs the
     * observers to the TaskProgress.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if TaskProgressObservers are attached as they should.
     */
    void testAttachObserver();

    /**
     * Tests if TaskProgressObservers are detached as they should.
     */
    void testDetachObserver();

    /**
     * Tests if the registered observers are notified when progress is made.
     */
    void testNotifyProgress();

private:

    /**
     * First TaskProgressObserver.
     */
    TaskProgressObserver* mTaskProgressObserver1;

    /**
     * Second TaskProgressObserver.
     */
    TaskProgressObserver* mTaskProgressObserver2;

    /**
     * Third TaskProgressObserver.
     */
    TaskProgressObserver* mTaskProgressObserver3;

    /**
     * TaskProgress to be tested.
     */
    TaskProgress* mTaskProgress;

    /**
     * The Task to associate the TaskProgress with.
     */
    Task* mTask;

};

}
}

#endif
