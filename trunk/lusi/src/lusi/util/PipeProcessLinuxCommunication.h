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

#ifndef LUSI_UTIL_PIPEPROCESSLINUXCOMMUNICATION_H
#define LUSI_UTIL_PIPEPROCESSLINUXCOMMUNICATION_H

#include <signal.h>

#include "lusi/util/ProcessLinuxCommunication.h"

namespace lusi {
namespace util {

/**
 * Handles opening and closing communication channels between parent and child
 * process in Linux using pipes.
 * A pipe is created for each pair parent/child. Node 0 of each pipe is used
 * for reading, and node 1 for writing. So stdin node 0 is assigned to the
 * child and node 1 to the parent, and stdout and stderr node 0 is assigned to
 * the parent and node 1 to the child.
 */
class PipeProcessLinuxCommunication: public ProcessLinuxCommunication {
public:

    /**
     * Creates a new PipeProcessCommunication.
     */
    PipeProcessLinuxCommunication();

    /**
     * Destroys this PipeProcessLinuxCommunication.
     */
    virtual ~PipeProcessLinuxCommunication();

    /**
     * Opens the communication channels.
     * If the communication channels are already opened, it closes them and
     * opens new channels (so be careful when calling it twice).
     *
     * A pipe is created for each pair parent/child and the file descriptor of
     * each side of the pipes are assigned to the attributes.
     *
     * If any of the pipes couldn't be created, an Exception is thrown. All the
     * already created pipes are closed and the attributes set to -1.
     *
     * @throw OpenCommunicationChannelsException If the pipes couldn't be
     *                                           created.
     */
    virtual void openCommunicationChannels()
                                    throw (OpenCommunicationChannelsException);

    /**
     * Closes the communication channels (stdin, stdout and stderr).
     * After closing them, all communication channels are set to -1.
     * If the communication channels are already closed, it does nothing.
     */
    virtual void closeCommunicationChannels();

private:

    /**
     * The number of PipeProcessLinuxCommunication currently alive.
     */
    static int sReferenceCount;

    /**
     * Struct to store the SIGPIPE sigaction before it's set to be ignored.
     */
    struct sigaction oldSigPipeSigAction;



    /**
     * Sets the SIGPIPE handler to ignore.
     * This is needed by ProcessLinux::writeData(const std::string&) so EPIPE
     * is returned when writing to a closed pipe.
     */
    void setupSigPipeHandler();

    /**
     * Resets the SIGPIPE handler.
     */
    void resetSigPipeHandler();

    /**
     * Copy constructor disabled.
     */
    PipeProcessLinuxCommunication(
            const PipeProcessLinuxCommunication& pipeProcessLinuxCommunication);

    /**
     * Assignment disabled.
     */
    PipeProcessLinuxCommunication& operator=(
            const PipeProcessLinuxCommunication& pipeProcessLinuxCommunication);

};

}
}

#endif
