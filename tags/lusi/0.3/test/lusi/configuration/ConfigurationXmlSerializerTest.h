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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONXMLSERIALIZERTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONXMLSERIALIZERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationXmlSerializer;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationXmlSerializer.
 *
 * @see ConfigurationXmlSerializer
 */
class ConfigurationXmlSerializerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationXmlSerializerTest);
    CPPUNIT_TEST(testVisitConfigurationParameterBool);
    CPPUNIT_TEST(testVisitConfigurationParameterDouble);
    CPPUNIT_TEST(testVisitConfigurationParameterInt);
    CPPUNIT_TEST(testVisitConfigurationParameterLocalUrl);
    CPPUNIT_TEST(testVisitConfigurationParameterMap);
    CPPUNIT_TEST(testVisitConfigurationParameterString);
    CPPUNIT_TEST(testSerialize);
    CPPUNIT_TEST(testNewNode);
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
     * Tests if the id, name, priority and information are serialized as
     * attributes, if the value and default value are serialized as text
     * elements, and if the created node is added as child to mNode.
     */
    void testVisitConfigurationParameterBool();

    /**
     * Tests if the id, name, priority and information are serialized as
     * attributes, if the value and default value are serialized as text
     * elements, and if the created node is added as child to mNode.
     */
    void testVisitConfigurationParameterDouble();

    /**
     * Tests if the id, name, priority and information are serialized as
     * attributes, if the value and default value are serialized as text
     * elements, and if the created node is added as child to mNode.
     */
    void testVisitConfigurationParameterInt();

    /**
     * Tests if the id, name, priority and information are serialized as
     * attributes, if the value and default value are serialized as text
     * elements, and if the created node is added as child to mNode.
     */
    void testVisitConfigurationParameterLocalUrl();

    /**
     * Tests if the id, name, priority and information are serialized as
     * attributes, if the child elements are added to the created node (except
     * the ones marked as not serializable), and if the created node is added
     * as child to mNode.
     */
    void testVisitConfigurationParameterMap();

    /**
     * Tests if the id, name, priority and information are serialized as
     * attributes, if the value and default value are serialized as text
     * elements, and if the created node is added as child to mNode.
     */
    void testVisitConfigurationParameterString();

    /**
     * Tests if the returned document contains the XML representation of the
     * map.
     */
    void testSerialize();

    /**
     * Tests if the id, name, priority and information are serialized as
     * attributes of the returned node.
     */
    void testNewNode();

private:

    /**
     * The ConfigurationXmlSerializer to test.
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
