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

#include <unistd.h>

#include "PipeProcessLinuxCommunication.h"

using namespace lusi::util;

//public:

PipeProcessLinuxCommunication::PipeProcessLinuxCommunication():
            ProcessLinuxCommunication() {
    if (!sReferenceCount) {
        setupSigPipeHandler();
    }
    ++sReferenceCount;
}

PipeProcessLinuxCommunication::~PipeProcessLinuxCommunication() {
    --sReferenceCount;
    if (!sReferenceCount) {
        resetSigPipeHandler();
    }
}

void PipeProcessLinuxCommunication::openCommunicationChannels()
                                throw (OpenCommunicationChannelsException) {
    ProcessLinuxCommunication::openCommunicationChannels();

    int stdinPipe[2], stdoutPipe[2], stderrPipe[2];
    if (pipe(stdinPipe) != 0 ||
            pipe(stdoutPipe) != 0 ||
            pipe(stderrPipe) != 0) {
        closeCommunicationChannels();
        throw OpenCommunicationChannelsException("Could not create pipes");
    }

    mChildStdin = stdinPipe[0];
    mChildStdout = stdoutPipe[1];
    mChildStderr = stderrPipe[1];
    mParentStdin = stdinPipe[1];
    mParentStdout = stdoutPipe[0];
    mParentStderr = stderrPipe[0];
}

void PipeProcessLinuxCommunication::closeCommunicationChannels() {
    if (!mOpenCommunicationChannels) {
        return;
    }

    close(mChildStdin);
    close(mChildStdout);
    close(mChildStderr);
    close(mParentStdin);
    close(mParentStdout);
    close(mParentStderr);

    ProcessLinuxCommunication::closeCommunicationChannels();
}

//private:

int PipeProcessLinuxCommunication::sReferenceCount = 0;



void PipeProcessLinuxCommunication::setupSigPipeHandler() {
    struct sigaction act;
    sigemptyset(&act.sa_mask);

    act.sa_handler = SIG_IGN;

    sigaction(SIGPIPE, &act, &oldSigPipeSigAction);
}

void PipeProcessLinuxCommunication::resetSigPipeHandler() {
    sigaction(SIGPIPE, &oldSigPipeSigAction, 0);
}
