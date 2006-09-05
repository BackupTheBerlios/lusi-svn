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

#include "ConfigurationParameterAnd.h"

using std::string;
using std::vector;

using namespace lusi::configuration;

//public:

ConfigurationParameterAnd::ConfigurationParameterAnd(const string& id,
                                PriorityType priorityType,
                                const string& information /*= 0*/):
            ConfigurationParameterComposed(id, priorityType, information) {
}

ConfigurationParameterAnd::~ConfigurationParameterAnd() {
}

bool ConfigurationParameterAnd::isInvalid() {
    vector<ConfigurationParameter*> configurationParameters =
                                            getConfigurationParameters();
    for (int i=0; i<configurationParameters.size(); ++i) {
        if (configurationParameters[i]->isInvalid()) {
            return true;
        }
    }

    return false;
}
