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

#ifndef LUSI_UTIL_SUPROCESS_H
#define LUSI_UTIL_SUPROCESS_H

#include <string>

#include <lusi/util/Process.h>
#include <lusi/util/SuProcessException.h>

namespace lusi {
namespace util {

/**
 * @class SuProcess SuProcess.h lusi/util/SuProcess.h
 *
 * A Process that can be executed using a different user than the current one.
 * This class abstracts the use of low level calls to execute a process as a
 * different user.
 * If the user isn't specified, or is the same as the current user, no switching
 * occurs and the process is executed as a normal process (so no password is
 * used).
 *
 * This class is abstract, so different implementations can be made depending
 * on the underlying system.
 *
 * It also follows Factory Method Design Pattern, so new SuProcess can be got
 * through newSuProcess() static method. It takes care of using the right
 * implementation.
 *
 * When deriving from this class, all the considerations noted in Process class
 * documentation also apply here.
 *
 * @see Process
 */
class SuProcess: public Process {
public:

    /**
     * Returns a new SuProcess.
     * The specified communicationType may be overriden by the meeds of the
     * created SuProcess (as they can need a concrete type of communication to
     * perform the user change).
     * The implementation of the SuProcess returned will depend on the available
     * implementations. This method takes care of creating a new object of the
     * needed class.
     * The returned SuProcess must be deleted when it's no longer needed.
     * This method follows Factory Method Design Pattern.
     *
     * @param communicationType The type of the communication with the child
     *                          process.
     * @return A SuProcess implementation.
     */
    static SuProcess* newSuProcess(CommunicationType communicationType);

    /**
     * Destroys this SuProcess.
     */
    virtual ~SuProcess();

    /**
     * Changes the user and starts the process.
     * Apart from the usual ProcessException thrown if the process couldn't be
     * executed, SuProcessException are thrown if some error happens when
     * switching the user (for example, invalid user).
     *
     * Must be implemented in derived classes.
     *
     * @throw ProcessException If the process couldn't be executed.
     * @throw SuProcessException If the user couldn't be switched.
     */
    virtual void start() throw (ProcessException, SuProcessException) = 0;

    /**
     * Returns the name of the user to execute the Process as.
     *
     * @return The name of the user to execute the Process as.
     */
    std::string getUserName() {
        return mUserName;
    }

    /**
     * Sets the name of the user to execute the Process as.
     *
     * @param userName The name of the user to execute the Process as.
     */
    void setUserName(const std::string& userName) {
        mUserName = userName;
    }

    /**
     * Sets the password of the user to execute the Process as.
     *
     * @param password The password of the user to execute the Process as.
     */
    void setPassword(const std::string& password) {
        mPassword = password;
    }

protected:

    /**
     * The name of the user to execute the Process as.
     */
    std::string mUserName;

    /**
     * The password of the user to execute the Process as.
     */
    std::string mPassword;


    /**
     * Creates a new SuProcess.
     * Protected to avoid classes other than derived to create SuProcess
     * objects.
     *
     * @param communicationType The type of the communication with the child
     *                          process.
     */
    SuProcess(CommunicationType communicationType);

private:

    /**
     * Copy constructor disabled.
     */
    SuProcess(const SuProcess& suProcess);

    /**
     * Assignment disabled.
     */
    SuProcess& operator=(const SuProcess& suProcess);

};

}
}

#endif
