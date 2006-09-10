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
#include <unistd.h>
#include <sys/wait.h>

#include "ProcessLinux.h"
#include "ProcessLinuxCommunication.h"

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

ProcessLinux::ProcessLinux(CommunicationType communicationType):
                Process(communicationType) {
    if (!sReferenceCount) {
        if (pipe(sExitPipe) != 0) {
            abort();
        }
        setupSigChldHandler();
    }
    ++sReferenceCount;

    mPid = 0;
    mProcessLinuxCommunication = ProcessLinuxCommunication::
                        newProcessLinuxCommunication(communicationType);
    mRunning = false;
    mExecutionError = false;
    mStatus = 0;
}

ProcessLinux::~ProcessLinux() {
    delete mProcessLinuxCommunication;
    if (mPid > 0 && !kill(mPid, 0)) {
        kill(mPid, SIGKILL);
    }

    --sReferenceCount;
    if (!sReferenceCount) {
        resetSigChldHandler();
        close(sExitPipe[0]);
        close(sExitPipe[1]);
    }
}

void ProcessLinux::start() throw (ProcessException) {
    mRunning = true;
    mExecutionError = false;

    //Pipe for notifying a failure in the child execution
    int childExitPipe[2];

    if (pipe(childExitPipe) != 0) {
        // childExitPipe doesn't need to be closed, as it wasn't opened
        handleExecutionError(communicationError);
    }
    try {
        mProcessLinuxCommunication->openCommunicationChannels();
    } catch (OpenCommunicationChannelsException e) {
        handleExecutionError(communicationError);
    }
    //Used only to shorten the access to the variables
    int childStdin = mProcessLinuxCommunication->getChildStdin();
    int childStdout = mProcessLinuxCommunication->getChildStdout();
    int childStderr = mProcessLinuxCommunication->getChildStderr();
    int parentStdin = mProcessLinuxCommunication->getParentStdin();
    int parentStdout = mProcessLinuxCommunication->getParentStdout();
    int parentStderr = mProcessLinuxCommunication->getParentStderr();

    mPid = fork();
    if (mPid == 0) {
        //Child process

        char** arguments = newCArguments();

        //Redirect stdin
        dup2(childStdin, 0);
        //Redirect stdout
        dup2(childStdout, 1);
        //Redirect stderr
        dup2(childStderr, 2);

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
    } else if (mPid == -1) {
        handleExecutionError(forkError);
    }

    fd_set readFdSet;

    bool exited = false;
    while (!exited) {
        //I'm not sure why, but this code must be into the loop
        //If put outside it, sometimes the process exit notification isn't got
        //in select call
        int fds[3] = { parentStdout, parentStderr, sExitPipe[0] };
        int maxFd = prepareFileDescriptorSet(&readFdSet, fds, 3);

        while (select(maxFd, &readFdSet, NULL, NULL, NULL) == -1);

        if (FD_ISSET(parentStdout, &readFdSet)) {
            notifyReceivedStdout(readStringFromFileDescriptor(parentStdout));
        }

        if (FD_ISSET(parentStderr, &readFdSet)) {
            notifyReceivedStderr(readStringFromFileDescriptor(parentStderr));
        }

        if (FD_ISSET(sExitPipe[0], &readFdSet)) {
            if (waitpid(mPid, &mStatus, WNOHANG) == mPid) {
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

    mProcessLinuxCommunication->closeCommunicationChannels();

    notifyProcessExited();

    mRunning = false;
}

bool ProcessLinux::writeData(const string& data) {
    //Used only to shorten the access to the variable
    int parentStdin = mProcessLinuxCommunication->getParentStdin();

    char buffer;
    int writedSize;

    int i = 0;
    while (i < data.size()) {
        buffer = data[i];
        if ((writedSize = write(parentStdin, &buffer, 1)) <= 0) {
            if (writedSize == -1 && (errno == EBADF || errno == EINVAL ||
                                     errno == EPIPE)) {
                return false;
            }
        } else {
            ++i;
        }
    }

    return true;
}

bool ProcessLinux::normalExit() {
    return mPid != 0 && !mRunning && !mExecutionError && WIFEXITED(mStatus);
}

int ProcessLinux::getExitStatus() {
    return WEXITSTATUS(mStatus);
}

/*
ProcessLinuxCommunication* ProcessLinux::getProcessLinuxCommunication() {
    return mProcessLinuxCommunication;
}
*/

//private:

int ProcessLinux::sReferenceCount = 0;

int ProcessLinux::sExitPipe[2];



void ProcessLinux::setupSigChldHandler() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);

    act.sa_handler = sigChldHandler;
    act.sa_flags = SA_NOCLDSTOP;

    sigaction(SIGCHLD, &act, &mOldSigChldSigAction);

    sigaddset(&act.sa_mask, SIGCHLD);
    //KProcessController code said:
    //"Make sure we don't block this signal. gdb tends to do that :-("
    //They're clever than me, so I'll follow their advice :)
    sigprocmask(SIG_UNBLOCK, &act.sa_mask, 0);
}

void ProcessLinux::resetSigChldHandler() {
    sigaction(SIGCHLD, &mOldSigChldSigAction, 0);
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
    //Used only to shorten the access to the variables
    int parentStdout = mProcessLinuxCommunication->getParentStdout();
    int parentStderr = mProcessLinuxCommunication->getParentStderr();

    fd_set readFdSet;

    bool pendingStdout = true;
    bool pendingStderr = true;
    while (pendingStdout || pendingStderr) {
        int fds[2] = { parentStdout, parentStderr };
        int maxFd = prepareFileDescriptorSet(&readFdSet, fds, 2);

        //Inmediate exit from select
        timeval zeroTimeout = { 0l, 0l };
        while (select(maxFd, &readFdSet, NULL, NULL, &zeroTimeout) == -1);

        if (FD_ISSET(parentStdout, &readFdSet)) {
            notifyReceivedStdout(readStringFromFileDescriptor(parentStdout));
            pendingStdout = true;
        } else {
            pendingStdout = false;
        }

        if (FD_ISSET(parentStderr, &readFdSet)) {
            notifyReceivedStderr(readStringFromFileDescriptor(parentStderr));
            pendingStderr = true;
        } else {
            pendingStderr = false;
        }
    }
}

void ProcessLinux::handleExecutionError(ErrorType errorType)
                                                    throw (ProcessException) {
    mProcessLinuxCommunication->closeCommunicationChannels();
    mRunning = false;
    mExecutionError = true;
    switch (errorType) {
        case communicationError:
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
