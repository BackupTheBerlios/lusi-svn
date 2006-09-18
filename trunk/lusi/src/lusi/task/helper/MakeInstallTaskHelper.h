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

#ifndef LUSI_TASK_HELPER_MAKEINSTALLTASKHELPER_H
#define LUSI_TASK_HELPER_MAKEINSTALLTASKHELPER_H

#include <string>

#include <lusi/task/helper/TaskHelperUsingMake.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterSimple;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Returns a new MakeInstallTaskHelper.
 * Used to register MakeInstallTaskHelpers with Task names.
 *
 * @param task The Task to help.
 * @return The new MakeInstallTaskHelper created.
 * @see TaskHelperManager
 */
TaskHelper* createMakeInstallTaskHelper(lusi::task::Task* task);

/**
 * @class MakeInstallTaskHelper MakeInstallTaskHelper.h \
 * lusi/task/helper/MakeInstallTaskHelper.h
 *
 * InstallTaskHelper for make command.
 * This InstallTask implementation adds support for make command. This command
 * reads the macros in a file called Makefile. When it's executed, it installs
 * the package or uninstalls it removing the files created when building it. It
 * uses no parameters (apart from the target of the Makefile to execute).
 *
 * ResourceMaps that can be used with MakeInstallTaskHelper are those
 * with a "Makefile" file in the base directory of the package. The package
 * directory must be the first LocalFileResource in the ResourceMap.
 *
 * It may happen that the directory where the package will be installed doesn't
 * belongs to the current user and she doesn't have write permissions on it. In
 * those cases, the configuration includes the name and the password of the
 * user owner of the directory to install the package to.
 */
class MakeInstallTaskHelper: public TaskHelperUsingMake {
public:

    /**
     * Creates a new MakeInstallTaskHelper.
     * The package directory is the first LocalFileResource in the ResourceMap.
     * If there's no LocalFileResource, or the first it's not a directory, an
     * empty LocalUrl is used.
     * No checks about, for example, more than one package directory, are made.
     *
     * @param task The Task to help.
     */
    MakeInstallTaskHelper(lusi::task::Task* task);

    /**
     * Destroys this MakeInstallTaskHelper.
     */
    virtual ~MakeInstallTaskHelper();

    /**
     * Inits the configuration parameters for this TaskHelper.
     * If the current user doesn't have enough permissions to access and write
     * in the prefix to install the package to, the configuration contains the
     * user name and the password of the owner of the prefix directory.
     * Otherwise, it is empty.
     */
    virtual void initConfigurationParameterMap();

protected:

    /**
     * Creates a new SuProcess with PtyCommunication and sets the arguments and
     * the working directory to call make command using install target.
     * The process switchs to a different user only if the current user doesn't
     * have the needed permissions in the destination dir. The user name and
     * password are got from the configuration.
     *
     * @return The Process to be executed.
     */
    virtual lusi::util::Process* getProcess();

private:

    /**
     * The configuration parameter for password.
     * If this paremeter isn't needed, it is null.
     */
    lusi::configuration::ConfigurationParameterSimple* mUserName;

    /**
     * The configuration parameter for user name.
     * If this paremeter isn't needed, it is null.
     */
    lusi::configuration::ConfigurationParameterSimple* mPassword;



    /**
     * Returns the path to the directory used as installation prefix for the
     * package.
     * The prefix is got from the Makefile, and it may not contain the ending
     * "/".
     *
     * @return The path to the directory used as installation prefix for the
     *         package.
     */
    std::string getInstallationPrefix();

    /**
     * Copy constructor disabled.
     */
    MakeInstallTaskHelper(const MakeInstallTaskHelper& makeInstall);

    /**
     * Assignment disabled.
     */
    MakeInstallTaskHelper& operator=(const MakeInstallTaskHelper& makeInstall);

};

}
}
}

#endif
