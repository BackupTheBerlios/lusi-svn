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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETEROR_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETEROR_H

#include <lusi/configuration/ConfigurationParameterComposed.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterOr ConfigurationParameterOr.h \
 * lusi/configuration/ConfigurationParameterOr.h
 *
 * A ConfigurationParameterComposed with an "or" relation between its
 * contained ConfigurationParameter.
 * To be valid, any of the contained parameters must be valid. If all of them
 * are invalid, the ConfigurationParameterAnd is invalid.
 */
class ConfigurationParameterOr: public ConfigurationParameterComposed {
public:

    /**
     * Creates a new ConfigurationParameterOr.
     * The information is optional, and empty by default.
     *
     * @param id The id.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameterOr.
     */
    ConfigurationParameterOr(const std::string& id,
                             PriorityType priorityType,
                             const std::string& information = 0);

    /**
     * Destroys this ConfigurationParameterOr.
     */
    virtual ~ConfigurationParameterOr();

    /**
     * Returns true if all the contained parameters are invalid, false
     * otherwise.
     * If there are no contained parameters, it's also valid.
     *
     * @return True if all the contained parameters are invalid, false
     *         otherwise.
     */
    virtual bool isInvalid();

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterOr(
            const ConfigurationParameterOr& configurationParameterOr);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterOr& operator=(
            const ConfigurationParameterOr& configurationParameterOr);

};

}
}

#endif
