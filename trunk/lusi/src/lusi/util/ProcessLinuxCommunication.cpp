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

#include "ProcessLinuxCommunication.h"
#include "PipeProcessLinuxCommunication.h"
#include "PtyProcessLinuxCommunication.h"

using namespace lusi::util;

//public:

ProcessLinuxCommunication*
ProcessLinuxCommunication::newProcessLinuxCommunication(
                                Process::CommunicationType communicationType) {
    switch (communicationType) {
        case Process::PipeCommunication:
            return new PipeProcessLinuxCommunication();
            break;
        case Process::PtyCommunication:
            return new PtyProcessLinuxCommunication();
            break;
        default:
            //Shouldn't happen... ;)
            return 0;
    }
}

ProcessLinuxCommunication::~ProcessLinuxCommunication() {
    if (mOpenCommunicationChannels) {
        closeCommunicationChannels();
    }
}

void ProcessLinuxCommunication::openCommunicationChannels()
                                    throw (OpenCommunicationChannelsException) {
    if (mOpenCommunicationChannels) {
        closeCommunicationChannels();
    }
    mOpenCommunicationChannels = true;
}

void ProcessLinuxCommunication::closeCommunicationChannels() {
    mOpenCommunicationChannels = false;
    mChildStdin = -1;
    mChildStdout = -1;
    mChildStderr = -1;
    mParentStdin = -1;
    mParentStdout = -1;
    mParentStderr = -1;
}

/*
inline int ProcessLinuxCommunication::getChildStdin() const {
    return mChildStdin;
}

inline int ProcessLinuxCommunication::getChildStdout() const {
    return mChildStdout;
}

inline int ProcessLinuxCommunication::getChildStderr() const {
    return mChildStderr;
}

inline int ProcessLinuxCommunication::getParentStdin() const {
    return mParentStdin;
}

inline int ProcessLinuxCommunication::getParentStdout() const {
    return mParentStdout;
}

inline int ProcessLinuxCommunication::getParentStderr() const {
    return mParentStderr;
}
*/

//protected:

ProcessLinuxCommunication::ProcessLinuxCommunication() {
    mOpenCommunicationChannels = false;
    mChildStdin = -1;
    mChildStdout = -1;
    mChildStderr = -1;
    mParentStdin = -1;
    mParentStdout = -1;
    mParentStderr = -1;
}
