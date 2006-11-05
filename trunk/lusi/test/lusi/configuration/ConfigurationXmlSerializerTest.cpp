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

#include "ConfigurationXmlSerializerTest.h"

#define protected public
#define private public
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

using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

void ConfigurationXmlSerializerTest::setUp() {
    mConfigurationXmlSerializer = new ConfigurationXmlSerializer();
    mConfigurationXmlSerializer->mNode = xmlNewNode(0, BAD_CAST "root");
}

void ConfigurationXmlSerializerTest::tearDown() {
    if (mConfigurationXmlSerializer->mNode != 0) {
        //It also freeds all the child nodes
        xmlFreeNode(mConfigurationXmlSerializer->mNode);
    }
    delete mConfigurationXmlSerializer;
}

void ConfigurationXmlSerializerTest::testVisitConfigurationParameterBool() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterBool> parameter(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "bool", node->name));

    xmlAttrPtr attribute = node->properties;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "id", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "boolId", attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "name", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "Boolean",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "optional",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "information", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "A boolean value",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT_EQUAL((xmlAttrPtr)0, attribute);

    node = node->children;

    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value", true));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "bool", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "true", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value"));
    parameter->setValue(true);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "bool", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "true", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Boolean",
            ConfigurationParameter::OptionalPriority, "A boolean value", true));
    parameter->setValue(true);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "bool", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "true", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "true", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);
}

void ConfigurationXmlSerializerTest::testVisitConfigurationParameterDouble() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterDouble> parameter(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "double", node->name));

    xmlAttrPtr attribute = node->properties;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "id", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "doubleId",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "name", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "Double",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "optional",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "information", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "A double value",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT_EQUAL((xmlAttrPtr)0, attribute);

    node = node->children;

    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value", 11.38));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "double", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "11.38", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value"));
    parameter->setValue(42.108);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "double", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "42.108", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::OptionalPriority, "A double value", 11.38));
    parameter->setValue(42.108);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "double", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "11.38", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "42.108", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);
}

void ConfigurationXmlSerializerTest::testVisitConfigurationParameterInt() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterInt> parameter(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "int", node->name));

    xmlAttrPtr attribute = node->properties;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "id", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "intId", attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "name", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "Int",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "optional",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "information", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "An int value",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT_EQUAL((xmlAttrPtr)0, attribute);

    node = node->children;

    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value", 42));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "int", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "42", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value"));
    parameter->setValue(66);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "int", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "66", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::OptionalPriority, "An int value", 42));
    parameter->setValue(66);

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "int", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "42", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "66", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);
}

void ConfigurationXmlSerializerTest::testVisitConfigurationParameterLocalUrl() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterLocalUrl> parameter(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "localUrl", node->name));

    xmlAttrPtr attribute = node->properties;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "id", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "localUrlId",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "name", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "LocalUrl",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "optional",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "information", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "A localUrl value",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT_EQUAL((xmlAttrPtr)0, attribute);

    node = node->children;

    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            LocalUrl("/home/")));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "localUrl", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "/home/", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value"));
    parameter->setValue(LocalUrl("/etc/"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "localUrl", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "/etc/", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::OptionalPriority, "A localUrl value",
            LocalUrl("/home/")));
    parameter->setValue(LocalUrl("/etc/"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "localUrl", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "/home/", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "/etc/", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);
}

void ConfigurationXmlSerializerTest::testVisitConfigurationParameterMap() {
    //Test with an empty map
    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "map", node->name));

    xmlAttrPtr attribute = node->properties;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "id", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "mapId", attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "name", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "Map",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "optional",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "information", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "A map of parameters",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT_EQUAL((xmlAttrPtr)0, attribute);

    node = node->children;

    CPPUNIT_ASSERT(!node);

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
    SmartPtr<ConfigurationParameterString> stringParameter(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::RequiredPriority, "A string value"));
    stringParameter->setSerializable(false);
    parameter->add(stringParameter);

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

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "map", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);

    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "int", node->name));
    node = node->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "bool", node->name));
    node = node->next;
    xmlNodePtr node2 = node->children;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "map", node->name));
    node = node->next;
    CPPUNIT_ASSERT(!node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "localUrl", node2->name));
    node2 = node2->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "double", node2->name));
    node2 = node2->next;
    CPPUNIT_ASSERT(!node2);
}

