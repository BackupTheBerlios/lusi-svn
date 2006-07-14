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

#ifndef LUSI_PACKAGE_RESOURCETESTIMPLEMENTATION_H
#define LUSI_PACKAGE_RESOURCETESTIMPLEMENTATION_H

#include <Resource.h>

namespace lusi {
namespace package {

/**
 * Implementation of Resource interface for testing purposes.
 * This class helps testing Resource class non-abstract methods, and also to be
 * used where Resource objects are needed.
 */
class ResourceTestImplementation : public Resource {
public:

    /**
     * Creates a new ResourceTestImplementation.
     */
    ResourceTestImplementation(const std::string& id);

    /**
     * Destroys this ResourceTestImplementation.
     */
    virtual ~ResourceTestImplementation();

    /**
     * Returns an empty vector.
     *
     * @return An empty vector.
     */
    virtual std::vector<char> getData();

};

}
}

#endif
