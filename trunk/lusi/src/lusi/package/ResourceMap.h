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

#include <string>
#include <vector>

namespace lusi {
namespace package {
    class Resource;
}
}

namespace lusi {
namespace package {

/**
 * @class ResourceMap ResourceMap.h lusi/package/ResourceMap.h
 *
 * Maps Resources with their ids.
 * Resources can be added using addResource(Resource). It uses the id of the
 * Resource as the key to map to. A specific Resource can be get using its id
 * with getResource(string). All the added Resources can be got as a vector
 * using getAllResources(). To remove a Resource, use removeResource(string).
 *
 * Once a Resource is added, ResourceMap gets control over lifespan and
 * destruction of the Resource. Resources are destroyed when the Map is
 * destroyed or when they're removed from it.
 *
 * @see Resource
 * @todo typedef stl::Map as ResourceMap? If not, overload operators for this
 * class?
 */
class ResourceMap {
public:

    /**
     * Creates a new empty ResourceMap.
     */
    ResourceMap();

    /**
     * Destroys this ResourceMap.
     * It also destroys all the contained Resources.
     */
    virtual ~ResourceMap();

    /**
     * Adds a new Resource to this ResourceMap, using as key the Resource id.
     * If the Resource (identified only by its id) is already added, nothing
     * happens.
     *
     * @param resource The Resource to add.
     * @return True if the Resource was added, false otherwise.
     */
    bool addResource(const Resource* resource);

    /**
     * Returns the Resource identified by id.
     * If there's no Resource mapped to the id, a null pointer is returned.
     * This is an accessor method.
     *
     * @param id The id of the Resource to get.
     * @return The Resource identified by the id.
     */
    Resource* getResource(const std::string& id) const;

    /**
     * Returns all the Resources in the Map in a vector.
     *
     * @return All the Resources in the Map in a vector.
     */
    std::vector<Resource> getAllResources();

    /**
     * Removes the Resource identified by id from the Map, also deleting it.
     * If there's no Resource with the specified id, nothing happens.
     *
     * @param id The id of the Resource to delete.
     * @return True if the Resource was removed, false otherwise.
     */
    bool removeResource(const std::string& id);

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ResourceMap(const ResourceMap& resourceMap);

    /**
     * Assignment disabled.
     */
    ResourceMap& operator=(const ResourceMap& resourceMap);

};

}
}

#endif
