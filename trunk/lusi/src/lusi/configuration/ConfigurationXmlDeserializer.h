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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONXMLDESERIALIZER_H
#define LUSI_CONFIGURATION_CONFIGURATIONXMLDESERIALIZER_H

#include <libxml/tree.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterBool;
class ConfigurationParameterDouble;
class ConfigurationParameterInt;
class ConfigurationParameterLocalUrl;
class ConfigurationParameterMap;
class ConfigurationParameterString;
}
}

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationXmlDeserializer ConfigurationParameterDeserializer.h \
 * lusi/configuration/ConfigurationParameterDeserializer.h
 *
 * Deserializes a Configuration from XML.
 * The XML representation to deserialize the configuration from has, at least,
 * a node which represents a map. The deserialization begins in that node, and
 * all the children of the node are deserialized recursively.
 *
 * The method that must be used to make the deserialization is
 * deserialize(xmlDocPtr). The XML document isn't checked to know whether it is
 * valid or not. Only documents created (also if they were later persisted) by
 * ConfigurationXmlSerializer should be used.
 *
 * In order to do the deserialization, it uses libxml-2.0. The document to
 * deserialize  is a xmlDocPtr.
 */
class ConfigurationXmlDeserializer {
public:

    /**
     * Creates a new ConfigurationXmlDeserializer.
     */
    ConfigurationXmlDeserializer();

    /**
     * Destroys this ConfigurationXmlDeserializer.
     */
    virtual ~ConfigurationXmlDeserializer();

    /**
     * Deserializes a ConfigurationParameterMap from its XML representation.
     * The root node of the XML document is the XML representation of the map.
     * All the children of the map are deserialized recursively.
     * The returned ConfigurationParameterMap must be deleted when it is no
     * longer needed.
     *
     * Only documents created (also if they were later persisted) by
     * ConfigurationXmlSerializer should be deserialized.
     *
     * @param document The XML document to deserialize the map from.
     * @return The deserialized ConfigurationParameterMap.
     */
    ConfigurationParameterMap* deserialize(xmlDocPtr document);

protected:

private:

    /**
     * Deserializes a ConfigurationParameterBool from its XML representation.
     *
     * @param node The XML node to deserialize the bool from.
     * @return The deserialized ConfigurationParameterBool.
     */
    ConfigurationParameterBool* deserializeConfigurationParameterBool(
                                                        const xmlNodePtr node);

    /**
     * Deserializes a ConfigurationParameterDouble from its XML representation.
     *
     * @param node The XML node to deserialize the double from.
     * @return The deserialized ConfigurationParameterDouble.
     */
    ConfigurationParameterDouble* deserializeConfigurationParameterDouble(
                                                        const xmlNodePtr node);

    /**
     * Deserializes a ConfigurationParameterInt from its XML representation.
     *
     * @param node The XML node to deserialize the int from.
     * @return The deserialized ConfigurationParameterInt.
     */
    ConfigurationParameterInt* deserializeConfigurationParameterInt(
                                                        const xmlNodePtr node);

    /**
     * Deserializes a ConfigurationParameterLocalUrl from its XML
     * representation.
     *
     * @param node The XML node to deserialize the LocalUrl from.
     * @return The deserialized ConfigurationParameterLocalUrl.
     */
    ConfigurationParameterLocalUrl* deserializeConfigurationParameterLocalUrl(
                                                        const xmlNodePtr node);

    /**
     * Deserializes a ConfigurationParameterMap from its XML representation.
     * All the children are also deserialized recursively and added to the map.
     *
     * @param node The XML node to deserialize the map from.
     * @return The deserialized ConfigurationParameterMap.
     */
    ConfigurationParameterMap* deserializeConfigurationParameterMap(
                                                        const xmlNodePtr node);

    /**
     * Deserializes a ConfigurationParameterString from its XML representation.
     *
     * @param node The XML node to deserialize the string from.
     * @return The deserialized ConfigurationParameterString.
     */
    ConfigurationParameterString* deserializeConfigurationParameterString(
                                                        const xmlNodePtr node);

    /**
     * Copy constructor disabled.
     */
    ConfigurationXmlDeserializer(
            const ConfigurationXmlDeserializer& configurationXmlDeserializer);

    /**
     * Assignment disabled.
     */
    ConfigurationXmlDeserializer& operator=(
            const ConfigurationXmlDeserializer& configurationXmlDeserializer);

};

}
}

#endif
