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

#ifndef LUSI_TASK_HELPER_EXECUTETASKHELPEREXCEPTION_H
#define LUSI_TASK_HELPER_EXECUTETASKHELPEREXCEPTION_H

#include <stdexcept>
#include <string>

namespace lusi {
namespace task {
namespace helper {

/**
 * @class ExecuteTaskHelperException ExecuteTaskHelperException.h
 * lusi/task/helper/ExecuteTaskHelperException.h
 *
 * Exception for errors happened when executing a task helper.
 * These exceptions are used when an error happens when a task helper is being
 * executed (and the error isn't an invalid configuration).
 *
 * The error message returned by what() will be the error message specified
 * when creating the exception.
 */
class ExecuteTaskHelperException: public std::exception {
public:

    /**
     * Creates a new ExecuteTaskHelperException.
     *
     * @param errorMessage The error message of the exception, empty by default.
     */
    explicit ExecuteTaskHelperException(const std::string& errorMessage = "");

    /**
     * Destroys this ExecuteTaskHelperException.
     */
    virtual ~ExecuteTaskHelperException() throw();

    /**
     * Returns the error message.
     *
     * @return The error message.
     */
    virtual const char* what() const throw() {
        return mErrorMessage.c_str();
    }

private:

    /**
     * Error message for the exception.
     */
    std::string mErrorMessage;

};

}
}
}

#endif
