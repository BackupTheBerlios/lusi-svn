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

#include "ConfigurationMergerTest.h"

#define protected public
#define private public
#include "ConfigurationMerger.h"
#undef private
#undef protected

#include "ConfigurationParameterBool.h"
#include "ConfigurationParameterDouble.h"
#include "ConfigurationParameterInt.h"
#include "ConfigurationParameterLocalUrl.h"
#include "ConfigurationParameterMap.h"
#include "ConfigurationParameterString.h"
#include "ConfigurationParameterTestImplementation.h"

using std::string;
using std::vector;

using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

void ConfigurationMergerTest::setUp() {
    mConfigurationMerger = new ConfigurationMerger();
}

void ConfigurationMergerTest::tearDown() {
    delete mConfigurationMerger;
}

void ConfigurationMergerTest::testVisitConfigurationParameterBool() {
    //Test with a parameter with value set
    SmartPtr<ConfigurationParameterBool> parameter(
        new ConfigurationParameterBool("boolId", "Bool",
            ConfigurationParameter::RequiredPriority, "A bool value"));
    parameter->setValue(false);

    SmartPtr<ConfigurationParameterBool> parameter2(
        new ConfigurationParameterBool("boolId", "Bool2",
            ConfigurationParameter::OptionalPriority, "A bool value2", true));
    parameter2->setValue(true);
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(string("Bool"), parameter->getName());
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         parameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(string("A bool value"),
                         parameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, parameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, parameter->getValue());

    //Test with a parameter without value set
    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Bool",
            ConfigurationParameter::OptionalPriority, "A bool value"));

    parameter2 = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Bool2",
            ConfigurationParameter::OptionalPriority, "A bool value2", true));
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());

    //Test with a parameter of a different class
    SmartPtr<ConfigurationParameterTestImplementation> parameterBad(
        new ConfigurationParameterTestImplementation("boolId", "Bad type",
            ConfigurationParameter::OptionalPriority, "A bad type parameter"));
    mConfigurationMerger->mParameter2 = getPtr(parameterBad);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());
}

void ConfigurationMergerTest::testVisitConfigurationParameterDouble() {
    //Test with a parameter with value set
    SmartPtr<ConfigurationParameterDouble> parameter(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::RequiredPriority, "A double value"));
    parameter->setValue(4.8);

    SmartPtr<ConfigurationParameterDouble> parameter2(
        new ConfigurationParameterDouble("doubleId", "Double2",
            ConfigurationParameter::OptionalPriority, "A double value2",
            15.16));
    parameter2->setValue(23.42);
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(string("Double"), parameter->getName());
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         parameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(string("A double value"),
                         parameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, parameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(23.42, parameter->getValue());

    //Test with a parameter without value set
    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value"));

    parameter2 = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double2",
            ConfigurationParameter::OptionalPriority, "A double value2",
            15.16));
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());

    //Test with a parameter of a different class
    SmartPtr<ConfigurationParameterTestImplementation> parameterBad(
        new ConfigurationParameterTestImplementation("doubleId", "Bad type",
            ConfigurationParameter::OptionalPriority, "A bad type parameter"));
    mConfigurationMerger->mParameter2 = getPtr(parameterBad);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());
}

void ConfigurationMergerTest::testVisitConfigurationParameterInt() {
    //Test with a parameter with value set
    SmartPtr<ConfigurationParameterInt> parameter(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::RequiredPriority, "A int value"));
    parameter->setValue(1138);

    SmartPtr<ConfigurationParameterInt> parameter2(
        new ConfigurationParameterInt("intId", "Int2",
            ConfigurationParameter::OptionalPriority, "A int value2", 42));
    parameter2->setValue(66);
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(string("Int"), parameter->getName());
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         parameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(string("A int value"),
                         parameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, parameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, parameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(66, parameter->getValue());

    //Test with a parameter without value set
    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "A int value"));

    parameter2 = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int2",
            ConfigurationParameter::OptionalPriority, "A int value2", 42));
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());

    //Test with a parameter of a different class
    SmartPtr<ConfigurationParameterTestImplementation> parameterBad(
        new ConfigurationParameterTestImplementation("intId", "Bad type",
            ConfigurationParameter::OptionalPriority, "A bad type parameter"));
    mConfigurationMerger->mParameter2 = getPtr(parameterBad);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());
}

void ConfigurationMergerTest::testVisitConfigurationParameterLocalUrl() {
    //Test with a parameter with value set
    SmartPtr<ConfigurationParameterLocalUrl> parameter(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::RequiredPriority, "A localUrl value"));
    parameter->setValue(LocalUrl("/usr/"));

    SmartPtr<ConfigurationParameterLocalUrl> parameter2(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl2",
            ConfigurationParameter::OptionalPriority, "A localUrl value2",
            LocalUrl("/home/")));
    parameter2->setValue(LocalUrl("/etc/"));
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(string("LocalUrl"), parameter->getName());
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         parameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(string("A localUrl value"),
                         parameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, parameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, parameter->isValueSet());
    CPPUNIT_ASSERT(LocalUrl("/etc/") == parameter->getValue());

    //Test with a parameter without value set
    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value"));

    parameter2 = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl2",
            ConfigurationParameter::OptionalPriority, "A localUrl value2",
            LocalUrl("/home/")));
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());

    //Test with a parameter of a different class
    SmartPtr<ConfigurationParameterTestImplementation> parameterBad(
        new ConfigurationParameterTestImplementation("localUrlId", "Bad type",
            ConfigurationParameter::OptionalPriority, "A bad type parameter"));
    mConfigurationMerger->mParameter2 = getPtr(parameterBad);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());
}

