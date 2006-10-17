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

using std::string;
using std::vector;

using lusi::util::IdSmartPtrMap;
using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

ConfigurationParameterMap::ConfigurationParameterMap():
            IdSmartPtrMap<ConfigurationParameter>() {
}

ConfigurationParameterMap::~ConfigurationParameterMap() {
}

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
