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

#include "ConfigurationParameterTestImplementation.h"

using std::string;

using namespace lusi::configuration;

//public:

ConfigurationParameterTestImplementation::
ConfigurationParameterTestImplementation(const string& id):
            ConfigurationParameter(id) {
    mInvalid = true;
}

ConfigurationParameterTestImplementation::
ConfigurationParameterTestImplementation(const string& id,
                                         const string& name,
                                         PriorityType priorityType,
                                         const string& information):
            ConfigurationParameter(id, name, priorityType, information) {
    mInvalid = true;
}

ConfigurationParameterTestImplementation::
~ConfigurationParameterTestImplementation() {
}

bool ConfigurationParameterTestImplementation::isInvalid() {
    return mInvalid;
}

void ConfigurationParameterTestImplementation::accept(
                                    ConfigurationParameterVisitor* visitor) {
}

void ConfigurationParameterTestImplementation::setInvalid(bool invalid) {
    mInvalid = invalid;
}
