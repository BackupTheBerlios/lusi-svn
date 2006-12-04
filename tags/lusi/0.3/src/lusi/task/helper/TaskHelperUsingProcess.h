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

#ifndef LUSI_TASK_HELPER_TASKHELPERUSINGPROCESS_H
#define LUSI_TASK_HELPER_TASKHELPERUSINGPROCESS_H

#include <string>

#include <lusi/task/helper/TaskHelper.h>
#include <lusi/util/ProcessObserver.h>

namespace lusi {
namespace task {
namespace helper {

/**
 * @class TaskHelperUsingProcess TaskHelperUsingProcess.h \
 * lusi/task/helper/TaskHelperUsingProcess.h
 *
 * Base TaskHelper using Process.
 * This class provides the base implementation for those TaskHelpers which rely
 * on external commands (such as tar, make...) to be executed. It gets a
 * Process (created in derived classes) and starts it, and also notifies the
 * TaskLogger when new data is received in stdout or stderr, and TaskProgress
 * both when the Process starts and when it finishes.
 *
 * Derived classes must implement getProcess() to, at least, create the Process
 * and set the needed arguments in it to be executed. However, more operations
 * can be done in that method if needed.
 */
class TaskHelperUsingProcess: public TaskHelper, lusi::util::ProcessObserver {
public:

    /**
     * Destroys this TaskHelperUsingProcess.
     */
    virtual ~TaskHelperUsingProcess();

    /**
     * Executes this TaskHelper.
     * The generic implementation is check for invalid configuration parameters
     * (with parent implementation), create a new Process using getProcess(),
     * and then execute it. That method must be implemented in derived classes.
     * Before starting the Process, but after preparing the execution, the
     * progress is set to 0.
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @throw ExecuteTaskHelperException If an error happened when executing the
     *                                   process.
     * @throws InvalidConfigurationException If the parameters are incomplete or
     *                                       invalid.
     * @see getProcess()
     */
    virtual void execute() throw (ExecuteTaskHelperException,
                            lusi::configuration::InvalidConfigurationException);

    /**
     * Called when new data is received in stdout.
     * Notifies the TaskLogger of the Task, using message type.
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStdout(lusi::util::Process* process,
                                const std::string& data);

    /**
     * Called when new data is received in stderr.
     * Notifies the TaskLogger of the Task, using error type.
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStderr(lusi::util::Process* process,
                                const std::string& data);

    /**
     * Called when the process exits.
     * Notifies the TaskProgress of the Task with a finished state.
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @param process A pointer to the process that exited.
     */
    virtual void processExited(lusi::util::Process* process);

protected:

    /**
     * Creates a new TaskHelperUsingProcess.
     *
     * @param name The name of this TaskHelperUsingProcess.
     * @param task The Task to help.
     */
    TaskHelperUsingProcess(const std::string& name, lusi::task::Task* task);

    /**
     * Creates the process and prepares it to be executed.
     * It must create the process and set all the arguments needed to execute
     * it. This method is called just before starting the Process, so apart
     * from setting the arguments, other operations can be made to prepare the
     * execution if needed.
     *
     * The process is deleted once it was executed, there's no need to delete it
     * in derived classes.
     *
     * Must be implemented in derived classes.
     *
     * @return process The Process to be executed.
     */
    virtual lusi::util::Process* getProcess() = 0;

    /**
     * Checks if an error happened when executing the process and throws an
     * exception in that case.
     * Default behaviour is throw an exception if the process was signalled or
     * if it finished normally but with errors.
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @param process The executed process.
     * @throw ExecuteTaskHelperException If an error happened when executing the
     *                                   process.
     */
    virtual void checkProcessExecutionErrors(
                    lusi::util::SmartPtr<lusi::util::Process> process) throw(
                                                ExecuteTaskHelperException);

private:

    /**
     * Copy constructor disabled.
     */
    TaskHelperUsingProcess(
            const TaskHelperUsingProcess& taskHelperUsingProcess);

    /**
     * Assignment disabled.
     */
    TaskHelperUsingProcess& operator=(
            const TaskHelperUsingProcess& taskHelperUsingProcess);

};

}
}
}

#endif
