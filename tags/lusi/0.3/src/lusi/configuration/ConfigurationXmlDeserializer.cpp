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

#include "ConfigurationXmlDeserializer.h"
#include "ConfigurationParameterBool.h"
#include "ConfigurationParameterDouble.h"
#include "ConfigurationParameterInt.h"
#include "ConfigurationParameterLocalUrl.h"
#include "ConfigurationParameterMap.h"
#include "ConfigurationParameterString.h"

using std::istringstream;
using std::string;

using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::configuration;

/**
 * Private function to get a string from an xmlChar* and free the xmlChar*.
 * Only xmlChar* which can be safely casted to char* can be used (that is,
 * only pure ASCII xmlChar*).
 *
 * @param xmlCharString The xmlChar* to use.
 * @return The string representation of the xmlChar*.
 */
string getStringAndFreeXmlChar(xmlChar* xmlCharString) {
    string value((const char*)xmlCharString);
    xmlFree(xmlCharString);

    return value;
}

/**
 * Private class to get all the attributes of a ConfigurationParameter from an
 * XML node.
 */
class ConfigurationParameterData {
public:

    /**
     * Creates a new ConfigurationParameterData from an xmlNodePtr.
     * All the attributes are initialized from the attributes in the node.
     * If name, priority and information doesn't exist, they are set to "",
     * NoPriority and "" respectively.
     *
     * @param node The xmlNodePtr to get the attributes from.
     */
    ConfigurationParameterData(xmlNodePtr node);

    /**
     * The id of the parameter.
     */
    std::string id;

    /**
     * The name of the parameter.
     */
    std::string name;

    /**
     * The type of the priority of the parameter.
     */
    ConfigurationParameter::PriorityType priorityType;

    /**
     * The information of the parameter.
     */
    std::string information;

};

ConfigurationParameterData::ConfigurationParameterData(const xmlNodePtr node) {
    id = getStringAndFreeXmlChar(xmlGetProp(node, BAD_CAST "id"));

    xmlChar* nameChar = xmlGetProp(node, BAD_CAST "name");

    //If there isn't name attribute, the saved parameter was created with brief
    //constructor, so name, priority and information weren't serialized
    if (!nameChar) {
        name = "";
        priorityType = ConfigurationParameter::NoPriority;
        information = "";
        return;
    }

    name = getStringAndFreeXmlChar(nameChar);

    string priorityTypeString =
            getStringAndFreeXmlChar(xmlGetProp(node, BAD_CAST "priorityType"));

    if (priorityTypeString == "required") {
        priorityType = ConfigurationParameter::RequiredPriority;
    } else if (priorityTypeString == "recommended") {
        priorityType = ConfigurationParameter::RecommendedPriority;
    } else if (priorityTypeString == "optional") {
        priorityType = ConfigurationParameter::OptionalPriority;
    } else if (priorityTypeString == "no") {
        priorityType = ConfigurationParameter::NoPriority;
    }

    information =
            getStringAndFreeXmlChar(xmlGetProp(node, BAD_CAST "information"));
}

//public:

ConfigurationXmlDeserializer::ConfigurationXmlDeserializer() {
}

ConfigurationXmlDeserializer::~ConfigurationXmlDeserializer() {
}

ConfigurationParameterMap* ConfigurationXmlDeserializer::deserialize(
                                                        xmlDocPtr document) {
    return deserializeConfigurationParameterMap(xmlDocGetRootElement(document));
}

//private:

ConfigurationParameterBool*
ConfigurationXmlDeserializer::deserializeConfigurationParameterBool(
                                                        const xmlNodePtr node) {
    ConfigurationParameterData parameterData(node);

    bool defaultValueSet = false;
    bool valueSet = false;
    bool defaultValue = false;
    bool value = false;

    xmlNodePtr nodeChildren = node->children;
    while (nodeChildren) {
        if (!xmlStrcmp(nodeChildren->name, BAD_CAST "defaultValue")) {
            defaultValueSet = true;
            string defaultValueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            defaultValue = (defaultValueString == "true")? true: false;
        } else if (!xmlStrcmp(nodeChildren->name, BAD_CAST "value")) {
            valueSet = true;
            string valueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            value = (valueString == "true")? true: false;
        }
        nodeChildren = nodeChildren->next;
    }

    ConfigurationParameterBool* parameter = 0;
    if (defaultValueSet) {
        parameter = new ConfigurationParameterBool(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information, defaultValue);
    } else {
        parameter = new ConfigurationParameterBool(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information);
    }

    if (valueSet) {
        parameter->setValue(value);
    }

    return parameter;
}

ConfigurationParameterDouble*
ConfigurationXmlDeserializer::deserializeConfigurationParameterDouble(
                                                        const xmlNodePtr node) {
    ConfigurationParameterData parameterData(node);

    bool defaultValueSet = false;
    bool valueSet = false;
    double defaultValue = 0;
    double value = 0;

    xmlNodePtr nodeChildren = node->children;
    while (nodeChildren) {
        if (!xmlStrcmp(nodeChildren->name, BAD_CAST "defaultValue")) {
            defaultValueSet = true;
            string defaultValueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            istringstream toDouble(defaultValueString);
            toDouble >> defaultValue;
        } else if (!xmlStrcmp(nodeChildren->name, BAD_CAST "value")) {
            valueSet = true;
            string valueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            istringstream toDouble(valueString);
            toDouble >> value;
        }
        nodeChildren = nodeChildren->next;
    }

    ConfigurationParameterDouble* parameter = 0;
    if (defaultValueSet) {
        parameter = new ConfigurationParameterDouble(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information, defaultValue);
    } else {
        parameter = new ConfigurationParameterDouble(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information);
    }

    if (valueSet) {
        parameter->setValue(value);
    }

    return parameter;
}

