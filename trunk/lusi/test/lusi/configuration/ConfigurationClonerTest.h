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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONCLONERTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONCLONERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationCloner;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationCloner.
 *
 * @see ConfigurationCloner
 */
class ConfigurationClonerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationClonerTest);
    CPPUNIT_TEST(testVisitConfigurationParameterBool);
    CPPUNIT_TEST(testVisitConfigurationParameterDouble);
    CPPUNIT_TEST(testVisitConfigurationParameterInt);
    CPPUNIT_TEST(testVisitConfigurationParameterLocalUrl);
    CPPUNIT_TEST(testVisitConfigurationParameterMap);
    CPPUNIT_TEST(testVisitConfigurationParameterString);
    CPPUNIT_TEST(testClone);
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
     * Tests if the id, name, priority and information are cloned, if the value
     * and default value are cloned only if they were set, and if the created
     * parameter is added as a child of mClonedConfiguration.
     */
    void testVisitConfigurationParameterBool();

    /**
     * Tests if the id, name, priority and information are cloned, if the value
     * and default value are cloned only if they were set, and if the created
     * parameter is added as a child of mClonedConfiguration.
     */
    void testVisitConfigurationParameterDouble();

    /**
     * Tests if the id, name, priority and information are cloned, if the value
     * and default value are cloned only if they were set, and if the created
     * parameter is added as a child of mClonedConfiguration.
     */
    void testVisitConfigurationParameterInt();

    /**
     * Tests if the id, name, priority, information and URL type are cloned, if
     * the value and default value are cloned only if they were set, and if the
     * created parameter is added as a child of mClonedConfiguration.
     */
    void testVisitConfigurationParameterLocalUrl();

    /**
     * Tests if the id, name, priority and information are cloned, if the child
     * are added to the clone, and if the created parameter is added as a child
     * of mClonedConfiguration only if it is null.
     */
    void testVisitConfigurationParameterMap();

    /**
     * Tests if the id, name, priority, information and string type are cloned,
     * if the value and default value are cloned only if they were set, and if
     * the created parameter is added as a child of mClonedConfiguration.
     */
    void testVisitConfigurationParameterString();

    /**
     * Tests if the returned ConfigurationParameterMap is a clone of the
     * specified ConfigurationParameterMap.
     */
    void testClone();

private:

    /**
     * The ConfigurationCloner to test.
     */
    ConfigurationCloner* mConfigurationCloner;



    /**
     * Calls tearDown and setUp.
     */
    void restartTestObjects();

};

}

}

#endif
