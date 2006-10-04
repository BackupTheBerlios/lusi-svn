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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERBOOL_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERBOOL_H

#include <lusi/configuration/ConfigurationParameterSimple.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterBool ConfigurationParameterBool.h \
 * lusi/configuration/ConfigurationParameterBool.h
 *
 * A simple parameter of configuration using boolean values.
 * A default value can be specified when creating the boolean parameter, so it's
 * used if the normal value isn't set.
 * Both the normal value and the default value are booleans.
 */
class ConfigurationParameterBool: public ConfigurationParameterSimple<bool> {
public:

    /**
     * Creates a new ConfigurationParameterBool.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     */
    ConfigurationParameterBool(const std::string& id,
                               const std::string& name,
                               PriorityType priorityType,
                               const std::string& information);

    /**
     * Creates a new ConfigurationParameterBool.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param defaultValue The default value.
     */
    ConfigurationParameterBool(const std::string& id,
                               const std::string& name,
                               PriorityType priorityType,
                               const std::string& information,
                               bool defaultValue);

    /**
     * Destroys this ConfigurationParameterBool.
     */
    virtual ~ConfigurationParameterBool();

    /**
     * Accepts a visitor.
     *
     * @param visitor The ConfigurationParameterVisitor to accept.
     */
    virtual void accept(ConfigurationParameterVisitor* visitor);

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterBool(
            const ConfigurationParameterBool& configurationParameterBool);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterBool& operator=(
            const ConfigurationParameterBool& configurationParameterBool);

};

}
}

#endif
