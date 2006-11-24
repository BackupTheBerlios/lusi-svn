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

#ifndef LUSI_UTIL_IDSMARTPTRMAP_H
#define LUSI_UTIL_IDSMARTPTRMAP_H

#include <map>
#include <string>
#include <vector>

#include <lusi/util/SmartPtr.h>

namespace lusi {
namespace util {

/**
 * @class IdSmartPtrMap IdSmartPtrMap.h lusi/util/IdSmartPtrMap.h
 *
 * Maps pointers with their ids.
 * This map works with pointers instead of full objects. Moreover, it only uses
 * SmartPtr to ensure correct destruction of the pointers. It is able to share
 * pointers with other instances of this class and, in general, with any other
 * class that uses smart pointers.
 * The type of the pointers added to the map must have a method with the
 * signature: std::string getId() The string returned from that method is used
 * as the key to map the pointers.
 *
 * Pointers can be added using add(SmartPtr). It uses the id of the
 * pointer as the key to map to. A specific pointer can be got using its id
 * with get(string). All the added pointers can be got as a vector using
 * getAll(). To remove a pointer, use remove(string).
 *
 * Only initialized pointers can be stored. The null pointer element can't be
 * added.
 *
 * When an IdSmartPtrMap is copied (using a copy constructor or an assignment
 * operator) the contained smart pointers are copied, but not the pointed
 * objects themselves. That is, the contained elements are shared by both maps.
 *
 * This class acts as a wrapper for STL Map class, simplifying its interface to
 * be used with pointers, and also getting control over lifespan of pointers
 * through the use of smart pointers.
 * It follows Adapter Design Pattern.
 *
 * @see SmartPtr
 */
template<typename T>
class IdSmartPtrMap {
public:

    /**
     * Creates a new empty IdSmartPtrMap.
     */
    IdSmartPtrMap() {
    }

    /**
     * Copy constructor.
     *
     * @param idSmartPtrMap The map to copy.
     */
    IdSmartPtrMap(const IdSmartPtrMap& idSmartPtrMap) {
        mMap = idSmartPtrMap.mMap;
    }

    /**
     * Destroys this IdSmartPtrMap.
     * It also destroys all the contained pointers (if needed, it delegates this
     * on smart pointers).
     */
    virtual ~IdSmartPtrMap() {
    }

    /**
     * Adds a new pointer to this IdSmartPtrMap, using as key the element id.
     * If the element (identified only by its id) is already added, nothing
     * happens.
     * A null pointer can't be added.
     *
     * @param element The SmartPtr to add.
     * @return True if the SmartPtr was added, false otherwise.
     */
    bool add(SmartPtr<T> element) {
        //TODO assert for null pointers
        return mMap.insert(std::make_pair(element->getId(), element)).second;
    }

    /**
     * Returns the pointer identified by id.
     * If there's no pointer mapped to the id, a null pointer is returned.
     * This is an accessor method.
     *
     * @param id The id of the pointer to get.
     * @return The SmartPtr identified by the id.
     */
    SmartPtr<T> get(const std::string& id) const {
        MapConstIterator iterator = mMap.find(id);

        if (iterator == mMap.end()) {
            return SmartPtr<T>(0);
        }

        return iterator->second;
    }

    /**
     * Returns all the pointers in the Map in a vector.
     * This is an accessor method.
     *
     * @return All the SmartPtr in the Map in a vector.
     */
    std::vector< SmartPtr<T> > getAll() const {
        std::vector< SmartPtr<T> > allElements;

        for (MapConstIterator iterator = mMap.begin(); iterator != mMap.end();
                    ++iterator) {
            allElements.push_back(iterator->second);
        }

        return allElements;
    }

    /**
     * Removes the pointer identified by id from the Map.
     * If there's no pointer with the specified id, nothing happens.
     *
     * @param id The id of the pointer to remove.
     * @return True if the pointer was removed, false otherwise.
     */
    bool remove(const std::string& id) {
        SmartPtr<T> element = get(id);
        if (element == 0) {
            return false;
        }

        mMap.erase(id);

        return true;
    }

    /**
     * Removes all the pointers from the Map.
     */
    void clear() {
        mMap.clear();
    }

    /**
     * Assignment operator.
     *
     * @param idSmartPtrMap The map to assing.
     */
    IdSmartPtrMap& operator=(const IdSmartPtrMap& idSmartPtrMap) {
        mMap = idSmartPtrMap.mMap;

        return *this;
    }

protected:

    /**
     * Needed to use const_iterators of map.
     * It doesn't compile if not present.
     */
    typedef typename std::map<std::string, SmartPtr<T> >::const_iterator
                                                            MapConstIterator;

    /**
     * The STL Map used internally to store the elements.
     */
    std::map<std::string, SmartPtr<T> > mMap;

private:

};

}
}

#endif
