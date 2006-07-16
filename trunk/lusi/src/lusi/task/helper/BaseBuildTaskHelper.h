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

#ifndef LUSI_TASK_HELPER_BASEBUILDTASKHELPER_H
#define LUSI_TASK_HELPER_BASEBUILDTASKHELPER_H

#include <string>

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
 * @class BaseBuildTaskHelper BaseBuildTaskHelper.h \
 * lusi/task/helper/BaseBuildTaskHelper.h
 *
 * Base TaskHelper for BuildTask.
 * This class provides a default behaviour for those TaskHelpers that only need
 * to call an external command to do the build. This command should be returned
 * by buildCommand() method. Also, the clean command to revert the changes
 * should be returned by cleanCommand(). This class takes care of executing the
 * commands as needed. However, if execute() and revert() methods can be
 * redefined if this behaviour doesn't suit the needs of the derived class.
 *
 * Derived classes must define hasValidResourceMap() method, as this
 * method depends on the specific build system used. checkConfiguration()
 * returns an empty ConfigurationParametersSet, as most build systems don't
 * need parameters. It can also be redefined if the derived class needs it.
 */
class BaseBuildTaskHelper: public TaskHelper {
public:

    /**
     * Destroys this BaseBuildTaskHelper.
     */
    virtual ~BaseBuildTaskHelper();

    /**
     * Returns the generic configuration needed by BaseBuildTaskHelpers.
     * The default configuration is empty, as there are no generic parameters
     * needed for build systems, and some of them doesn't have even specific
     * parameters.
     *
     * @return Returns the Configuration needed by this TaskHelper.
     */
    virtual lusi::configuration::ConfigurationParametersSet
                                            checkConfiguration();

    /**
     * Builds the package.
     * The generic implementation for BuildTasks is invoke the command returned
     * by buildCommand().
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @see buildCommand()
     */
    virtual void execute();

    /**
     * Reverts the changes made when building the package.
     * The generic implementation for BuildTasks is invoke the command returned
     * by cleanCommand().
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @see cleanCommand()
     * @todo Create a default implementation such as deleting all the new files
     *       created building the package? Would need support of execute method
     *       to register in the configuration all the created files.
     */
    virtual void revert();

protected:

    /**
     * Creates a new BaseBuildTaskHelper.
     *
     * @param name The name of the BaseBuildTaskHelper.
     * @param task The task to help.
     */
    BaseBuildTaskHelper(const std::string& name, lusi::task::Task* task);

    /**
     * Returns the name of the build command to invoke to execute the
     * TaskHelper.
     * Must be implemented in derived classes.
     *
     * @return The build command to be invoked.
     * @todo If a derived class doesn't use default execute() method there's no
     *       need to redefine this method. However, being pure virtual, it must
     *       be redefined anyway. Make this method return an empty string? Move
     *       it and other default implementations to a derived class called
     *       DefaultBuildTaskHelper or something like that?
     */
    virtual std::string buildCommand() = 0;

    /**
     * Returns the name of the clean command to invoke to revert the changes
     * made executing this TaskHelper.
     * Must be implemented in derived classes.
     *
     * @return The clean command to be invoked.
     * @todo If a derived class doesn't use default revert() method there's no
     *       need to redefine this method. However, being pure virtual, it must
     *       be redefined anyway. Make this method return an empty string? Move
     *       it and other default implementations to a derived class called
     *       DefaultBuildTaskHelper or something like that?
     */
    virtual std::string cleanCommand() = 0;

private:

    /**
     * Copy constructor disabled.
     */
    BaseBuildTaskHelper(const BaseBuildTaskHelper& baseBuildTaskHelper);

    /**
     * Assignment disabled.
     */
    BaseBuildTaskHelper& operator=(
            const BaseBuildTaskHelper& baseBuildTaskHelper);

};

}
}
}

#endif
