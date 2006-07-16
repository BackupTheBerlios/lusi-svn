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

#ifndef LUSI_TASK_EXTRACTTASK_H
#define LUSI_TASK_EXTRACTTASK_H

#include <lusi/task/Task.h>

namespace lusi {
namespace task {

/**
 * @class ExtractTask ExtractTask.h lusi/task/ExtractTask.h
 *
 * The Task to extract a Package.
 * Extracts all the files from a packed (compressed or not) package and adds
 * them to the ResourceMap.
 *
 * The name used is "ExtractTask". Needed status is PackedPackageStatus,
 * while provided status is UnpackedPackageStatus.
 *
 * @todo Rename to UnpackTask?
 */
class ExtractTask: public Task {
public:

    /**
     * Creates a new ExtractTask.
     * The name used for ExtractTasks is "ExtractTask".
     *
     * @param package The Package to use.
     * @param taskConfiguration The TaskConfiguration to use.
     */
    ExtractTask(lusi::package::Package* package,
            TaskConfiguration* taskConfiguration);

    /**
     * Destroys this ExtractTask.
     */
    virtual ~ExtractTask();

    /**
     * Returns the instance of PackedPackageStatus.
     *
     * @return The PackageStatus needed.
     */
    virtual const package::status::PackageStatus* needsPackageStatus() const;

    /**
     * Returns the instance of UnpackedPackageStatus.
     *
     * @return The PackageStatus provided.
     */
    virtual const package::status::PackageStatus* providesPackageStatus()
                                                        const;

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ExtractTask(const ExtractTask& extractTask);

    /**
     * Assignment disabled.
     */
    ExtractTask& operator=(const ExtractTask& extractTask);

};

}
}

#endif
