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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERINT_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERINT_H

#include <lusi/configuration/ConfigurationParameterSimple.h>
#include <lusi/configuration/ConfigurationParameterVisitor.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterInt ConfigurationParameterInt.h \
 * lusi/configuration/ConfigurationParameterInt.h
 *
 * A simple parameter of configuration using integer values.
 * A default value can be specified when creating the int parameter, so it's
 * used if the normal value isn't set.
 * Both the normal value and the default value are ints.
 */
class ConfigurationParameterInt: public ConfigurationParameterSimple<int> {
public:

    /**
     * Creates a new ConfigurationParameterInt.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     */
    ConfigurationParameterInt(const std::string& id);

    /**
     * Creates a new ConfigurationParameterInt.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param defaultValue The default value.
     */
    ConfigurationParameterInt(const std::string& id, int defaultValue);

    /**
     * Creates a new ConfigurationParameterInt.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     */
    ConfigurationParameterInt(const std::string& id,
                              const std::string& name,
                              PriorityType priorityType,
                              const std::string& information);

    /**
     * Creates a new ConfigurationParameterInt.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param defaultValue The default value.
     */
    ConfigurationParameterInt(const std::string& id,
                              const std::string& name,
                              PriorityType priorityType,
                              const std::string& information,
                              int defaultValue);

    /**
     * Destroys this ConfigurationParameterInt.
     */
    virtual ~ConfigurationParameterInt();

    /**
     * Accepts a visitor.
     *
     * @param visitor The ConfigurationParameterVisitor to accept.
     */
    virtual void accept(ConfigurationParameterVisitor* visitor) {
        visitor->visit(this);
    }

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterInt(
            const ConfigurationParameterInt& configurationParameterInt);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterInt& operator=(
            const ConfigurationParameterInt& configurationParameterInt);

};

}
}

#endif
