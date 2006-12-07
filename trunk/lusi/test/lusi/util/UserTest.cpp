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

#include "UserTest.h"

#define protected public
#define private public
#include "User.h"
#undef private
#undef protected

using std::string;

using namespace lusi::util;

//public:

void UserTest::setUp() {
}

void UserTest::tearDown() {
}

void UserTest::testGetCurrentUser() {
    User currentUser = User::getCurrentUser();
    User user(geteuid());

    CPPUNIT_ASSERT_EQUAL(user.mId, currentUser.mId);
    CPPUNIT_ASSERT_EQUAL(user.mName, currentUser.mName);
    CPPUNIT_ASSERT(user.mGroup == currentUser.mGroup);
    CPPUNIT_ASSERT_EQUAL(user.mHome, currentUser.mHome);
}

void UserTest::testConstructorId() {
    User user(0);

    CPPUNIT_ASSERT_EQUAL(0, user.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), user.mName);
    CPPUNIT_ASSERT(Group(0) == user.mGroup);
    CPPUNIT_ASSERT_EQUAL(string("/root/"), user.mHome);

    //Invalid user
    user = User(-273);

    CPPUNIT_ASSERT_EQUAL(-1, user.mId);
    CPPUNIT_ASSERT_EQUAL(string(""), user.mName);
    CPPUNIT_ASSERT(Group(-1) == user.mGroup);
    CPPUNIT_ASSERT_EQUAL(string(""), user.mHome);
}

void UserTest::testConstructorName() {
    User user("root");

    CPPUNIT_ASSERT_EQUAL(0, user.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), user.mName);
    CPPUNIT_ASSERT(Group(0) == user.mGroup);
    CPPUNIT_ASSERT_EQUAL(string("/root/"), user.mHome);

    //Invalid user
    user = User("areYouGeekEnoughToHaveAUserCalledSpockInYourSystem?");

    CPPUNIT_ASSERT_EQUAL(-1, user.mId);
    CPPUNIT_ASSERT_EQUAL(string(""), user.mName);
    CPPUNIT_ASSERT(Group(-1) == user.mGroup);
    CPPUNIT_ASSERT_EQUAL(string(""), user.mHome);
}

void UserTest::testCopyConstructor() {
    User user(0);
    User userCopy(user);

    CPPUNIT_ASSERT_EQUAL(0, userCopy.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), userCopy.mName);
    CPPUNIT_ASSERT(Group(0) == user.mGroup);
    CPPUNIT_ASSERT_EQUAL(string("/root/"), userCopy.mHome);
}

void UserTest::testExists() {
    //Test a valid user
    User user(0);

    CPPUNIT_ASSERT_EQUAL(true, user.exists());

    //Test an invalid user
    user = User("aUserWithAStupidName");

    CPPUNIT_ASSERT_EQUAL(false, user.exists());
}

void UserTest::testGetGroup() {
    User user(0);

    CPPUNIT_ASSERT(Group(0) == user.getGroup());
}

void UserTest::testGetHome() {
    User user(0);
    user.mHome = "/home/Tux/";

    CPPUNIT_ASSERT_EQUAL(string("/home/Tux/"), user.getHome());
}

void UserTest::testGetId() {
    User user(0);
    user.mId = 1138;

    CPPUNIT_ASSERT_EQUAL(1138, user.getId());
}

void UserTest::testGetName() {
    User user(0);
    user.mName = "Tux";

    CPPUNIT_ASSERT_EQUAL(string("Tux"), user.getName());
}

void UserTest::testIsRoot() {
    //Test root user
    User user(0);

    CPPUNIT_ASSERT_EQUAL(true, user.isRoot());

    //Test not root user (I hope you aren't executing this as root...)
    user = User(geteuid());

    CPPUNIT_ASSERT_EQUAL(false, user.isRoot());
}

void UserTest::testOperatorAssignment() {
    //Test self assignment
    User rootUser(0);

    CPPUNIT_ASSERT_EQUAL(&rootUser, &(rootUser = rootUser));
    CPPUNIT_ASSERT_EQUAL(0, rootUser.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), rootUser.mName);
    CPPUNIT_ASSERT(Group(0) == rootUser.mGroup);
    CPPUNIT_ASSERT_EQUAL(string("/root/"), rootUser.mHome);

    //Test normal assignment
    User user(geteuid());

    CPPUNIT_ASSERT_EQUAL(&user, &(user = rootUser));
    CPPUNIT_ASSERT_EQUAL(0, user.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), user.mName);
    CPPUNIT_ASSERT(Group(0) == user.mGroup);
    CPPUNIT_ASSERT_EQUAL(string("/root/"), user.mHome);
}

void UserTest::testOperatorEqual() {
    //Test equal users
    User user1(0);
    User user2(0);

    CPPUNIT_ASSERT_EQUAL(true, user1 == user2);

    //Test users with different id
    user2.mId = 42;

    CPPUNIT_ASSERT_EQUAL(false, user1 == user2);

    //Test users with different name
    user2.mId = 0;
    user2.mName = "mightyRoot";

    CPPUNIT_ASSERT_EQUAL(false, user1 == user2);

    //Test users with different group
    user2.mName = "root";
    user2.mGroup = Group(108);

    CPPUNIT_ASSERT_EQUAL(false, user1 == user2);

    //Test users with different home
    user2.mGroup = Group(0);
    user2.mHome = "/home/root/";

    CPPUNIT_ASSERT_EQUAL(false, user1 == user2);
}

void UserTest::testOperatorDifferent() {
    User user1(0);
    User user2(0);

    //Test users with different id
    user2.mId = 42;

    CPPUNIT_ASSERT_EQUAL(true, user1 != user2);

    //Test users with different name
    user2.mId = 0;
    user2.mName = "mightyRoot";

    CPPUNIT_ASSERT_EQUAL(true, user1 != user2);

    //Test users with different group
    user2.mName = "root";
    user2.mGroup = Group(108);

    CPPUNIT_ASSERT_EQUAL(true, user1 != user2);

    //Test users with different home
    user2.mGroup = Group(0);
    user2.mHome = "/home/root/)";

    CPPUNIT_ASSERT_EQUAL(true, user1 != user2);

    //Test equal users
    user2 = User(0);

    CPPUNIT_ASSERT_EQUAL(false, user1 != user2);
}
