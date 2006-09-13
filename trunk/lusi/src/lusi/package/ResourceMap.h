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

#ifndef LUSI_PACKAGE_RESOURCEMAP_H
#define LUSI_PACKAGE_RESOURCEMAP_H

#include <lusi/package/Resource.h>
#include <lusi/util/IdSmartPtrMap.h>

namespace lusi {
namespace package {

/**
 * @class ResourceMap ResourceMap.h lusi/package/ResourceMap.h
 *
 * Maps Resources with their ids.
 * This is a specialized version of IdSmartPtrMap to be used with Resources.
 * Everything that applies in IdSmartPtrMap applies here.
 *
 * Moreover, this class allows getting all the Resources from a specific Type
 * in a vector using getAllResourcesByType(). The Type can be any of the derived
 * classes of Resource.
 *
 * @see Resource
 */
class ResourceMap: public lusi::util::IdSmartPtrMap<Resource> {
public:

    /**
     * Creates a new empty ResourceMap.
     */
    ResourceMap();

    /**
     * Copy constructor.
     *
     * @param resourceMap The map to copy.
     */
    ResourceMap(const ResourceMap& resourceMap);

    /**
     * Destroys this ResourceMap.
     */
    virtual ~ResourceMap();

    /**
     * Returns all the Resources of the specified Type in the Map in a vector.
     * The Type is the class type of the pointer contained in the smart pointer.
     * Only classes derived from Resource can be used.
     * The Resources are returned also as smart pointers of the specified type,
     * so they can be alive after the ResourceMap is deleted if needed.
     *
     * This is an accessor method.
     *
     * @return All the Resources of the specified Type in the Map in a vector.
     */
    template<typename Type>
    std::vector< lusi::util::SmartPtr<Type> > getAllResourcesByType() const;

    /**
     * Assignment operator.
     *
     * @param resourceMap The map to assign.
     */
    ResourceMap& operator=(const ResourceMap& resourceMap);

protected:

private:

};

template<typename Type>
std::vector< lusi::util::SmartPtr<Type> > ResourceMap::getAllResourcesByType()
                                                                        const {
    std::vector< lusi::util::SmartPtr<Type> > resourcesByType;

    for (MapConstIterator iterator = mMap.begin(); iterator != mMap.end();
            ++iterator) {
        lusi::util::SmartPtr<Type> resource =
                (lusi::util::SmartPtr<Type>)iterator->second;
        if (resource != 0) {
            resourcesByType.push_back(resource);
        }
    }

    return resourcesByType;
}

}
}

#endif
