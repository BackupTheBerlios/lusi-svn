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

#ifndef LUSI_CONFIGURATION_INVALIDCONFIGURATIONEXCEPTION_H
#define LUSI_CONFIGURATION_INVALIDCONFIGURATIONEXCEPTION_H

#include <stdexcept>
#include <string>

#include <lusi/configuration/ConfigurationParameterMap.h>

namespace lusi {
namespace util {
template<typename T>
class SmartPtr;
}
}

namespace lusi {
namespace configuration {

/**
 * @class InvalidConfigurationException InvalidConfigurationException.h
 * lusi/configuration/InvalidConfigurationException.h
 *
 * Exception for invalid configurations.
 * This exception can be used to signal incomplete configuration parameters,
 * values not allowed... The involved configuration parameters can be got in a
 * ConfigurationParameterMap through getConfigurationParameterMap().
 *
 * The Map contains only the parameters related to the exception. If the problem
 * with the configuration signaled by this exception happened in a
 * ConfigurationParameterMap with parameters involved and other not related,
 * the whole ConfigurationParameterMap can't be added to the exception. A new
 * one containing only the wrong parameters must be created.
 *
 * The error message returned by what() will be the error message specified
 * when creating the exception.
 */
class InvalidConfigurationException: public std::exception {
public:

    /**
     * Creates a new InvalidConfigurationException.
     *
     * @param errorMessage The error message of the exception.
     * @param configurationParameterMap The map containing the parameters
     *                                  related to the exception.
     */
    InvalidConfigurationException(const std::string& errorMessage,
            lusi::util::SmartPtr<ConfigurationParameterMap>
                    configurationParameterMap);

    /**
     * Destroys this InvalidConfigurationException.
     */
    virtual ~InvalidConfigurationException() throw() ;

    /**
     * Returns the error message.
     *
     * @return The error message.
     */
    virtual const char* what() const throw() {
        return mErrorMessage.c_str();
    }

    /**
     * Returns the ConfigurationParameterMap containing the parameters related
     * to the exception.
     *
     * @return The ConfigurationParameterMap containing the parameters related
     *         to the exception.
     */
    lusi::util::SmartPtr<ConfigurationParameterMap>
    getConfigurationParameterMap() const throw() {
        return mConfigurationParameterMap;
    }

private:

    /**
     * Error message for the exception.
     */
    std::string mErrorMessage;

    /**
     * The ConfigurationParameterMap containing the parameters related to the
     * exception.
     */
    lusi::util::SmartPtr<ConfigurationParameterMap> mConfigurationParameterMap;

};

}
}

#endif
