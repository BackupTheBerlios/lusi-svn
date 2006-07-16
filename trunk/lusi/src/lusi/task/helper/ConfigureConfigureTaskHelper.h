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

#include <lusi/task/helper/TaskHelper.h>

namespace lusi {
namespace configuration {
class ConfigurationParametersSet;
}
}

namespace lusi {
namespace package {
class ResourceMap;
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
 * creates the files needed by the build system. It usually accept a set of
 * options that depends on each package.
 *
 * ResourceMaps that can be used with ConfigureConfigureTaskHelper are those
 * with an executable script "configure" in the base directory of the package.
 *
 * The configuration accepted includes all the parameters that the configure
 * script being used can accept.
 *
 * execute() invokes the configure script keeping track of the created files,
 * so they can be removed later using revert().
 */
class ConfigureConfigureTaskHelper: public TaskHelper {
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
     *
     * @return bool True if the ResourceMap contains a configure script.
     */
    virtual bool hasValidResourceMap();

    /**
     * Returns the parameters accepted by configure script.
     *
     * @return All the parameters accepted by configure script.
     * @todo How should parameters priority be set? And default values?
     */
    virtual lusi::configuration::ConfigurationParametersSet
                                            checkConfiguration();

    /**
     * Configures the package.
     * It invokes the configure script, keeping track of created files so they
     * can be removed if the Task needs to be reverted.
     */
    virtual void execute();

    /**
     * Reverts the configuration of the package.
     * Removes the files created by configure script.
     */
    virtual void revert();

protected:

private:

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
