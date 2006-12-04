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

#ifndef LUSI_TASK_HELPER_TASKHELPERUSINGPROCESSTEST_H
#define LUSI_TASK_HELPER_TASKHELPERUSINGPROCESSTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace package {
class Package;
class PackageId;
}
}

namespace lusi {
namespace task {
class Task;
class TaskConfiguration;
class TaskLoggerObserverTestImplementation;
class TaskProgressObserverTestImplementation;
}
}

namespace lusi {
namespace task {
namespace helper {
class TaskHelperUsingProcess;
}
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Test class for TaskHelperUsingProcess.
 *
 * @see TaskHelperUsingProcess
 */
class TaskHelperUsingProcessTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TaskHelperUsingProcessTest);
    CPPUNIT_TEST(testExecute);
    CPPUNIT_TEST(testReceivedStdout);
    CPPUNIT_TEST(testReceivedStderr);
    CPPUNIT_TEST(testProcessExited);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Checks if the process to be executed is prepared and, once finished, the
     * progress is set to FINISHED.
     * Also, it's checked if the TaskLogger is notified about the operations
     * made.
     */
    void testExecute();

    /**
     * Checks if the received stdout is notified to the Task.
     */
    void testReceivedStdout();

    /**
     * Checks if the received stderr is notified to the Task.
     */
    void testReceivedStderr();

    /**
     * Checks if the Progress is set to FINISHED.
     */
    void testProcessExited();

private:

    /**
     * The TaskHelperUsingProcess to test.
     */
    TaskHelperUsingProcess* mTaskHelperUsingProcess;

    /**
     * The Task to use in mTaskHelperUsingProcess.
     */
    lusi::task::Task* mTask;

    /**
     * The TaskLoggerObserverTestImplementation to observe the Task.
     */
    lusi::task::TaskLoggerObserverTestImplementation* mTaskLoggerObserver;

    /**
     * The TaskProgressObserverTestImplementation to observe the Task.
     */
    lusi::task::TaskProgressObserverTestImplementation* mTaskProgressObserver;

};

}
}
}

#endif
