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

#include <termios.h>

#include "SuProcessLinuxConverser.h"
#include "ProcessLinux.h"
#include "ProcessLinuxCommunication.h"

using std::string;

using namespace lusi::util;

//public:

SuProcessLinuxConverser::SuProcessLinuxConverser(
                            SuProcessLinux* suProcessLinux):
                ProcessObserver() {
    mSuProcessLinux = suProcessLinux;
    mPasswordSent = false;
}

SuProcessLinuxConverser::~SuProcessLinuxConverser() {
}

void SuProcessLinuxConverser::receivedStdout(Process* process,
                                             const string& data) {
    if (mSuProcessLinux->mStateType ==
                SuProcessLinux::ExecuteCurrentUserState ||
            mSuProcessLinux->mStateType ==
                SuProcessLinux::ExecuteSwitchedUserState) {
        mSuProcessLinux->notifyReceivedStdout(data);
    }
}

void SuProcessLinuxConverser::receivedStderr(Process* process,
                                             const string& data) {
    if (mSuProcessLinux->mStateType == SuProcessLinux::SwitchingUserState &&
            mPasswordSent && data == "\n") {
        mSuProcessLinux->mStateType = SuProcessLinux::ExecuteSwitchedUserState;
        return;
    } else {
        mStderrData += data;
    }

    if (mSuProcessLinux->mStateType ==
                SuProcessLinux::ExecuteCurrentUserState ||
            mSuProcessLinux->mStateType ==
                SuProcessLinux::ExecuteSwitchedUserState) {
        mSuProcessLinux->notifyReceivedStderr(data);
    } else if (isPasswordPrompt(data)) {
        mStderrData = "";
        waitEcho();
        mSuProcessLinux->mProcessLinux->writeData(mSuProcessLinux->mPassword);
        mSuProcessLinux->mProcessLinux->writeData("\n");
        mPasswordSent = true;
    }
}

void SuProcessLinuxConverser::processExited(Process* process) {
    if (mSuProcessLinux->mStateType ==
                SuProcessLinux::ExecuteCurrentUserState ||
            mSuProcessLinux->mStateType ==
                SuProcessLinux::ExecuteSwitchedUserState) {
        mSuProcessLinux->notifyProcessExited();
    }
}

//private:

//The following regular expression was got from kdelibs/kdesu/su.cpp
bool SuProcessLinuxConverser::isPasswordPrompt(const string& line) {
    int j = 0, colon = 0;
    for (int i = 0; i<line.size(); ++i) {
        if (line[i] == ':') {
            j = i;
            ++colon;
            continue;
        }
        if (line[i] != ' ' && line[i] != '\t') {
            ++j;
        }
    }

    return colon == 1 && line[j] == ':';
}

void SuProcessLinuxConverser::waitEcho() {
    int slave = mSuProcessLinux->mProcessLinux->getProcessLinuxCommunication()->
                    getChildStdin();

    struct termios tio;
    bool finished = false;
    while (!finished) {
        tcgetattr(slave, &tio);

        if (tio.c_lflag & ECHO) {
            waitMiliseconds(10);
        } else {
            finished = true;
        }
    }
}

void SuProcessLinuxConverser::waitMiliseconds(int miliseconds) {
    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 1000 * miliseconds;

    select(0, 0L, 0L, 0L, &timeout);
}
