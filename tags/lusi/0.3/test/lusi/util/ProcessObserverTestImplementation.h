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

#ifndef LUSI_UTIL_PROCESSOBSERVERTESTIMPLEMENTATION_H
#define LUSI_UTIL_PROCESSOBSERVERTESTIMPLEMENTATION_H

#include <lusi/util/ProcessObserver.h>

namespace lusi {
namespace util {

/**
 * Implementation of ProcessObserver interface for testing purposes.
 * This class helps testing Process class non-abstract methods, as those are the
 * ones related to observers.
 */
class ProcessObserverTestImplementation: public ProcessObserver {
public:

    /**
     * Creates a new ProcessObserverTestImplementation.
     */
    ProcessObserverTestImplementation();

    /**
     * Destroys this ProcessObserverTestImplementation.
     */
    virtual ~ProcessObserverTestImplementation();

    /**
     * Called when new data is received in stdout.
     * The data is copied to mStdoutLastData.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStdout(Process* process, const std::string& data);

    /**
     * Called when new data is received in stderr.
     * The data is copied to mStderrLastData.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStderr(Process* process, const std::string& data);

    /**
     * Called when the process exits.
     * mProcessExited is incremented in 1.
     *
     * @param process A pointer to the process that exited.
     */
    virtual void processExited(Process* process);

    /**
     * Returns the last data received in stdout.
     *
     * @return The last data received in stdout.
     */
    const std::string& getStdoutLastData() const {
        return mStdoutLastNotification.data;
    }

    /**
     * Returns the last data received in stderr.
     *
     * @return The last data received in stderr.
     */
    const std::string& getStderrLastData() const {
        return mStderrLastNotification.data;
    }

    /**
     * Returns the last process that notified stdout.
     * mStdoutLastNotification.process is cleaned, so, if no new notification
     * is made, it'll return a null pointer.
     *
     * @return The last process that notified stdout.
     */
    Process* getStdoutLastProcess() {
        Process* process = mStdoutLastNotification.process;
        mStdoutLastNotification.process = 0;
        return process;
    }

    /**
     * Returns the last process that notified stderr.
     * mStderrLastNotification.process is cleaned, so, if no new notification
     * is made, it'll return a null pointer.
     *
     * @return The last process that notified stderr.
     */
    Process* getStderrLastProcess() {
        Process* process = mStderrLastNotification.process;
        mStderrLastNotification.process = 0;
        return process;
    }

    /**
     * Returns all the data received in stdout.
     *
     * @return All the data received in stdout.
     */
    const std::string& getStdoutAllData() const {
        return mStdoutAllData;
    }

    /**
     * Returns all the data received in stderr.
     *
     * @return All the data received in stderr.
     */
    const std::string& getStderrAllData() const {
        return mStderrAllData;
    }

    /**
     * Returns the last process exited.
     * mLastProcessExited is cleaned, so, if no newprocess exits, it'll return
     * a null pointer.
     *
     * @return The last process exited.
     */
    Process* getLastProcessExited() {
        Process* process = mLastProcessExited;
        mLastProcessExited = 0;
        return process;
    }

    /**
     * Returns the number of times that processExited was called.
     *
     * @return The number of times that processExited was called.
     */
    int getProcessExitedNumber() const {
        return mProcessExitedNumber;
    }

    /**
     * Cleans all the received data and the number of times that processExited
     * was called.
     */
    void cleanData();

private:

    /**
     * Struct which contains a process and the data notified.
     */
    struct DataNotification {
        Process* process;
        std::string data;
    };

    /**
     * The last notification received in stdout.
     */
    DataNotification mStdoutLastNotification;

    /**
     * The last notification received in stderr.
     */
    DataNotification mStderrLastNotification;

    /**
     * All the data received in stdout.
     */
    std::string mStdoutAllData;

    /**
     * All the data received in stderr.
     */
    std::string mStderrAllData;

    /**
     * Returns the last process exited.
     */
    Process* mLastProcessExited;

    /**
     * Returns how many times processExited was called.
     */
    int mProcessExitedNumber;

};

}
}

#endif
