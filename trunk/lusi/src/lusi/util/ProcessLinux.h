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

#include <signal.h>

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
class ProcessLinuxCommunication;
}
}

namespace lusi {
namespace util {

/**
 * An implementation of Process using Linux system calls.
 * It makes use of read, write, select (and macros), dup2, execvp and signal
 * functions. It will likely work in any POSIX compliant system.
 *
 * When a process is executed, the parent process waits for a notification in
 * sExitPipe, which means that a child has exited. Meanwhile, notifies
 * observers about new data in stdout and stderr. start() has further
 * documentation about how process are executed.
 *
 * The static members of this class exist only to be used with the handler of
 * SIGCHLD signal, as the handler is pure C, and it must use static members as
 * objects aren't supported.
 *
 * Opening and closing the communication channels between parent and child
 * process is handled by another class, ProcessLinuxCommunication. Depending on
 * the selected communication type, pipes or pseudo terminals are created. It
 * takes care of assigning the right file descriptor to each channel (stdin,
 * stdout and stderr in parent and child).
 * As file descriptor are used, read, write, and select operations work doesn't
 * matter which communication type is being used.
 */
class ProcessLinux: public Process {
public:

    /**
     * Pipe to be notified when child process exits.
     * Is static, as it is used by SIGCHLD signal hanlder.
     */
    static int sExitPipe[2];



    /**
     * Creates a new ProcessLinux.
     * If no other ProcessLinux is currently alive, it sets the handler for
     * SIGCHLD signal and creates the sExitPipe to use to notify about an exited
     * child.
     * A ProcessLinuxCommunication is created for each instance of ProcessLinux,
     * although channels aren't opened yet.
     *
     * @param communicationType The type of the communication with the child
     *                          process.
     */
    ProcessLinux(CommunicationType communicationType);

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
     * be updated with the data in stdout and stderr concurrently. Data can also
     * be written to the process being executed while this method is running (in
     * fact, this is the only time when data can be written).
     *
     * In order to execute the process, a fork is made to execute it. The
     * input, output and error standard streams of the executed process are
     * redirected so they can be used in this process, the parent.
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

    /**
     * Writes the data as a string in the standard input of this Process.
     *
     * @param data The data to be written.
     * @return True if the data was written, false otherwise.
     */
    virtual bool writeData(const std::string& data);

    /**
     * Returns the ProcessLinuxCommunication used to manage communication
     * channels.
     *
     * @return The ProcessLinuxCommunication used to manage communication
     *         channels.
     */
    ProcessLinuxCommunication* getProcessLinuxCommunication() {
        return mProcessLinuxCommunication;
    }

private:

    /**
     * Enumeration with the possible error types happened when trying to
     * execute the process.
     */
    enum ErrorType {
        communicationError,
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
    struct sigaction mOldSigChldSigAction;

    /**
     * The pid of the executed process.
     */
    pid_t mPid;

    /**
     * The ProcessLinuxCommunication to use to open and close the communication
     * channels.
     */
    ProcessLinuxCommunication* mProcessLinuxCommunication;



    /**
     * Sets the SIGCHLD handler.
     */
    void setupSigChldHandler();

    /**
     * Resets the SIGCHLD handler.
     */
    void resetSigChldHandler();

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
     * closeCommunicationChannels() in mProcessLinuxCommunication.
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
