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

#include "SuProcessLinuxConverserTest.h"

#define protected public
#define private public
#include "SuProcessLinuxConverser.h"
#undef private
#undef protected

#include "SuProcessLinux.h"

using std::string;

using namespace lusi::util;

//public:

void SuProcessLinuxConverserTest::setUp() {
    mSuProcessLinux = new SuProcessLinux();
    mSuProcessLinuxConverser = new SuProcessLinuxConverser(mSuProcessLinux);
}

void SuProcessLinuxConverserTest::tearDown() {
    delete mSuProcessLinuxConverser;
    delete mSuProcessLinux;
}

void SuProcessLinuxConverserTest::testIsPasswordPrompt() {
    //Tests with valid password prompts
    CPPUNIT_ASSERT_EQUAL(true,
            mSuProcessLinuxConverser->isPasswordPrompt("Password: "));
    CPPUNIT_ASSERT_EQUAL(true,
            mSuProcessLinuxConverser->isPasswordPrompt("Contraseña: "));
    CPPUNIT_ASSERT_EQUAL(true,
            mSuProcessLinuxConverser->isPasswordPrompt("Pallabra secreta: "));
    CPPUNIT_ASSERT_EQUAL(true,
            mSuProcessLinuxConverser->isPasswordPrompt("Mot de passe: "));

    //Tests with data which isn't password prompt
    CPPUNIT_ASSERT_EQUAL(false,
                mSuProcessLinuxConverser->isPasswordPrompt("Password"));
    CPPUNIT_ASSERT_EQUAL(false,
                mSuProcessLinuxConverser->isPasswordPrompt("Password "));
    CPPUNIT_ASSERT_EQUAL(false,
                mSuProcessLinuxConverser->isPasswordPrompt("Password: pass"));
}
