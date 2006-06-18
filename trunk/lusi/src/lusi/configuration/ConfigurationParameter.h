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

#include <lusi/configuration/ConfigurationParameterPriority.h>

namespace lusi {
namespace configuration {

/**
 * @todo Documentation
 */
class ConfigurationParameter {
public:

    virtual ~ConfigurationParameter();

    virtual ConfigurationParameter* checkInvalidStatus() = 0;

    std::string getId() {
        return mId;
    }

    std::string getInformation() {
        return mInformation;
    }

    ConfigurationParameterPriority getPriority();

protected:

    ConfigurationParameter(std::string id,
                           ConfigurationParameterPriority priority,
                           std::string information = 0);

private:

    std::string mId;
    std::string mInformation;

};

}
}

#endif
