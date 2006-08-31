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

#include <pwd.h>

#include "SuProcessLinuxTest.h"
#include "ProcessObserverTestImplementation.h"

#define protected public
#define private public
#include "SuProcessLinux.h"
#undef private
#undef protected

using std::string;

using namespace lusi::util;

//public:

void SuProcessLinuxTest::setUp() {
    mSuProcessLinux = new SuProcessLinux();
    mProcessObserver = new ProcessObserverTestImplementation();

    mSuProcessLinux->attachObserver(mProcessObserver);

    //Set here a user name
    mValidUserName = "";
    //Set here the password
    mValidPassword = "";
}

void SuProcessLinuxTest::tearDown() {
    delete mSuProcessLinux;
    delete mProcessObserver;
}

void SuProcessLinuxTest::testStart() {
    *mSuProcessLinux << "echo" << "Casting Transfiguration Spell";

    //Test with an invalid user
    mSuProcessLinux->setUserName("doesAnyoneHaveAUserNamedLikeThis");

    CPPUNIT_ASSERT_THROW(mSuProcessLinux->start(), SuProcessException);

    //Test with an invalid password
    mSuProcessLinux->setUserName("root");
    mSuProcessLinux->setPassword("aRootPasswordYouWontLikelyHaveInYourSystem");

    CPPUNIT_ASSERT_THROW(mSuProcessLinux->start(), SuProcessException);

    //Test with current user (using empty user name)
    mSuProcessLinux->setUserName("");
    mSuProcessLinux->setPassword("");

    mSuProcessLinux->start();
    CPPUNIT_ASSERT_EQUAL(string("Casting Transfiguration Spell\n"),
            mProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(string(""), mProcessObserver->getStderrAllData());
    CPPUNIT_ASSERT_EQUAL(1, mProcessObserver->getProcessExitedNumber());
    mProcessObserver->cleanData();

    //Test with current user (using real user name)
    mSuProcessLinux->setUserName(getpwuid(getuid())->pw_name);
    mSuProcessLinux->setPassword("");

    mSuProcessLinux->start();
    CPPUNIT_ASSERT_EQUAL(string("Casting Transfiguration Spell\n"),
            mProcessObserver->getStdoutAllData());
    CPPUNIT_ASSERT_EQUAL(string(""), mProcessObserver->getStderrAllData());
    CPPUNIT_ASSERT_EQUAL(1, mProcessObserver->getProcessExitedNumber());
    mProcessObserver->cleanData();

    //Test with a different user
    if (mValidUserName != "") {
        mSuProcessLinux->setUserName(mValidUserName);
        mSuProcessLinux->setPassword(mValidPassword);

        //Doing so many checks can slow a lot the finish of the tests, let it
        //run for a while ;)
        for (int i=0; i<10; ++i) {
            mSuProcessLinux->start();
            CPPUNIT_ASSERT_EQUAL(string("Casting Transfiguration Spell\n"),
                                 mProcessObserver->getStdoutAllData());
            CPPUNIT_ASSERT_EQUAL(string(""),
                                 mProcessObserver->getStderrAllData());
            CPPUNIT_ASSERT_EQUAL(1, mProcessObserver->getProcessExitedNumber());
            mProcessObserver->cleanData();
        }
    }
}

void SuProcessLinuxTest::testCheckUserName() {
    *mSuProcessLinux << "echo" << "Checking user name";

    //Test with an invalid user
    mSuProcessLinux->setUserName("doesAnyoneHaveAUserNamedLikeThis");

    CPPUNIT_ASSERT_THROW(mSuProcessLinux->checkUserName(), SuProcessException);

    //Test with a valid user
    mSuProcessLinux->setUserName("root");

    try {
        mSuProcessLinux->checkUserName();
    } catch (SuProcessException) {
        CPPUNIT_FAIL("checkPassword() threw SuProcessException");
    }
}

void SuProcessLinuxTest::testCheckPassword() {
    ProcessLinux* processLinux = mSuProcessLinux->mProcessLinux;
    *mSuProcessLinux << "echo" << "It's \"bosco\"";

    //Test with an invalid password
    mSuProcessLinux->setUserName("root");
    mSuProcessLinux->setPassword("aRootPasswordYouWontLikelyHaveInYourSystem");

    CPPUNIT_ASSERT_THROW(mSuProcessLinux->checkPassword(), SuProcessException);
    CPPUNIT_ASSERT_EQUAL(processLinux, mSuProcessLinux->mProcessLinux);

    //Test with a valid user name and password
    if (mValidUserName != "") {
        mSuProcessLinux->setUserName(mValidUserName);
        mSuProcessLinux->setPassword(mValidPassword);

        try {
            mSuProcessLinux->checkPassword();
        } catch (SuProcessException) {
            CPPUNIT_FAIL("checkPassword() threw SuProcessException");
        }
        CPPUNIT_ASSERT_EQUAL(processLinux, mSuProcessLinux->mProcessLinux);
    }
}
