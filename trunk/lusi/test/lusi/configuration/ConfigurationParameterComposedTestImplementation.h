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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERCOMPOSEDTESTIMPLEMENTATION_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERCOMPOSEDTESTIMPLEMENTATION_H

#include <lusi/configuration/ConfigurationParameterComposed.h>

namespace lusi {
namespace configuration {

/**
 * Implementation of ConfigurationParameterComposed for testing purposes.
 * This class helps testing ConfigurationParameterComposed class non-abstract
 * methods.
 */
class ConfigurationParameterComposedTestImplementation:
            public ConfigurationParameterComposed {
public:

    /**
     * Creates a new ConfigurationParameterComposedTestImplementation.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this parameter.
     */
    ConfigurationParameterComposedTestImplementation(const std::string& id,
                                                const std::string& name,
                                                PriorityType priorityType,
                                                const std::string& information);

    /**
     * Destroys this ConfigurationParameterComposedTestImplementation.
     */
    virtual ~ConfigurationParameterComposedTestImplementation();

    /**
     * Returns false.
     *
     * @return False.
     */
    virtual bool isInvalid();

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
