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

#ifndef LUSI_TASK_HELPER_CONFIGURECONFIGURETASKHELPERTEST_H
#define LUSI_TASK_HELPER_CONFIGURECONFIGURETASKHELPERTEST_H

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

namespace lusi {
namespace task {
namespace helper {
class ConfigureConfigureTaskHelper;
}
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Test class for ConfigureConfigureTaskHelper.
 *
 * @see MakeBuilderTaskHelper
 */
class ConfigureConfigureTaskHelperTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigureConfigureTaskHelperTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testHasValidResources);
    CPPUNIT_TEST(testGetProcess);
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
     * Checks if mPackageDirectory is set as it should.
     */
    void testConstructor();

    /**
     * Checks if true is returned only if a valid configure script is available.
     */
    void testHasValidResources();

    /**
     * Checks if the Process arguments set are correct.
     */
    void testGetProcess();

private:

    /**
     * The TarExtractTaskHelper to use.
     */
    ConfigureConfigureTaskHelper* mConfigureConfigureTaskHelper;

    /**
     * The Task to use in mConfigureConfigureTaskHelper.
     */
    lusi::task::Task* mTask;

};

}
}
}

#endif
