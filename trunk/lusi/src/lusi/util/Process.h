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

#ifndef LUSI_UTIL_PROCESS_H
#define LUSI_UTIL_PROCESS_H

#include <string>
#include <vector>

#include <lusi/util/ProcessException.h>

namespace lusi {
namespace util {
class ProcessObserver;
}
}

namespace lusi {
namespace util {

/**
 * @class Process Process.h lusi/util/Process.h
 *
 * A Process that can be executed.
 * This class abstracts the use of low level calls to execute a process.
 *
 * Objects implementing ProcessObserver interface can be registered with a
 * Process, so they'll be notified each time new data is received in stdout or
 * stderr, or when the process exits. No assumptions should be made about the
 * contents of the data (like that all the notified data ends with a new
 * line).
 *
 * Moreover, this class is abstract, so different implementations can be made.
 * This was due to the initial intended internal use of KDELibs class KProcess
 * that, finally, wasn't used.
 * But this approach easies the possibility to port LUSI to different systems as
 * the interface used by the library won't change, only the implementations
 * used, so that's why it was kept.
 *
 * It also follows Factory Method Design Pattern, so new Process can be get
 * through newProcess() static method. It takes care of using the right
 * implementation.
 *
 * When deriving from this class, not only abstract methods must be implemented.
 * Also, the notifier methods must be called when needed.
 */
class Process {
public:

    /**
     * Returns a new Process.
     * The implementation of the Process returned will depend on the available
     * implementations. This method takes care of creating a new object of the
     * needed class.
     * The returned Process must be deleted when it's no longer needed.
     * This method follows Factory Method Design Pattern.
     *
     * @return A Process implementation.
     */
    static Process* newProcess();

    /**
     * Destroys this Process.
     */
    virtual ~Process();

    /**
     * Starts this process.
     * The ProcessException are refered to problems when trying to execute the
     * process (like a command not found), not errors in the process itself
     * (like if a process is executed but finishes with an error code different
     * to 0).
     *
     * Must be implemented in derived classes.
     *
     * @throw ProcessException If the process couldn't be executed.
     */
    virtual void start() throw (ProcessException) = 0;

    /**
     * Returns the list of arguments of this Process.
     * The first element is the executable name (or the full path to it), and
     * later elements all the needed arguments.
     * The arguments are set using operator<<(std::string)
     *
     * @return The list of arguments of this Process.
     */
    const std::vector<std::string>& getArguments() const {
        return mArguments;
    }

    /**
     * Returns the current working directory of this Process.
     *
     * @return The current working directory of this Process.
     */
    const std::string& getWorkingDirectory() const {
        return mWorkingDirectory;
    }

    /**
     * Sets the current working directory of this Process.
     * This function must be called before starting this Process.
     *
     * @param directory The directory to set the working directory to.
     */
    void setWorkingDirectory(const std::string& workingDirectory) {
        mWorkingDirectory = workingDirectory;
    }

    /**
     * Adds a new observer to be notified when an update happens in this
     * Process.
     * If the observer was already added, it's not added again.
     * All the updates (received stdout, received stderr and process exited) are
     * notified.
     *
     * @param processObserver The ProcessObserver to add.
     */
    void attachObserver(ProcessObserver* processObserver);

    /**
     * Removes an observer, so it will no longer be notified when an update
     * happens in this Process.
     *
     * @param processObserver The ProcessObserver to remove.
     */
    void detachObserver(ProcessObserver* processObserver);

    /**
     * Sets the executable or adds a new argument to the process to be executed.
     * The executable and the arguments list must be added using this method.
     * The first call must set the executable name (or the full path to it), and
     * later calls all the needed arguments.
     * Empty arguments are ignored.
     *
     * @param arg The executable to set or argument to add.
     * @return This Process instance.
     */
    Process& operator<<(const std::string& argument);

protected:

    /**
     * The executable and arguments list.
     * First element is the executable. The others are the arguments.
     */
    std::vector<std::string> mArguments;

    /**
     * Working directory for the process.
     */
    std::string mWorkingDirectory;



    /**
     * Creates a new Process.
     * Protected to avoid classes other than derived to create Process
     * objects.
     */
    Process();

    /**
     * Notifies all the observers about a received stdout.
     *
     * @param data The data received.
     */
    void notifyReceivedStdout(const std::string& data);

    /**
     * Notifies all the observers about a received stderr.
     *
     * @param data The data received.
     */
    void notifyReceivedStderr(const std::string& data);

    /**
     * Notifies all the observers that the process exited.
     */
    void notifyProcessExited();

private:

    /**
     * A vector containing all the ProcessObserver registered.
     */
    std::vector<ProcessObserver*> mProcessObservers;



    /**
     * Copy constructor disabled.
     */
    Process(const Process& process);

    /**
     * Assignment disabled.
     */
    Process& operator=(const Process& process);

};

}
}

#endif
