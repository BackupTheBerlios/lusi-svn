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

#ifndef LUSI_UTIL_PROCESSTESTIMPLEMENTATION_H
#define LUSI_UTIL_PROCESSTESTIMPLEMENTATION_H

#include <lusi/util/Process.h>

namespace lusi {
namespace util {

/**
 * Implementation of Process abstract class for testing purposes.
 * The abstract methods have empty implementations. It's used to test the
 * already implemented methods in Process.
 */
class ProcessTestImplementation: public Process {
public:

    /**
     * Creates a new ProcessTestImplementation.
     * CommunicationType is set to pipe (although it's not used).
     */
    ProcessTestImplementation();

    /**
     * Destroys this ProcessTestImplementation.
     */
    virtual ~ProcessTestImplementation();

    /**
     * Empty implementation.
     */
    virtual void start() throw (ProcessException);

    /**
     * Returns false.
     *
     * @return False.
     */
    virtual bool writeData(const std::string& data);

};

}
}

#endif
