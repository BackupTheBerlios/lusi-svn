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

#include <sstream>

#include "ConfigurationXmlSerializer.h"
#include "ConfigurationParameterBool.h"
#include "ConfigurationParameterDouble.h"
#include "ConfigurationParameterInt.h"
#include "ConfigurationParameterLocalUrl.h"
#include "ConfigurationParameterMap.h"
#include "ConfigurationParameterString.h"

using std::ostringstream;
using std::string;
using std::vector;

using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

ConfigurationXmlSerializer::ConfigurationXmlSerializer():
        ConfigurationParameterVisitor() {
    mNode = 0;
}

ConfigurationXmlSerializer::~ConfigurationXmlSerializer() {
}

void ConfigurationXmlSerializer::visit(ConfigurationParameterBool* parameter) {
    xmlNodePtr boolNode = newNode(parameter, "bool");

    if (parameter->isDefaultValueSet()) {
        string defaultValue = parameter->getDefaultValue() ? "true": "false";
        xmlNewTextChild(boolNode, 0, BAD_CAST "defaultValue",
                        BAD_CAST defaultValue.c_str());
    }

    if (parameter->isValueSet()) {
        string value = parameter->getValue() ? "true": "false";
        xmlNewTextChild(boolNode, 0, BAD_CAST "value", BAD_CAST value.c_str());
    }

    xmlAddChild(mNode, boolNode);
}

void ConfigurationXmlSerializer::visit(
                                    ConfigurationParameterDouble* parameter) {
    xmlNodePtr doubleNode = newNode(parameter, "double");

    if (parameter->isDefaultValueSet()) {
        ostringstream fromDouble;
        fromDouble << parameter->getDefaultValue();
        string defaultValue = fromDouble.str();
        xmlNewTextChild(doubleNode, 0, BAD_CAST "defaultValue",
                        BAD_CAST defaultValue.c_str());
    }

    if (parameter->isValueSet()) {
        ostringstream fromDouble;
        fromDouble << parameter->getValue();
        string value = fromDouble.str();
        xmlNewTextChild(doubleNode, 0, BAD_CAST "value",
                        BAD_CAST value.c_str());
    }

    xmlAddChild(mNode, doubleNode);
}

void ConfigurationXmlSerializer::visit(ConfigurationParameterInt* parameter) {
    xmlNodePtr intNode = newNode(parameter, "int");

    if (parameter->isDefaultValueSet()) {
        ostringstream fromInt;
        fromInt << parameter->getDefaultValue();
        string defaultValue = fromInt.str();
        xmlNewTextChild(intNode, 0, BAD_CAST "defaultValue",
                        BAD_CAST defaultValue.c_str());
    }

    if (parameter->isValueSet()) {
        ostringstream fromInt;
        fromInt << parameter->getValue();
        string value = fromInt.str();
        xmlNewTextChild(intNode, 0, BAD_CAST "value", BAD_CAST value.c_str());
    }

    xmlAddChild(mNode, intNode);
}

void ConfigurationXmlSerializer::visit(
                                    ConfigurationParameterLocalUrl* parameter) {
    xmlNodePtr localUrlNode = newNode(parameter, "localUrl");

    if (parameter->isDefaultValueSet()) {
        string defaultValue = parameter->getDefaultValue().getPath();
        xmlNewTextChild(localUrlNode, 0, BAD_CAST "defaultValue",
                        BAD_CAST defaultValue.c_str());
    }

    if (parameter->isValueSet()) {
        string value = parameter->getValue().getPath();
        xmlNewTextChild(localUrlNode, 0, BAD_CAST "value",
                        BAD_CAST value.c_str());
    }

    xmlAddChild(mNode, localUrlNode);
}

void ConfigurationXmlSerializer::visit(ConfigurationParameterMap* parameter) {
    xmlNodePtr mapNode = 0;
    if (mNode == 0) {
        //TODO add namespace?
        mNode = newNode(parameter, "map");
        mapNode = mNode;
    } else {
        mapNode = newNode(parameter, "map");
        xmlAddChild(mNode, mapNode);
    }

    xmlNodePtr parentNode = mNode;
    mNode = mapNode;

    vector< SmartPtr<ConfigurationParameter> > children =
                                                        parameter->getAll();
    for (uint i=0; i<children.size(); ++i) {
        if (children[i]->isSerializable()) {
            children[i]->accept(this);
        }
    }

    mNode = parentNode;
}

void ConfigurationXmlSerializer::visit(
                                    ConfigurationParameterString* parameter) {
    xmlNodePtr stringNode = newNode(parameter, "string");

    if (parameter->isDefaultValueSet()) {
        string defaultValue = parameter->getDefaultValue();
        xmlNewTextChild(stringNode, 0, BAD_CAST "defaultValue",
                        BAD_CAST defaultValue.c_str());
    }

    if (parameter->isValueSet()) {
        string value = parameter->getValue();
        xmlNewTextChild(stringNode, 0, BAD_CAST "value",
                        BAD_CAST value.c_str());
    }

    xmlAddChild(mNode, stringNode);
}

xmlDocPtr ConfigurationXmlSerializer::serialize(
                        ConfigurationParameterMap* configurationParameterMap) {
    xmlDocPtr document = xmlNewDoc(BAD_CAST "1.0");

    configurationParameterMap->accept(this);

    xmlDocSetRootElement(document, mNode);
    mNode = 0;

    return document;
}

//TODO ConfigurationParameter shouldn't save i18ned name nor information
xmlNodePtr ConfigurationXmlSerializer::newNode(
                                            ConfigurationParameter* parameter,
                                            const char* name) {
    xmlNodePtr node = xmlNewNode(0, BAD_CAST name);

    xmlNewProp(node, BAD_CAST "id", BAD_CAST parameter->getId().c_str());

    if (parameter->getName() == "" &&
            parameter->getPriorityType() == ConfigurationParameter::NoPriority &&
            parameter->getInformation() == "") {
        return node;
    }

    xmlNewProp(node, BAD_CAST "name", BAD_CAST parameter->getName().c_str());

    if (parameter->getPriorityType() ==
                                ConfigurationParameter::RequiredPriority) {
        xmlNewProp(node, BAD_CAST "priorityType", BAD_CAST "required");
    } else if (parameter->getPriorityType() ==
                                ConfigurationParameter::RecommendedPriority) {
        xmlNewProp(node, BAD_CAST "priorityType", BAD_CAST "recommended");
    } else if (parameter->getPriorityType() ==
                                ConfigurationParameter::OptionalPriority) {
        xmlNewProp(node, BAD_CAST "priorityType", BAD_CAST "optional");
    } else {
        xmlNewProp(node, BAD_CAST "priorityType", BAD_CAST "no");
    }

    xmlNewProp(node, BAD_CAST "information",
               BAD_CAST parameter->getInformation().c_str());

    return node;
}
