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

#include "ResourceMap.h"
#include "Resource.h"

using std::make_pair;
using std::map;
using std::string;
using std::vector;

using namespace lusi::package;

//public:

ResourceMap::ResourceMap(): mMap() {
}

ResourceMap::~ResourceMap() {
    for (map<string, Resource*>::const_iterator iterator = mMap.begin();
            iterator != mMap.end(); ++iterator) {
        delete iterator->second;
    }
}

bool ResourceMap::addResource(Resource* resource) {
    //TODO assert for null pointers
    return mMap.insert(make_pair(resource->getId(), resource)).second;
}

Resource* ResourceMap::getResource(const string& id) const {
    map<string, Resource*>::const_iterator iterator = mMap.find(id);

    if (iterator == mMap.end()) {
        return 0;
    }

    return iterator->second;
}

vector<Resource*> ResourceMap::getAllResources() const {
    vector<Resource*> allResources;

    for (map<string, Resource*>::const_iterator iterator = mMap.begin();
            iterator != mMap.end(); ++iterator) {
        allResources.push_back(iterator->second);
    }

    return allResources;
}

/*
template<typename Type>
vector<Type*> ResourceMap::getAllResourcesByType() const {
    vector<Type*> resourcesByType;

    for (map<string, Resource*>::const_iterator iterator = mMap.begin();
            iterator != mMap.end(); ++iterator) {
        Type* resource = dynamic_cast<Type*>(iterator->second);
        if (resource != 0) {
            resourcesByType.push_back(resource);
        }
    }

    return resourcesByType;
}
*/

bool ResourceMap::removeResource(const string& id) {
    Resource* resource = getResource(id);
    if (resource == 0) {
        return false;
    }

    mMap.erase(id);
    delete resource;

    return true;
}
