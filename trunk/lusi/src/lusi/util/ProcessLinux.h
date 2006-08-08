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

extern "C" {
/**
 * Hanlder for SIGCHLD signal.
 * It simply writes a 0 in ProcessLinux::sExitPipe[1].
 */
static void sigChldHandler(int signalNumber);
}

namespace lusi {
namespace util {

/**
 * An implementation of Process using Linux system calls.
 * It makes use of read, write, select (and macros), dup2, execvp, pipe and
 * signal functions.
 *
 * When a process is executed, the parent process waits for a notification in
 * sExitPipe, which means that a child has exited. Meanwhile, notifies
 * observers about new data in stdout and stderr. start() has further
 * documentation about how process are executed.
 *
 * Tha static members of this class exist only to be used with the handler of
 * SIGCHLD signal, as the handler is pure C, and it must use static members as
 * objects aren't supported.
 */
class ProcessLinux: public Process {
public:

    /**
     * Pipe to be notified when child process exites.
     * Is static, as it is used by SIGCHLD signal hanlder.
     */
    static int sExitPipe[2];



    /**
     * Creates a new ProcessLinux.
     * If no other ProcessLinux is currently alive, it sets the handler for
     * SIGCHLD signal and creates the sExitPipe to use to notify about an
     * exited child.
     */
    ProcessLinux();

    /**
     * Destroys this ProcessLinux.
     * If no other ProcessLinux is currently alive, it resets the handler for
     * SIGCHLD signal and closes the sExitPipe used to notify about an exited
     * child.
     */
    ~ProcessLinux();

    /**
     * Starts this process.
     * This is a blocking call: the execution of the calling process, the
     * parent, won't continue until the process ends. However, notifiers will
     * be updated with the data in stdout and stderr concurrently.
     *
     * In order to execute the process, a fork is made to execute it. The
     * output of the executed process is redirected so it can be got in this
     * process, the parent.
     *
     * Parent process waits until the child has exited. It's notified through
     * sExitPipe by SIGCHLD signal handler.
     *
     * This process, the parent, is the one that takes into account notify the
     * observers about changes in stdout, stderr and the exit of the real
     * process.
     *
     * If the child process couldn't be executed, a ProcessException is thrown
     * with a message explaining the problem occured.
     *
     * @throw ProcessException If the child process couldn't be executed.
     */
    virtual void start() throw (ProcessException);

private:

    /**
     * Enumeration with the possible error types happened when trying to
     * execute the process.
     */
    enum ErrorType {
        pipeError,
        forkError,
        execvpError
    };

    /**
     * The number of ProcessLinux currently alive.
     */
    static int sReferenceCount;

    /**
     * Struct to store the SIGCHLD sigaction before it's modified to use
     * sigChldHandler.
     */
    static struct sigaction oldSigChldSigAction;

    /**
     * The pid of the executed process.
     */
    pid_t pid;

    /**
     * Pipe to get executed process stdout.
     */
    int mStdoutPipe[2];

    /**
     * Pipe to get executed process stderr.
     */
    int mStderrPipe[2];



    /**
     * Sets the SIGCHLD handler.
     */
    static void setupSigChldHandler();

    /**
     * Resets the SIGCHLD handler.
     */
    static void resetSigChldHandler();

    /**
     * Closes all the pipes.
     */
    void closeCommunicationChannels();

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
     * Closes the communication channels and throws an exception with a message
     * with information about the error.
     * Errors thrown are only errors when trying to execute the process, but
     * not errors in the process itself.
     * Before throwning the exception, communication channels are closed using
     * closeCommunicationChannels().
     *
     * @throw ProcessException A ProcessException with a message about the
     *                         error happened.
     */
    void handleExecutionError(ErrorType errorType) throw (ProcessException);

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
