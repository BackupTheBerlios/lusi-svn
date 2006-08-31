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

#ifndef LUSI_UTIL_SUPROCESSEXCEPTION_H
#define LUSI_UTIL_SUPROCESSEXCEPTION_H

#include <lusi/util/ProcessException.h>

namespace lusi {

namespace util {

/**
 * @class SuProcessException SuProcessException.h lusi/util/SuProcessException.h
 *
 * Exception for errors happened when executing a process switching the user.
 * Those exceptions are only intended for errors when switching to the new user.
 * Errors forking and executing the child process are signaled with
 * ProcessException. Neither SuProcessException nor ProcessException are
 * The error message returned by what() will be "ProcessException: " followed
 * by the error message specified when creating the exception.
 */
class SuProcessException: public ProcessException {
public:

    /**
     * Creates a new SuProcessException.
     *
     * @param errorMessage The error message of the exception,
     *                     "SuProcessException: unspecified" by default.
     */
    explicit SuProcessException(const std::string& errorMessage =
                        std::string("SuProcessException: unspecified"));

    /**
     * Destroys this SuProcessException.
     */
    virtual ~SuProcessException() throw();

};

}

}

#endif
