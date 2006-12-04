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

#ifndef LUSI_TASK_HELPER_TASKHELPERUSINGMAKE_H
#define LUSI_TASK_HELPER_TASKHELPERUSINGMAKE_H

#include <lusi/task/helper/TaskHelperUsingProcess.h>

namespace lusi {
namespace util {
class LocalUrl;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * @class TaskHelperUsingMake TaskHelperUsingMake.h \
 * lusi/task/helper/TaskHelperUsingMake.h
 *
 * Base TaskHelper using make command.
 * This class provides the base implementation for those TaskHelpers which use
 * make command to be executed. This class extends TaskHelperUsingProcess.
 *
 * Resources are valid if they contain a "Makefile" file in the directory of
 * the package. It also handles redirecting the output in stderr to notify
 * warnings instead of errors when needed (as make outputs warnings to stderr).
 * No configuration is used, although it can be overriden in derived classes.
 *
 * Derived classes must implement getProcess() to, at least, create the Process
 * and set the needed arguments in it (including the make command) to be
 * executed. However, more operations can be done in that method if needed.
 */
class TaskHelperUsingMake: public TaskHelperUsingProcess {
public:

    /**
     * Destroys this TaskHelperUsingMake.
     */
    virtual ~TaskHelperUsingMake();

    /**
     * Returns true if the resource files contain a Makefile to be executed by
     * make command.
     * The "Makefile" is searched in the directory of the package. If the
     * resources don't contain the Makefile, but it does exist in the
     * directory, it also returns true.
     *
     * @return True if the resources (or the actual directory) contains
     *         a valid Makefile.
     * @todo Check for targets such as install in Makefile?
     */
    virtual bool hasValidResources();

    /**
     * Called when new data is received in stderr.
     * Warnings are sent to stderr, so before notifying the TaskLogger, it is
     * checked if the string "warning:" is in the data received, and if that's
     * the case, it's notified to warning instead of error.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStderr(lusi::util::Process* process,
                                const std::string& data);

protected:

    /**
     * The LocalUrl with the base directory of the package.
     * This base directory contains all the files and subdirectories which will
     * be installed.
     */
    lusi::util::LocalUrl* mPackageDirectory;

    /**
     * Stores the received data in stderr.
     * The data stored is only temporal and it's removed when a complete line is
     * available.
     * This attribute is used only in receivedStderr(Process*, const string&).
     *
     * @see receivedStderr(Process*, const string&)
     */
    std::string mReceivedStderrData;



    /**
     * Creates a new TaskHelperUsingMake.
     * The package directory is the first ConfigurationParameterLocalUrl in the
     * resource files.
     * If there's no ConfigurationParameterLocalUrl, or the first it's not a
     * directory, an empty LocalUrl is used.
     * No checks about, for example, more than one package directory, are made.
     *
     * @param name The name of this TaskHelperUsingMake.
     * @param task The Task to help.
     */
    TaskHelperUsingMake(const std::string& name, lusi::task::Task* task);

private:

    /**
     * Copy constructor disabled.
     */
    TaskHelperUsingMake(const TaskHelperUsingMake& taskHelperUsingMake);

    /**
     * Assignment disabled.
     */
    TaskHelperUsingMake& operator=(
                        const TaskHelperUsingMake& taskHelperUsingMake);

};

}
}
}

#endif
