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

#include "GroupTest.h"

#define protected public
#define private public
#include "Group.h"
#undef private
#undef protected

#include "User.h"

using std::string;

using namespace lusi::util;

//public:

void GroupTest::setUp() {
}

void GroupTest::tearDown() {
}

void GroupTest::testConstructorId() {
    Group group(0);

    CPPUNIT_ASSERT_EQUAL(0, group.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), group.mName);

    //Invalid group
    group = Group(-273);

    CPPUNIT_ASSERT_EQUAL(-1, group.mId);
    CPPUNIT_ASSERT_EQUAL(string(""), group.mName);
}

void GroupTest::testConstructorName() {
    Group group("root");

    CPPUNIT_ASSERT_EQUAL(0, group.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), group.mName);

    //Invalid group
    group = Group("areYouGeekEnoughToHaveAGroupCalledSpockInYourSystem?");

    CPPUNIT_ASSERT_EQUAL(-1, group.mId);
    CPPUNIT_ASSERT_EQUAL(string(""), group.mName);
}

void GroupTest::testCopyConstructor() {
    Group group(0);
    Group groupCopy(group);

    CPPUNIT_ASSERT_EQUAL(0, groupCopy.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), groupCopy.mName);
}

void GroupTest::testExists() {
    //Test a valid group
    Group group(0);

    CPPUNIT_ASSERT_EQUAL(true, group.exists());

    //Test an invalid group
    group = Group("aGroupWithAStupidName");

    CPPUNIT_ASSERT_EQUAL(false, group.exists());
}

void GroupTest::testGetId() {
    Group group(0);
    group.mId = 1138;

    CPPUNIT_ASSERT_EQUAL(1138, group.getId());
}

void GroupTest::testGetName() {
    Group group(0);
    group.mName = "Tux";

    CPPUNIT_ASSERT_EQUAL(string("Tux"), group.getName());
}

void GroupTest::testIsRoot() {
    //Test root group
    Group group(0);

    CPPUNIT_ASSERT_EQUAL(true, group.isRoot());

    //Test not root group (I hope you aren't executing this as root...)
    group = User::getCurrentUser().getGroup();

    CPPUNIT_ASSERT_EQUAL(false, group.isRoot());
}

void GroupTest::testOperatorAssignment() {
    //Test self assignment
    Group rootGroup(0);

    CPPUNIT_ASSERT_EQUAL(&rootGroup, &(rootGroup = rootGroup));
    CPPUNIT_ASSERT_EQUAL(0, rootGroup.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), rootGroup.mName);

    //Test normal assignment
    Group group(User::getCurrentUser().getGroup());

    CPPUNIT_ASSERT_EQUAL(&group, &(group = rootGroup));
    CPPUNIT_ASSERT_EQUAL(0, group.mId);
    CPPUNIT_ASSERT_EQUAL(string("root"), group.mName);
}

void GroupTest::testOperatorEqual() {
    //Test equal groups
    Group group1(0);
    Group group2(0);

    CPPUNIT_ASSERT_EQUAL(true, group1 == group2);

    //Test different groups
    group2 = User::getCurrentUser().getGroup();

    CPPUNIT_ASSERT_EQUAL(false, group1 == group2);
}

void GroupTest::testOperatorDifferent() {
    //Test different groups
    Group group1(0);
    Group group2 = User::getCurrentUser().getGroup();

    CPPUNIT_ASSERT_EQUAL(true, group1 != group2);

    //Test equal groups
    group2 = Group(0);

    CPPUNIT_ASSERT_EQUAL(false, group1 != group2);
}
