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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSSET_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERSSET_H

#include <lusi/configuration/ConfigurationParameter.h>
#include <lusi/util/IdSmartPtrMap.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterMap ConfigurationParameterMap.h \
 * lusi/configuration/ConfigurationParameterMap.h
 *
 * Maps ConfigurationParameters with their ids.
 * This is a specialized version of IdSmartPtrMap to be used with
 * ConfigurationParameters.
 * Everything that applies in IdSmartPtrMap applies here.
 *
 * Moreover, this class allows merging a ConfigurationParameterMap with another
 * one using merge method. Contents of the map to merge are added to the merged
 * map. If a parameter to add has the same id as another already present in the
 * merged map, the content in the merged map can be overriden or not.
 *
 * @see ConfigurationParameter
 */
class ConfigurationParameterMap:
            public lusi::util::IdSmartPtrMap<ConfigurationParameter> {
public:

    /**
     * The type of merge between two ConfigurationParameterMaps.
     */
    enum MergeType {
        KeepParameters,
        OverrideParameters
    };

    /**
     * Creates a new empty ConfigurationParameterMap.
     */
    ConfigurationParameterMap();

    /**
     * Destroys this ConfigurationParameterMap.
     */
    virtual ~ConfigurationParameterMap();

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
