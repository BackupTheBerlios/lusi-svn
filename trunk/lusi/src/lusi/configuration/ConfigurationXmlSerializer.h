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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONXMLSERIALIZER_H
#define LUSI_CONFIGURATION_CONFIGURATIONXMLSERIALIZER_H

#include <libxml/tree.h>

#include <lusi/configuration/ConfigurationParameterVisitor.h>

namespace lusi {
namespace configuration {
class ConfigurationParameter;
}
}

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationXmlSerializer ConfigurationParameterSerializer.h \
 * lusi/configuration/ConfigurationParameterSerializer.h
 *
 * Serializes a Configuration in XML.
 * Even the simplest configuration has, at least, a map as its base element. The
 * serialization begins in that base map, and all the children of the map are
 * serialized recursively (except those marked as not serializable). A Visitor
 * design pattern is used to traverse all the configuration.
 *
 * The method that must be used to make the serialization is
 * serialize(ConfigurationParameterMap*). All the other public methods called
 * visit must not be used, as they depend on the invocation of serialize. They
 * are public due to language restrictions.
 *
 * In order to do the serialization, it uses libxml-2.0. The serialized document
 * is a xmlDocPtr.
 */
class ConfigurationXmlSerializer: public ConfigurationParameterVisitor {
public:

    /**
     * Creates a new ConfigurationXmlSerializer.
     */
    ConfigurationXmlSerializer();

    /**
     * Destroys this ConfigurationXmlSerializer.
     */
    virtual ~ConfigurationXmlSerializer();

    /**
     * Adds the XML representation of the ConfigurationParameterBool as a child
     * of mNode.
     * The node includes the id, name, priority and information as attributes,
     * and the value and default value (if any) as text child elements with the
     * string representation of the bool ("true" or "false" in each case).
     *
     * @param parameter The ConfigurationParameterBool to serialize to XML.
     * @see newNode(ConfigurationParameter*, const char*)
     */
    virtual void visit(ConfigurationParameterBool* parameter);

    /**
     * Adds the XML representation of the ConfigurationParameterDouble as a
     * child of mNode.
     * The node includes the id, name, priority and information as attributes,
     * and the value and default value (if any) as text child elements with the
     * string representation of the double.
     *
     * @param parameter The ConfigurationParameterDouble to serialize to XML.
     * @see newNode(ConfigurationParameter*, const char*)
     */
    virtual void visit(ConfigurationParameterDouble* parameter);

    /**
     * Adds the XML representation of the ConfigurationParameterInt as a child
     * of mNode.
     * The node includes the id, name, priority and information as attributes,
     * and the value and default value (if any) as text child elements with the
     * string representation of the int.
     *
     * @param parameter The ConfigurationParameterInt to serialize to XML.
     * @see newNode(ConfigurationParameter*, const char*)
     */
    virtual void visit(ConfigurationParameterInt* parameter);

    /**
     * Adds the XML representation of the ConfigurationParameterLocalUrl as a
     * child of mNode.
     * The node includes the id, name, priority and information as attributes,
     * and the value and default value (if any) as text child elements with the
     * path of the url.
     *
     * @param parameter The ConfigurationParameterLocalUrl to serialize to XML.
     * @see newNode(ConfigurationParameter*, const char*)
     */
    virtual void visit(ConfigurationParameterLocalUrl* parameter);

    /**
     * Adds the XML representation of the ConfigurationParameterMap as a child
     * of mNode.
     * The node includes the id, name, priority and information as attributes,
     * and all the child parameters as child nodes (in the same order they have
     * in the parameter). The only exception are child parameter set as not
     * serializable, which aren't added as child nodes.
     *
     * @param parameter The ConfigurationParameterMap to serialize to XML.
     * @see newNode(ConfigurationParameter*, const char*)
     */
    virtual void visit(ConfigurationParameterMap* parameter);

    /**
     * Adds the XML representation of the ConfigurationParameterString as a
     * child of mNode.
     * The node includes the id, name, priority and information as attributes,
     * and the value and default value (if any) as text child elements with the
     * strings.
     *
     * @param parameter The ConfigurationParameterString to serialize to XML.
     * @see newNode(ConfigurationParameter*, const char*)
     */
    virtual void visit(ConfigurationParameterString* parameter);

    /**
     * Serializes a ConfigurationParameterMap to its XML representation.
     * The root node of the generated XML document is the XML representation of
     * the map. All the children of the map are serialized recursively.
     *
     * The returned xmlDocPtr must be freed.
     *
     * @param configurationParameterMap The ConfigurationParameterMap to
     *                                  serialize.
     * @return The XML representation of the ConfigurationParameterMap.
     */
    xmlDocPtr serialize(ConfigurationParameterMap* configurationParameterMap);

protected:

private:

    /**
     * Parent node of the node currently being visited.
     * If it is null, there's no parent node, so when a map is visited it will
     * be set as parent.
     */
    xmlNodePtr mNode;



    /**
     * Creates and initializes a new node with the data gathered from the
     * ConfigurationParameter.
     * The id, name, priority and information of the parameter are set as
     * attributes of the node. The priority is set to "required", "recommended"
     * or "optional" depending on the type of the priority.
     *
     * @param parameter The ConfigurationParameter to use.
     * @param name The name of the node to create.
     */
    xmlNodePtr newNode(ConfigurationParameter* parameter, const char* name);

    /**
     * Copy constructor disabled.
     */
    ConfigurationXmlSerializer(
            const ConfigurationXmlSerializer& configurationXmlSerializer);

    /**
     * Assignment disabled.
     */
    ConfigurationXmlSerializer& operator=(
            const ConfigurationXmlSerializer& configurationXmlSerializer);

};

}
}

#endif
