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

#include "SuProcessTest.h"

#define protected public
#define private public
#include "SuProcessTestImplementation.h"
#undef private
#undef protected

using std::string;

using namespace lusi::util;

//public:

void SuProcessTest::setUp() {
    mSuProcess = new SuProcessTestImplementation();
}

void SuProcessTest::tearDown() {
    delete mSuProcess;
}

void SuProcessTest::testConstructor() {
    CPPUNIT_ASSERT_EQUAL(string(""), mSuProcess->mUserName);
    CPPUNIT_ASSERT_EQUAL(string(""), mSuProcess->mPassword);
}

void SuProcessTest::testGetUserName() {
    mSuProcess->mUserName = "dani";

    CPPUNIT_ASSERT_EQUAL(string("dani"), mSuProcess->getUserName());
}

void SuProcessTest::testSetUserName() {
    mSuProcess->setPassword("again me");

    CPPUNIT_ASSERT_EQUAL(string("again me"),
                         mSuProcess->mPassword);
}

void SuProcessTest::testSetPassword() {
    mSuProcess->setPassword("not my real password, sorry :P");

    CPPUNIT_ASSERT_EQUAL(string("not my real password, sorry :P"),
                         mSuProcess->mPassword);
}
