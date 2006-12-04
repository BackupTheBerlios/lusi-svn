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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONMERGERTEST_H
#define LUSI_CONFIGURATION_CONFIGURATIONMERGERTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace configuration {
class ConfigurationMerger;
}
}

namespace lusi {
namespace configuration {

/**
 * Test class for ConfigurationMerger.
 *
 * @see ConfigurationMerger
 */
class ConfigurationMergerTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ConfigurationMergerTest);
    CPPUNIT_TEST(testVisitConfigurationParameterBool);
    CPPUNIT_TEST(testVisitConfigurationParameterDouble);
    CPPUNIT_TEST(testVisitConfigurationParameterInt);
    CPPUNIT_TEST(testVisitConfigurationParameterLocalUrl);
    CPPUNIT_TEST(testVisitConfigurationParameterMap);
    CPPUNIT_TEST(testVisitConfigurationParameterString);
    CPPUNIT_TEST(testMerge);
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
     * Tests that a second bool parameter with a value set overrides the first
     * parameter value.
     * Also, it is tested that a second bool parameter without a value set and
     * that a second parameter different than a ConfigurationParameterBool
     * doesn't set anything on the first value.
     */
    void testVisitConfigurationParameterBool();

    /**
     * Tests that a second double parameter with a value set overrides the first
     * parameter value.
     * Also, it is tested that a second double parameter without a value set and
     * that a second parameter different than a ConfigurationParameterDouble
     * doesn't set anything on the first value.
     */
    void testVisitConfigurationParameterDouble();

    /**
     * Tests that a second int parameter with a value set overrides the first
     * parameter value.
     * Also, it is tested that a second int parameter without a value set and
     * that a second parameter different than an ConfigurationParameterInt
     * doesn't set anything on the first value.
     */
    void testVisitConfigurationParameterInt();

    /**
     * Tests that a second LocalUrl parameter with a value set overrides the
     * first parameter value.
     * Also, it is tested that a second LocalUrl parameter without a value set
     * and that a second parameter different than a
     * ConfigurationParameterLocalUrl doesn't set anything on the first value.
     */
    void testVisitConfigurationParameterLocalUrl();

    /**
     * Tests that the parameters in the first parameter with an equivalent in
     * the second parameter are merged.
     * Also, it is tested that if the second parameter is different than a
     * ConfigurationParameterMap, no parameter is merged.
     */
    void testVisitConfigurationParameterMap();

    /**
     * Tests that a second string parameter with a value set overrides the first
     * parameter value.
     * Also, it is tested that a second string parameter without a value set and
     * that a second parameter different than a ConfigurationParameterString
     * doesn't set anything on the first value.
     */
    void testVisitConfigurationParameterString();

    /**
     * Tests if the second configuration is merged into the first.
     */
    void testMerge();

private:

    /**
     * The ConfigurationMerger to test.
     */
    ConfigurationMerger* mConfigurationMerger;

};

}
}

#endif
