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

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#include "BaseProcessLinuxCommunicationTest.h"
#include "ProcessLinuxCommunication.h"

using std::string;

using namespace lusi::util;

//public:

void BaseProcessLinuxCommunicationTest::testOpenCommunicationChannels() {
    mProcessLinuxCommunication->openCommunicationChannels();

    CPPUNIT_ASSERT_EQUAL(true, writeDataToFileDescriptor(
                mProcessLinuxCommunication->getParentStdin(), "Uhura, "));
    CPPUNIT_ASSERT_EQUAL(string("Uhura, "), readDataFromFileDescriptor(
                        mProcessLinuxCommunication->getChildStdin()));

    CPPUNIT_ASSERT_EQUAL(true, writeDataToFileDescriptor(
                mProcessLinuxCommunication->getChildStdout(), "open "));
    CPPUNIT_ASSERT_EQUAL(string("open "), readDataFromFileDescriptor(
                        mProcessLinuxCommunication->getParentStdout()));

    CPPUNIT_ASSERT_EQUAL(true, writeDataToFileDescriptor(
                mProcessLinuxCommunication->getChildStderr(),
                "hailing frequencies\n"));
    CPPUNIT_ASSERT_EQUAL(string("hailing frequencies\n"),
                readDataFromFileDescriptor(
                        mProcessLinuxCommunication->getParentStderr()));


    //Try with already opened channels (they should be closed and new channels
    //opened, so the data written must have disappeared)
    writeDataToFileDescriptor(mProcessLinuxCommunication->getParentStdin(),
            "Data");
    writeDataToFileDescriptor(mProcessLinuxCommunication->getChildStdout(),
            "never");
    writeDataToFileDescriptor(mProcessLinuxCommunication->getChildStderr(),
            "read");

    mProcessLinuxCommunication->openCommunicationChannels();

    CPPUNIT_ASSERT_EQUAL(string(""), readDataFromFileDescriptor(
                        mProcessLinuxCommunication->getChildStdin()));
    CPPUNIT_ASSERT_EQUAL(string(""), readDataFromFileDescriptor(
                        mProcessLinuxCommunication->getParentStdout()));
    CPPUNIT_ASSERT_EQUAL(string(""), readDataFromFileDescriptor(
                        mProcessLinuxCommunication->getParentStderr()));
}

void BaseProcessLinuxCommunicationTest::testCloseCommunicationChannels() {
    mProcessLinuxCommunication->openCommunicationChannels();
    int parentStdin = mProcessLinuxCommunication->getParentStdin();
    int childStdout = mProcessLinuxCommunication->getChildStdout();
    int childStderr = mProcessLinuxCommunication->getChildStderr();
    mProcessLinuxCommunication->closeCommunicationChannels();

    //Checks if the file descriptor are closed trying to write to them.
    //If closed, write will fail with errno == EBADF.
    char buffer = ' ';
    CPPUNIT_ASSERT_EQUAL(-1, write(parentStdin, &buffer, 0));
    CPPUNIT_ASSERT_EQUAL(EBADF, errno);
    CPPUNIT_ASSERT_EQUAL(-1, write(childStdout, &buffer, 0));
    CPPUNIT_ASSERT_EQUAL(EBADF, errno);
    CPPUNIT_ASSERT_EQUAL(-1, write(childStderr, &buffer, 0));
    CPPUNIT_ASSERT_EQUAL(EBADF, errno);
}

//protected:

bool BaseProcessLinuxCommunicationTest::writeDataToFileDescriptor(
                                                int fileDescriptor,
                                                const string& data) const {
    char buffer;
    int writedSize;

    uint i = 0;
    while (i < data.size()) {
        buffer = data[i];
        if ((writedSize = write(fileDescriptor, &buffer, 1)) <= 0) {
            if (writedSize == -1 && (errno == EBADF || errno == EINVAL ||
                                     errno == EPIPE)) {
                return false;
            }
        } else {
            ++i;
        }
    }

    return true;
}

string BaseProcessLinuxCommunicationTest::readDataFromFileDescriptor(
                                                int fileDescriptor) const {
    string data;

    char buffer;

    int openFlags = fcntl(fileDescriptor, F_GETFL);
    fcntl(fileDescriptor, F_SETFL, openFlags | O_NONBLOCK);

    int readedSize;
    while ((readedSize = read(fileDescriptor, &buffer, 1)) > 0 ||
           (readedSize == -1 && errno == EINTR)) {
        data += buffer;
    }

    fcntl(fileDescriptor, F_SETFL, openFlags);

    return data;
}
