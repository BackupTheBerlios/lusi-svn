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
#include <termios.h>

#include "PtyProcessLinuxCommunicationTest.h"

#define protected public
#define private public
#include "PtyProcessLinuxCommunication.h"
#undef private
#undef protected

using std::string;

using namespace lusi::util;

//public:

void PtyProcessLinuxCommunicationTest::setUp() {
    mProcessLinuxCommunication = new PtyProcessLinuxCommunication();
}

void PtyProcessLinuxCommunicationTest::tearDown() {
    delete mProcessLinuxCommunication;
}

void PtyProcessLinuxCommunicationTest::testOpenCommunicationChannels() {
    BaseProcessLinuxCommunicationTest::testOpenCommunicationChannels();

    struct termios tio;
    //If the file descriptors are from slave of a terminal, no error must occur
    CPPUNIT_ASSERT_EQUAL(0, tcgetattr(mProcessLinuxCommunication->getChildStdout(),
                                      &tio));
    CPPUNIT_ASSERT_EQUAL(0, tcgetattr(mProcessLinuxCommunication->getChildStderr(),
                                      &tio));
}
