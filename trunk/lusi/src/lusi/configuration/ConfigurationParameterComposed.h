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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERCOMPOSED_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERCOMPOSED_H

#include <vector>

#include <lusi/configuration/ConfigurationParameter.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterComposed ConfigurationParameterComposed.h \
 * lusi/configuration/ConfigurationParameterComposed.h
 *
 * Base class for composed configuration parameters.
 * Composed parameters represent a group of other parameters, being them simple
 * or composed.
 * This base class provides the common behaviour for composed parameters. This
 * behaviour is simply adding new parameters and getting a vector with all the
 * parameters added already.
 *
 * Once a ConfigurationParameter is added, ConfigurationParameterComposed gets
 * control over lifespan and destruction of the ConfigurationParameter.
 * ConfigurationParameter are destroyed when this parameter is destroyed.
 * ConfigurationParameters added to this parameter must not be deleted from
 * outside.
 */
class ConfigurationParameterComposed: public ConfigurationParameter {
public:

    /**
     * Destroys this ConfigurationParameterComposed.
     * It also destroys all the contained ConfigurationParameters.
     */
    virtual ~ConfigurationParameterComposed();

    /**
     * Adds a new ConfigurationParameter to this ConfigurationParameterComposed.
     * If the ConfigurationParameter added was already added, it's added again.
     *
     * @param configurationParameter The ConfigurationParameter to add.
     */
    void addConfigurationParameter(
                ConfigurationParameter* configurationParameter) {
        mConfigurationParameters.push_back(configurationParameter);
    }

    /**
     * Returns a vector containing all the ConfigurationParameters added.
     * This is an accessor method.
     *
     * @return A vector containing all the ConfigurationParameters added.
     */
    std::vector<ConfigurationParameter*> getConfigurationParameters() const {
        return mConfigurationParameters;
    }

protected:

    /**
     * Creates a new ConfigurationParameterComposed.
     * The information is optional, and empty by default.
     *
     * Protected to avoid classes other than derived to create
     * ConfigurationParameterComposed objects.
     *
     * @param id The id.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter,
     *                    empty by default.
     */
    ConfigurationParameterComposed(const std::string& id,
                                   PriorityType priorityType,
                                   const std::string& information = "");

private:

    /**
     * The vector with all the configuration parameters in this
     * ConfigurationParameterComposed.
     */
    std::vector<ConfigurationParameter*> mConfigurationParameters;

};

}
}

#endif
