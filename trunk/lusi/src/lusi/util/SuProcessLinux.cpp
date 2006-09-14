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

#include "SuProcessLinux.h"
#include "ProcessLinux.h"
#include "SuProcessLinuxConverser.h"
#include "User.h"

using std::string;

using namespace lusi::util;

//public:

SuProcessLinux::SuProcessLinux(): SuProcess(PtyCommunication) {
    mProcessLinux = 0;
    mStateType = FinishedState;
}

SuProcessLinux::~SuProcessLinux() {
    delete mProcessLinux;
}

void SuProcessLinux::start() throw (ProcessException, SuProcessException) {
    delete mProcessLinux;
    mProcessLinux = new ProcessLinux(PtyCommunication);
    SuProcessLinuxConverser suProcessLinuxConverser(this);

    if (mUserName == "" || mUserName == User::getCurrentUser().getName()) {
        for (uint i=0; i<mArguments.size(); ++i) {
            *mProcessLinux << mArguments[i];
        }
        mStateType = ExecuteCurrentUserState;
    } else {
        checkUserName();
        checkPassword();
        *mProcessLinux << "su" << "-c" << getArgumentsAsString() << "-l" <<
                          mUserName;
        mStateType = SwitchingUserState;
    }

    mProcessLinux->attachObserver(&suProcessLinuxConverser);
    mProcessLinux->start();

    mStateType = FinishedState;
}

bool SuProcessLinux::writeData(const string& data) {
    if (!mProcessLinux) {
        return false;
    }

    if (mStateType != ExecuteCurrentUserState ||
            mStateType != ExecuteSwitchedUserState) {
        return false;
    }

    return mProcessLinux->writeData(data);
}

bool SuProcessLinux::normalExit() {
    return mStateType == FinishedState && mProcessLinux != 0 &&
            mProcessLinux->normalExit();
}

int SuProcessLinux::getExitStatus() {
    return (normalExit())?mProcessLinux->getExitStatus():-1;
}

//private:

void SuProcessLinux::checkUserName() throw (SuProcessException) {
    if (!User(mUserName).exists()) {
        throw SuProcessException("Invalid user name: " + mUserName);
    }
}

void SuProcessLinux::checkPassword() throw (SuProcessException) {
    ProcessLinux* savedProcessLinux = mProcessLinux;
    mProcessLinux = new ProcessLinux(PtyCommunication);

    *mProcessLinux << "su" << "-c" << "echo -n" << "-l" << mUserName;

    mStateType = CheckPasswordState;
    SuProcessLinuxConverser suProcessLinuxConverser(this);
    mProcessLinux->attachObserver(&suProcessLinuxConverser);
    mProcessLinux->start();

    delete mProcessLinux;
    mProcessLinux = savedProcessLinux;

    if (suProcessLinuxConverser.getStderrData() != "\n") {
        throw SuProcessException("Invalid password");
    }
}
