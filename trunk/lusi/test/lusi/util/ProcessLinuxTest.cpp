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

#include <string>

#include "ProcessLinuxTest.h"
#include "ProcessObserverTestImplementation.h"

#define protected public
#define private public
#include "ProcessLinux.h"
#undef private
#undef protected

using std::string;

using namespace lusi::util;

//public:

void ProcessLinuxTest::setUp() {
    mProcessLinux = new ProcessLinux();
    mProcessObserver = new ProcessObserverTestImplementation();

    mProcessLinux->attachObserver(mProcessObserver);
}

void ProcessLinuxTest::tearDown() {
    delete mProcessLinux;
    delete mProcessObserver;
}

void ProcessLinuxTest::testOperatorAppend() {
    *mProcessLinux << "/bin/echo" << "Hello World!\n" << "Bye!";

    CPPUNIT_ASSERT_EQUAL(string("/bin/echo"),
            mProcessLinux->mArguments[0]);
    CPPUNIT_ASSERT_EQUAL(string("Hello World!\n"),
            mProcessLinux->mArguments[1]);
    CPPUNIT_ASSERT_EQUAL(string("Bye!"),
            mProcessLinux->mArguments[2]);
}

void ProcessLinuxTest::testNotifyReceivedStdout() {
    *mProcessLinux << "/bin/echo" << "Hello World!\nBye!";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mProcessObserver->getStdoutAllData());


    //Test without endline in the output
    restartTestObjects();

    *mProcessLinux << "echo" << "-n" << "Without endline";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mProcessObserver->getStdoutAllData());


    //Test with sleeping process
    restartTestObjects();

    *mProcessLinux << "/bin/sh" << "-c" <<
                "echo -n \"Hello World!\n\" && sleep 0.5 && echo Bye!";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL_MESSAGE(string("May fail if it wasn't slept for ") +
                                 string("enough time"),
            string("Bye!\n"),
            mProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mProcessObserver->getStdoutAllData());
}

void ProcessLinuxTest::testNotifyReceivedStderr() {
    *mProcessLinux << "/bin/sh" << "-c" << "echo \"Hello World!\nBye!\" >&2";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mProcessObserver->getStderrAllData());


    //Test without endline in the output
    restartTestObjects();

    *mProcessLinux << "/bin/sh" << "-c" << "echo -n Without endline >&2";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mProcessObserver->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mProcessObserver->getStderrAllData());


    //Test with sleeping process
    restartTestObjects();

    *mProcessLinux << "/bin/sh" << "-c" <<
                "echo -n \"Hello World!\n\" >&2 && sleep 0.5 && echo Bye! >&2";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL_MESSAGE(string("May fail if it wasn't slept for ") +
                                 string("enough time"),
            string("Bye!\n"),
            mProcessObserver->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mProcessObserver->getStderrAllData());
}

void ProcessLinuxTest::testNotifyProcessExited() {
    *mProcessLinux << "/bin/echo" << "Hello World!";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(1, mProcessObserver->getProcessExitedNumber());
}

void ProcessLinuxTest::testSetWorkingDirectory() {
    *mProcessLinux << "/bin/pwd";
    mProcessLinux->setWorkingDirectory("/");
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("/\n"),
            mProcessObserver->getStdoutLastData());


    //Test with another directory
    mProcessLinux->setWorkingDirectory("/etc");
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("/etc\n"),
            mProcessObserver->getStdoutLastData());
}

void ProcessLinuxTest::testStart() {
    *mProcessLinux << "echo" << "Without path";
    mProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without path\n"),
            mProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without path\n"),
            mProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(1, mProcessObserver->getProcessExitedNumber());


    //Test with non existing program
    restartTestObjects();

    *mProcessLinux << "someNonExistentProgram" << "--dummy args";
    CPPUNIT_ASSERT_THROW(mProcessLinux->start(), ProcessException);

    CPPUNIT_ASSERT_EQUAL(string(""),
            mProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(string(""),
            mProcessObserver->getStderrAllData());
    CPPUNIT_ASSERT_EQUAL(0, mProcessObserver->getProcessExitedNumber());
}

//private:

void ProcessLinuxTest::restartTestObjects() {
    tearDown();
    setUp();
}
