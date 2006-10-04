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
 * The type of both the normal value and the default value is the type of the
 * typename used for the template.
 *
 * This is an abstract class. In order to use a simple parameter, a subclass
 * using an specific type must be done. The subclass must define accept method,
 * so it can be used with visitors.
 *
 * A ConfigurationParameterSimple is invalid if it is required, it has no
 * default value an the value wasn't set.
 *
 * Due to the use of templates, everything is implemented in the header file. No
 * source file exists for this class.
 */
template<typename T>
class ConfigurationParameterSimple: public ConfigurationParameter {
public:

    /**
     * Destroys this ConfigurationParameterSimple.
     */
    virtual ~ConfigurationParameterSimple() {
    }

    /**
     * Returns True if this ConfigurationParameter is invalid, false otherwise.
     * This ConfigurationParameterSimple is invalid if the priority is
     * required, its value wasn't set yet and there is no default value.
     *
     * @return True if this ConfigurationParameterSimple is invalid, false
     *         otherwise.
     */
    virtual bool isInvalid() {
        if (getPriorityType() == RequiredPriority && !mValueSet &&
                !mDefaultValueSet) {
            return true;
        }

        return false;
    }

    /**
     * Returns the default value, if any.
     * If the default value wsan't set, the value returned isn't defined.
     *
     * @return The default value, if any.
     */
    const T& getDefaultValue() const {
        return mDefaultValue;
    }

    /**
     * Returns the value.
     * If the normal value isn't set, the default value, if it exists, is
     * returned. If the normal value nor the default value were set, the
     * value returned isn't defined.
     *
     * @return The value.
     */
    const T& getValue() const {
        return (!mValueSet && mDefaultValueSet)? mDefaultValue: mValue;
    }

    /**
     * Returns true if the value is equal to the default value, false otherwise.
     * If no default value was set, false is returned.
     *
     * @return True if the value is equal to the default value, false otherwise.
     */
    bool isDefaultValue() const {
        return mDefaultValueSet && getValue() == mDefaultValue;
    }

    /**
     * Returns true if the default value was set, false otherwise.
     *
     * @return True if the default value was set, false otherwise.
     */
    bool isDefaultValueSet() const {
        return mDefaultValueSet;
    }

    /**
     * Returns true if the value was set, false otherwise.
     *
     * @return True if the value was set, false otherwise.
     */
    bool isValueSet() const {
        return mValueSet;
    }

    /**
     * Sets the value.
     *
     * @param value The value.
     */
    void setValue(const T& value) {
        mValueSet = true;
        mValue = value;
    }

protected:

    /**
     * Creates a new ConfigurationParameterSimple.
     * This constructor doesn't set the default value.
     *
     * Protected to avoid classes other than derived to create
     * ConfigurationParameterSimple objects.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     */
    ConfigurationParameterSimple(const std::string& id,
                                 const std::string& name,
                                 PriorityType priorityType,
                                 const std::string& information):
            ConfigurationParameter(id, name, priorityType, information) {
        mDefaultValueSet = false;
        mValueSet = false;
    }

    /**
     * Creates a new ConfigurationParameterSimple.
     * This constructor sets the default value.
     *
     * Protected to avoid classes other than derived to create
     * ConfigurationParameterSimple objects.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param defaultValue The default value.
     */
    ConfigurationParameterSimple(const std::string& id,
                                 const std::string& name,
                                 PriorityType priorityType,
                                 const std::string& information,
                                 const T& defaultValue):
            ConfigurationParameter(id, name, priorityType, information) {
        mDefaultValue = defaultValue;
        mDefaultValueSet = true;
        mValueSet = false;
    }


private:

    /**
     * The default value of this parameter.
     * It's optional.
     */
    T mDefaultValue;

    /**
     * The value of this parameter.
     */
    T mValue;

    /**
     * If the default value was set.
     */
    bool mDefaultValueSet;

    /**
     * If the normal value was set.
     */
    bool mValueSet;



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
