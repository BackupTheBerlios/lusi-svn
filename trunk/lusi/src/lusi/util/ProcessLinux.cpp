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

#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#include "ProcessLinux.h"

using std::string;
using std::vector;

using namespace lusi::util;

//public:

ProcessLinux::ProcessLinux(): Process() {
}

ProcessLinux::~ProcessLinux() {
}

void ProcessLinux::start() throw (ProcessException) {
    if (pipe(mStdoutPipe) != 0 ||
            pipe(mStderrPipe) != 0 ||
            pipe(mExitPipe)) {
        closeCommunicationChannels();
        throw ProcessException("Could not create communication channels");
    }

    pid_t pid = fork();
    if (pid == 0) {
        //Executes the real process and waits for it to exit. When the real
        //process exits, mExitPipe is set with a value of ExitResult specifying
        //if it was a success or any problem happened.
        executeWaitingProcess();
    } else if (pid == -1) {
        closeCommunicationChannels();
        throw ProcessException("Could not fork process");
    }

    fd_set readFdSet;

    bool exited = false;
    while (!exited) {
        //I'm not sure why, but this code must be into the loop
        //If put outside it, sometimes the process exit notification isn't get
        //in select call
        int fds[3] = { mStdoutPipe[0], mStderrPipe[0], mExitPipe[0] };
        int maxFd = prepareFileDescriptorSet(&readFdSet, fds, 3);

        //TODO handle errors
        select(maxFd, &readFdSet, NULL, NULL, NULL);

        if (FD_ISSET(mStdoutPipe[0], &readFdSet)) {
            notifyReceivedStdout(readStringFromFileDescriptor(mStdoutPipe[0]));
        }

        if (FD_ISSET(mStderrPipe[0], &readFdSet)) {
            notifyReceivedStderr(readStringFromFileDescriptor(mStderrPipe[0]));
        }

        if (FD_ISSET(mExitPipe[0], &readFdSet)) {
            exited = true;
        }
    }

    sendPendingData();

    //Throws ProcessException and closes communication channels if any error
    //happened when executing the process
    checkExecutionErrors();

    closeCommunicationChannels();

    notifyProcessExited();
}

//private:

void ProcessLinux::closeCommunicationChannels() {
    close(mStdoutPipe[0]);
    close(mStdoutPipe[1]);
    close(mStderrPipe[0]);
    close(mStderrPipe[1]);
    close(mExitPipe[0]);
    close(mExitPipe[1]);
}

void ProcessLinux::exitChildProcess(char exitValue, int fd) {
    while (write(fd, &exitValue, 1) <= 0);

    exit(exitValue);
}

void ProcessLinux::executeWaitingProcess() {
    //Pipe for notifying a failure in the child execution
    int childExitPipe[2];
    if (pipe(childExitPipe) != 0) {
        exitChildProcess(pipeError, mExitPipe[1]);
    }

    pid_t pid = fork();
    if (pid == 0) {
        //Child process

        char** arguments = newCArguments();

        //Redirect stdout
        dup2(mStdoutPipe[1], 1);
        //Redirect stderr
        dup2(mStderrPipe[1], 2);

        //Prepare environment
        if (!mWorkingDirectory.empty()) {
            chdir(mWorkingDirectory.c_str());
        }

        execvp(arguments[0], arguments);

        exitChildProcess(executionError, childExitPipe[1]);
    } else if (pid == -1) {
        exitChildProcess(forkError, mExitPipe[1]);
    }

    while (waitpid(pid, 0, 0) <= 0);

    //Checks if child process could be executed
    close(childExitPipe[1]);
    char exitResult;
    if (read(childExitPipe[0], &exitResult, 1) > 0) {
        exitChildProcess(executionError, mExitPipe[1]);
    }

    exitChildProcess(success, mExitPipe[1]);
}

char** ProcessLinux::newCArguments() {
    char** arguments = static_cast<char **>(malloc((mArguments.size() + 1) *
                                                sizeof(char *)));

    for (int i=0; i<mArguments.size(); i++) {
        arguments[i] = static_cast<char *>(malloc((mArguments[i].size() + 1) *
                                                sizeof(char)));

        for (int j=0; j < mArguments[i].size(); j++) {
            arguments[i][j] = mArguments[i].c_str()[j];
        }
        arguments[i][mArguments[i].size()] = 0;
    }
    arguments[mArguments.size()] = 0;

    return arguments;
}

void ProcessLinux::deleteCArguments(char** arguments) {
    for (int i=0; arguments[i] != 0; i++) {
        free(arguments[i]);
    }
    free(arguments);
}

int ProcessLinux::prepareFileDescriptorSet(fd_set* fdSet, int fds[],
                        int fdsLength) {
    FD_ZERO(fdSet);
    int maxFd = 0;

    for (int i=0; i<fdsLength; i++) {
        FD_SET(fds[i], fdSet);

        if (fds[i] > maxFd) {
            maxFd = fds[i];
        }
    }

    maxFd++;

    return maxFd;
}

string ProcessLinux::readStringFromFileDescriptor(int fileDescriptor) const {
    string data;

    char buffer;

    int openFlags = fcntl(fileDescriptor, F_GETFL);
    fcntl(fileDescriptor, F_SETFL, openFlags | O_NONBLOCK);

    while (read(fileDescriptor, &buffer, 1) > 0) {
        data += buffer;
    }

    fcntl(fileDescriptor, F_SETFL, openFlags);

    return data;
}

void ProcessLinux::sendPendingData() {
    fd_set readFdSet;

    bool pendingStdout = true;
    bool pendingStderr = true;
    while (pendingStdout || pendingStderr) {
        int fds[2] = { mStdoutPipe[0], mStderrPipe[0] };
        int maxFd = prepareFileDescriptorSet(&readFdSet, fds, 2);

        //Inmediate exit from select
        timeval zeroTimeout = { 0l, 0l };
        //TODO handle errors
        select(maxFd, &readFdSet, NULL, NULL, &zeroTimeout);

        if (FD_ISSET(mStdoutPipe[0], &readFdSet)) {
            notifyReceivedStdout(readStringFromFileDescriptor(mStdoutPipe[0]));
            pendingStdout = true;
        } else {
            pendingStdout = false;
        }

        if (FD_ISSET(mStderrPipe[0], &readFdSet)) {
            notifyReceivedStderr(readStringFromFileDescriptor(mStderrPipe[0]));
            pendingStderr = true;
        } else {
            pendingStderr = false;
        }
    }
}

void ProcessLinux::checkExecutionErrors() throw (ProcessException) {
    char exitResult;
    read(mExitPipe[0], &exitResult, 1);

    if (exitResult != success) {
        closeCommunicationChannels();
        switch (exitResult) {
            case pipeError:
                throw ProcessException("Could not create pipes with child");
                break;
            case forkError:
                throw ProcessException("Could not fork process");
                break;
            case executionError:
                throw ProcessException("Could not execute process");
                break;
            default:
                throw ProcessException("Unknown error");
        }
    }
}
