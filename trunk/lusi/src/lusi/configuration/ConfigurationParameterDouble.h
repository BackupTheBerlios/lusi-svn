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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERDOUBLE_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERDOUBLE_H

#include <lusi/configuration/ConfigurationParameterSimple.h>
#include <lusi/configuration/ConfigurationParameterVisitor.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterDouble ConfigurationParameterDouble.h \
 * lusi/configuration/ConfigurationParameterDouble.h
 *
 * A simple parameter of configuration using double values.
 * A default value can be specified when creating the double parameter, so it's
 * used if the normal value isn't set.
 * Both the normal value and the default value are doubles.
 */
class ConfigurationParameterDouble:
            public ConfigurationParameterSimple<double> {
public:

    /**
     * Creates a new ConfigurationParameterDouble.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     */
    ConfigurationParameterDouble(const std::string& id);

    /**
     * Creates a new ConfigurationParameterDouble.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param defaultValue The default value.
     */
    ConfigurationParameterDouble(const std::string& id, double defaultValue);

    /**
     * Creates a new ConfigurationParameterDouble.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     */
    ConfigurationParameterDouble(const std::string& id,
                                 const std::string& name,
                                 PriorityType priorityType,
                                 const std::string& information);

    /**
     * Creates a new ConfigurationParameterDouble.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param defaultValue The default value.
     */
    ConfigurationParameterDouble(const std::string& id,
                                 const std::string& name,
                                 PriorityType priorityType,
                                 const std::string& information,
                                 double defaultValue);

    /**
     * Destroys this ConfigurationParameterDouble.
     */
    virtual ~ConfigurationParameterDouble();

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
    ConfigurationParameterDouble(
            const ConfigurationParameterDouble& configurationParameterDouble);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterDouble& operator=(
            const ConfigurationParameterDouble& configurationParameterDouble);

};

}
}

#endif
