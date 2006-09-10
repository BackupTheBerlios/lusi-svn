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

#ifndef LUSI_UTIL_SUPROCESSLINUX_H
#define LUSI_UTIL_SUPROCESSLINUX_H

#include "SuProcess.h"

namespace lusi {
namespace util {
class ProcessLinux;
class SuProcessLinuxConverser;
}
}

namespace lusi {
namespace util {

/**
 * An implementation of SuProcess wrapping a ProcessLinux to allow the change
 * of the user.
 * It wraps the ProcessLinux so the desired command to be executed is wrapped in
 * a call to su.
 * If the user isn't specified, or is the same as the current user, no switching
 * occurs and the process is executed as a normal process (without using su).
 *
 * The executed su process is handled to know when the command could be executed
 * successfully or when a problem changing the user happened (and an exception
 * is thrown in that case).
 *
 * The exit status returned in getExitStatus() is always from the executed
 * process, not su. If the process didn't got to be executed, the returned value
 * is invalid.
 *
 * This class is prepared to work with GNU su. Other su commands might not work.
 * Sourcecode of KDE kdesu was a great source of information about the
 * interaction with su used in this class and SuProcessLinuxConverser. Kudos to
 * the developers of kdesu ;)
 *
 * @see SuProcessLinuxConverser
 */
class SuProcessLinux: public SuProcess {
friend class lusi::util::SuProcessLinuxConverser;
public:

    /**
     * Creates a new SuProcessLinux.
     */
    SuProcessLinux();

    /**
     * Destroys this SuProcessLinux.
     */
    virtual ~SuProcessLinux();

    /**
     * Changes the user and starts the process.
     * If the user isn't specified, or is the same as the current user, no
     * switching occurs and the process is executed as a normal process (so the
     * password takes no effect, it can be invalid because it isn't used).
     *
     * To execute the process, a ProcessLinux is used internally. A
     * SuProcessConverser is attached to the process and manages the switching
     * of the user. It also handles notifying the observers of SuProcessLinux,
     * both when a user switching is needed and not.
     *
     * If the user or the password are invalid, a SuProcessException is thrown.
     *
     * @throw ProcessException If the process couldn't be executed.
     * @throw SuProcessException If the user couldn't be switched.
     */
    virtual void start() throw (ProcessException, SuProcessException);

    /**
     * Writes the data as a string in the standard input of this Process.
     * Note that the data won't be written if su started, but not the real
     * process to be executed.
     *
     * @param data The data to be written.
     * @return True if the data was written, false otherwise.
     */
    virtual bool writeData(const std::string& data);

    /**
     * Returns true if the process exited "by itself" (not due to a signal),
     * false otherwise.
     * The returned value correspond to the subshell executed by su to wrap the
     * process, not by su itself. If the process isn't found, a normal exit
     * happens anyway, as the subshell is executed.
     *
     * @return True if the process exited "by itself" (not due to a signal),
     *         false otherwise.
     */
    virtual bool normalExit();

    /**
     * Returns the exit status of the process.
     * The returned value is valid only if the process exited normally. It
     * correspond to the subshell executed by su to wrap the process, not by su
     * itself. This means that, if the process isn't found, a 127 exit value
     * will be returned, as it's the value returned by the shell.
     *
     * @return The exit status of the process.
     */
    virtual int getExitStatus();

private:

    /**
     * The state in the execution of the process.
     */
    enum StateType {
        CheckPasswordState,
        SwitchingUserState,
        ExecuteSwitchedUserState,
        ExecuteCurrentUserState,
        FinishedState
    };

    /**
     * The ProcessLinux to wrap.
     * This is the Process executed really, but tweaked to allow changing the
     * user that executes it.
     */
    ProcessLinux* mProcessLinux;

    /**
     * The current state type in the execution of the process.
     */
    StateType mStateType;



    /**
     * Checks if the user name is the name of a valid user to switch to.
     *
     * @throw SuProcessException If the user name isn't valid.
     */
    void checkUserName() throw (SuProcessException);

    /**
     * Checks if the password used with the user name is valid.
     * This method must be called only with valid user names (that is, first
     * checkUserName should be called to ensure it).
     * It executes su command with a dummy command to check if the user can be
     * switched without problems.
     * mProcessLinux is temporary changed, as SuProcessConverser uses that
     * process, and then restored after su command is run.
     *
     * @throw SuProcessException If the password for the user name isn't valid.
     */
    void checkPassword() throw (SuProcessException);

    /**
     * Returns the user name of the current user.
     *
     * @return The user name of the current user.
     */
    std::string getCurrentUserName();

    /**
     * Copy constructor disabled.
     */
    SuProcessLinux(const SuProcessLinux& suProcessLinux);

    /**
     * Assignment disabled.
     */
    SuProcessLinux& operator=(const SuProcessLinux& suProcessLinux);

};

}
}

#endif
