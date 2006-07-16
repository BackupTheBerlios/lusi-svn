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

#ifndef LUSI_TASK_CONFIGURETASK_H
#define LUSI_TASK_CONFIGURETASK_H

#include <lusi/task/Task.h>

namespace lusi {
namespace task {

/**
 * @class ConfigureTask ConfigureTask.h lusi/task/ConfigureTask.h
 *
 * The Task to configure a Package.
 * Configuration of packages sets some parameters dependents on the system
 * where the package is going to be built and installed, and generally creates
 * the build files.
 *
 * The name used is "ConfigureTask". Needed status is UnpackedPackageStatus,
 * while provided status is ConfiguredPackageStatus.
 */
class ConfigureTask: public Task {
public:

    /**
     * Creates a new ConfigureTask.
     * The name used for ConfigureTasks is "ConfigureTask".
     *
     * @param package The Package to use.
     * @param taskConfiguration The TaskConfiguration to use.
     */
    ConfigureTask(lusi::package::Package* package,
            TaskConfiguration* taskConfiguration);

    /**
     * Destroys this ConfigureTask.
     */
    virtual ~ConfigureTask();

    /**
     * Returns the instance of ConfiguredPackageStatus.
     *
     * @return The PackageStatus needed.
     */
    virtual const package::status::PackageStatus* needsPackageStatus() const;

    /**
     * @return package::status::PackageStatus
     */
    virtual const package::status::PackageStatus* providesPackageStatus()
                                                        const;

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ConfigureTask(const ConfigureTask& configureTask);

    /**
     * Assignment disabled.
     */
    ConfigureTask& operator=(const ConfigureTask& configureTask);

};

}
}

#endif
