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

#ifndef LUSI_PACKAGE_RESOURCE_H
#define LUSI_PACKAGE_RESOURCE_H

#include <string>
#include <vector>

namespace lusi {
namespace package {

/**
 * @class Resource Resource.h lusi/package/Resource.h
 *
 * Resources are elements that are part of a Package.
 * A Resource can be anything, from a local file part of the package to a
 * recipe explaining how to install a Package, including among them remote
 * files, the URL to the webpage for the package... It's a generic and
 * extensible form to represent a Package and related things to it.
 *
 * Every Resource has a unique identifier. Its meaning depends on each type of
 * Resource. The contents of Resources can be got in a binary form as a
 * vector of char. Like the identifier, its meaning depends on each type of
 * Resource.
 *
 * Resource is an abstract class, so it must be derived to be used. When a new
 * Resource is created, its id is set and can't be modified. Data management,
 * however, is left entirely to derived classes.
 */
class Resource {
public:

    /**
     * Destroys this Resource.
     */
    virtual ~Resource();

    /**
     * Returns the data of this Resource, as a char vector.
     * Derived classes must define this method.
     *
     * @return The data of this Resource.
     * @todo Return vector<char>? Use a stream?
     */
    virtual std::vector<char> getData() = 0;

    /**
     * Returns the identifier of this Resource.
     * The id is read only, and this is an accessor method.
     *
     * @return The identifier of this Resource.
     */
    const std::string& getId() const {
        return mId;
    }

protected:

    /**
     * Creates a new Resource with the specified id.
     * Protected to avoid classes other than derived to create Resource
     * objects.
     */
    Resource(std::string id);

private:

    /**
     * Unique identifier for this Resource.
     */
    std::string mId;




    /**
     * Copy constructor disabled.
     */
    Resource(const Resource &resource);

    /**
     * Assignment disabled.
     */
    Resource& operator=(const Resource &resource);

};

}
}

#endif
