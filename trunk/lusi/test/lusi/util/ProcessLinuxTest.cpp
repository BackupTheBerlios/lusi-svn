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
    mPipeProcessLinux = new ProcessLinux(Process::PipeCommunication);
    mPtyProcessLinux = new ProcessLinux(Process::PtyCommunication);
    mPipeProcessObserver = new ProcessObserverTestImplementation();
    mPtyProcessObserver = new ProcessObserverTestImplementation();

    mPipeProcessLinux->attachObserver(mPipeProcessObserver);
    mPtyProcessLinux->attachObserver(mPtyProcessObserver);
}

void ProcessLinuxTest::tearDown() {
    delete mPipeProcessLinux;
    delete mPtyProcessLinux;
    delete mPipeProcessObserver;
}

void ProcessLinuxTest::testWriteData() {
    //Test with ProcessLinux using pipe communication
    //Unstarted process
    CPPUNIT_ASSERT_EQUAL(false, mPipeProcessLinux->writeData("BBY"));

    *mPipeProcessLinux << "echo" << "testWriteData";
    mPipeProcessLinux->start();

    //Finished process
    CPPUNIT_ASSERT_EQUAL(false, mPipeProcessLinux->writeData("ABY"));


    //----------------------------------------------
    //Test with ProcessLinux using pty communication
    //----------------------------------------------
    //Unstarted process
    CPPUNIT_ASSERT_EQUAL(false, mPtyProcessLinux->writeData("BBY"));

    *mPtyProcessLinux << "echo" << "testWriteData";
    mPtyProcessLinux->start();

    //Finished process
    CPPUNIT_ASSERT_EQUAL(false, mPtyProcessLinux->writeData("ABY"));
}

void ProcessLinuxTest::testNotifyReceivedStdout() {
    //Test with ProcessLinux using pipe communication
    *mPipeProcessLinux << "/bin/echo" << "Hello World!\nBye!";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPipeProcessObserver->getStdoutAllData());


    //Test without endline in the output
    restartTestObjects();

    *mPipeProcessLinux << "echo" << "-n" << "Without endline";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPipeProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPipeProcessObserver->getStdoutAllData());


    //Test with sleeping process
    restartTestObjects();

    *mPipeProcessLinux << "/bin/sh" << "-c" <<
                "echo -n \"Hello World!\n\" && sleep 0.5 && echo Bye!";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL_MESSAGE(string("May fail if it wasn't slept for ") +
                                 string("enough time"),
            string("Bye!\n"),
            mPipeProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPipeProcessObserver->getStdoutAllData());

    //----------------------------------------------
    //Test with ProcessLinux using pty communication
    //----------------------------------------------
    *mPtyProcessLinux << "/bin/echo" << "Hello World!\nBye!";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPtyProcessObserver->getStdoutAllData());


    //Test without endline in the output
    restartTestObjects();

    *mPtyProcessLinux << "echo" << "-n" << "Without endline";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPtyProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPtyProcessObserver->getStdoutAllData());


    //Test with sleeping process
    restartTestObjects();

    *mPtyProcessLinux << "/bin/sh" << "-c" <<
                "echo -n \"Hello World!\n\" && sleep 0.5 && echo Bye!";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL_MESSAGE(string("May fail if it wasn't slept for ") +
                                 string("enough time"),
            string("Bye!\n"),
            mPtyProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPtyProcessObserver->getStdoutAllData());
}

