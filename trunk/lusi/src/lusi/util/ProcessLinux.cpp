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

extern "C" {
static void sigChldHandler(int signalNumber) {
    char dummy = 0;
    while (write(ProcessLinux::sExitPipe[1], &dummy, 1) <= 0);
}
}

//public:

ProcessLinux::ProcessLinux(): Process() {
    if (!sReferenceCount) {
        if (pipe(sExitPipe) != 0) {
            abort();
        }
        setupSigChldHandler();
    }
    ++sReferenceCount;

    pid = 0;
}

ProcessLinux::~ProcessLinux() {
    if (pid > 0 && !kill(pid, 0)) {
        kill(pid, SIGKILL);
    }

    --sReferenceCount;
    if (!sReferenceCount) {
        resetSigChldHandler();
        close(sExitPipe[0]);
        close(sExitPipe[1]);
    }
}

void ProcessLinux::start() throw (ProcessException) {
    //Pipe for notifying a failure in the child execution
    int childExitPipe[2];

    if (pipe(mStdoutPipe) != 0 ||
            pipe(mStderrPipe) != 0 ||
            pipe(childExitPipe) != 0) {
        //childExitPipe is the last, so there's no need to close it, because
        //it never was created (or it failed before creating it, or when
        //creating it)
        handleExecutionError(pipeError);
    }

    pid = fork();
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

        char errorBuffer = 1;
        while (write(childExitPipe[1], &errorBuffer, 1) <= 0);

        //Use _exit() instead of exit() to avoid destruction of static resources
        //of the library
        _exit(1);
    } else if (pid == -1) {
        handleExecutionError(forkError);
    }

    fd_set readFdSet;

    bool exited = false;
    while (!exited) {
        //I'm not sure why, but this code must be into the loop
        //If put outside it, sometimes the process exit notification isn't got
        //in select call
        int fds[3] = { mStdoutPipe[0], mStderrPipe[0], sExitPipe[0] };
        int maxFd = prepareFileDescriptorSet(&readFdSet, fds, 3);

        while (select(maxFd, &readFdSet, NULL, NULL, NULL) == -1);

        if (FD_ISSET(mStdoutPipe[0], &readFdSet)) {
            notifyReceivedStdout(readStringFromFileDescriptor(mStdoutPipe[0]));
        }

        if (FD_ISSET(mStderrPipe[0], &readFdSet)) {
            notifyReceivedStderr(readStringFromFileDescriptor(mStderrPipe[0]));
        }

        if (FD_ISSET(sExitPipe[0], &readFdSet)) {
            if (waitpid(pid, 0, WNOHANG) == pid) {
                exited = true;
                char dummy = 0;
                while (read(sExitPipe[0], &dummy, 1) != 1);

                //Checks if child process could be executed
                close(childExitPipe[1]);
                int readedSize;
                while ((readedSize = read(childExitPipe[0], &dummy, 1)) == -1);

                //If childExitPipe had data the process couldn't be executed
                if (readedSize > 0) {
                    close(childExitPipe[0]);
                    handleExecutionError(execvpError);
                }
                close(childExitPipe[0]);
            }
        }
    }

    sendPendingData();

    closeCommunicationChannels();

    notifyProcessExited();
}

//private:

int ProcessLinux::sReferenceCount = 0;

int ProcessLinux::sExitPipe[2];

struct sigaction ProcessLinux::oldSigChldSigAction;



void ProcessLinux::setupSigChldHandler() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);

    act.sa_handler = sigChldHandler;
    act.sa_flags = SA_NOCLDSTOP;

    sigaction(SIGCHLD, &act, &oldSigChldSigAction);

    sigaddset(&act.sa_mask, SIGCHLD);
    //KProcessController code said:
    //Make sure we don't block this signal. gdb tends to do that :-(
    //They're clever than me, so I'll follow their advice :)
    sigprocmask(SIG_UNBLOCK, &act.sa_mask, 0);
}

void ProcessLinux::resetSigChldHandler() {
    sigaction(SIGCHLD, &oldSigChldSigAction, 0);
}

void ProcessLinux::closeCommunicationChannels() {
    close(mStdoutPipe[0]);
    close(mStdoutPipe[1]);
    close(mStderrPipe[0]);
    close(mStderrPipe[1]);
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

    int readedSize;
    while ((readedSize = read(fileDescriptor, &buffer, 1)) > 0 ||
           (readedSize == -1 && errno == EINTR)) {
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
        while (select(maxFd, &readFdSet, NULL, NULL, &zeroTimeout) == -1);

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

void ProcessLinux::handleExecutionError(ErrorType errorType)
                                                    throw (ProcessException) {
    closeCommunicationChannels();
    switch (errorType) {
        case pipeError:
            throw ProcessException("Could not create communication channels");
            break;
        case forkError:
            throw ProcessException("Could not fork process");
            break;
        case execvpError:
            throw ProcessException("Could not execute process");
            break;
        default:
            throw ProcessException("Unknown error");
    }
}
