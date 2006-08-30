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

#ifndef LUSI_UTIL_BASEPROCESSLINUXCOMMUNICATIONTEST_H
#define LUSI_UTIL_BASEPROCESSLINUXCOMMUNICATIONTEST_H

#include <string>

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace util {
class ProcessLinuxCommunication;
}
}

namespace lusi {
namespace util {

/**
 * Base implementation for test of subclasses of ProcessLinuxCommunication.
 * This class provides base tests for openCommunicationChannels and
 * openCommunicationChannels.
 * Subclasses must initialize mProcessLinuxCommunication with a instance of the
 * class being tested.
 */
class BaseProcessLinuxCommunicationTest: public CppUnit::TestFixture {
public:

    /**
     * Tests if the communication channels are opened and can be written/read.
     * It also tests that calling the method twice closes the previous
     * communication channels and opens new ones.
     */
    virtual void testOpenCommunicationChannels();

    /**
     * Tests if the communication channels are closed.
     */
    virtual void testCloseCommunicationChannels();

protected:

    /**
     * The ProcessLinuxCommunication to test.
     */
    ProcessLinuxCommunication* mProcessLinuxCommunication;



    /**
     * Writes the data as a string to the file descriptor.
     * It can fail if the file descriptor isn't suitable for writing.
     *
     * @param data The data to be written.
     * @return True if the data was written, false otherwise.
     */
    bool writeDataToFileDescriptor(int fileDescriptor, const std::string& data)
                                                                        const;

    /**
     * Reads the file descriptor and returns its content as a string.
     * It reads the file descriptor until no more data is available for reading.
     *
     * @param fileDescriptor The file descriptor to read from.
     * @return A string containing the data read.
     */
    std::string readDataFromFileDescriptor(int fileDescriptor) const;

};

}
}

#endif
