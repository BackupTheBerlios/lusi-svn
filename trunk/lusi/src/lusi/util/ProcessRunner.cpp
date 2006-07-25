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

#include "ProcessRunner.h"

using std::string;

using namespace lusi::util;

ProcessRunner::ProcessRunner(Process* process /*= Process::newProcess()*/) {
    mProcess = process;
    mStdoutData = string("");
    mStderrData = string("");
    mProcessExitedNumber = 0;

    mProcess->attachObserver(this);
}

ProcessRunner::~ProcessRunner() {
    delete mProcess;
}

/*
inline void ProcessRunner::receivedStdout(Process* process,
                                          const string& data) {
    mStdoutData += data;
}

inline void ProcessRunner::receivedStderr(Process* process,
                                          const string& data) {
    mStderrData += data;
}

inline void ProcessRunner::processExited(Process* process) {
    mProcessExitedNumber++;
}

inline Process* ProcessRunner::getProcess() {
    return mProcess;
}

inline const std::string& ProcessRunner::getStdoutData() const {
    return mStdoutData;
}

inline const std::string& ProcessRunner::getStderrData() const {
    return mStderrData;
}

inline int ProcessRunner::getProcessExitedNumber() const {
    return mProcessExitedNumber;
}
*/
