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

#include "ConfigurationParameterInt.h"

using std::string;

using namespace lusi::configuration;

//public:

ConfigurationParameterInt::ConfigurationParameterInt(const string& id):
        ConfigurationParameterSimple<int>(id) {
}

ConfigurationParameterInt::ConfigurationParameterInt(const string& id,
                                    int defaultValue):
        ConfigurationParameterSimple<int>(id, defaultValue) {
}

ConfigurationParameterInt::ConfigurationParameterInt(const string& id,
                                    const string& name,
                                    PriorityType priorityType,
                                    const string& information):
        ConfigurationParameterSimple<int>(id, name, priorityType,
                                          information) {
}

ConfigurationParameterInt::ConfigurationParameterInt(const string& id,
                                    const string& name,
                                    PriorityType priorityType,
                                    const string& information,
                                    int defaultValue):
        ConfigurationParameterSimple<int>(id, name, priorityType,
                                          information, defaultValue) {
}

ConfigurationParameterInt::~ConfigurationParameterInt() {
}

/*
inline void ConfigurationParameterInt::accept(
                                        ConfigurationParameterVisitor* visitor) {
    visitor->visit(this);
}
*/
