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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERCOMPOSEDTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERCOMPOSEDTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterComposed;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationParameterComposed.
 *
 * @see ConfigurationParameterComposed
 */
class ConfigurationParameterComposedTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationParameterComposedTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testAddConfigurationParameter);
    CPPUNIT_TEST(testGetConfigurationParameters);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the ConfigurationParameterComposed with id "Test", priority
     * "required" and information "A test parameter".
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Tests if all the values are well set in the constructor.
     */
    void testConstructor();

    /**
     * Tests if the ConfigurationParameter is added.
     */
    void testAddConfigurationParameter();

    /**
     * Tests if mConfigurationParameters is returned.
     */
    void testGetConfigurationParameters();

private:

    /**
     * The ConfigurationParameterComposed to test.
     */
    ConfigurationParameterComposed* mConfigurationParameterComposed;

};

}
}

#endif
