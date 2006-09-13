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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLE_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLE_H

#include <lusi/configuration/ConfigurationParameter.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterSimple ConfigurationParameterSimple.h \
 * lusi/configuration/ConfigurationParameterSimple.h
 *
 * A simple parameter of configuration.
 * Simple parameters represent a single value. It has no child parameters.
 * A default value can be specified when creating the simple parameter, so it's
 * used if the normal value isn't set.
 * Both the normal value and the default value are strings. A not set value is
 * an empty string.
 *
 * A ConfigurationParameterSimple is invalid if it has no default value and
 * the value isn't set.
 *
 * @TODO add boolean, int and double values
 */
class ConfigurationParameterSimple: public ConfigurationParameter {
public:

    /**
     * Creates a new ConfigurationParameterSimple.
     * The information and default value are optional, and empty by default.
     * The value is empty.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter,
     *                    empty by default.
     * @param defaultValue The default value, empty by default.
     */
    ConfigurationParameterSimple(const std::string& id,
                                 const std::string& name,
                                 PriorityType priorityType,
                                 const std::string& information = "",
                                 const std::string& defaultValue = "");

    /**
     * Destroys this ConfigurationParameterSimple.
     */
    virtual ~ConfigurationParameterSimple();

    /**
     * Returns True if this ConfigurationParameter is invalid, false otherwise.
     * This ConfigurationParameterSimple is invalid if the priority is
     * required, its value wasn't set yet and there is no default value.
     *
     * @return True if this ConfigurationParameterSimple is invalid, false
     *         otherwise.
     */
    virtual bool isInvalid();

    /**
     * Returns the value.
     * If the normal value isn't set, the default value, if it exists, is
     * returned.
     *
     * @return The value.
     */
    const std::string& getValue() const {
        return (mValue == "" && mDefaultValue != "")? mDefaultValue: mValue;
    }

    /**
     * Returns true if the value is equal to the default value, false otherwise.
     * If no default value was set (it's empty), false is returned.
     *
     * @return true if the value is equal to the default value, false otherwise.
     */
    bool isDefaultValue() const {
        return mDefaultValue != "" && mValue == mDefaultValue;
    }

    /**
     * Sets the value.
     *
     * @param value The value.
     */
    void setValue(const std::string& value) {
        mValue = value;
    }

protected:

private:

    /**
     * The default value of this parameter.
     * It's optional.
     */
    std::string mDefaultValue;

    /**
     * The value of this parameter.
     */
    std::string mValue;



    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterSimple(
            const ConfigurationParameterSimple& configurationParameterSimple);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterSimple& operator=(
            const ConfigurationParameterSimple& configurationParameterSimple);

};

}
}

#endif
