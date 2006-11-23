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

#ifndef LUSI_TASK_HELPER_TAREXTRACTTASKHELPERTEST_H
#define LUSI_TASK_HELPER_TAREXTRACTTASKHELPERTEST_H

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
class TarExtractTaskHelper;
}
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Test class for TarExtractTaskHelper.
 *
 * @see TarExtractTaskHelper
 */
class TarExtractTaskHelperTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TarExtractTaskHelperTest);
    CPPUNIT_TEST(testHasValidResources);
    CPPUNIT_TEST(testReceivedStdout);
    CPPUNIT_TEST(testGetProcess);
    CPPUNIT_TEST(testInferTarFormat);
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
     * Checks if true is returned only if the format of the packed file is
     * supported.
     */
    void testHasValidResources();

    /**
     * Checks the notification to the base class about extracted files.
     */
    void testReceivedStdout();

    /**
     * Tests if the number of files to be extracted is set, if the Process
     * arguments are correct, and if the TaskProgress is set as extended.
     */
    void testGetProcess();

    /**
     * Checks if the inferred tar format is valid.
     */
    void testInferTarFormat();

private:

    /**
     * The TarExtractTaskHelper to use.
     */
    TarExtractTaskHelper* mTarExtractTaskHelper;

    /**
     * The Task to use in mTarExtractTaskHelper.
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
