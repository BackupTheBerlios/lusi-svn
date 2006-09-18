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

#ifndef LUSI_TASK_TASKTEST_H
#define LUSI_TASK_TASKTEST_H

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
}
}

/**
 * Test class for Task.
 *
 * @see Task
 */
namespace lusi {
namespace task {

class TaskTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TaskTest);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST(testGetPackage);
    CPPUNIT_TEST(testGetTaskConfiguration);
    CPPUNIT_TEST(testGetNeededPackageStatus);
    CPPUNIT_TEST(testGetProvidedPackageStatus);
    CPPUNIT_TEST(testGetTaskLogger);
    CPPUNIT_TEST(testGetTaskProgress);
    CPPUNIT_TEST(testNextTaskHelper);
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
     * Checks if getName() returns the name set in the constructor.
     */
    void testGetName();

    /**
     * Checks if getPackage() returns the Package set in the constructor.
     */
    void testGetPackage();

    /**
     * Checks if getTaskConfiguration() returns the TaskConfiguration set in the
     * constructor.
     */
    void testGetTaskConfiguration();

    /**
     * Checks if getNeededPackageStatus() returns the PackageStatus set in the
     * constructor.
     */
    void testGetNeededPackageStatus();

    /**
     * Checks if getProvidedPackageStatus() returns the PackageStatus set in the
     * constructor.
     */
    void testGetProvidedPackageStatus();

    /**
     * Checks if getTaskLogger() returns the TaskLogger created in the
     * constructor, and that it works as it should.
     */
    void testGetTaskLogger();

    /**
     * Checks if getTaskProgress() returns the TaskProgress created in the
     * constructor, and that it works as it should.
     */
    void testGetTaskProgress();

    /**
     * Checks if nextTaskHelper() sets the TaskHelpers suitable for the Package.
     */
    void testNextTaskHelper();

private:

    /**
     * The Task to test.
     */
    Task* mTask;

    /**
     * The PackageId for the Package.
     */
    lusi::package::PackageId* mPackageId;

    /**
     * The Package for the Task.
     */
    lusi::package::Package* mPackage;

    /**
     * The TaskConfiguration for the Task.
     */
    TaskConfiguration* mTaskConfiguration;

};

}
}

#endif
