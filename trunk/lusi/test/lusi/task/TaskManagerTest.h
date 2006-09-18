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

#ifndef LUSI_TASK_TASKMANAGERTEST_H
#define LUSI_TASK_TASKMANAGERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace task {
class TaskManager;
}
}

namespace lusi {
namespace task {

/**
 * Test class for TaskManager.
 *
 * @see TaskManager
 */
class TaskManagerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TaskManagerTest);
    CPPUNIT_TEST(testSingleton);
    CPPUNIT_TEST(testGetTask);
    CPPUNIT_TEST(testRegisterTask);
    CPPUNIT_TEST(testGetTasksByPackageStatus);
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
     * Checks if getInstance() always returns the same not null reference.
     */
    void testSingleton();

    /**
     * Checks if the task returned is a suitable Task to execute.
     */
    void testGetTask();

    /**
     * Checks if the task is registered in the two internal multimaps.
     */
    void testRegisterTask();

    /**
     * Checks if the registered Tasks using the needed and provided
     * PackageStatus are returned in the vector.
     */
    void testGetTasksByPackageStatus();

private:

    /**
     * The TaskManager to test.
     */
    TaskManager* mTaskManager;

};

}
}

#endif
