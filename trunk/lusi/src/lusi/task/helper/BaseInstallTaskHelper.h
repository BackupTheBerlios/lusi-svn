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

#ifndef LUSI_TASK_HELPER_BASEINSTALLTASKHELPER_H
#define LUSI_TASK_HELPER_BASEINSTALLTASKHELPER_H

#include <lusi/task/helper/TaskHelper.h>

namespace lusi {
namespace configuration {
class ConfigurationParametersSet;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * @class BaseInstallTaskHelper BaseInstallTaskHelper.h \
 * lusi/task/helper/BaseInstallTaskHelper.h
 *
 * Base TaskHelper for InstallTask.
 * This class provides a default behaviour for those TaskHelpers that only need
 * to call an external command to do the installtion. This command should be
 * returned by installCommand() method. Also, the uninstall command to revert
 * the changes should be returned by uninstallCommand(). This class takes care
 * of executing the commands as needed. However, if execute() and revert()
 * methods can be redefined if this behaviour doesn't suit the needs of the
 * derived class.
 *
 * Derived classes must define hasValidResourceMap() method, as this
 * method depends on the specific installtion system used. checkConfiguration()
 * returns an empty ConfigurationParametersSet, as most installation systems
 * don't need parameters. It can also be redefined if the derived class needs
 * it.
 *
 * @todo User changes to another user or root should be handled.
 */
class BaseInstallTaskHelper: public TaskHelper {
public:

    /**
     * Destroys this BaseInstallTaskHelper.
     */
    virtual ~BaseInstallTaskHelper();

    /**
     * Returns the generic configuration needed by BaseInstallTaskHelpers.
     * The default configuration is empty, as there are no generic parameters
     * needed for installation systems, and some of them doesn't have even
     * specific parameters.
     *
     * @return Returns the Configuration needed by this TaskHelper.
     */
    virtual lusi::configuration::ConfigurationParametersSet
                                            checkConfiguration();

    /**
     * Installs the package.
     * The generic implementation for InstallTasks is invoke the command
     * returned by installationCommand().
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @see installationCommand()
     */
    virtual void execute();

    /**
     * Reverts the changes made when installing the package.
     * The generic implementation for InstallTasks is invoke the command
     * returned by uninstallCommand().
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @see uninstallCommand()
     * @todo Create a default implementation such as deleting all the new files
     *       created installing the package? Would need support of execute
     *       method to register in the configuration all the created files.
     */
    virtual void revert();

protected:

    /**
     * Creates a new BaseInstallTaskHelper.
     *
     * @param name The name of the BaseInstallTaskHelper.
     * @param task The Task to help.
     */
    BaseInstallTaskHelper(const std::string& name, lusi::task::Task* task);

    /**
     * Returns the name of the install command to invoke to execute the
     * TaskHelper.
     * Must be implemented in derived classes.
     *
     * @return The install command to be invoked.
     * @todo If a derived class doesn't use default execute() method there's no
     *       need to redefine this method. However, being pure virtual, it must
     *       be redefined anyway. Make this method return an empty string? Move
     *       it and other default implementations to a derived class called
     *       DefaultInstallTaskHelper or something like that?
     */
    virtual std::string installCommand() = 0;

    /**
     * Returns the name of the uninstall command to invoke to revert the changes
     * made executing this TaskHelper.
     * Must be implemented in derived classes.
     *
     * @return The uninstall command to be invoked.
     * @todo If a derived class doesn't use default revert() method there's no
     *       need to redefine this method. However, being pure virtual, it must
     *       be redefined anyway. Make this method return an empty string? Move
     *       it and other default implementations to a derived class called
     *       DefaultInstallTaskHelper or something like that?
     */
    virtual std::string uninstallCommand() = 0;

private:

    /**
     * Copy constructor disabled.
     */
    BaseInstallTaskHelper(const BaseInstallTaskHelper& baseInstallTaskHelper);

    /**
     * Assignment disabled.
     */
    BaseInstallTaskHelper& operator=(
            const BaseInstallTaskHelper& baseInstallTaskHelper);

};

}
}
}

#endif
