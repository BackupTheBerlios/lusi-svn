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

#ifndef LUSI_TASK_HELPER_CONFIGURECONFIGURETASKHELPER_H
#define LUSI_TASK_HELPER_CONFIGURECONFIGURETASKHELPER_H

#include <lusi/task/helper/TaskHelperUsingProcess.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterMap;
}
}

namespace lusi {
namespace util {
class LocalUrl;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * Returns a new ConfigureConfigureTaskHelper.
 * Used to register ConfigureConfigureTaskHelpers with Task names.
 *
 * @param task The Task to help.
 * @return The new ConfigureConfigureTaskHelper created.
 * @see TaskHelperManager
 */
TaskHelper* createConfigureConfigureTaskHelper(lusi::task::Task* task);

/**
 * @class ConfigureConfigureTaskHelper ConfigureConfigureTaskHelper.h \
 * lusi/task/helper/ConfigureConfigureTaskHelper.h
 *
 * ConfigureTaskHelper for configure script.
 * This ConfigureTask implementation adds support for configure script. This
 * script is generally created automatically by GNU autoconf from some macros
 * specified in other files. When it's executed, it checks for dependencies and
 * creates the files needed by the build system. It usually accepts a set of
 * options that depends on each package.
 *
 * ResourceMaps that can be used with ConfigureConfigureTaskHelper are those
 * with an executable script "configure" in the base directory of the package.
 *
 * The configuration accepted includes all the parameters that the configure
 * script being used can accept.
 */
class ConfigureConfigureTaskHelper: public TaskHelperUsingProcess {
public:

    /**
     * Creates a new ConfigureConfigureTaskHelper.
     *
     * @param task The Task to help.
     */
    ConfigureConfigureTaskHelper(lusi::task::Task* task);

    /**
     * Destroys this ConfigureConfigureTaskHelper.
     */
    virtual ~ConfigureConfigureTaskHelper();

    /**
     * Returns True if the ResourceMap contains a configure script that can be
     * executed.
     * The script is searched in the directory of the package.
     *
     * @return bool True if the ResourceMap contains a configure script.
     */
    virtual bool hasValidResourceMap();

    /**
     * Inits the configuration parameters for this TaskHelper.
     * The configuration contains all the parameters accepted by configure
     * script.
     *
     * @todo implement configuration getting parameters from script
     */
    virtual void initConfigurationParameterMap();

protected:

    /**
     * Creates a new Process with PipeCommunication and sets the arguments and
     * the working directory to call configure script.
     *
     * @return The Process to be executed.
     */
    virtual lusi::util::Process* getProcess();

private:

    /**
     * The LocalUrl with the base directory of the package.
     * This base directory contains the configure script.
     */
    lusi::util::LocalUrl* mPackageDirectory;



    /**
     * Returns all the parameters for configure script in a string.
     * The parameters are got from the configuration. All the parameters that
     * were set are used. The returned string contains the parameters in the
     * format used by configure script.
     *
     * @return All the parameters for configure script in a string.
     */
    std::string getConfigureParameters(lusi::util::Process* process);

    /**
     * Returns the default prefix directory used in configure script.
     * If the default prefix can't be determined, "" is returned.
     *
     * This method will likely dissapear when a generic way to get the
     * parameters from the configure script is implemented.
     *
     * @return The default prefix directory used in configure script.
     */
    std::string getDefaultPrefix();

    /**
     * Copy constructor disabled.
     */
    ConfigureConfigureTaskHelper(
        const ConfigureConfigureTaskHelper& configureConfigureTaskHelper);

    /**
     * Assignment disabled.
     */
    ConfigureConfigureTaskHelper& operator=(
        const ConfigureConfigureTaskHelper& configureConfigureTaskHelper);

};

}
}
}

#endif
