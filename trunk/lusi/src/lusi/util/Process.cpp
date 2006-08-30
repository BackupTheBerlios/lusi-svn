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

#include <algorithm>

#include "Process.h"
#include "ProcessObserver.h"
#include "ProcessLinux.h"

using std::string;
using std::vector;

using namespace lusi::util;

//public:

Process* Process::newProcess(CommunicationType communicationType) {
    return new ProcessLinux(communicationType);
}

Process::~Process() {
}

/*
inline const vector<string>& Process::getArguments() {
    return mArguments;
}
*/

std::string Process::getArgumentsAsString() const {
    string argumentsAsString("");

    if (mArguments.size() > 0) {
        int i=0;
        for (; i<mArguments.size()-1; ++i) {
            argumentsAsString += mArguments[i] + " ";
        }
        argumentsAsString += mArguments[i];
    }

    return argumentsAsString;
}

/*
inline const string& Process::getWorkingDirectory() const {
    return mWorkingDirectory;
}

inline void Process::setWorkingDirectory(const string& workingDirectory) {
    mWorkingDirectory = workingDirectory;
}
*/

void Process::attachObserver(ProcessObserver* processObserver) {
    if (find(mProcessObservers.begin(), mProcessObservers.end(),
                    processObserver) != mProcessObservers.end()) {
        return;
    }

    mProcessObservers.push_back(processObserver);
}

void Process::detachObserver(ProcessObserver* processObserver) {
    vector<ProcessObserver*>::iterator iterator =
                    find(mProcessObservers.begin(), mProcessObservers.end(),
                         processObserver);

    if (iterator != mProcessObservers.end()) {
        mProcessObservers.erase(iterator);
    }
}

Process& Process::operator<<(const string& argument) {
    if (!argument.empty()) {
        mArguments.push_back(argument);
    }
    return *this;
}

//protected:

Process::Process(CommunicationType communicationType) {
    mCommunicationType = communicationType;

    mArguments = vector<string>();
    mWorkingDirectory = string();
    mProcessObservers = vector<ProcessObserver*>();
}

void Process::notifyReceivedStdout(const string& data) {
    vector<ProcessObserver*>::iterator it;
    for (it = mProcessObservers.begin(); it != mProcessObservers.end(); ++it) {
        (*it)->receivedStdout(this, data);
    }
}

void Process::notifyReceivedStderr(const string& data) {
    vector<ProcessObserver*>::iterator it;
    for (it = mProcessObservers.begin(); it != mProcessObservers.end(); ++it) {
        (*it)->receivedStderr(this, data);
    }
}

void Process::notifyProcessExited() {
    vector<ProcessObserver*>::iterator it;
    for (it = mProcessObservers.begin(); it != mProcessObservers.end(); ++it) {
        (*it)->processExited(this);
    }
}
