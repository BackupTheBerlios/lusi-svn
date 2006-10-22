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

#include "ConfigurationParameterMap.h"
#include "ConfigurationParameterVisitor.h"

using std::string;
using std::vector;

using lusi::util::IdSmartPtrMap;
using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

ConfigurationParameterMap::ConfigurationParameterMap(const string& id,
                                const string& name,
                                PriorityType priorityType,
                                const string& information,
                                InvalidPolicy invalidPolicy /*= NoPolicy*/):
        ConfigurationParameter(id, name, priorityType, information) {
    mInvalidPolicy = invalidPolicy;
}

ConfigurationParameterMap::~ConfigurationParameterMap() {
}

bool ConfigurationParameterMap::isInvalid() {
    if (mInvalidPolicy == NoPolicy) {
        return false;
    }

    vector< SmartPtr<ConfigurationParameter> > configurationParameters =
                                            mConfigurationParameters.getAll();
    if (configurationParameters.size() == 0) {
        return false;
    }

    if (mInvalidPolicy == AndPolicy) {
        for (uint i=0; i<configurationParameters.size(); ++i) {
            if (configurationParameters[i]->isInvalid()) {
                return true;
            }
        }

        return false;
    }

    if (mInvalidPolicy == OrPolicy) {
        for (uint i=0; i<configurationParameters.size(); ++i) {
            if (!configurationParameters[i]->isInvalid()) {
                return false;
            }
        }

        return true;
    }

    //Unknown policy, shouldn't happen, but if it does...
    return true;
}

void ConfigurationParameterMap::accept(ConfigurationParameterVisitor* visitor) {
    visitor->visit(this);
}

bool ConfigurationParameterMap::add(
                    SmartPtr<ConfigurationParameter> configurationParameter) {
    if (!mConfigurationParameters.add(configurationParameter)) {
        return false;
    }

    mConfigurationParametersVector.push_back(configurationParameter);

    return true;
}

/*
inline SmartPtr<ConfigurationParameter>
ConfigurationParameterMap::get(const string& id) const {
    return mConfigurationParameters.get(id);
}

inline vector< SmartPtr<ConfigurationParameter> >
ConfigurationParameterMap::getAll() const {
    return mConfigurationParameters.getAll();
}
*/

bool ConfigurationParameterMap::remove(const string& id) {
    if (!mConfigurationParameters.remove(id)) {
        return false;
    }

    bool deleted = false;
    vector< SmartPtr<ConfigurationParameter> >::iterator it =
                                    mConfigurationParametersVector.begin();
    while (!deleted) {
        if ((*it)->getId() == id) {
            mConfigurationParametersVector.erase(it);
            deleted = true;
        }
        ++it;
    }

    return true;
}

/*
inline InvalidPolicy ConfigurationParameterMap::getInvalidPolicy() const {
    return mInvalidPolicy;
}
*/

void ConfigurationParameterMap::merge(
            const ConfigurationParameterMap& configurationParameterMap,
            MergeType type /*= KeepParameters*/) {
    vector< SmartPtr<ConfigurationParameter> > configurationParameters =
                                            configurationParameterMap.getAll();

    for (uint i=0; i<configurationParameters.size(); ++i) {
        string id = configurationParameters[i]->getId();
        if (get(id).isNull()) {
            add(configurationParameters[i]);
        } else if (type == OverrideParameters) {
            remove(id);
            add(configurationParameters[i]);
        }
    }
}
