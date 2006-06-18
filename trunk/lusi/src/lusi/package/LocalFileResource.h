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

#ifndef LUSI_PACKAGE_LOCALFILERESOURCE_H
#define LUSI_PACKAGE_LOCALFILERESOURCE_H

#include <lusi/package/Resource.h>

namespace lusi {
namespace package {

/**
 * @class LocalFileResource LocalFileResource.h lusi/package/LocalFileResource.h
 *
 * This class represents files in the local filesystem which are part of a
 * Package.
 * LocalFileResources are only intended to be read, but not modified in any
 * way (creating, deleting or editing a file).
 *
 * The id of this Resource is the full path and name of the file in the local
 * filesystem. Data is the contents of the file, returned in binary form even
 * if the file readed is a text file. The file is opened, read and closed every
 * time the getData() method is called. There's no caching for file contents.
 */
class LocalFileResource: public Resource {
public:

    /**
     * Creates a new LocalFileResource for the specified local file.
     * The file path must include the full path and full name of the file
     * (name and extension, if any). The filePath will be used as the id.
     *
     * @param filePath The full path and name to the local file.
     */
    LocalFileResource(const std::string& filePath);

    /**
     * Destroys this LocalFileResource.
     */
    virtual ~LocalFileResource();

    /**
     * Returns the data of the file.
     * Each time this method is called, the file will be opened, read and
     * closed. File data isn't cached.
     *
     * @return The data of the file.
     */
    virtual std::vector<char> getData();

protected:

private:

    /**
     * Copy constructor disabled.
     */
    LocalFileResource(const LocalFileResource& localFileResource);

    /**
     * Assignment disabled.
     */
    LocalFileResource& operator=(const LocalFileResource& localFileResource);

};

}
}

#endif
