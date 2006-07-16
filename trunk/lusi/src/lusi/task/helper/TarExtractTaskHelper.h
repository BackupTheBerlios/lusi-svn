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

#ifndef LUSI_TASK_HELPER_TAREXTRACTTASKHELPER_H
#define LUSI_TASK_HELPER_TAREXTRACTTASKHELPER_H

#include <string>

#include <lusi/task/helper/BaseExtractTaskHelper.h>

namespace lusi {
namespace package {
class ResourceMap;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Returns a new TarExtractTaskHelper.
 * Used to register TarExtractTaskHelper with Task names.
 *
 * @param task The Task to help.
 * @return The new TarExtractTaskHelper created.
 * @see TaskHelperManager
 */
TaskHelper* createTarExtractTaskHelper(lusi::task::Task* task);

/**
 * @class TarExtractTaskHelper TarExtractTaskHelper.h \
 * lusi/task/helper/TarExtractTaskHelper.h
 *
 * ExtractTaskHelper for tar command.
 * This ExtractTask implementation adds support for tar command. This command
 * extracts the contents of packed files supported by it. An optional parameter
 * is where the packed file should be extracted.
 *
 * ResourceMaps that can be used with TarExtractTaskHelper are those
 * with a packed file with a format supported by tar, containing the Package.
 *
 * No specific configuration is needed, only the generic for
 * BaseExtractTaskHelpers.
 */
class TarExtractTaskHelper: public BaseExtractTaskHelper {
public:

    /**
     * Creates a new TarExtractTaskHelper.
     */
    TarExtractTaskHelper(lusi::task::Task* task);

    /**
     * Destroys this TarExtractTaskHelper.
     */
    virtual ~TarExtractTaskHelper();

    /**
     * Returns True if the ResourceMap contains a packed file with the name of
     * the Package in a format supported by "tar" command (those are tar, gzip
     * and bzip2).
     *
     * @return bool True if the ResourceMap contains the packed Package.
     */
    virtual bool hasValidResourceMap();

protected:

    /**
     * Extracts the Package to the specified path.
     * The Package is extracted using "tar" command.
     *
     * @param path The full path where the package should be extracted.
     */
    virtual void extract(std::string path);

private:

    /**
     * Copy constructor disabled.
     */
    TarExtractTaskHelper(const TarExtractTaskHelper& tarExtractTaskHelper);

    /**
     * Assignment disabled.
     */
    TarExtractTaskHelper& operator=(
            const TarExtractTaskHelper& tarExtractTaskHelper);

};

}
}
}

#endif
