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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationParameter;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationParameter.
 *
 * @see ConfigurationParameter
 */
class ConfigurationParameterTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationParameterTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testGetId);
    CPPUNIT_TEST(testGetName);
    CPPUNIT_TEST(testGetInformation);
    CPPUNIT_TEST(testGetPriorityType);
    CPPUNIT_TEST(testIsSerializable);
    CPPUNIT_TEST(testSetSerializable);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the ConfigurationParameter with id "Test", name "Test name",
     * priority "required" and information "A test parameter".
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
     * Tests if it returns mId.
     */
    void testGetId();

    /**
     * Tests if it returns mName.
     */
    void testGetName();

    /**
     * Tests if it returns mInformation.
     */
    void testGetInformation();

    /**
     * Tests if it returns mPriorityType.
     */
    void testGetPriorityType();

    /**
     * Tests if it returns mSerializable.
     */
    void testIsSerializable();

    /**
     * Tests if it sets mSerializable.
     */
    void testSetSerializable();

private:

    /**
     * The ConfigurationParameter to test.
     */
    ConfigurationParameter* mConfigurationParameter;

};

}
}

#endif
