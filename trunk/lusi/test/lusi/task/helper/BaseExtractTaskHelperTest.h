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

#ifndef LUSI_TASK_HELPER_BASEEXTRACTTASKHELPERTEST_H
#define LUSI_TASK_HELPER_BASEEXTRACTTASKHELPERTEST_H

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
class BaseExtractTaskHelper;
}
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Test class for BaseExtractTaskHelper.
 *
 * @see BaseExtractTaskHelper
 */
class BaseExtractTaskHelperTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(BaseExtractTaskHelperTest);
    CPPUNIT_TEST(testExecute);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetNumberOfFilesToExtract);
    CPPUNIT_TEST(testSetNumberOfFilesToExtract);
    CPPUNIT_TEST(testFileExtracted);
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
     * Checks if the method from parent is called (the process to be executed is
     * prepared and executed, progress is then set to FINISHED) and the file to
     * unpack is removed from the ResourceMap.
     */
    void testExecute();

    /**
     * Checks if the constructor initializes the attributes as it should.
     */
    void testConstructor();

    /**
     * Checks if mNumberOfFilesToExtract is returned.
     */
    void testGetNumberOfFilesToExtract();

    /**
     * Checks if mNumberOfFilesToExtract is set.
     */
    void testSetNumberOfFilesToExtract();

    /**
     * Checks if the progress is updated and the Resource with the file is added
     * to the ResourceMap.
     */
    void testFileExtracted();

private:

    /**
     * The BaseExtractTaskHelper to test.
     */
    BaseExtractTaskHelper* mBaseExtractTaskHelper;

    /**
     * The Package for the Task.
     */
    lusi::package::Package* mPackage;

    /**
     * The Task to use in mBaseExtractTaskHelper.
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