void ConfigurationXmlSerializerTest::testVisitConfigurationParameterString() {
    //Test with a parameter without a default value set and without value set
    SmartPtr<ConfigurationParameterString> parameter(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    xmlNodePtr node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "string", node->name));

    xmlAttrPtr attribute = node->properties;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "id", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "stringId",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "name", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "String",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "optional",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "information", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "A string value",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT_EQUAL((xmlAttrPtr)0, attribute);

    node = node->children;

    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value", "foo"));

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "string", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "foo", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value"));
    parameter->setValue("bar");

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "string", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "bar", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);

    //Test with a parameter with a value and default value set
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::OptionalPriority, "A string value", "foo"));
    parameter->setValue("bar");

    mConfigurationXmlSerializer->visit(getPtr(parameter));
    node = mConfigurationXmlSerializer->mNode->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "string", node->name));

    node = node->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "defaultValue", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "foo", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "value", node->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "bar", node->children->content));

    node = node->next;
    CPPUNIT_ASSERT(!node);
}

void ConfigurationXmlSerializerTest::testSerialize() {
    xmlFreeNode(mConfigurationXmlSerializer->mNode);
    mConfigurationXmlSerializer->mNode = 0;

    SmartPtr<ConfigurationParameterMap> parameter(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));

    xmlDocPtr doc = mConfigurationXmlSerializer->serialize(getPtr(parameter));
    xmlNodePtr node = doc->children;

    CPPUNIT_ASSERT(0 != node);
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "map", node->name));

    //True, it won't be freed if an error happened... but, hey! That's why there
    //are tests, to prevent the errors from happen, so they shouldn't happen ;)
    xmlFreeDoc(doc);
}

void ConfigurationXmlSerializerTest::testNewNode() {
    SmartPtr<ConfigurationParameterTestImplementation> parameter(
        new ConfigurationParameterTestImplementation("testId", "Test",
            ConfigurationParameter::OptionalPriority, "A test"));

    xmlNodePtr node = mConfigurationXmlSerializer->newNode(getPtr(parameter),
                                                           "test");
    //The node is added to the root node so it's freed when the tearDown method
    //is called
    xmlAddChild(mConfigurationXmlSerializer->mNode, node);

    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "test", node->name));

    xmlAttrPtr attribute = node->properties;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "id", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "testId", attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "name", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "Test",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "optional",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "information", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "A test",
                              attribute->children->content));
    attribute = attribute->next;
    CPPUNIT_ASSERT_EQUAL((xmlAttrPtr)0, attribute);

    node = node->children;

    CPPUNIT_ASSERT(!node);

    //Test with a recommended priority
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterTestImplementation>(
        new ConfigurationParameterTestImplementation("testId", "Test",
            ConfigurationParameter::RecommendedPriority, "A test"));

    node = mConfigurationXmlSerializer->newNode(getPtr(parameter),
                                                           "test");
    xmlAddChild(mConfigurationXmlSerializer->mNode, node);

    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "test", node->name));

    attribute = node->properties;
    attribute = attribute->next;
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "recommended",
                              attribute->children->content));

    //Test with a required priority
    restartTestObjects();

    parameter = SmartPtr<ConfigurationParameterTestImplementation>(
        new ConfigurationParameterTestImplementation("testId", "Test",
            ConfigurationParameter::RequiredPriority, "A test"));

    node = mConfigurationXmlSerializer->newNode(getPtr(parameter),
                                                           "test");
    xmlAddChild(mConfigurationXmlSerializer->mNode, node);

    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "test", node->name));

    attribute = node->properties;
    attribute = attribute->next;
    attribute = attribute->next;
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "priorityType", attribute->name));
    CPPUNIT_ASSERT(!xmlStrcmp(BAD_CAST "required",
                              attribute->children->content));
}

//private:

void ConfigurationXmlSerializerTest::restartTestObjects() {
    tearDown();
    setUp();
}
