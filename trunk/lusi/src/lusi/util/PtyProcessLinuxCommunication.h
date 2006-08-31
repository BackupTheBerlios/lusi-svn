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

#ifndef LUSI_UTIL_PTYPROCESSLINUXCOMMUNICATION_H
#define LUSI_UTIL_PTYPROCESSLINUXCOMMUNICATION_H

#include "lusi/util/ProcessLinuxCommunication.h"

namespace lusi {
namespace util {

/**
 * Handles opening and closing communication channels between parent and child
 * process in Linux using pseudo terminals.
 * A pseudo terminal is created for stdin/stdout, and another one is created for
 * stderr. Master sides are set in the parent for stdout and stderr and in the
 * child for stdin. Slave sides are set in the child for stdout and stderr, and
 * in the parent for stdin.
 *
 * It makes use of getpt, grantpt, unlockpt, ptsname, isastream, ioctl,
 * tcgetattr, tcsetattr, open and close functions. It will likely work in any
 * system with the GNU C Library.
 */
class PtyProcessLinuxCommunication: public ProcessLinuxCommunication {
public:

    /**
     * Creates a new PtyProcessLinuxCommunication.
     */
    PtyProcessLinuxCommunication();

    /**
     * Destroys this PtyProcessLinuxCommunication.
     */
    virtual ~PtyProcessLinuxCommunication();

    /**
     * Opens the communication channels.
     * If the communication channels are already opened, it closes them and
     * opens new channels (so be careful when calling it twice).
     *
     * Two pseudo terminals are created: one for stdin/stdout and another only
     * for stderr. Using only one terminal doesn't allow to differentiate
     * between stderr and stdout, so that is why two are used.
     *
     * If any of the pseudo terminals couldn't be created, or an error happened
     * when setting some of their parameters, an Exception is thrown. All the
     * already created pseudo terminals are closed and the attributes set to -1.
     *
     * @throw OpenCommunicationChannelsException If the pseudo terminals
     *                                           couldn't be created, or an
     *                                           error happened when setting the
     *                                           parameters.
     */
    virtual void openCommunicationChannels()
                                    throw (OpenCommunicationChannelsException);

    /**
     * Closes the communication channels (stdin, stdout and stderr).
     * After closing them, all communication channels are set to -1.
     * If the communication channels are already closed, it does nothing.
     *
     * It closes the two opened pseudo terminals.
     */
    virtual void closeCommunicationChannels();

private:

    /**
     * The file descriptor of the master side of the first pseudo terminal (the
     * one used for stdin/stdout).
     */
    int mStdinStdoutMaster;

    /**
     * The file descriptor of the slave side of the first pseudo terminal (the
     * one used for stdin/stdout).
     */
    int mStdinStdoutSlave;

    /**
     * The file descriptor of the master side of the second pseudo terminal (the
     * one used for stderr).
     */
    int mStderrMaster;

    /**
     * The file descriptor of the slave side of the second pseudo terminal (the
     * one used for stderr).
     */
    int mStderrSlave;



    /**
     * Opens a new master/slave pseudo terminal pair.
     *
     * @param master The file descriptor for the master side.
     * @param slave The file descriptor for the slave side.
     */
    void openPtyPair(int& master, int& slave)
                                    throw (OpenCommunicationChannelsException);

    /**
     * Prepares the terminal setting some parameters in it.
     * The slave pseudo-terminal device must be a valid one, as no checks are
     * made to ensure that.
     * Disables the mapping of NL to CR-NL.
     */
    void preparePtySlave(int slave);

};

}
}

#endif
