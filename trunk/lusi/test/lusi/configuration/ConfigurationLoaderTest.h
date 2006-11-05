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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONLOADERTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONLOADERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationLoader.
 *
 * @see ConfigurationLoader
 */
class ConfigurationLoaderTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationLoaderTest);
    CPPUNIT_TEST(testLoad);
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
     * Tests if a file saved with ConfigurationSaver is loaded successfully. It
     * also tests that if the url is a directory, a relative url or an
     * inexistent file, an exception is thrown.
     */
    void testLoad();

private:

    /**
     * The path to the test directory where files will be created for test.
     * It is the current working directory followed by "created for LUSI
     * tests/".
     */
    std::string mTestDirectoryPath;

};

}
}

#endif
