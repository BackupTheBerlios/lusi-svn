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

#include "ProcessObserverTestImplementation.h"

using std::string;

using namespace lusi::util;

//public:

ProcessObserverTestImplementation::ProcessObserverTestImplementation():
                    ProcessObserver(),
                    mStdoutLastNotification(), mStderrLastNotification(),
                    mStdoutAllData(), mStderrAllData() {
    mLastProcessExited = 0;
    mProcessExitedNumber = 0;
}

ProcessObserverTestImplementation::~ProcessObserverTestImplementation() {
}

void ProcessObserverTestImplementation::receivedStdout(Process* process,
                                            const string& data) {
    mStdoutLastNotification.process = process;
    mStdoutLastNotification.data = data;
    mStdoutAllData += data;
}

void ProcessObserverTestImplementation::receivedStderr(Process* process,
                                            const string& data) {
    mStderrLastNotification.process = process;
    mStderrLastNotification.data = data;
    mStderrAllData += data;
}

void ProcessObserverTestImplementation::processExited(Process* process) {
    mLastProcessExited = process;
    mProcessExitedNumber++;
}

/*
inline const std::string& getStdoutLastData() const {
    return mStdoutLastNotification.data;
}

inline const std::string& getStderrLastData() const {
    return mStderrLastNotification.data;
}

const Process* getStdoutLastProcess() const {
    return mStdoutLastNotification.process;
}

const Process* getStderrLastProcess() const {
    return mStderrLastNotification.process;
}

inline const std::string& getStdoutAllData() const {
    return mStdoutAllData;
}

inline const std::string& getStderrAllData() const {
    return mStderrAllData;
}

Process* getLastProcessExited() {
    Process* process = mLastProcessExited;
    mLastProcessExited = 0;
    return process;
}

inline int getProcessExitedNumber() const {
    return mProcessExitedNumber;
}
*/

void ProcessObserverTestImplementation::cleanData() {
    mStdoutLastNotification = DataNotification();
    mStderrLastNotification = DataNotification();
    mStdoutAllData = string();
    mStderrAllData = string();
    mLastProcessExited = 0;
    mProcessExitedNumber = 0;
}
