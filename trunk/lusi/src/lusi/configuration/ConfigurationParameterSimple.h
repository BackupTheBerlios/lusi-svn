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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLE_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSIMPLE_H

#include <lusi/configuration/ConfigurationParameter.h>

namespace lusi {
namespace configuration {

/**
 * @todo Documentation
 */
class ConfigurationParameterSimple: public ConfigurationParameter {
public:

    ConfigurationParameterSimple(const std::string& id,
            ConfigurationParameterPriority priority,
            const std::string& defaultValue,
            const std::string& information = 0);

    virtual ~ConfigurationParameterSimple();

    virtual ConfigurationParameter checkInvalidStatus();

    string getValue() {
        return mValue;
    }

    bool isDefaultValue() {
        return mValue == mDefaultValue;
    }

    void setValue(string value) {
        mValue = value;
    }

protected:

private:

    string mDefaultValue;
    string mValue;

};

}
}

#endif
