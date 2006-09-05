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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETER_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETER_H

#include <string>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameter ConfigurationParameter.h \
 * lusi/configuration/ConfigurationParameter.h
 *
 * A parameter of configuration.
 * Configuration is made of different parameters, and each parameter can be
 * simple or composed. Simple parameters represent a single value. Composed
 * parameters represent a group of other parameters, being them simple or
 * composed. The parameters in the groups can have an "and" or an "or" relation
 * between them, that is, that all the parameters or only one are needed.
 *
 * Each parameter also has a priority. This priority represents the degree of
 * importance of it: required, recommended or optional.
 *
 * Based on the type of the parameter and its priority, it can be checked if
 * this parameter is valid or invalid using isInvalid(). The meaning of an
 * invalid parameter depends on its concrete type.
 *
 * Each ConfigurationParameter has its own unique id, so concrete parameters can
 * be got easily in ConfigurationParameterSet if needed.
 *
 * Each parameter can also have some information explaining its purpose. It is
 * optional, although recommended.
 *
 * Configuration is used mainly in Tasks and TaskHelpers so different parameters
 * can be used in them. Of course, it can also be used anywhere else if needed.
 */
class ConfigurationParameter {
public:

    /**
     * The priority of a ConfigurationParameter.
     */
    enum PriorityType {
        RequiredPriority = 0,
        RecommendedPriority,
        OptionalPriority
    };

    /**
     * Destroys this ConfigurationParameter.
     */
    virtual ~ConfigurationParameter();

    /**
     * Returns True if this ConfigurationParameter is invalid, false otherwise.
     * A parameter is invalid if not all the mandatory parameters have been set.
     * The meaning of a mandatory parameter depends on the type of the
     * parameter.
     *
     * Must be implemented in derived classes.
     *
     * @return True if this ConfigurationParameter is invalid, false otherwise.
     */
    virtual bool isInvalid() = 0;

    /**
     * Returns the id of this ConfigurationParameter.
     *
     * @return The id of this ConfigurationParatemer.
     */
    const std::string& getId() const {
        return mId;
    }

    /**
     * Returns the information about this ConfigurationParameter.
     * The information is optional, so the returned string may be empty.
     *
     * @return The information about this ConfigurationParatemer.
     */
    const std::string& getInformation() const {
        return mInformation;
    }

    /**
     * Returns the type of the priority of this ConfigurationParameter.
     *
     * @return The type of the priority of this ConfigurationParameter.
     */
    PriorityType getPriorityType() const {
        return mPriorityType;
    }

protected:

    /**
     * Creates a new ConfigurationParameter.
     * The information is optional (if not set it will be empty).
     *
     * Protected to avoid classes other than derived to create
     * ConfigurationParameter objects.
     *
     * @param id The id.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     */
    ConfigurationParameter(const std::string& id,
                           PriorityType priorityType,
                           const std::string& information = "");

private:

    /**
     * The id of this ConfigurationParameter.
     */
    std::string mId;

    /**
     * The information about this ConfigurationParameter.
     * The information is optional.
     */
    std::string mInformation;

    /**
     * The type of the priority of this ConfigurationParameter.
     */
    PriorityType mPriorityType;



    /**
     * Copy constructor disabled.
     */
    ConfigurationParameter(
            const ConfigurationParameter& configurationParameter);

    /**
     * Assignment disabled.
     */
    ConfigurationParameter& operator=(
            const ConfigurationParameter& configurationParameter);

};

}
}

#endif
