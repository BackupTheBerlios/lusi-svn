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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONXMLDESERIALIZERTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONXMLDESERIALIZERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationXmlDeserializer;
class ConfigurationXmlSerializer;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationXmlDeserializer.
 *
 * @see ConfigurationXmlDeserializer
 */
class ConfigurationXmlDeserializerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationXmlDeserializerTest);
    CPPUNIT_TEST(testDeserialize);
    CPPUNIT_TEST(testDeserializeConfigurationParameterBool);
    CPPUNIT_TEST(testDeserializeConfigurationParameterDouble);
    CPPUNIT_TEST(testDeserializeConfigurationParameterInt);
    CPPUNIT_TEST(testDeserializeConfigurationParameterLocalUrl);
    CPPUNIT_TEST(testDeserializeConfigurationParameterMap);
    CPPUNIT_TEST(testDeserializeConfigurationParameterString);
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
     * Tests if a serialized configuration using ConfigurationXmlSerializer is
     * deserialized.
     */
    void testDeserialize();

    /**
     * Tests if a serialized ConfigurationParameterBool using
     * ConfigurationXmlSerializer is deserialized to a parameter equal to the
     * original.
     */
    void testDeserializeConfigurationParameterBool();

    /**
     * Tests if a serialized ConfigurationParameterDouble using
     * ConfigurationXmlSerializer is deserialized to a parameter equal to the
     * original.
     */
    void testDeserializeConfigurationParameterDouble();

    /**
     * Tests if a serialized ConfigurationParameterInt using
     * ConfigurationXmlSerializer is deserialized to a parameter equal to the
     * original.
     */
    void testDeserializeConfigurationParameterInt();

    /**
     * Tests if a serialized ConfigurationParameterLocalUrl using
     * ConfigurationXmlSerializer is deserialized to a parameter equal to the
     * original.
     */
    void testDeserializeConfigurationParameterLocalUrl();

    /**
     * Tests if a serialized ConfigurationParameterMap using
     * ConfigurationXmlSerializer is deserialized to a parameter equal to the
     * original.
     */
    void testDeserializeConfigurationParameterMap();

    /**
     * Tests if a serialized ConfigurationParameterString using
     * ConfigurationXmlSerializer is deserialized to a parameter equal to the
     * original.
     */
    void testDeserializeConfigurationParameterString();

private:

    /**
     * The ConfigurationXmlDeserializer to test.
     */
    ConfigurationXmlDeserializer* mConfigurationXmlDeserializer;

    /**
     * The ConfigurationXmlDeserializer to use.
     */
    ConfigurationXmlSerializer* mConfigurationXmlSerializer;



    /**
     * Calls tearDown and setUp.
     */
    void restartTestObjects();

};

}

}

#endif
