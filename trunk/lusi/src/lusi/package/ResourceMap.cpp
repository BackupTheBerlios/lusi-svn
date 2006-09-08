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

using lusi::util::IdSmartPtrMap;

using namespace lusi::package;

//public:

ResourceMap::ResourceMap(): IdSmartPtrMap<Resource>() {
}

ResourceMap::~ResourceMap() {
}

/*
template<typename Type>
vector< SmartPtr<Type> > ResourceMap::getAllResourcesByType() const {
    vector< SmartPtr<Type> > resourcesByType;

    for (MapConstIterator iterator = mMap.begin(); iterator != mMap.end();
            ++iterator) {
        SmartPtr<Type> resource = (SmartPtr<Type>)iterator->second;
        if (resource != 0) {
            resourcesByType.push_back(resource);
        }
    }

    return resourcesByType;
}
*/
