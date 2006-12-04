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

#include "ConfigurationMerger.h"
#include "ConfigurationParameterBool.h"
#include "ConfigurationParameterDouble.h"
#include "ConfigurationParameterInt.h"
#include "ConfigurationParameterLocalUrl.h"
#include "ConfigurationParameterMap.h"
#include "ConfigurationParameterString.h"

using std::vector;

using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

ConfigurationMerger::ConfigurationMerger(): ConfigurationParameterVisitor() {
    mParameter2 = 0;
}

ConfigurationMerger::~ConfigurationMerger() {
}

//TODO extract all the code in visit ConfigurationParameterSimple subclasses
//methods to a generic templated method
void ConfigurationMerger::visit(ConfigurationParameterBool* parameter) {
    ConfigurationParameterBool* parameter2 =
                        dynamic_cast<ConfigurationParameterBool*>(mParameter2);
    if (!parameter2) {
        return;
    }

    if (parameter2->isValueSet()) {
        parameter->setValue(parameter2->getValue());
    }
}

void ConfigurationMerger::visit(ConfigurationParameterDouble* parameter) {
    ConfigurationParameterDouble* parameter2 =
                    dynamic_cast<ConfigurationParameterDouble*>(mParameter2);
    if (!parameter2) {
        return;
    }

    if (parameter2->isValueSet()) {
        parameter->setValue(parameter2->getValue());
    }
}

void ConfigurationMerger::visit(ConfigurationParameterInt* parameter) {
    ConfigurationParameterInt* parameter2 =
                        dynamic_cast<ConfigurationParameterInt*>(mParameter2);
    if (!parameter2) {
        return;
    }

    if (parameter2->isValueSet()) {
        parameter->setValue(parameter2->getValue());
    }
}

void ConfigurationMerger::visit(ConfigurationParameterLocalUrl* parameter) {
    ConfigurationParameterLocalUrl* parameter2 =
                    dynamic_cast<ConfigurationParameterLocalUrl*>(mParameter2);
    if (!parameter2) {
        return;
    }

    if (parameter2->isValueSet()) {
        parameter->setValue(parameter2->getValue());
    }
}

void ConfigurationMerger::visit(ConfigurationParameterMap* parameter) {
    ConfigurationParameterMap* parameter2 =
                        dynamic_cast<ConfigurationParameterMap*>(mParameter2);
    if (!parameter2) {
        return;
    }

    vector< SmartPtr<ConfigurationParameter> > parameters = parameter->getAll();
    for (uint i=0; i<parameters.size(); ++i) {
        ConfigurationParameter* childParameter2 =
                                getPtr(parameter2->get(parameters[i]->getId()));
        if (childParameter2) {
            mParameter2 = childParameter2;
            parameters[i]->accept(this);
            mParameter2 = parameter2;
        }
    }
}

void ConfigurationMerger::visit(ConfigurationParameterString* parameter) {
    ConfigurationParameterString* parameter2 =
                    dynamic_cast<ConfigurationParameterString*>(mParameter2);
    if (!parameter2) {
        return;
    }

    if (parameter2->isValueSet()) {
        parameter->setValue(parameter2->getValue());
    }
}

void ConfigurationMerger::merge(
                        ConfigurationParameterMap* configurationParameterMap1,
                        ConfigurationParameterMap* configurationParameterMap2) {
    mParameter2 = configurationParameterMap2;

    configurationParameterMap1->accept(this);
}
