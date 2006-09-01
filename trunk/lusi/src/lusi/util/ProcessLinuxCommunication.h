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

#ifndef LUSI_UTIL_PROCESSLINUXCOMMUNICATION_H
#define LUSI_UTIL_PROCESSLINUXCOMMUNICATION_H

#include "lusi/util/OpenCommunicationChannelsException.h"

#include <lusi/util/Process.h>

namespace lusi {
namespace util {

/**
 * Handles opening and closing communication channels between parent and child
 * process in Linux.
 * Communication channels are stdin (input), stdout (output) and stderr (error
 * output). Two versions of each channel exist: one for the parent process (the
 * forking process)and one for the child (the forked process).
 * Parent process writes to stdin and reads from stdout and stderr. Child
 * process reads from stdin and writes to stdout and stderr.
 * Each channel is a file descriptor.
 * When communication channels are closed, all the returned channels are -1.
 *
 * This class follows Factory Method Design Pattern, so new
 * ProcessLinuxCommunication can be got through newProcessLinuxCommunication()
 * static method. It takes care of using the right implementation depending on
 * the communication type requested.
 *
 * Subclasses implement the opening and closing of the communication channels.
 * Those are the only operations dependent on the type of the communication
 * channels. Write and read are independent, as file descriptors are used.
 */
class ProcessLinuxCommunication {
public:

    /**
     * Returns a new ProcessLinuxCommunication.
     * The implementation of the ProcessLinuxCommunication returned will depend
     * on the type of communication requested. This method takes care of
     * creating a new object of the needed class.
     * The returned ProcessLinuxCommunication must be deleted when it's no
     * longer needed.
     * This method follows Factory Method Design Pattern.
     *
     * @param communicationType The type of the communication with the child
     *                          process.
     * @return A ProcessLinuxCommunication implementation handling the specified
     *         communication type.
     */
    static ProcessLinuxCommunication* newProcessLinuxCommunication(
                                Process::CommunicationType communicationType);

    /**
     * Destroys this ProcessLinuxCommunication.
     * If the communication channels were opened but not closed, it closes them.
     */
    virtual ~ProcessLinuxCommunication();

    /**
     * Opens the communication channels.
     * If the communication channels are already opened, it closes them and
     * opens new channels (so be careful when calling it twice).
     *
     * This method must be overriden in subclasses, taking care of setting
     * mOpenCommunicationChannels in a suitable way.
     * Base implementation checks if the channels are already opened and closes
     * them if that is the case. Then, sets mOpenCommunicationChannels to true.
     *
     * @throw OpenCommunicationChannels If the communication channels couldn't
     *                                  be opened.
     */
    virtual void openCommunicationChannels()
                                    throw (OpenCommunicationChannelsException);

    /**
     * Closes the communication channels (stdin, stdout and stderr).
     * After closing them, all communication channels are set to -1.
     * If the communication channels are already closed, it does nothing.
     *
     * This method must be overriden in subclasses, taking care of setting
     * mOpenCommunicationChannels in a suitable way.
     * Base implementation sets mOpenCommunicationChannels to true and all the
     * communication channels to -1.
     */
    virtual void closeCommunicationChannels();

    /**
     * Returns the file descriptor to use in the child process to receive input.
     *
     * @return The file descriptor to use in the child process to receive input.
     */
    int getChildStdin() const {
        return mChildStdin;
    }

    /**
     * Returns the file descriptor to use in the child process to send normal
     * output.
     *
     * @return The file descriptor to use in the child process to send normal
     *         output.
     */
    int getChildStdout() const {
        return mChildStdout;
    }

    /**
     * Returns the file descriptor to use in the child process to send error
     * output.
     *
     * @return The file descriptor to use in the child process to send error
     *         output.
     */
    int getChildStderr() const {
        return mChildStderr;
    }

    /**
     * Returns the file descriptor to use in the parent process to send input.
     *
     * @return The file descriptor to use in the parent process to send input.
     */
    int getParentStdin() const {
        return mParentStdin;
    }

    /**
     * Returns the file descriptor to use in the parent process to receive
     * normal output.
     *
     * @return The file descriptor to use in the parent process to receive
     *         normal output.
     */
    int getParentStdout() const {
        return mParentStdout;
    }

    /**
     * Returns the file descriptor to use in the parent process to receive
     * error output.
     *
     * @return The file descriptor to use in the parent process to receive
     *         error output.
     */
    int getParentStderr() const {
        return mParentStderr;
    }

protected:

    /**
     * True if the communication channels were opened but not closed yet, false
     * otherwise.
     */
    bool mOpenCommunicationChannels;

    /**
     * The file descriptor to use in the child process to receive input.
     */
    int mChildStdin;

    /**
     * The file descriptor to use in the child process to send normal output.
     */
    int mChildStdout;

    /**
     * The file descriptor to use in the child process to send error output.
     */
    int mChildStderr;

    /**
     * The file descriptor to use in the parent process to send input.
     */
    int mParentStdin;

    /**
     * The file descriptor to use in the parent process to receive normal
     * output.
     */
    int mParentStdout;

    /**
     * The file descriptor to use in the parent process to receive error output.
     */
    int mParentStderr;



    /**
     * Creates a new ProcessLinuxCommunication.
     * All the communication channels are set to -1.
     */
    ProcessLinuxCommunication();

private:

    /**
     * Copy constructor disabled.
     */
    ProcessLinuxCommunication(
                const ProcessLinuxCommunication& processLinuxCommunication);

    /**
     * Assignment disabled.
     */
    ProcessLinuxCommunication& operator=(
                const ProcessLinuxCommunication& processLinuxCommunication);

};

}
}

#endif
