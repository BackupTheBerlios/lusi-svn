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

#ifndef LUSI_UTIL_NULLPOINTEREXCEPTION_H
#define LUSI_UTIL_NULLPOINTEREXCEPTION_H

#include <stdexcept>
#include <string>

namespace lusi {
namespace util {

/**
 * @class NullPointerException NullPointerException.h \
 * lusi/util/NullPointerException.h
 *
 * Exception for dereferencing a null pointer in a smart pointer.
 * This is a runtime exception.
 *
 * The error message returned by what() will be the error message specified
 * when creating the exception.
 */
class NullPointerException: public std::runtime_error {
public:

    /**
     * Creates a new NullPointerException.
     *
     * @param errorMessage The error message of the exception, empty by default.
     */
    explicit NullPointerException(const std::string& errorMessage = "");

    /**
     * Destroys this NullPointerException.
     */
    virtual ~NullPointerException() throw();

};

}
}

#endif
