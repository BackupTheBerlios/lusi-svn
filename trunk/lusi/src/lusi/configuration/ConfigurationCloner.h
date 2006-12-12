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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONCLONER_H
#define LUSI_CONFIGURATION_CONFIGURATIONCLONER_H

#include <lusi/configuration/ConfigurationParameterVisitor.h>

namespace lusi {
namespace configuration {
class ConfigurationParameter;
}
}

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationCloner ConfigurationCloner.h \
 * lusi/configuration/ConfigurationCloner.h
 *
 * Clones a Configuration.
 * Even the simplest configuration has, at least, a map as its base element. The
 * cloning begins in that base map, and all the children of the map are
 * cloned recursively. It makes a depth copy of the configuration. A Visitor
 * design pattern is used to traverse all the configuration.
 *
 * The method that must be used to make the depth copy is
 * clone(ConfigurationParameterMap*). All the other public methods called
 * visit must not be used, as they depend on the invocation to clone. They are
 * public due to language restrictions.
 *
 * Depth copy of configurations must be made using this class. Depth copy can't
 * be made through copy constructor nor assignment operators. Well, it can, but
 * it would add a lot of class type checks in ConfigurationParameterMap to
 * create the child elements, so a specific Visitor for this purpose was made.
 */
class ConfigurationCloner: public ConfigurationParameterVisitor {
public:

    /**
     * Creates a new ConfigurationCloner.
     */
    ConfigurationCloner();

    /**
     * Destroys this ConfigurationCloner.
     */
    virtual ~ConfigurationCloner();

    /**
     * Clones the ConfigurationParameterBool.
     * All the common attributes for all the parameters are set in the cloned
     * ConfigurationParameterBool. If the default value or the value are set,
     * they are also cloned.
     *
     * @param parameter The ConfigurationParameterBool to clone.
     */
    virtual void visit(ConfigurationParameterBool* parameter);

    /**
     * Clones the ConfigurationParameterDouble.
     * All the common attributes for all the parameters are set in the cloned
     * ConfigurationParameterDouble. If the default value or the value are set,
     * they are also cloned.
     *
     * @param parameter The ConfigurationParameterDouble to clone.
     */
    virtual void visit(ConfigurationParameterDouble* parameter);

    /**
     * Clones the ConfigurationParameterInt.
     * All the common attributes for all the parameters are set in the cloned
     * ConfigurationParameterInt. If the default value or the value are set,
     * they are also cloned.
     *
     * @param parameter The ConfigurationParameterInt to clone.
     */
    virtual void visit(ConfigurationParameterInt* parameter);

    /**
     * Clones the ConfigurationParameterLocalUrl.
     * All the common attributes for all the parameters are set in the cloned
     * ConfigurationParameterLocalUrl. If the default value or the value are
     * set, they are also cloned.
     *
     * @param parameter The ConfigurationParameterLocalUrl to clone.
     */
    virtual void visit(ConfigurationParameterLocalUrl* parameter);

    /**
     * Clones the ConfigurationParameterMap.
     * All the common attributes for all the parameters are set in the cloned
     * ConfigurationParameterMap. The child parameters are added to
     * mClonedConfiguration in each visit method.
     *
     * @param parameter The ConfigurationParameterMap to clone.
     */
    virtual void visit(ConfigurationParameterMap* parameter);

    /**
     * Clones the ConfigurationParameterString.
     * All the common attributes for all the parameters are set in the cloned
     * ConfigurationParameterString. If the default value or the value are set,
     * they are also cloned.
     *
     * @param parameter The ConfigurationParameterString to clone.
     */
    virtual void visit(ConfigurationParameterString* parameter);

    /**
     * Returns a depth copy of the ConfigurationParameterMap.
     * The returned ConfigurationParameterMap must be deleted when it is no
     * longer needed.
     *
     * @param configurationParameterMap The ConfigurationParameterMap to clone.
     * @return A depth copy of the ConfigurationParameterMap.
     */
    ConfigurationParameterMap* clone(
                        ConfigurationParameterMap* configurationParameterMap);

protected:

private:

    /**
     * Cloned ConfigurationParameterMap.
     * All the ConfigurationParameters are added to this
     * ConfigurationParameterMap.
     * When a ConfigurationParameterMap is visited and this is null, it is set
     * to the cloned ConfigurationParameterMap.
     */
    ConfigurationParameterMap* mClonedConfiguration;



    /**
     * Copy constructor disabled.
     */
    ConfigurationCloner(
            const ConfigurationCloner& configurationXmlSerializer);

    /**
     * Assignment disabled.
     */
    ConfigurationCloner& operator=(
            const ConfigurationCloner& configurationXmlSerializer);

};

}
}

#endif
