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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERTESTIMPLEMENTATION_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERTESTIMPLEMENTATION_H

#include <lusi/configuration/ConfigurationParameter.h>

namespace lusi {
namespace configuration {

/**
 * Implementation of ConfigurationParameter for testing purposes.
 * This class helps testing ConfigurationParameter class non-abstract methods.
 */
class ConfigurationParameterTestImplementation: public ConfigurationParameter {
public:

    /**
     * Creates a new ConfigurationParameterTestImplementation.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this parameter.
     */
    ConfigurationParameterTestImplementation(const std::string& id,
                                             const std::string& name,
                                             PriorityType priorityType,
                                             const std::string& information);

    /**
     * Destroys this ConfigurationParameterTestImplementation.
     */
    virtual ~ConfigurationParameterTestImplementation();

    /**
     * Returns mInvalid.
     *
     * @return The value of mINvalid.
     */
    virtual bool isInvalid();

    /**
     * Does nothing.
     *
     * @param visitor Not used.
     */
    virtual void accept(ConfigurationParameterVisitor* visitor);

    /**
     * Sets the value to return in isInvalid()
     *
     * @param invalid The value to set.
     */
    void setInvalid(bool invald);

private:

    /**
     * The value to return in isInvalid() method.
     */
    bool mInvalid;

};

}
}

#endif
