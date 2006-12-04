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

#ifndef LUSI_UTIL_PROCESSRUNNER_H
#define LUSI_UTIL_PROCESSRUNNER_H

#include <lusi/util/Process.h>
#include <lusi/util/ProcessObserver.h>

namespace lusi {
namespace util {
class Process;
}
}

namespace lusi {
namespace util {

/**
 * @class ProcessRunner ProcessRunner.h lusi/util/ProcessRunner.h
 *
 * A wrapper class to run a Process.
 * The only utility of this class is run a Process and then get all the data
 * received in stdout and stderr at the same time.
 * It's useful when only the output of a Process is needed, for example, when
 * using GNU tools such as "wc".
 *
 * The Process must be initialized in the usual way (using getProcess to get it
 * if it wasn't set in the constructor) and then executed. Once executed, all
 * the data received can be got using getStdoutData() and getStderrData. The
 * Process used is deleted when the ProcessRunner is destroyed.
 */
class ProcessRunner: public ProcessObserver {
public:

    /**
     * Creates a new ProcessRunner.
     * If no Process is set, a new Process using pipe communication is created
     * and set.
     *
     * @param process The Process to run, or a default Process if none was set.
     */
    ProcessRunner(Process* process =
                            Process::newProcess(Process::PipeCommunication));

    /**
     * Destroys this ProcessRunner.
     * It also deletes the Process.
     */
    virtual ~ProcessRunner();

    /**
     * Called when new data is received in stdout.
     * The data is added to mStdoutData.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStdout(Process* process, const std::string& data) {
        mStdoutData += data;
    }

    /**
     * Called when new data is received in stderr.
     * The data is added to mStderrData.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStderr(Process* process, const std::string& data) {
        mStderrData += data;
    }

    /**
     * Called when the process exits.
     * mProcessExited is incremented in 1.
     *
     * @param process A pointer to the process that exited.
     */
    virtual void processExited(Process* process) {
        mProcessExitedNumber++;
    }

    /**
     * Returns the Process to be run.
     */
    Process* getProcess() {
        return mProcess;
    }

    /**
     * Returns all the data received in stdout.
     *
     * @return All the data received in stdout.
     */
    const std::string& getStdoutData() const {
        return mStdoutData;
    }

    /**
     * Returns all the data received in stderr.
     *
     * @return All the data received in stderr.
     */
    const std::string& getStderrData() const {
        return mStderrData;
    }

    /**
     * Returns the number of times that processExited was called.
     *
     * @return The number of times that processExited was called.
     */
    int getProcessExitedNumber() const {
        return mProcessExitedNumber;
    }

private:

    /**
     * The Process to run.
     */
    Process* mProcess;

    /**
     * All the data received in stdout.
     */
    std::string mStdoutData;

    /**
     * All the data received in stderr.
     */
    std::string mStderrData;

    /**
     * Returns how many times processExited was called.
     */
    int mProcessExitedNumber;



    /**
     * Copy constructor disabled.
     */
    ProcessRunner(const ProcessRunner& processRunner);

    /**
     * Assignment disabled.
     */
    ProcessRunner& operator=(const ProcessRunner& processRunner);

};

}
}

#endif
