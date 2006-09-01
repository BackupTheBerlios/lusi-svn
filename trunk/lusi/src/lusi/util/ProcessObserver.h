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

#ifndef LUSI_UTIL_PROCESSOBSERVER_H
#define LUSI_UTIL_PROCESSOBSERVER_H

#include <string>

#include <lusi/util/Process.h>

namespace lusi {
namespace util {

/**
 * @class ProcessObserver ProcessObserver.h lusi/util/ProcessObserver.h
 *
 * Interface to observe updates in the execution of a Process.
 * The updates observed can be new data sent by stdout or stderr, or the Process
 * exiting.
 * Each update type has its own method. All the methods receive, at least, the
 * Process that had suffered the update.
 */
class ProcessObserver {
public:

    /**
     * Destroys this ProcessObserver.
     */
    virtual ~ProcessObserver() {
    }

    /**
     * Called when new data is received in stdout.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStdout(Process* process, const std::string& data) = 0;

    /**
     * Called when new data is received in stderr.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStderr(Process* process, const std::string& data) = 0;

    /**
     * Called when the process exits.
     *
     * @param process A pointer to the process that exited.
     */
    virtual void processExited(Process* process) = 0;

protected:

    /**
     * Creates a new ProcessObserver.
     * Protected to avoid classes other than derived to create ProcessObserver
     * objects.
     */
    ProcessObserver() {
    }

private:

    /**
     * Copy constructor disabled.
     */
    ProcessObserver(const ProcessObserver& processObserver);

    /**
     * Assignment disabled.
     */
    ProcessObserver& operator=(const ProcessObserver& processObserver);

};

}
}

#endif
