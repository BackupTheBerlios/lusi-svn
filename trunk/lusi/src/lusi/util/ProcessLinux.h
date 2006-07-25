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

#ifndef LUSI_UTIL_PROCESSLINUX_H
#define LUSI_UTIL_PROCESSLINUX_H

#include <lusi/util/Process.h>

namespace lusi {
namespace util {

/**
 * An implementation of Process using Linux system calls.
 * It makes use of read, write, select (and macros), dup2, execvp and pipe.
 *
 * To execute a process, an auxiliar process is made which waits for the
 * executed process to finish and then notifies the parent process. The parent
 * process waits for the notification and, meanwhile, notifies observers about
 * new data in stdout and stderr. start() and executeWaitingProcess() have
 * further documentation about how process are executed.
 */
class ProcessLinux: public Process {
public:

    /**
     * Creates a new ProcessLinux.
     */
    ProcessLinux();

    /**
     * Destroys this ProcessLinux.
     */
    ~ProcessLinux();

    /**
     * Starts this process.
     *
     * In order to execute the process, two forks are made. One for the process
     * that will wait for the real process to end, and another for the real
     * process. The output of the real process is redirected to the process
     * which notifies about changes in stdout and stderr.
     *
     * This process, the parent process of the waiting process, is the one that
     * takes into account notify the observers about changes in stdout, stderr
     * and the exit of the real process.
     *
     * If the real process couldn't be executed, a ProcessException is thrown
     * with a message explaining the problem occured.
     *
     * @throw ProcessException If the process couldn't be executed.
     *
     * @see executeWaitingProcess()
     */
    virtual void start() throw (ProcessException);

private:

    /**
     * Enumeration with the possible exit values for the executed process.
     */
    enum ExitResult {
        success,
        pipeError,
        forkError,
        executionError
    };

    /**
     * Pipe to get executed process stdout.
     */
    int mStdoutPipe[2];

    /**
     * Pipe to get executed process stderr.
     */
    int mStderrPipe[2];

    /**
     * Pipe to be notified when child process exites.
     */
    int mExitPipe[2];



    /**
     * Closes all the pipes.
     */
    void closeCommunicationChannels();

    /**
     * Exits a child process with the specified exitValue, writing it to the
     * specified file descriptor.
     *
     * @param exitValue The exit value for the process.
     * @param fd The file descriptor to write the exit value to.
     */
    void exitChildProcess(char exitValue, int fd);

    /**
     * Executes the code in the waiting process.
     * When starting a process, it's forked. The child process is the waiting
     * process. That process will also fork to execute the real process. Then,
     * the waiting process will wait for the real process to finish.
     *
     * Once finished, the waiting process will notify with mExitPipe that the
     * real process finished, also specifying if some error happened when trying
     * to execute the real process.
     */
    void executeWaitingProcess();

    /**
     * Returns the arguments list as a char** to be used with C functions.
     * The returned arguments must be freed using deleteCArguments(char**).
     *
     * @return The arguments list as a char**.
     */
    char** newCArguments();

    /**
     * Frees the memory allocated by newCArguments in arguments.
     *
     * @param arguments The arguments list returned by newCArguments()
     */
    void deleteCArguments(char** arguments);

    /**
     * Prepares the file descriptor set to be used with the specified file
     * descriptors.
     * The file descriptor set is cleaned and each file descriptor in the list
     * is added to the set. Moreover, the highest file descriptor plus one is
     * returned to be used in select() statements.
     *
     * @param fdSet The file descriptors set to be prepared.
     * @param fds An array containing the file descriptors to add to the set.
     * @param fdsLength The length of the array.
     * @return The highest file descriptor plus one.
     */
    int prepareFileDescriptorSet(fd_set* fdSet, int fds[], int fdsLength);

    /**
     * Reads the file descriptor and returns its content as a string.
     * It reads the file descriptor until no more data is available for reading.
     *
     * @param fileDescriptor The file descriptor to read from.
     * @return A string containing the data read.
     */
    std::string readStringFromFileDescriptor(int fileDescriptor) const;

    /**
     * Sends all the data still pending in stdout and stderr pipes to the
     * observers.
     */
    void sendPendingData();

    /**
     * Checks the execution result using mExitPipe and, in case of error, throws
     * an exception with a message with information about the error.
     * Errors checked are only errors to execute the process, but not errors in
     * the process itself.
     * Before throwning the exception, communication channels are closed.
     *
     * @throw ProcessException If any problem happened in the execution of the
     *                         process.
     */
    void checkExecutionErrors() throw (ProcessException);

    /**
     * Copy constructor disabled.
     */
    ProcessLinux(const ProcessLinux& processLinux);

    /**
     * Assignment disabled.
     */
    ProcessLinux& operator=(const ProcessLinux& processLinux);

};

}
}

#endif
