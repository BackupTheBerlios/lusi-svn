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

#include "ConfigurationParameterMapTest.h"

#define protected public
#define private public
#include "ConfigurationParameterMap.h"
#undef private
#undef protected

#include "ConfigurationParameterTestImplementation.h"
#include "../util/SmartPtr.h"

using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

void ConfigurationParameterMapTest::setUp() {
    mConfigurationParameterMap = new ConfigurationParameterMap();

    mParameter1 = new ConfigurationParameterTestImplementation("1", "1",
                            ConfigurationParameter::RequiredPriority, "1");
    mParameter2 = new ConfigurationParameterTestImplementation("2", "2",
                            ConfigurationParameter::RequiredPriority, "2");
    mParameter3 = new ConfigurationParameterTestImplementation("3", "3",
                            ConfigurationParameter::RequiredPriority, "3");

    mConfigurationParameterMap->add(
                            SmartPtr<ConfigurationParameter>(mParameter1));
    mConfigurationParameterMap->add(
                            SmartPtr<ConfigurationParameter>(mParameter2));
    mConfigurationParameterMap->add(
                            SmartPtr<ConfigurationParameter>(mParameter3));
}

void ConfigurationParameterMapTest::tearDown() {
    delete mConfigurationParameterMap;
}

void ConfigurationParameterMapTest::testCopyConstructor() {
    ConfigurationParameterMap configurationParameterMap(
                                            *mConfigurationParameterMap);

    //Tests the original map
    CPPUNIT_ASSERT_EQUAL(mParameter1,
                         getPtr(mConfigurationParameterMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(mParameter2,
                         getPtr(mConfigurationParameterMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(mParameter3,
                         getPtr(mConfigurationParameterMap->get("3")));

    //Tests the copied map
    CPPUNIT_ASSERT_EQUAL(mParameter1,
                         getPtr(configurationParameterMap.get("1")));
    CPPUNIT_ASSERT_EQUAL(mParameter2,
                         getPtr(configurationParameterMap.get("2")));
    CPPUNIT_ASSERT_EQUAL(mParameter3,
                         getPtr(configurationParameterMap.get("3")));
}

void ConfigurationParameterMapTest::testMerge() {
    delete mConfigurationParameterMap;
    mConfigurationParameterMap = new ConfigurationParameterMap();

    ConfigurationParameterMap configurationParameterMap;

    SmartPtr<ConfigurationParameter> parameter1(
            new ConfigurationParameterTestImplementation("1", "1",
                    ConfigurationParameter::RequiredPriority, "1"));
    SmartPtr<ConfigurationParameter> parameter2(
            new ConfigurationParameterTestImplementation("2", "2",
                    ConfigurationParameter::RequiredPriority, "2"));
    SmartPtr<ConfigurationParameter> parameter3(
            new ConfigurationParameterTestImplementation("3", "3",
                    ConfigurationParameter::RequiredPriority, "3a"));
    SmartPtr<ConfigurationParameter> parameter3B(
            new ConfigurationParameterTestImplementation("3", "3",
                    ConfigurationParameter::RecommendedPriority, "3b"));

    mConfigurationParameterMap->add(parameter1);
    mConfigurationParameterMap->add(parameter3);
    configurationParameterMap.add(parameter2);
    configurationParameterMap.add(parameter3B);

    //Test keep merge
    mConfigurationParameterMap->merge(configurationParameterMap);

    CPPUNIT_ASSERT_EQUAL(getPtr(parameter1),
                         getPtr(mConfigurationParameterMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter2),
                         getPtr(mConfigurationParameterMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter3),
                         getPtr(mConfigurationParameterMap->get("3")));
    CPPUNIT_ASSERT_EQUAL((size_t)3,
                         mConfigurationParameterMap->getAll().size());

    //Test override merge
    SmartPtr<ConfigurationParameter> parameter4(
            new ConfigurationParameterTestImplementation("4", "4",
                    ConfigurationParameter::RequiredPriority, "4"));
    configurationParameterMap.add(parameter4);

    mConfigurationParameterMap->merge(configurationParameterMap,
                                ConfigurationParameterMap::OverrideParameters);


    CPPUNIT_ASSERT_EQUAL(getPtr(parameter1),
                         getPtr(mConfigurationParameterMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter2),
                         getPtr(mConfigurationParameterMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter3B),
                         getPtr(mConfigurationParameterMap->get("3")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter4),
                         getPtr(mConfigurationParameterMap->get("4")));
    CPPUNIT_ASSERT_EQUAL((size_t)4,
                         mConfigurationParameterMap->getAll().size());
}

void ConfigurationParameterMapTest::testOperatorAssignment() {
    ConfigurationParameterMap configurationParameterMap;
    configurationParameterMap = *mConfigurationParameterMap;

    //Tests the original map
    CPPUNIT_ASSERT_EQUAL(mParameter1,
                         getPtr(mConfigurationParameterMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(mParameter2,
                         getPtr(mConfigurationParameterMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(mParameter3,
                         getPtr(mConfigurationParameterMap->get("3")));

    //Tests the copied map
    CPPUNIT_ASSERT_EQUAL(mParameter1,
                         getPtr(configurationParameterMap.get("1")));
    CPPUNIT_ASSERT_EQUAL(mParameter2,
                         getPtr(configurationParameterMap.get("2")));
    CPPUNIT_ASSERT_EQUAL(mParameter3,
                         getPtr(configurationParameterMap.get("3")));

    //Test self assignment
    configurationParameterMap = configurationParameterMap;

    CPPUNIT_ASSERT_EQUAL(mParameter1,
                         getPtr(configurationParameterMap.get("1")));
    CPPUNIT_ASSERT_EQUAL(mParameter2,
                         getPtr(configurationParameterMap.get("2")));
    CPPUNIT_ASSERT_EQUAL(mParameter3,
                         getPtr(configurationParameterMap.get("3")));
}
