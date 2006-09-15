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

#include <fcntl.h>
#include <stropts.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "PtyProcessLinuxCommunication.h"

using namespace lusi::util;

//public:

PtyProcessLinuxCommunication::PtyProcessLinuxCommunication():
            ProcessLinuxCommunication() {
    mStdinStdoutMaster = -1;
    mStdinStdoutSlave = -1;
    mStderrMaster = -1;
    mStderrSlave = -1;
}

PtyProcessLinuxCommunication::~PtyProcessLinuxCommunication() {
}

void PtyProcessLinuxCommunication::openCommunicationChannels()
                                throw (OpenCommunicationChannelsException) {
    ProcessLinuxCommunication::openCommunicationChannels();

    openPtyPair(mStdinStdoutMaster, mStdinStdoutSlave);
    openPtyPair(mStderrMaster, mStderrSlave);

    preparePtySlave(mStdinStdoutSlave);
    preparePtySlave(mStderrSlave);

    mChildStdin = mStdinStdoutMaster;
    mChildStdout = mStdinStdoutSlave;
    mChildStderr = mStderrSlave;
    mParentStdin = mStdinStdoutSlave;
    mParentStdout = mStdinStdoutMaster;
    mParentStderr = mStderrMaster;
}

void PtyProcessLinuxCommunication::closeCommunicationChannels() {
    if (!mOpenCommunicationChannels) {
        return;
    }

    close(mStdinStdoutSlave);
    close(mStdinStdoutMaster);
    close(mStderrSlave);
    close(mStderrMaster);

    ProcessLinuxCommunication::closeCommunicationChannels();
}

//private:

void PtyProcessLinuxCommunication::openPtyPair(int& master, int& slave)
                                    throw (OpenCommunicationChannelsException) {
    int localMaster = getpt();
    if (localMaster < 0) {
        throw OpenCommunicationChannelsException(
                "Couldn't open the master pseudo-terminal device");
    }

    if (grantpt(localMaster) < 0) {
        close(localMaster);
        throw OpenCommunicationChannelsException(
                "Couldn't grant access to the slave pseudo-terminal device");
    }

    if (unlockpt(localMaster) < 0) {
        close(localMaster);
        throw OpenCommunicationChannelsException(
                "Couldn't unlock a pseudo-terminal master/slave pair");
    }


    char* name = ptsname(localMaster);
    if (name == NULL) {
        close(localMaster);
        throw OpenCommunicationChannelsException(
                "Couldn't get the name of the slave pseudo-terminal device");
    }

    int localSlave = open(name, O_RDWR | O_NOCTTY);
    if (localSlave < 0) {
        close(localMaster);
        throw OpenCommunicationChannelsException(
                "Couldn't open the slave pseudo-terminal device");
    }

    if (isastream(localSlave) && (ioctl(localSlave, I_PUSH, "ptem") < 0 ||
                                  ioctl(localSlave, I_PUSH, "ldterm") < 0)) {
        close(localSlave);
        close(localMaster);
        throw OpenCommunicationChannelsException(
                "Couldn't push ptem and ldterm modules");
    }

    master = localMaster;
    slave = localSlave;
    return;
}

void PtyProcessLinuxCommunication::preparePtySlave(int slave) {
    struct termios tio;
    //Slave is always a valid slave pty device, no errors can happen
    tcgetattr(slave, &tio);

    tio.c_oflag &= ~ONLCR;

    //The only error that can happen is EINTR (as the slave and the flags set
    //are always valid)
    while (tcsetattr(slave, TCSANOW, &tio) < 0);
}
