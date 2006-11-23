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

#ifndef LUSI_TASK_TASKCONFIGURATIONTEST_H
#define LUSI_TASK_TASKCONFIGURATIONTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace package {
class Package;
}
}

namespace lusi {
namespace task {
class Task;
class TaskConfiguration;
}
}

namespace lusi {
namespace task {

/**
 * Test class for TaskConfiguration.
 *
 * @see TaskConfiguration
 */
class TaskConfigurationTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TaskConfigurationTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetTaskHelperConfiguration);
    CPPUNIT_TEST(testGetAllTaskHelperConfigurations);
    CPPUNIT_TEST(testAddTaskHelperConfiguration);
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
     * Tests if the Task is set, if mConfigurationToSave is created and if
     * mConfiguration is set to 0 (as nothing can be loaded).
     */
    void testConstructor();

    /**
     * Tests if it returns the ConfigurationParameterMap for the requested
     * TaskHelper.
     */
    void testGetTaskHelperConfiguration();

    /**
     * Tests if it returns all the ConfigurationParameterMap in the same order
     * they were loaded.
     */
    void testGetAllTaskHelperConfigurations();

    /**
     * Tests if it adds the TaskHelper configuration to mConfigurationToSave.
     */
    void testAddTaskHelperConfiguration();

private:

    /**
     * The TaskConfiguration to test.
     */
    TaskConfiguration* mTaskConfiguration;

    /**
     * The Task to get the TaskConfiguration to test from.
     */
    Task* mTask;

    /**
     * The Package for the Task.
     */
    lusi::package::Package* mPackage;

};

}
}

#endif