ConfigurationParameterInt*
ConfigurationXmlDeserializer::deserializeConfigurationParameterInt(
                                                        const xmlNodePtr node) {
    ConfigurationParameterData parameterData(node);

    bool defaultValueSet = false;
    bool valueSet = false;
    int defaultValue = 0;
    int value = 0;

    xmlNodePtr nodeChildren = node->children;
    while (nodeChildren) {
        if (!xmlStrcmp(nodeChildren->name, BAD_CAST "defaultValue")) {
            defaultValueSet = true;
            string defaultValueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            istringstream toInt(defaultValueString);
            toInt >> defaultValue;
        } else if (!xmlStrcmp(nodeChildren->name, BAD_CAST "value")) {
            valueSet = true;
            string valueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            istringstream toInt(valueString);
            toInt >> value;
        }
        nodeChildren = nodeChildren->next;
    }

    ConfigurationParameterInt* parameter = 0;
    if (defaultValueSet) {
        parameter = new ConfigurationParameterInt(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information, defaultValue);
    } else {
        parameter = new ConfigurationParameterInt(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information);
    }

    if (valueSet) {
        parameter->setValue(value);
    }

    return parameter;
}

ConfigurationParameterLocalUrl*
ConfigurationXmlDeserializer::deserializeConfigurationParameterLocalUrl(
                                                        const xmlNodePtr node) {
    ConfigurationParameterData parameterData(node);

    bool defaultValueSet = false;
    bool valueSet = false;
    LocalUrl defaultValue;
    LocalUrl value;

    xmlNodePtr nodeChildren = node->children;
    while (nodeChildren) {
        if (!xmlStrcmp(nodeChildren->name, BAD_CAST "defaultValue")) {
            defaultValueSet = true;
            string defaultValueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            defaultValue = LocalUrl(defaultValueString);
        } else if (!xmlStrcmp(nodeChildren->name, BAD_CAST "value")) {
            valueSet = true;
            string valueString =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));

            value = LocalUrl(valueString);
        }
        nodeChildren = nodeChildren->next;
    }

    ConfigurationParameterLocalUrl* parameter = 0;
    if (defaultValueSet) {
        parameter = new ConfigurationParameterLocalUrl(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information, defaultValue);
    } else {
        parameter = new ConfigurationParameterLocalUrl(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information);
    }

    if (valueSet) {
        parameter->setValue(value);
    }

    return parameter;
}

ConfigurationParameterMap*
ConfigurationXmlDeserializer::deserializeConfigurationParameterMap(
                                                        const xmlNodePtr node) {
    ConfigurationParameterData parameterData(node);
    ConfigurationParameterMap* parameter = new ConfigurationParameterMap(
            parameterData.id, parameterData.name, parameterData.priorityType,
            parameterData.information);

    xmlNodePtr nodeChildren = node->children;
    while (nodeChildren) {
        string nodeName((const char*)nodeChildren->name);

        ConfigurationParameter* parameterToAdd = 0;
        if (nodeName == "bool") {
            parameterToAdd =
                deserializeConfigurationParameterBool(nodeChildren);
        } else if (nodeName == "double") {
            parameterToAdd =
                deserializeConfigurationParameterDouble(nodeChildren);
        } else if (nodeName == "int") {
            parameterToAdd =
                deserializeConfigurationParameterInt(nodeChildren);
        } else if (nodeName == "localUrl") {
            parameterToAdd =
                deserializeConfigurationParameterLocalUrl(nodeChildren);
        } else if (nodeName == "map") {
            parameterToAdd =
                deserializeConfigurationParameterMap(nodeChildren);
        } else if (nodeName == "string") {
            parameterToAdd =
                deserializeConfigurationParameterString(nodeChildren);
        }

        if (parameterToAdd) {
            parameter->add(SmartPtr<ConfigurationParameter>(parameterToAdd));
        }

        nodeChildren = nodeChildren->next;
    }

    return parameter;
}

ConfigurationParameterString*
ConfigurationXmlDeserializer::deserializeConfigurationParameterString(
                                                        const xmlNodePtr node) {
    ConfigurationParameterData parameterData(node);

    bool defaultValueSet = false;
    bool valueSet = false;
    string defaultValue;
    string value;

    xmlNodePtr nodeChildren = node->children;
    while (nodeChildren) {
        if (!xmlStrcmp(nodeChildren->name, BAD_CAST "defaultValue")) {
            defaultValueSet = true;

            defaultValue =
                    getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));
        } else if (!xmlStrcmp(nodeChildren->name, BAD_CAST "value")) {
            valueSet = true;

            value = getStringAndFreeXmlChar(xmlNodeGetContent(nodeChildren));
        }
        nodeChildren = nodeChildren->next;
    }

    ConfigurationParameterString* parameter = 0;
    if (defaultValueSet) {
        parameter = new ConfigurationParameterString(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information, defaultValue);
    } else {
        parameter = new ConfigurationParameterString(parameterData.id,
                            parameterData.name, parameterData.priorityType,
                            parameterData.information);
    }

    if (valueSet) {
        parameter->setValue(value);
    }

    return parameter;
}
