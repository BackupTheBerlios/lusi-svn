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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONMERGER_H
#define LUSI_CONFIGURATION_CONFIGURATIONMERGER_H

#include <lusi/configuration/ConfigurationParameterVisitor.h>

namespace lusi {
namespace configuration {
class ConfigurationParameter;
}
}

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationMerger ConfigurationMerger.h \
 * lusi/configuration/ConfigurationMerger.h
 *
 * Merges the parameters from a configuration into another.
 * The configurations to merge are ConfigurationParameterMaps. One of them will
 * be modified, while the other contains the parameter that will be used to
 * modify the first. A Visitor design pattern is used to traverse the
 * configuration which will be modified.
 *
 * The parameters to be modified are those with the same id as their equivalent
 * in the modifier configuration. The parents of each parameter (a
 * ConfigurationParameterMap, as it is the only parameter which can hold other
 * parameters) must also have equal ids. Moreover, the parameters must be of the
 * same class (for example, a bool can't be merged with an int). That is, the
 * merged parameters will be those that have the same structure in both
 * configurations.
 *
 * The method that must be used to make the merge is
 * merge(ConfigurationParameterMap*, ConfigurationParameterMap*). All the other
 * public methods called visit must not be used, as they depend on the
 * invocation of merge. They are public due to language restrictions.
 */
class ConfigurationMerger: public ConfigurationParameterVisitor {
public:

    /**
     * Creates a new ConfigurationMerger.
     */
    ConfigurationMerger();

    /**
     * Destroys this ConfigurationMerger.
     */
    virtual ~ConfigurationMerger();

    /**
     * Merges this parameter with the one with the same id in the second
     * configuration.
     *
     * @param parameter The ConfigurationParameterBool to be modified.
     */
    virtual void visit(ConfigurationParameterBool* parameter);

    /**
     * Merges this parameter with the one with the same id in the second
     * configuration.
     *
     * @param parameter The ConfigurationParameterDouble to be modified.
     */
    virtual void visit(ConfigurationParameterDouble* parameter);

    /**
     * Merges this parameter with the one with the same id in the second
     * configuration.
     *
     * @param parameter The ConfigurationParameterInt to be modified.
     */
    virtual void visit(ConfigurationParameterInt* parameter);

    /**
     * Merges this parameter with the one with the same id in the second
     * configuration.
     *
     * @param parameter The ConfigurationParameterLocalUrl to be modified.
     */
    virtual void visit(ConfigurationParameterLocalUrl* parameter);

    /**
     * Merges all the parameters in the ConfigurationParameterMap with their
     * equivalent parameters in the second configuration.
     * The parameters are merged if they have the same id. No checks are made
     * here about their type. This is done in the visit method of each simple
     * parameter.
     *
     * @param parameter The ConfigurationParameterMap to traverse.
     */
    virtual void visit(ConfigurationParameterMap* parameter);

    /**
     * Merges this parameter with the one with the same id in the second
     * configuration.
     *
     * @param parameter The ConfigurationParameterString to be modified.
     */
    virtual void visit(ConfigurationParameterString* parameter);

    /**
     * Merges the second configuration into the first.
     * ConfigurationParameterSimple values are modified, but the name,
     * priority, information and default value aren't modified.
     * ConfigurationParameterMaps aren't modified at all.
     *
     * The first configuration is traversed, and, if there is a parameter with
     * the same id and with equivalent parent in the second configuration, they
     * are merged.
     *
     * @param configurationParameterMap1 The configuration to be modified.
     * @param configurationParameterMap2 The modifier configuration.
     */
    void merge(ConfigurationParameterMap* configurationParameterMap1,
               ConfigurationParameterMap* configurationParameterMap2);

protected:

private:

    /**
     * The equivalent parameter of the current parameter in the second
     * configuration.
     */
    ConfigurationParameter* mParameter2;



    /**
     * Copy constructor disabled.
     */
    ConfigurationMerger(const ConfigurationMerger& configurationMerger);

    /**
     * Assignment disabled.
     */
    ConfigurationMerger& operator=(
                            const ConfigurationMerger& configurationMerger);

};

}
}

#endif
