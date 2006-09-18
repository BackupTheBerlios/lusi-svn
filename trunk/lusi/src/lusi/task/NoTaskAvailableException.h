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

#ifndef LUSI_TASK_NOTASKAVAILABLEEXCEPTION_H
#define LUSI_TASK_NOTASKAVAILABLEEXCEPTION_H

#include <stdexcept>
#include <string>

namespace lusi {
namespace task {

/**
 * @class NoTaskAvailableException NoTaskAvailableException.h
 * lusi/task/NoTaskAvailableException.h
 *
 * Exception thrown when a new task is requested and there are no more
 * available.
 * These exceptions are usedin modules, when they fail because there are no more
 * available tasks to be executed.
 *
 * The error message returned by what() will be the error message specified
 * when creating the exception.
 */
class NoTaskAvailableException: public std::exception {
public:

    /**
     * Creates a new NoTaskAvailableException.
     *
     * @param errorMessage The error message of the exception, empty by default.
     */
    explicit NoTaskAvailableException(const std::string& errorMessage = "");

    /**
     * Destroys this NoTaskAvailableException.
     */
    virtual ~NoTaskAvailableException() throw();

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

#endif
