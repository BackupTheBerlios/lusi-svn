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

#include "ConfigurationXmlDeserializerTest.h"

#define protected public
#define private public
#include "ConfigurationXmlDeserializer.h"
#include "ConfigurationXmlSerializer.h"
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

void ConfigurationXmlDeserializerTest::setUp() {
    mConfigurationXmlDeserializer = new ConfigurationXmlDeserializer();

    mConfigurationXmlSerializer = new ConfigurationXmlSerializer();
    mConfigurationXmlSerializer->mNode = xmlNewNode(0, BAD_CAST "root");
}

void ConfigurationXmlDeserializerTest::tearDown() {
    delete mConfigurationXmlDeserializer;

    if (mConfigurationXmlSerializer->mNode != 0) {
        //It also freeds all the child nodes
        xmlFreeNode(mConfigurationXmlSerializer->mNode);
    }
    delete mConfigurationXmlSerializer;
}

void ConfigurationXmlDeserializerTest::testDeserialize() {
    xmlFreeNode(mConfigurationXmlSerializer->mNode);
    mConfigurationXmlSerializer->mNode = 0;

    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));

    xmlDocPtr doc = mConfigurationXmlSerializer->serialize(getPtr(parameter));

    SmartPtr<ConfigurationParameterMap> deserializedParameter(
                            mConfigurationXmlDeserializer->deserialize(doc));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL((size_t)0, deserializedParameter->getAll().size());

    //True, it won't be freed if an error happened... but, hey! That's why there
    //are tests, to prevent the errors from happen, so they shouldn't happen ;)
    //And yes, I copied and pasted the same text from the serializer test :P
    xmlFreeDoc(doc);
}

void ConfigurationXmlDeserializerTest::
testDeserializeConfigurationParameterBool() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterBool> parameter(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    SmartPtr<ConfigurationParameterBool> deserializedParameter(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterBool(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value", true));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterBool>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterBool(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value"));
    parameter->setValue(true);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterBool>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterBool(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value", true));
    parameter->setValue(true);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterBool>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterBool(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());
}

void ConfigurationXmlDeserializerTest::
testDeserializeConfigurationParameterDouble() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterDouble> parameter(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    SmartPtr<ConfigurationParameterDouble> deserializedParameter(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterDouble(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value", 4.8));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterDouble>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterDouble(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value"));
    parameter->setValue(15.16);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterDouble>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterDouble(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value", 4.8));
    parameter->setValue(15.16);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterDouble>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterDouble(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());
}

void ConfigurationXmlDeserializerTest::
testDeserializeConfigurationParameterInt() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterInt> parameter(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    SmartPtr<ConfigurationParameterInt> deserializedParameter(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterInt(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value", 23));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterInt>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterInt(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value"));
    parameter->setValue(42);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterInt>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterInt(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value", 23));
    parameter->setValue(42);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterInt>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterInt(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());
}

void ConfigurationXmlDeserializerTest::
testDeserializeConfigurationParameterLocalUrl() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterLocalUrl> parameter(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    SmartPtr<ConfigurationParameterLocalUrl> deserializedParameter(
        mConfigurationXmlDeserializer->
            deserializeConfigurationParameterLocalUrl(node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            LocalUrl("/home/")));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterLocalUrl>(
        mConfigurationXmlDeserializer->
            deserializeConfigurationParameterLocalUrl(node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT(parameter->getDefaultValue() ==
                   deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value"));
    parameter->setValue(LocalUrl("/etc/"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterLocalUrl>(
        mConfigurationXmlDeserializer->
            deserializeConfigurationParameterLocalUrl(node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT(parameter->getValue() == deserializedParameter->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            LocalUrl("/home/")));
    parameter->setValue(LocalUrl("/etc/"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterLocalUrl>(
        mConfigurationXmlDeserializer->
            deserializeConfigurationParameterLocalUrl(node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT(parameter->getDefaultValue() ==
                   deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT(parameter->getValue() ==
                   deserializedParameter->getValue());
}

void ConfigurationXmlDeserializerTest::
testDeserializeConfigurationParameterMap() {
    //Test with an empty map
    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    SmartPtr<ConfigurationParameterMap> deserializedParameter(
        mConfigurationXmlDeserializer->
            deserializeConfigurationParameterMap(node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL((size_t)0, deserializedParameter->getAll().size());

    //Test with a map with elements
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterMap>(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));
    parameter->add(SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::RequiredPriority, "An int value")));
    parameter->add(SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Bool",
            ConfigurationParameter::RequiredPriority, "A bool value")));
    parameter->add(SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::RequiredPriority, "A string value")));

    SmartPtr<ConfigurationParameterMap> parameter2(
        new ConfigurationParameterMap("mapId2", "Map2",
            ConfigurationParameter::OptionalPriority,
            "Another map of parameters"));
    parameter->add(parameter2);
    parameter2->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::RequiredPriority, "A LocalUrl value")));
    parameter2->add(SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::RequiredPriority, "A double value")));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterMap>(
        mConfigurationXmlDeserializer->
            deserializeConfigurationParameterMap(node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    vector< SmartPtr<ConfigurationParameter> > parameters =
                                                deserializedParameter->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)4, parameters.size());
    CPPUNIT_ASSERT_EQUAL(string("intId"), parameters[0]->getId());
    CPPUNIT_ASSERT_EQUAL(string("boolId"), parameters[1]->getId());
    CPPUNIT_ASSERT_EQUAL(string("stringId"), parameters[2]->getId());
    CPPUNIT_ASSERT_EQUAL(string("mapId2"), parameters[3]->getId());
    parameters = ((SmartPtr<ConfigurationParameterMap>)parameters[3])->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)2, parameters.size());
    CPPUNIT_ASSERT_EQUAL(string("localUrlId"), parameters[0]->getId());
    CPPUNIT_ASSERT_EQUAL(string("doubleId"), parameters[1]->getId());
}

void ConfigurationXmlDeserializerTest::
testDeserializeConfigurationParameterString() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterString> parameter(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    SmartPtr<ConfigurationParameterString> deserializedParameter(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterString(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value", "foo"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterString>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterString(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isValueSet());

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value"));
    parameter->setValue("bar");

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterString>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterString(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(false, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value", "foo"));
    parameter->setValue("bar");

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    deserializedParameter = SmartPtr<ConfigurationParameterString>(
        mConfigurationXmlDeserializer->deserializeConfigurationParameterString(
            node));

    CPPUNIT_ASSERT(0 != getPtr(deserializedParameter));
    CPPUNIT_ASSERT_EQUAL(parameter->getId(), deserializedParameter->getId());
    CPPUNIT_ASSERT_EQUAL(parameter->getName(),
                         deserializedParameter->getName());
    CPPUNIT_ASSERT_EQUAL(parameter->getPriorityType(),
                         deserializedParameter->getPriorityType());
    CPPUNIT_ASSERT_EQUAL(parameter->getInformation(),
                         deserializedParameter->getInformation());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isDefaultValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getDefaultValue(),
                         deserializedParameter->getDefaultValue());
    CPPUNIT_ASSERT_EQUAL(true, deserializedParameter->isValueSet());
    CPPUNIT_ASSERT_EQUAL(parameter->getValue(),
                         deserializedParameter->getValue());
}

//private:

void ConfigurationXmlDeserializerTest::restartTestObjects() {
    tearDown();
    setUp();
}
