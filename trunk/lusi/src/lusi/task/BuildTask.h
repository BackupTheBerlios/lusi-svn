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

#ifndef LUSI_TASK_BUILDTASK_H
#define LUSI_TASK_BUILDTASK_H

#include <lusi/task/Task.h>

namespace lusi {
namespace task {

/**
 * @class BuildTask BuildTask.h lusi/task/BuildTask.h
 *
 * The Task to build a Package.
 * Build of packages creates all the needed files to be installed.
 *
 * The name used is "BuildTask". Needed status is ConfiguredPackageStatus,
 * while provided status is BuiltPackageStatus.
 *
 * @see helper::BuildTaskHelper
 */
class BuildTask: public Task {
public:

    /**
     * Creates a new BuildTask.
     * The name used for BuildTasks is "BuildTask".
     *
     * @param package The Package to use.
     * @param taskConfiguration The TaskConfiguration to use.
     */
    BuildTask(lusi::package::Package *package,
            TaskConfiguration *taskConfiguration);

    /**
     * Destroys this BuildTask.
     */
    virtual ~BuildTask();

    /**
     * Returns the instance of ConfiguredPackageStatus.
     *
     * @return The PackageStatus needed.
     */
    virtual const package::status::PackageStatus* needsPackageStatus() const;

    /**
     * Returns the instance of BuiltPackageStatus.
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
    BuildTask(const BuildTask &buildTask);

    /**
     * Assignment disabled.
     */
    BuildTask& operator=(const BuildTask &buildTask);

};

}
}

#endif
