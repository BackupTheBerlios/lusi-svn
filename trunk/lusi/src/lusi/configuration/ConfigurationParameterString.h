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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSTRING_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSTRING_H

#include <lusi/configuration/ConfigurationParameterSimple.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterString ConfigurationParameterString.h \
 * lusi/configuration/ConfigurationParameterString.h
 *
 * A simple parameter of configuration using string values.
 * A default value can be specified when creating the string parameter, so it's
 * used if the normal value isn't set.
 * Both the normal value and the default value are strings.
 *
 * The string can have an specific type from the enumeration StringType. It
 * makes possible to difference two string values with different meaning, for
 * example, for passwords.
 */
class ConfigurationParameterString:
            public ConfigurationParameterSimple<std::string> {
public:

    /**
     * The type of the string.
     */
    enum StringType {
        NormalType,
        PasswordType
    };

    /**
     * Creates a new ConfigurationParameterString.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     * @param stringType The type of the string, normal by default.
     */
    ConfigurationParameterString(const std::string& id,
                                 StringType stringType = NormalType);

    /**
     * Creates a new ConfigurationParameterString.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param defaultValue The default value.
     * @param stringType The type of the string, normal by default.
     */
    ConfigurationParameterString(const std::string& id,
                                 const std::string& defaultValue,
                                 StringType stringType = NormalType);

    /**
     * Creates a new ConfigurationParameterString.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param stringType The type of the string, normal by default.
     */
    ConfigurationParameterString(const std::string& id,
                                 const std::string& name,
                                 PriorityType priorityType,
                                 const std::string& information,
                                 StringType stringType = NormalType);

    /**
     * Creates a new ConfigurationParameterString.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param defaultValue The default value.
     * @param stringType The type of the string, normal by default.
     */
    ConfigurationParameterString(const std::string& id,
                                 const std::string& name,
                                 PriorityType priorityType,
                                 const std::string& information,
                                 const std::string& defaultValue,
                                 StringType stringType = NormalType);

    /**
     * Destroys this ConfigurationParameterString.
     */
    virtual ~ConfigurationParameterString();

    /**
     * Accepts a visitor.
     *
     * @param visitor The ConfigurationParameterVisitor to accept.
     */
    virtual void accept(ConfigurationParameterVisitor* visitor);

    /**
     * Returns the type of the string.
     *
     * @return The type of the string.
     */
    StringType getStringType() const {
        return mStringType;
    }

protected:

private:

    /**
     * The type of the string.
     */
    StringType mStringType;


    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterString(
            const ConfigurationParameterString& configurationParameterString);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterString& operator=(
            const ConfigurationParameterString& configurationParameterString);

};

}
}

#endif
