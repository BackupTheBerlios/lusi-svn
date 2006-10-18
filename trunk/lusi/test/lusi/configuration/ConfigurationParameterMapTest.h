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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERMAPTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERMAPTEST_H

#include <cppunit/extensions/HelperMacros.h>

#include <lusi/util/SmartPtr.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterMap;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationParameterMap.
 *
 * @see ConfigurationParameterMap
 */
class ConfigurationParameterMapTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationParameterMapTest);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testIsInvalid);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testGet);
    CPPUNIT_TEST(testGetAll);
    CPPUNIT_TEST(testRemove);
    CPPUNIT_TEST(testGetInvalidPolicy);
    CPPUNIT_TEST(testMerge);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     * Creates the ConfigurationParameterMap.
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
     * Tests if the ConfigurationParameterMap is invalid depending on the
     * selected policy.
     */
    void testIsInvalid();

    /**
     * Tests if the ConfigurationParameter is added to the internal map.
     */
    void testAdd();

    /**
     * Tests if the ConfigurationParameter is returned.
     */
    void testGet();

    /**
     * Tests if all the ConfigurationParameters are returned.
     */
    void testGetAll();

    /**
     * Tests if the ConfigurationParameter is removed from the internal map.
     */
    void testRemove();

    /**
     * Tests if it returns mInvalidPolicy.
     */
    void testGetInvalidPolicy();

    /**
     * Tests if a map merged with another one with parameters with the same id
     * are kept or overriden depending on the type of merge.
     */
    void testMerge();

private:

    /**
     * The ConfigurationParameterMap to test.
     */
    ConfigurationParameterMap* mConfigurationParameterMap;

};

}
}

#endif
