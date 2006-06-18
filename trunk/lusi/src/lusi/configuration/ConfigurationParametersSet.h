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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSSET_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSSET_H

#include <string>
#include <vector>

#include <lusi/configuration/ConfigurationParameterPriority.h>

namespace lusi {
namespace configuration {
class ConfigurationParameter;
}
}

namespace lusi {
namespace configuration {

/**
 * @todo Documentation
 */
class ConfigurationParametersSet {
public:

    ConfigurationParametersSet();

    virtual ~ConfigurationParametersSet();

    std::vector<ConfigurationParameter*> getAllParameters();

    void getParameters(ConfigurationParameterPriority prority);

    ConfigurationParameter* getParameter(std::string parameterID);

    void setParameter(ConfigurationParameter* parameter);

    void merge(ConfigurationParametersSet configurationParametersSet,
                bool override = false);

protected:

private:

};

}
}

#endif
