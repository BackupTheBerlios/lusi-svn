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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERMAP_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERMAP_H

#include <lusi/configuration/ConfigurationParameter.h>
#include <lusi/util/IdSmartPtrMap.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterMap ConfigurationParameterMap.h \
 * lusi/configuration/ConfigurationParameterMap.h
 *
 * Composed configuration parameter that maps the parameters with their ids.
 * Composed parameters represent a group of other parameters, being them simple
 * or composed. Child parameters can be added, got and removed using the methods
 * provided by this class. It uses Composite Design Pattern.
 *
 * ConfigurationParameterMap works with SmartPtr to ConfigurationParameters, so
 * the ConfigurationParameters added to this parameter must not be deleted from
 * outside. As SmartPtr are used, the parameters can be shared between
 * different ConfigurationParmeterMaps. It uses internally a specialized
 * version of IdSmartPtrMap to be used with ConfigurationParameters.
 *
 * This class provides different policies to check wheter it is invalid or not.
 * It can be set using InvalidPolicy enumeration values when creating an object
 * of this class.
 *
 * Moreover, this class allows merging a ConfigurationParameterMap with another
 * one using merge method. Contents of the map to merge are added to the merged
 * map. If a parameter to add has the same id as another already present in the
 * merged map, the content in the merged map can be overriden or not.
 */
class ConfigurationParameterMap: public ConfigurationParameter {
public:

    /**
     * The policy to check if this ConfigurationParameterMap is invalid.
     * NoPolicy means that it will be always valid.
     * AndPolicy means that it will be invalid if at least one parameter is
     * invalid.
     * OrPolicy means that it will be invalid if all the parameters are invalid.
     * Empty maps are always valid.
     */
    enum InvalidPolicy {
        NoPolicy,
        AndPolicy,
        OrPolicy
    };

    /**
     * The type of merge between two ConfigurationParameterMaps.
     */
    enum MergeType {
        KeepParameters,
        OverrideParameters
    };

    /**
     * Creates a new empty ConfigurationParameterMap.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param invalidPolicy The invalid policy, no policy by default.
     */
    ConfigurationParameterMap(const std::string& id,
                              const std::string& name,
                              PriorityType priorityType,
                              const std::string& information,
                              InvalidPolicy invalidPolicy = NoPolicy);

    /**
     * Destroys this ConfigurationParameterMap.
     * It also destroys all the contained ConfigurationParameters.
     */
    virtual ~ConfigurationParameterMap();

    /**
     * Returns true if this ConfigurationParameterMap is invalid, false
     * otherwise.
     * How it is determined whether this ConfigurationParameterMap is invalid or
     * not depends on its InvalidPolicy.
     *
     * @return True if this ConfigurationParameterMap is invalid, false
     *         otherwise.
     * @see InvalidPolicy
     */
    virtual bool isInvalid();

    /**
     * Accepts a visitor.
     *
     * @param visitor The ConfigurationParameterVisitor to accept.
     */
    virtual void accept(ConfigurationParameterVisitor* visitor);

    /**
     * Adds a new ConfigurationParameter to this ConfigurationParameterMap.
     * If the parameter (identified only by its id) is already added, nothing
     * happens.
     * A null pointer can't be added.
     *
     * @param configurationParameter The ConfigurationParameter to add.
     */
    bool add(lusi::util::SmartPtr<ConfigurationParameter>
                                                    configurationParameter) {
        return mConfigurationParameters.add(configurationParameter);
    }

    /**
     * Returns the ConfigurationParameter identified by id.
     * If there's no ConfigurationParameter mapped to the id, a null pointer is
     * returned.
     *
     * @param id The id of the ConfigurationParameter to get.
     * @return The ConfigurationParameter identified by the id.
     */
    lusi::util::SmartPtr<ConfigurationParameter> get(const std::string& id)
                                                                        const {
        return mConfigurationParameters.get(id);
    }

    /**
     * Returns a vector containing all the ConfigurationParameters added.
     *
     * @return A vector containing all the ConfigurationParameters added.
     */
    std::vector< lusi::util::SmartPtr<ConfigurationParameter> > getAll() const {
        return mConfigurationParameters.getAll();
    }

    /**
     * Removes the ConfigurationParameter identified by id from the Map.
     * If there's no ConfigurationParameter with the specified id, nothing
     * happens.
     *
     * @param id The id of the ConfigurationParameter to remove.
     * @return True if the ConfigurationParameter was removed, false otherwise.
     */
    bool remove(const std::string& id) {
        return mConfigurationParameters.remove(id);
    }

    /**
     * Returns the policy to check if this ConfigurationParameterMap is invalid.
     *
     * @return The policy to check if this ConfigurationParameterMap is invalid.
     */
    InvalidPolicy getInvalidPolicy() const {
        return mInvalidPolicy;
    }

    /**
     * Merges this ConfigurationParameter with the one specified.
     * The contents of the specified map are added to this map. If there's
     * already a parameter with the same id to be added, the one from this map
     * will be kept or it will be replaced, depending on the value of the type
     * of merge.
     * Merging happens only with the ConfigurationParameters contained directly
     * in the map. When adding or overriding a parameter, the whole parameter
     * is used. For example, if two composed parameters have the same id and
     * different children, children aren't added individually. Either the
     * composed parameter is kept as a whole, or replaced as a whole.
     *
     * @param configurationParameterMap The map to merge.
     * @param type The type of merge to do.
     */
    void merge(const ConfigurationParameterMap& configurationParameterMap,
               MergeType type = KeepParameters);

protected:

private:

    /**
     * The map that contains the ConfigurationParameters.
     */
    lusi::util::IdSmartPtrMap<ConfigurationParameter> mConfigurationParameters;

    /**
     * The policy to check if this ConfigurationParameterMap is invalid.
     */
    InvalidPolicy mInvalidPolicy;



    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterMap(
            const ConfigurationParameterMap& configurationParameterMap);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterMap& operator=(
            const ConfigurationParameterMap& configurationParameterMap);

};

}
}

#endif
