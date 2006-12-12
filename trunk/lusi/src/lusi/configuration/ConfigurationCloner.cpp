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

#include "ConfigurationCloner.h"
#include "ConfigurationParameterBool.h"
#include "ConfigurationParameterDouble.h"
#include "ConfigurationParameterInt.h"
#include "ConfigurationParameterLocalUrl.h"
#include "ConfigurationParameterMap.h"
#include "ConfigurationParameterString.h"

using std::string;
using std::vector;

using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

ConfigurationCloner::ConfigurationCloner(): ConfigurationParameterVisitor() {
    mClonedConfiguration = 0;
}

ConfigurationCloner::~ConfigurationCloner() {
}

void ConfigurationCloner::visit(ConfigurationParameterBool* parameter) {
    ConfigurationParameterBool* clone;

    if (parameter->isDefaultValueSet()) {
        clone = new ConfigurationParameterBool(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation(), parameter->getDefaultValue());
    } else {
        clone = new ConfigurationParameterBool(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation());
    }

    if (parameter->isValueSet()) {
        clone->setValue(parameter->getValue());
    }

    mClonedConfiguration->add(SmartPtr<ConfigurationParameterBool>(clone));
}

void ConfigurationCloner::visit(ConfigurationParameterDouble* parameter) {
    ConfigurationParameterDouble* clone;

    if (parameter->isDefaultValueSet()) {
        clone = new ConfigurationParameterDouble(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation(), parameter->getDefaultValue());
    } else {
        clone = new ConfigurationParameterDouble(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation());
    }

    if (parameter->isValueSet()) {
        clone->setValue(parameter->getValue());
    }

    mClonedConfiguration->add(SmartPtr<ConfigurationParameterDouble>(clone));
}

void ConfigurationCloner::visit(ConfigurationParameterInt* parameter) {
    ConfigurationParameterInt* clone;

    if (parameter->isDefaultValueSet()) {
        clone = new ConfigurationParameterInt(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation(), parameter->getDefaultValue());
    } else {
        clone = new ConfigurationParameterInt(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation());
    }

    if (parameter->isValueSet()) {
        clone->setValue(parameter->getValue());
    }

    mClonedConfiguration->add(SmartPtr<ConfigurationParameterInt>(clone));
}

void ConfigurationCloner::visit(ConfigurationParameterLocalUrl* parameter) {
    ConfigurationParameterLocalUrl* clone;

    if (parameter->isDefaultValueSet()) {
        clone = new ConfigurationParameterLocalUrl(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation(), parameter->getDefaultValue(),
            parameter->getUrlType());
    } else {
        clone = new ConfigurationParameterLocalUrl(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation(), parameter->getUrlType());
    }

    if (parameter->isValueSet()) {
        clone->setValue(parameter->getValue());
    }

    mClonedConfiguration->add(SmartPtr<ConfigurationParameterLocalUrl>(clone));
}

void ConfigurationCloner::visit(ConfigurationParameterMap* parameter) {
    ConfigurationParameterMap* clone = new ConfigurationParameterMap(
        parameter->getId(), parameter->getName(), parameter->getPriorityType(),
        parameter->getInformation(), parameter->getInvalidPolicy());

    if (mClonedConfiguration == 0) {
        mClonedConfiguration = clone;
    } else {
        mClonedConfiguration->add(SmartPtr<ConfigurationParameter>(clone));
    }

    ConfigurationParameterMap* parentConfiguration = mClonedConfiguration;
    mClonedConfiguration = clone;

    vector< SmartPtr<ConfigurationParameter> > children = parameter->getAll();
    for (uint i=0; i<children.size(); ++i) {
        children[i]->accept(this);
    }

    mClonedConfiguration = parentConfiguration;
}

void ConfigurationCloner::visit(ConfigurationParameterString* parameter) {
    ConfigurationParameterString* clone;

    if (parameter->isDefaultValueSet()) {
        clone = new ConfigurationParameterString(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation(), parameter->getDefaultValue(),
            parameter->getStringType());
    } else {
        clone = new ConfigurationParameterString(parameter->getId(),
            parameter->getName(), parameter->getPriorityType(),
            parameter->getInformation(), parameter->getStringType());
    }

    if (parameter->isValueSet()) {
        clone->setValue(parameter->getValue());
    }

    mClonedConfiguration->add(SmartPtr<ConfigurationParameterString>(clone));
}

ConfigurationParameterMap* ConfigurationCloner::clone(
                        ConfigurationParameterMap* configurationParameterMap) {
    mClonedConfiguration = 0;

    configurationParameterMap->accept(this);

    return mClonedConfiguration;
}
