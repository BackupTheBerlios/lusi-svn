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

#include "ConfigurationClonerTest.h"

#define protected public
#define private public
#include "ConfigurationCloner.h"
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

using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

void ConfigurationClonerTest::setUp() {
    mConfigurationCloner = new ConfigurationCloner();
    mConfigurationCloner->mClonedConfiguration =
        new ConfigurationParameterMap("clone");
}

void ConfigurationClonerTest::tearDown() {
    delete mConfigurationCloner->mClonedConfiguration;
    delete mConfigurationCloner;
}

void ConfigurationClonerTest::testVisitConfigurationParameterBool() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterBool> parameter(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value"));

    mConfigurationCloner->visit(getPtr(parameter));

    SmartPtr<ConfigurationParameterBool> clone(
                    mConfigurationCloner->mClonedConfiguration->get("boolId"));

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value", true));

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("boolId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         parameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value"));
    parameter->setValue(true);

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("boolId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value", true));
    parameter->setValue(true);

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("boolId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         clone->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());
}

void ConfigurationClonerTest::testVisitConfigurationParameterDouble() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterDouble> parameter(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value"));

    mConfigurationCloner->visit(getPtr(parameter));

    SmartPtr<ConfigurationParameterDouble> clone(
                mConfigurationCloner->mClonedConfiguration->get("doubleId"));

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value", 11.38));

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("doubleId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         parameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value"));
    parameter->setValue(42.108);

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("doubleId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value", 11.38));
    parameter->setValue(42.108);

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("doubleId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         clone->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());
}

void ConfigurationClonerTest::testVisitConfigurationParameterInt() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterInt> parameter(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value"));

    mConfigurationCloner->visit(getPtr(parameter));

    SmartPtr<ConfigurationParameterInt> clone(
                mConfigurationCloner->mClonedConfiguration->get("intId"));

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value", 42));

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("intId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         parameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value"));
    parameter->setValue(66);

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("intId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value", 42));
    parameter->setValue(66);

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("intId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         clone->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());
}

void ConfigurationClonerTest::testVisitConfigurationParameterLocalUrl() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterLocalUrl> parameter(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            ConfigurationParameterLocalUrl::FileType));

    mConfigurationCloner->visit(getPtr(parameter));

    SmartPtr<ConfigurationParameterLocalUrl> clone(
                mConfigurationCloner->mClonedConfiguration->get("localUrlId"));

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getUrlType(), clone->getUrlType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            LocalUrl("/home/"), ConfigurationParameterLocalUrl::FileType));

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("localUrlId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getUrlType(), clone->getUrlType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT(parameter->getDefaultValue() ==
                   parameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            ConfigurationParameterLocalUrl::FileType));
    parameter->setValue(LocalUrl("/etc/"));

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("localUrlId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getUrlType(), clone->getUrlType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT(parameter->getValue() == clone->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            LocalUrl("/home/"), ConfigurationParameterLocalUrl::FileType));
    parameter->setValue(LocalUrl("/etc/"));

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("localUrlId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getUrlType(), clone->getUrlType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT(parameter->getDefaultValue() ==
                   clone->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT(parameter->getValue() == clone->getValue());
}

void ConfigurationClonerTest::testVisitConfigurationParameterMap() {
    //Test with an empty map
    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));

    mConfigurationCloner->visit(getPtr(parameter));

    SmartPtr<ConfigurationParameterMap> clone(
                mConfigurationCloner->mClonedConfiguration->get("mapId"));

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());

    //Test with a map with elements
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterMap>(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));

    SmartPtr<ConfigurationParameterMap> parameter2(
        new ConfigurationParameterMap("mapId2", "Map2",
            ConfigurationParameter::OptionalPriority,
            "Another map of parameters"));
    parameter->add(parameter2);
    SmartPtr<ConfigurationParameterDouble> doubleParameter(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::RequiredPriority, "A double value"));
    parameter2->add(doubleParameter);

    SmartPtr<ConfigurationParameterString> stringParameter(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::RequiredPriority, "A string value"));
    parameter->add(stringParameter);

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("mapId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());

    SmartPtr<ConfigurationParameterMap> parameter2Clone(clone->get("mapId2"));
    CPPUNIT_ASSERT_EQUAL(false, parameter2Clone.isNull());
    CPPUNIT_ASSERT(parameter2 != parameter2Clone);
    CPPUNIT_ASSERT_EQUAL(parameter2->getName(), parameter2Clone->getName());

    SmartPtr<ConfigurationParameterDouble> doubleParameterClone(
        parameter2Clone->get("doubleId"));
    CPPUNIT_ASSERT_EQUAL(false, doubleParameterClone.isNull());
    CPPUNIT_ASSERT(doubleParameter != doubleParameterClone);
    CPPUNIT_ASSERT_EQUAL(doubleParameter->getName(),
                         doubleParameterClone->getName());

    SmartPtr<ConfigurationParameterString> stringParameterClone(
        clone->get("stringId"));
    CPPUNIT_ASSERT_EQUAL(false, stringParameterClone.isNull());
    CPPUNIT_ASSERT(stringParameter != stringParameterClone);
    CPPUNIT_ASSERT_EQUAL(stringParameter->getName(),
                         stringParameterClone->getName());
}

void ConfigurationClonerTest::testVisitConfigurationParameterString() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterString> parameter(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value",
            ConfigurationParameterString::PasswordType));

    mConfigurationCloner->visit(getPtr(parameter));

    SmartPtr<ConfigurationParameterString> clone(
                mConfigurationCloner->mClonedConfiguration->get("stringId"));

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getStringType(), clone->getStringType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value", "foo",
            ConfigurationParameterString::PasswordType));

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("stringId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getStringType(), clone->getStringType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         parameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value",
            ConfigurationParameterString::PasswordType));
    parameter->setValue("bar");

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("stringId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getStringType(), clone->getStringType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value", "foo",
            ConfigurationParameterString::PasswordType));
    parameter->setValue("bar");

    mConfigurationCloner->visit(getPtr(parameter));

    clone = mConfigurationCloner->mClonedConfiguration->get("stringId");

    CPPUNIT_ASSERT_EQUAL(false, clone.isNull());
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
    CPPUNIT_ASSERT_EQUAL(parameter->getStringType(), clone->getStringType());
    CPPUNIT_ASSERT_EQUAL(parameter->isDefaultValueSet(),
                         clone->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         clone->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(parameter->isValueSet(), clone->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(), clone->getValue());
}

void ConfigurationClonerTest::testClone() {
    delete mConfigurationCloner->mClonedConfiguration;
    mConfigurationCloner->mClonedConfiguration = 0;

    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));

    ConfigurationParameterMap* clone =
        mConfigurationCloner->clone(getPtr(parameter));

    CPPUNIT_ASSERT(0 != clone);
    CPPUNIT_ASSERT(parameter != clone);
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), clone->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(), clone->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         clone->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(), clone->getInformation());
}

//private:

void ConfigurationClonerTest::restartTestObjects() {
    tearDown();
    setUp();
}
