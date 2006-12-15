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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPATHSTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONPATHSTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationPaths;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationPaths.
 *
 * @see ConfigurationPaths
 */
class ConfigurationPathsTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationPathsTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetBaseDirectory);
    CPPUNIT_TEST(testGetPackagesBaseDirectory);
    CPPUNIT_TEST(testGetPackageDirectory);
    CPPUNIT_TEST(testGetPackageFile);
    CPPUNIT_TEST(testGetProfileFile);
    CPPUNIT_TEST(testGetTaskFile);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * It creates the ConfigurationPaths using the default user.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if the constructor sets mBaseDirectory to the home directory of the
     * specified user followed by ".lusi/".
     */
    void testConstructor();

    /**
     * Tests if the returned directory is mBaseDirectory.
     */
    void testGetBaseDirectory();

    /**
     * Tests if the returned directory is mBaseDirectory followed by "package".
     */
    void testGetPackagesBaseDirectory();

    /**
     * Tests if the returned directory is the base directory followed by
     * "${packageName}/${packageVersion}/", or "${packageName}/" if there is no
     * version.
     */
    void testGetPackageDirectory();

    /**
     * Tests if the returned file is the package directory followed by
     * "package-data.xml".
     */
    void testGetPackageFile();

    /**
     * Tests if the returned file is the package directory followed by
     * "profile.xml".
     */
    void testGetProfileFile();

    /**
     * Tests if the returned file is the package directory followed by
     * "{taskId}.xml".
     */
    void testGetTaskFile();

private:

    /**
     * The ConfigurationPaths to test.
     */
    ConfigurationPaths* mConfigurationPaths;

};

}
}

#endif
