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

#ifndef LUSI_TASK_INSTALLTASK_H
#define LUSI_TASK_INSTALLTASK_H

#include <lusi/task/Task.h>

namespace lusi {
namespace task {

/**
 * @class InstallTask InstallTask.h lusi/task/InstallTask.h
 *
 * The Task to install a Package.
 * Installation of the package copies all the files to their destination and,
 * in some cases, also executes auxiliar programas (such as ld).
 *
 * The name used is "InstallTask". Needed status is BuiltPackageStatus,
 * while provided status is InstalledPackageStatus.
 *
 * @see helper::InstallTaskHelper
 */
class InstallTask: public Task {
public:

    /**
     * Creates a new InstallTask.
     * The name used for InstallTasks is "InstallTask".
     *
     * @param package The Package to use.
     * @param taskConfiguration The TaskConfiguration to use.
     */
    InstallTask(lusi::package::Package* package,
            TaskConfiguration* taskConfiguration);

    /**
     * Destroys this InstallTask.
     */
    virtual ~InstallTask();

    /**
     * Returns the instance of BuiltPackageStatus.
     *
     * @return The PackageStatus needed.
     */
    virtual const package::status::PackageStatus* needsPackageStatus() const;

    /**
     * Returns the instance of InstalledPackageStatus.
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
    InstallTask(const InstallTask& installTask);

    /**
     * Assignment disabled.
     */
    InstallTask& operator=(const InstallTask& installTask);

};

}
}

#endif
