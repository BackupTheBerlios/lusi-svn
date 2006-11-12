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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLETESTIMPLEMENTATION_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLETESTIMPLEMENTATION_H

#include <lusi/configuration/ConfigurationParameterSimple.h>

namespace lusi {
namespace configuration {

/**
 * Implementation of ConfigurationParameterSimple for testing purposes.
 * This class helps testing ConfigurationParameterSimple class non-abstract
 * methods.
 * Uses std::string as the type of the template.
 */
class ConfigurationParameterSimpleTestImplementation:
            public ConfigurationParameterSimple<std::string> {
public:

    /**
     * Creates a new ConfigurationParameterSimpleTestImplementation.
     *
     * @param id The id.
     */
    ConfigurationParameterSimpleTestImplementation(const std::string& id);

    /**
     * Creates a new ConfigurationParameterSimpleTestImplementation.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param defaultValue The default value.
     */
    ConfigurationParameterSimpleTestImplementation(const std::string& id,
                                            const std::string& defaultValue);

    /**
     * Creates a new ConfigurationParameterSimpleTestImplementation.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this parameter.
     */
    ConfigurationParameterSimpleTestImplementation(const std::string& id,
                                                const std::string& name,
                                                PriorityType priorityType,
                                                const std::string& information);

    /**
     * Creates a new ConfigurationParameterSimpleTestImplementation.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this parameter.
     * @param defaultValue The default value.
     */
    ConfigurationParameterSimpleTestImplementation(const std::string& id,
                                            const std::string& name,
                                            PriorityType priorityType,
                                            const std::string& information,
                                            const std::string& defaultValue);

    /**
     * Destroys this ConfigurationParameterSimpleTestImplementation.
     */
    virtual ~ConfigurationParameterSimpleTestImplementation();

    /**
     * Does nothing.
     *
     * @param visitor Not used.
     */
    virtual void accept(ConfigurationParameterVisitor* visitor);

};

}
}

#endif
