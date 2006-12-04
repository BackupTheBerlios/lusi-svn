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

#ifndef LUSI_MODULE_H
#define LUSI_MODULE_H

#include <string>

#include <lusi/task/NoTaskAvailableException.h>

namespace lusi {
namespace package {
class Package;
}
}

namespace lusi {
namespace package {
namespace status {
class PackageStatus;
}
}
}

namespace lusi {
namespace task {
class Task;
}
}

namespace lusi {

/**
 * @class Module Module.h lusi/Module.h
 *
 * Modules are "high level" actions to be executed by applications using the
 * library.
 * Modules are the main classes for applications using the library. Every
 * Module works over a Package provided by the application using the Module.
 * Each module has an specific mission, for example, install or uninstall a
 * Package. They follow the Strategy Design Pattern, and also resemble Façade,
 * as they abstract most of all the underlying execution of Tasks.
 *
 * Modules return Tasks to be executed. Before executing them, the Tasks should
 * be checked to know if all the parameters are valid.
 * Once a Task was executed, a new Task can be got in the Module using nextTask,
 * repeating this process until the returned Task is a null pointer, which means
 * that all the Tasks were executed and the module has finished.
 */
class Module {
public:

    /**
     * Destroys this Module.
     */
    virtual ~Module();

    /**
     * Returns the package being used in this module.
     *
     * @return The package being used in this module.
     */
    lusi::package::Package* getPackage() {
        return mPackage;
    }

    /**
     * Returns an estimation of the number of tasks needed to finish the module.
     * Currently returns 0.
     *
     * @return An estimation of the number of tasks needed to finish the module.
     * @todo Implement it
     */
    int getEstimatedNumberOfTasks();

    /**
     * If the module has finished.
     * The module finished if the current package status is equal to the final
     * package status of the module.
     *
     * @return True if the module has finished, false otherwise.
     */
    bool finished();

    /**
     * Returns the next Task to execute.
     * The returned Task must be executed (although completing before the
     * configuration of the Task). Once executed, the next one must be executed.
     * The same must be repeated until a null pointer is returned, which means
     * that the module finished.
     *
     * @return The next Task to execute.
     * @throw NoTaskAvailableException If there are no more available tasks.
     */
    lusi::task::Task* nextTask() throw (lusi::task::NoTaskAvailableException);

protected:

    /**
     * The Package to use.
     */
    lusi::package::Package* mPackage;

    /**
     * The current task.
     */
    lusi::task::Task* mCurrentTask;



    /**
     * Creates a new Module.
     * Protected to avoid classes other than derived to create Module
     * objects.
     *
     * @param package The Package to use.
     */
    Module(lusi::package::Package* package);

    /**
     * Returns the package status which signals that the package was installed.
     *
     * Must be implemented in derived classes.
     *
     * @return The package status which signals that the package was installed.
     */
    virtual const lusi::package::status::PackageStatus*
    getFinalPackageStatus() = 0;

private:

    /**
     * The initial PackageStatus of the Package.
     */
    const lusi::package::status::PackageStatus* mInitialPackageStatus;



    /**
     * Copy constructor disabled.
     */
    Module(const Module& module);

    /**
     * Assignment disabled.
     */
    Module& operator=(const Module& module);

};

}

#endif
