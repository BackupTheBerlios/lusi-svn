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

#ifndef LUSI_UTIL_PROCESSLINUXCOMMUNICATIONTESTIMPLEMENTATION_H
#define LUSI_UTIL_PROCESSLINUXCOMMUNICATIONTESTIMPLEMENTATION_H

#include <lusi/util/ProcessLinuxCommunication.h>

namespace lusi {
namespace util {

/**
 * Specialization of ProcessLinuxCommunication class for testing purposes.
 * This class sets a flag whenever closeCommunicationChannels is called. It
 * helps to test openCommunicationChannels method.
 */
class ProcessLinuxCommunicationTestImplementation:
                        public ProcessLinuxCommunication {
public:

    /**
     * Creates a new ProcessLinuxCommunicationTestImplementation;
     */
    ProcessLinuxCommunicationTestImplementation();

    /**
     * Destroys this ProcessLinuxCommunicationTestImplementation.
     */
    virtual ~ProcessLinuxCommunicationTestImplementation();

    /**
     * Calls the base implementation and sets mCloseCommunicationChannelsCalled
     * to true.
     */
    virtual void closeCommunicationChannels();

private:

    /**
     * True if closeCommunicationChannels method was called, false otherwise.
     */
    bool mCloseCommunicationChannelsCalled;

};

}
}

#endif
