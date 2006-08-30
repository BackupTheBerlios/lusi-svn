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

#ifndef LUSI_UTILOPENCOMMUNICATIONCHANNELSEXCEPTION_H
#define LUSI_UTILOPENCOMMUNICATIONCHANNELSEXCEPTION_H

#include <stdexcept>
#include <string>

namespace lusi {
namespace util {

/**
 * Exception for errors happened when opening the communication channels in
 * ProcessLinuxCommunication.
 * The error message returned by what() will be
 * "OpenCommunicationChannelsException: " followed by the error message
 * specified when creating the exception.
 */
class OpenCommunicationChannelsException: public std::exception {
public:

    /**
     * Creates a new OpenCommunicationChannelsException.
     *
     * @param errorMessage The error message of the exception,
     *                      "OpenCommunicationChannelsException: unspecified" by
     *                      default.
     */
    explicit OpenCommunicationChannelsException(
            const std::string& errorMessage =
                std::string("OpenCommunicationChannelsException: unspecified"));

    /**
     * Destroys this ProcessException.
     */
    virtual ~OpenCommunicationChannelsException() throw();

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
