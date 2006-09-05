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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLETEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLETEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterSimple;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationParameterSimple.
 *
 * @see ConfigurationParameterSimple
 */
class ConfigurationParameterSimpleTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationParameterSimpleTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testIsInvalid);
    CPPUNIT_TEST(testGetValue);
    CPPUNIT_TEST(testIsDefaultValue);
    CPPUNIT_TEST(testSetValue);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the ConfigurationParameterSimple with id "Test", priority
     * "required", information "A test parameter" and default value "Default".
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
     * Tests if a required simple parameter without a value is invalid and if
     * not required simple parameter without a value and required simple
     * parameter with a default value are valid.
     */
    void testIsInvalid();

    /**
     * Tests if the value returned is mValue or mDefaultValue if normal value
     * was empty.
     */
    void testGetValue();

    /**
     * Tests if the value is compared to default value as it should.
     */
    void testIsDefaultValue();

    /**
     * Tests if it sets mValue.
     */
    void testSetValue();

private:

    /**
     * The ConfigurationParameterSimple to test.
     */
    ConfigurationParameterSimple* mConfigurationParameterSimple;

};

}
}

#endif