void ProcessLinuxTest::testNotifyReceivedStderr() {
    //Test with ProcessLinux using pipe communication
    *mPipeProcessLinux << "/bin/sh" << "-c" <<
                          "echo \"Hello World!\nBye!\" >&2";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPipeProcessObserver->getStderrAllData());


    //Test without endline in the output
    restartTestObjects();

    *mPipeProcessLinux << "/bin/sh" << "-c" << "echo -n Without endline >&2";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPipeProcessObserver->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPipeProcessObserver->getStderrAllData());


    //Test with sleeping process
    restartTestObjects();

    *mPipeProcessLinux << "/bin/sh" << "-c" <<
                "echo -n \"Hello World!\n\" >&2 && sleep 0.5 && echo Bye! >&2";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL_MESSAGE(string("May fail if it wasn't slept for ") +
                                 string("enough time"),
            string("Bye!\n"),
            mPipeProcessObserver->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPipeProcessObserver->getStderrAllData());

    //----------------------------------------------
    //Test with ProcessLinux using pty communication
    //----------------------------------------------
    *mPtyProcessLinux << "/bin/sh" << "-c" <<
                          "echo \"Hello World!\nBye!\" >&2";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPtyProcessObserver->getStderrAllData());


    //Test without endline in the output
    restartTestObjects();

    *mPtyProcessLinux << "/bin/sh" << "-c" << "echo -n Without endline >&2";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPtyProcessObserver->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without endline"),
            mPtyProcessObserver->getStderrAllData());


    //Test with sleeping process
    restartTestObjects();

    *mPtyProcessLinux << "/bin/sh" << "-c" <<
                "echo -n \"Hello World!\n\" >&2 && sleep 0.5 && echo Bye! >&2";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL_MESSAGE(string("May fail if it wasn't slept for ") +
                                 string("enough time"),
            string("Bye!\n"),
            mPtyProcessObserver->getStderrLastData());
    CPPUNIT_ASSERT_EQUAL(string("Hello World!\nBye!\n"),
            mPtyProcessObserver->getStderrAllData());
}

void ProcessLinuxTest::testNotifyProcessExited() {
    //Test with ProcessLinux using pipe communication
    *mPipeProcessLinux << "/bin/echo" << "Hello World!";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(1, mPipeProcessObserver->getProcessExitedNumber());

    //----------------------------------------------
    //Test with ProcessLinux using pty communication
    //----------------------------------------------
    *mPtyProcessLinux << "/bin/echo" << "Hello World!";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(1, mPtyProcessObserver->getProcessExitedNumber());
}

void ProcessLinuxTest::testSetWorkingDirectory() {
    //Test with ProcessLinux using pipe communication
    *mPipeProcessLinux << "/bin/pwd";
    mPipeProcessLinux->setWorkingDirectory("/");
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("/\n"),
            mPipeProcessObserver->getStdoutLastData());


    //Test with another directory
    mPipeProcessLinux->setWorkingDirectory("/etc");
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("/etc\n"),
            mPipeProcessObserver->getStdoutLastData());

    //----------------------------------------------
    //Test with ProcessLinux using pty communication
    //----------------------------------------------
    *mPtyProcessLinux << "/bin/pwd";
    mPtyProcessLinux->setWorkingDirectory("/");
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("/\n"),
            mPtyProcessObserver->getStdoutLastData());


    //Test with another directory
    mPtyProcessLinux->setWorkingDirectory("/etc");
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("/etc\n"),
            mPtyProcessObserver->getStdoutLastData());
}

void ProcessLinuxTest::testStart() {
    //Test with ProcessLinux using pipe communication
    *mPipeProcessLinux << "echo" << "Without path";
    mPipeProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without path\n"),
            mPipeProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without path\n"),
            mPipeProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(1, mPipeProcessObserver->getProcessExitedNumber());


    //Test with non existing program
    restartTestObjects();

    *mPipeProcessLinux << "someNonExistentProgram" << "--dummy args";
    CPPUNIT_ASSERT_THROW(mPipeProcessLinux->start(), ProcessException);

    CPPUNIT_ASSERT_EQUAL(string(""),
            mPipeProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(string(""),
            mPipeProcessObserver->getStderrAllData());
    CPPUNIT_ASSERT_EQUAL(0, mPipeProcessObserver->getProcessExitedNumber());

    //----------------------------------------------
    //Test with ProcessLinux using pty communication
    //----------------------------------------------
    *mPtyProcessLinux << "echo" << "Without path";
    mPtyProcessLinux->start();

    CPPUNIT_ASSERT_EQUAL(string("Without path\n"),
            mPtyProcessObserver->getStdoutLastData());
    CPPUNIT_ASSERT_EQUAL(string("Without path\n"),
            mPtyProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(1, mPtyProcessObserver->getProcessExitedNumber());


    //Test with non existing program
    restartTestObjects();

    *mPtyProcessLinux << "someNonExistentProgram" << "--dummy args";
    CPPUNIT_ASSERT_THROW(mPtyProcessLinux->start(), ProcessException);

    CPPUNIT_ASSERT_EQUAL(string(""),
            mPtyProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(string(""),
            mPtyProcessObserver->getStderrAllData());
    CPPUNIT_ASSERT_EQUAL(0, mPtyProcessObserver->getProcessExitedNumber());
}

//private:

void ProcessLinuxTest::restartTestObjects() {
    tearDown();
    setUp();
}