void ConfigurationMergerTest::testVisitConfigurationParameterMap() {
    //Test with a ConfigurationParameterMap
    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::RequiredPriority, "A string value"));
    parameter->add(SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::RequiredPriority, "An int value")));
    parameter->add(SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Bool",
            ConfigurationParameter::RequiredPriority, "A bool value")));
    SmartPtr<ConfigurationParameterString> stringParameter(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::RequiredPriority, "A string value"));
    stringParameter->setValue("No equivalent in 2");
    parameter->add(stringParameter);
    SmartPtr<ConfigurationParameterMap> childParameter(
        new ConfigurationParameterMap("mapIdChild", "Child map",
            ConfigurationParameter::OptionalPriority,
            "Another map of parameters"));
    parameter->add(childParameter);
    childParameter->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::RequiredPriority, "A LocalUrl value")));
    childParameter->add(SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::RequiredPriority, "A double value")));

    SmartPtr<ConfigurationParameterMap> parameter2(
        new ConfigurationParameterMap("mapId", "Map2",
            ConfigurationParameter::RequiredPriority, "A string value2"));
    parameter2->add(SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId2", "Int2",
            ConfigurationParameter::RequiredPriority, "Not present in 1")));
    parameter2->add(SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("boolId", "String2",
            ConfigurationParameter::RequiredPriority, "Wrong type")));
    SmartPtr<ConfigurationParameterMap> childParameter2(
        new ConfigurationParameterMap("mapIdChild", "Map2",
            ConfigurationParameter::OptionalPriority,
            "Another map of parameters"));
    parameter2->add(childParameter2);
    childParameter2->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl2",
            ConfigurationParameter::RequiredPriority, "No value set")));
    SmartPtr<ConfigurationParameterDouble> doubleParameter2(
        new ConfigurationParameterDouble("doubleId",
            "Double2", ConfigurationParameter::RequiredPriority,
            "A double value2"));
    doubleParameter2->setValue(42.108);
    childParameter2->add(doubleParameter2);
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    vector< SmartPtr<ConfigurationParameter> > parameters = parameter->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)4, parameters.size());
    CPPUNIT_ASSERT_EQUAL(false,
            ((ConfigurationParameterInt*)getPtr(parameters[0]))->isValueSet());
    CPPUNIT_ASSERT_EQUAL(false,
            ((ConfigurationParameterBool*)getPtr(parameters[1]))->isValueSet());
    CPPUNIT_ASSERT_EQUAL(string("No equivalent in 2"),
            ((ConfigurationParameterString*)getPtr(parameters[2]))->getValue());
    CPPUNIT_ASSERT_EQUAL(string("mapIdChild"), parameters[3]->getId());
    parameters = ((SmartPtr<ConfigurationParameterMap>)parameters[3])->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)2, parameters.size());
    CPPUNIT_ASSERT_EQUAL(false,
        ((ConfigurationParameterLocalUrl*)getPtr(parameters[0]))->isValueSet());
    CPPUNIT_ASSERT_EQUAL(42.108,
            ((ConfigurationParameterDouble*)getPtr(parameters[1]))->getValue());

    //Test with a second parameter different than a ConfigurationParameterMap
    SmartPtr<ConfigurationParameterTestImplementation> parameterBad(
        new ConfigurationParameterTestImplementation("mapId", "Bad type",
            ConfigurationParameter::OptionalPriority, "A bad type parameter"));
    mConfigurationMerger->mParameter2 = getPtr(parameterBad);

    mConfigurationMerger->visit(getPtr(parameter));
}

void ConfigurationMergerTest::testVisitConfigurationParameterString() {
    //Test with a parameter with value set
    SmartPtr<ConfigurationParameterString> parameter(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::RequiredPriority, "A string value"));
    parameter->setValue("foo");

    SmartPtr<ConfigurationParameterString> parameter2(
        new ConfigurationParameterString("stringId", "String2",
            ConfigurationParameter::OptionalPriority, "A string value2",
            "bar"));
    parameter2->setValue("baz");
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(string("String"), parameter->getName());
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         parameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(string("A string value"),
                         parameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, parameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, parameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(string("baz"), parameter->getValue());

    //Test with a parameter without value set
    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value"));

    parameter2 = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String2",
            ConfigurationParameter::OptionalPriority, "A string value2",
            "bar"));
    mConfigurationMerger->mParameter2 = getPtr(parameter2);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());

    //Test with a parameter of a different class
    SmartPtr<ConfigurationParameterTestImplementation> parameterBad(
        new ConfigurationParameterTestImplementation("stringId", "Bad type",
            ConfigurationParameter::OptionalPriority, "A bad type parameter"));
    mConfigurationMerger->mParameter2 = getPtr(parameterBad);

    mConfigurationMerger->visit(getPtr(parameter));

    CPPUNIT_ASSERT_EQUAL(false, parameter->isValueSet());
}

void ConfigurationMergerTest::testMerge() {
    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::RequiredPriority, "A string value"));
    SmartPtr<ConfigurationParameterInt> intParameter(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::RequiredPriority, "An int value"));
    intParameter->setValue(42);
    parameter->add(intParameter);

    SmartPtr<ConfigurationParameterMap> parameter2(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::RequiredPriority, "A string value"));
    SmartPtr<ConfigurationParameterInt> intParameter2(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::RequiredPriority, "An int value"));
    intParameter2->setValue(66);
    parameter2->add(intParameter2);

    mConfigurationMerger->merge(getPtr(parameter), getPtr(parameter2));

    CPPUNIT_ASSERT_EQUAL(66, intParameter->getValue());
}
