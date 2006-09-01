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

#ifndef LUSI_UTIL_SUPROCESSLINUXCONVERSER_H
#define LUSI_UTIL_SUPROCESSLINUXCONVERSER_H

#include <string>

#include <lusi/util/ProcessObserver.h>

#include "SuProcessLinux.h"

namespace lusi {
namespace util {
class ProcessLinux;
}
}

namespace lusi {
namespace util {

/**
 * Helper class for SuProcessLinux which handles conversation with su command.
 * It observes the notifications sent by the wrapped ProcessLinux executed by
 * SuProcessLinux and handles switching the user (if needed) and notifiying the
 * observers of SuProcessLinux.
 *
 * If no user switching is needed (as pointed in the state of SuProcessLinux),
 * it simply redirects the notifications sent by the executed ProcessLinux to
 * the observers of SuProcessLinux.
 * If the user must be switched, it converses with su, sending the password when
 * needed, and then redirecting the notifications to the observers of
 * SuProcessLinux.
 *
 * In order to know whether a user name or password are valid, the data received
 * in stderr is stored. The checking is made in SuProcessLinux. If the
 * ProcessLinux finishes while checking the user name and password and the
 * password wasn't sent, the user name is invalid. If it finishes and the stored
 * data in stderr is different to "\n", the password is invalid (the received
 * stderr data is cleaned after sending the password).
 *
 * The actions made by each method inherited from ProcessObserver depends on
 * the state of SuProcessLinux.
 *
 * @see SuProcessLinux.
 */
class SuProcessLinuxConverser: public ProcessObserver {
public:

    /**
     * Creates a new SuProcessLinuxConverser.
     *
     * @param suProcessLinux The SuProcessLinux to help conversing with su
     *                       command.
     */
    SuProcessLinuxConverser(SuProcessLinux* suProcessLinux);

    /**
     * Destroys this SuProcessLinuxConverser.
     */
    virtual ~SuProcessLinuxConverser();

    /**
     * Called when new data is received in stdout.
     * If there is no need to switch user or if the user was already switched,
     * it notifies the exit to the observers of SuProcessLinux.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     */
    virtual void receivedStdout(Process* process, const std::string& data);

    /**
     * Called when new data is received in stderr.
     * If there is no need to switch user or if the user was already switched,
     * it notifies the exit to the observers of SuProcessLinux.
     *
     * Moreover, it handles switching the user. Su command writes its output to
     * stderr. This output is processed so, when a password prompt is received,
     * it sends the password to su (after waiting for su command to set some
     * parameters in the slave device of the pseudo terminal).
     * Once the password is sent, a new line is received in stderr if it was a
     * valid password (so the user was switched). If the password wasn't valid,
     * a new line with an error message is received.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     * @see waitEcho()
     */
    virtual void receivedStderr(Process* process, const std::string& data);

    /**
     * Called when the process exits.
     * If there is no need to switch user or if the user was already switched,
     * it notifies the exit to the observers of SuProcessLinux.
     *
     * @param process A pointer to the process that exited.
     */
    virtual void processExited(Process* process);

    /**
     * Returns the data received in stderr while trying to switch user.
     * After the password is sent, stderr is cleaned. It's used to know whether
     * the password was valid or not.
     * A new line is written to stderr when the password is sent. If stderr
     * contains anything else than a new line character, the password was
     * invalid.
     *
     * @return The data received in stderr.
     * @see SuProcessLinux::checkUserNameAndPassword()
     */
    std::string getStderrData() {
        return mStderrData;
    }

private:

    /**
     * The SuProcessLinux to help conversing with su command.
     */
    SuProcessLinux* mSuProcessLinux;

    /**
     * The data received in stderr.
     * After the password is sent, stderr is cleaned. It's used to know whether
     * the password was valid or not.
     */
    std::string mStderrData;

    /**
     * If the password was sent to su command, false otherwise.
     */
    bool mPasswordSent;



    /**
     * Checks if the data is a password prompt.
     * Password prompt depends on the version of su used. A regular expression
     * got from kdelibs/kdesu/su.cpp is used.
     *
     * @param data The data to check.
     * @return True if it is a password prompt, false otherwise.
     */
    bool isPasswordPrompt(const std::string& line);

    /**
     * Waits until su command deactivates the echo in the stdin slave.
     * After the password prompt is shown, su does some changes in the slave
     * device of the pseudo terminal used in stdin. Once it's done, the password
     * can be sent, but if done before it may lead to a race condition.
     * When the echo is disabled in the pseudo terminal, su changes are ready,
     * so the password can then be sent.
     */
    void waitEcho();

    /**
     * Waits the specified number of miliseconds.
     * It is like sleep, although with a precission of miliseconds instead of
     * seconds.
     *
     * @param miliseconds The number of miliseconds to wait.
     */
    void waitMiliseconds(int miliseconds);

    /**
     * Copy constructor disabled.
     */
    SuProcessLinuxConverser(
                    const SuProcessLinuxConverser& suProcessLinuxConverser);

    /**
     * Assignment disabled.
     */
    SuProcessLinuxConverser& operator=(
                    const SuProcessLinuxConverser& suProcessLinuxConverser);

};

}
}

#endif
