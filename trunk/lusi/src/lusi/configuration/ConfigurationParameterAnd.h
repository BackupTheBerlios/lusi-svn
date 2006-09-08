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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERAND_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERAND_H

#include <lusi/configuration/ConfigurationParameterComposed.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterAnd ConfigurationParameterAnd.h \
 * lusi/configuration/ConfigurationParameterAnd.h
 *
 * A ConfigurationParameterComposed with an "and" relation between its
 * contained ConfigurationParameter.
 * To be valid, all the contained parameters must be valid. If any of them is
 * invalid, the ConfigurationParameterAnd is invalid.
 */
class ConfigurationParameterAnd: public ConfigurationParameterComposed {
public:

    /**
     * Creates a new ConfigurationParameterAnd.
     * The information is optional, and empty by default.
     *
     * @param id The id.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter,
     *                    empty by default.
     */
    ConfigurationParameterAnd(const std::string& id,
                              PriorityType priorityType,
                              const std::string& information = "");

    /**
     * Destroys this ConfigurationParameterAnd.
     */
    virtual ~ConfigurationParameterAnd();

    /**
     * Returns true if any of the contained parameters is invalid, false
     * otherwise.
     * If there are no contained parameters, it's also valid.
     *
     * @return True if any of the contained parameters is invalid, false
     *         otherwise.
     */
    virtual bool isInvalid();

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterAnd(
            const ConfigurationParameterAnd& configurationParameterAnd);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterAnd& operator=(
            const ConfigurationParameterAnd& configurationParameterAnd);

};

}
}

#endif
