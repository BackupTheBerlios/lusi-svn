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

#ifndef LUSI_TASK_HELPER_MAKEINSTALLTASKHELPERTEST_H
#define LUSI_TASK_HELPER_MAKEINSTALLTASKHELPERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace task {
class Task;
}
}

namespace lusi {
namespace task {
namespace helper {
class MakeInstallTaskHelper;
}
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Test class for MakeInstallTaskHelper.
 *
 * @see MakeInstallerTaskHelper
 */
class MakeInstallTaskHelperTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(MakeInstallTaskHelperTest);
    CPPUNIT_TEST(testConstructor);
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
     * Checks if the name, the task and the make target are set.
     */
    void testConstructor();

    /**
     * Checks if the Process arguments set are correct. It is tested with a
     * install and an uninstall target.
     */
    void testGetProcess();

private:

    /**
     * The MakeInstallTaskHelper to use.
     */
    MakeInstallTaskHelper* mMakeInstallTaskHelper;

    /**
     * The Task to use in mMakeInstallTaskHelper.
     */
    lusi::task::Task* mTask;

};

}
}
}

#endif
