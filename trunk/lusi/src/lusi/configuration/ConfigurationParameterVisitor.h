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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERVISITOR_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERVISITOR_H

namespace lusi {
namespace configuration {
class ConfigurationParameterAnd;
class ConfigurationParameterOr;
class ConfigurationParameterBool;
class ConfigurationParameterDouble;
class ConfigurationParameterInt;
class ConfigurationParameterLocalUrl;
class ConfigurationParameterString;
}
}

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterVisitor ConfigurationParameterVisitor.h \
 * lusi/configuration/ConfigurationParameterVisitor.h
 *
 * Interface for configuration parameter visitors.
 * Parameter visitors can help traversing a ConfigurationParameter without
 * needing to use casts and type inference to work with the parameters.
 * It follows, obviously, Visitor design pattern.
 *
 * When implementing this interface, you must provide an implementation for all
 * the methods. No default implementation exists for them.
 * Each method should do the needed operations for the type of the parameter it
 * receives. If the parameter is composed, the method must iterate through all
 * the parameters contained in the composed parameters to visit each them.
 *
 * @see ConfigurationParameter
 */
class ConfigurationParameterVisitor {
public:

    /**
     * Destroys this ConfigurationParameterVisitor.
     */
    virtual ~ConfigurationParameterVisitor() {
    }

    /**
     * Visits a ConfigurationParameterAnd.
     *
     * @param parameter The ConfigurationParameterAnd to visit.
     */
    virtual void visit(ConfigurationParameterAnd* parameter) = 0;

    /**
     * Visits a ConfigurationParameterOr.
     *
     * @param parameter The ConfigurationParameterOr to visit.
     */
    virtual void visit(ConfigurationParameterOr* parameter) = 0;

    /**
     * Visits a ConfigurationParameterBool.
     *
     * @param parameter The ConfigurationParameterBool to visit.
     */
    virtual void visit(ConfigurationParameterBool* parameter) = 0;

    /**
     * Visits a ConfigurationParameterDouble.
     *
     * @param parameter The ConfigurationParameterDouble to visit.
     */
    virtual void visit(ConfigurationParameterDouble* parameter) = 0;

    /**
     * Visits a ConfigurationParameterInt.
     *
     * @param parameter The ConfigurationParameterInt to visit.
     */
    virtual void visit(ConfigurationParameterInt* parameter) = 0;

    /**
     * Visits a ConfigurationParameterLocalUrl.
     *
     * @param parameter The ConfigurationParameterLocalUrl to visit.
     */
    virtual void visit(ConfigurationParameterLocalUrl* parameter) = 0;

    /**
     * Visits a ConfigurationParameterString.
     *
     * @param parameter The ConfigurationParameterString to visit.
     */
    virtual void visit(ConfigurationParameterString* parameter) = 0;

protected:

    /**
     * Creates a new ConfigurationParameterVisitor.
     * Protected to avoid classes other than derived to create PackageStatus
     * objects.
     */
    ConfigurationParameterVisitor() {
    }

};

}
}

#endif
