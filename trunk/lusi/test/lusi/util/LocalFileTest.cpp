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

#include "LocalFileTest.h"

#define protected public
#define private public
#include "LocalFile.h"
#undef private
#undef protected

#include "Group.h"
#include "User.h"

using std::string;

using namespace lusi::util;

//public:

void LocalFileTest::setUp() {
}

void LocalFileTest::tearDown() {
}

void LocalFileTest::testExistsString() {
    //Test a valid absolute url
    string path("/usr/");

    CPPUNIT_ASSERT_EQUAL(true, LocalFile::exists(path));

    //Test a non existent absolute url
    path = string("/usr/AsWeirdAlSaid");

    CPPUNIT_ASSERT_EQUAL(false, LocalFile::exists(path));

    //Test an absolute url without access to it
    path = string("/root/.bash_profile");

    CPPUNIT_ASSERT_EQUAL(false, LocalFile::exists(path));

    //Test a valid relative url
    path = string("./");

    CPPUNIT_ASSERT_EQUAL(true, LocalFile::exists(path));

    //Test an non existent relative url
    path = string("../InItsSongTheSagaBegins");

    CPPUNIT_ASSERT_EQUAL(false, LocalFile::exists(path));
}

void LocalFileTest::testConstructor() {
    //Test a file
    LocalFile localFile(LocalUrl("/bin/grep"));

    CPPUNIT_ASSERT_EQUAL(string("/bin/grep"), localFile.mLocalUrl.getPath());

    //Test a directory
    localFile = LocalFile(LocalUrl("/bin/"));

    CPPUNIT_ASSERT_EQUAL(string("/bin/"), localFile.mLocalUrl.getPath());

    //Test a directory using file syntax
    localFile = LocalFile(LocalUrl("/bin"));

    CPPUNIT_ASSERT_EQUAL(string("/bin/"), localFile.mLocalUrl.getPath());
}

void LocalFileTest::testExists() {
    //Test a valid absolute url
    LocalFile localFile(LocalUrl("/usr/"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.exists());

    //Test a non existent absolute url
    localFile = LocalFile(LocalUrl("/usr/ALongLongTimeAgo/"));

    CPPUNIT_ASSERT_EQUAL(false, localFile.exists());

    //Test an absolute url without access to it
    localFile = LocalFile(LocalUrl("/root/.bash_profile"));

    CPPUNIT_ASSERT_EQUAL(false, localFile.exists());

    //Test a valid relative url
    localFile = LocalFile(LocalUrl("./"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.exists());

    //Test an non existent relative url
    localFile = LocalFile(LocalUrl("../InAGalaxyFarAway"));

    CPPUNIT_ASSERT_EQUAL(false, localFile.exists());
}

void LocalFileTest::testGetGroup() {
    //Test a valid url
    LocalFile localFile(LocalUrl("/etc/"));

    CPPUNIT_ASSERT(Group(0) == localFile.getGroup());

    //Test an non existent url
    localFile = LocalFile(LocalUrl("/usr/NabooWasUnderAttack"));

    CPPUNIT_ASSERT(Group(0) == localFile.getGroup());
}

void LocalFileTest::testGetLocalUrl() {
    LocalFile localFile(LocalUrl("/"));

    CPPUNIT_ASSERT_EQUAL((const LocalUrl*)&localFile.mLocalUrl,
                         &localFile.getLocalUrl());
}

void LocalFileTest::testGetAbsoluteLocalUrl() {
    //Test an absolute url
    LocalFile localFile(LocalUrl("/usr/bin/"));

    CPPUNIT_ASSERT_EQUAL((const LocalUrl*)&localFile.mLocalUrl,
                         &localFile.getLocalUrl());

    //Test a relative url
    localFile = LocalFile(LocalUrl("../someFile"));

    LocalUrl url(LocalFile::getCurrentWorkingDirectory());
    url.appendRelativePathToDirectory(LocalUrl("../someFile"));
    CPPUNIT_ASSERT(url == localFile.getAbsoluteLocalUrl());
}

void LocalFileTest::testGetOwner() {
    //Test a valid url
    LocalFile localFile(LocalUrl("/etc/"));

    CPPUNIT_ASSERT(User(0) == localFile.getOwner());

    //Test an non existent url
    localFile = LocalFile(LocalUrl("/usr/AndImNotGoingOnSinging"));

    CPPUNIT_ASSERT(User(0) == localFile.getOwner());
}

void LocalFileTest::testIsExecutable() {
    string userHome = "/home/" + User::getCurrentUser().getName() + "/";

    //Test a executable file owned by the user
    LocalFile localFile(userHome);

    CPPUNIT_ASSERT_EQUAL(true, localFile.isExecutable());

    //Test with a non existent child
    localFile = LocalFile(LocalUrl(userHome + "BecauseIDontWantToBeSued"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isExecutable());

    //Test a non executable file owned by the user
    localFile = LocalFile(LocalUrl(userHome + ".bash_history"));

    CPPUNIT_ASSERT_EQUAL(false, localFile.isExecutable());



    //Test a executable file not owned by the user nor its group
    localFile = LocalFile(LocalUrl("/bin/"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isExecutable());

    //Test with a non existent child
    localFile = LocalFile(LocalUrl("/bin/SoNoMoreVersesAsFileNames"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isExecutable());

    //Test a non executable file not owned by the user nor its group
    localFile = LocalFile(LocalUrl("/root/"));

    CPPUNIT_ASSERT_EQUAL(false, localFile.isExecutable());
}

void LocalFileTest::testIsReadable() {
    string userHome = "/home/" + User::getCurrentUser().getName() + "/";

    //Test a readable file owned by the user
    LocalFile localFile(userHome);

    CPPUNIT_ASSERT_EQUAL(true, localFile.isReadable());

    //Test with a non existent child
    localFile = LocalFile(LocalUrl(userHome + "IDontKnowWhatToUseNow"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isReadable());



    //Test a readable file not owned by the user nor its group
    localFile = LocalFile(LocalUrl("/bin/"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isReadable());

    //Test with a non existent child
    localFile = LocalFile(LocalUrl("/bin/MaybeOnlySimpleSentences"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isReadable());

    //Test a non readable file not owned by the user nor its group
    localFile = LocalFile(LocalUrl("/root/"));

    CPPUNIT_ASSERT_EQUAL(false, localFile.isReadable());
}

void LocalFileTest::testIsWritable() {
    string userHome = "/home/" + User::getCurrentUser().getName() + "/";

    //Test a writable file owned by the user
    LocalFile localFile(userHome);

    CPPUNIT_ASSERT_EQUAL(true, localFile.isWritable());

    //Test with a non existent child
    localFile = LocalFile(LocalUrl(userHome + "IsReallyAnyoneReadingThis"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isWritable());



    //Test a writable file not owned by the user nor its group
    localFile = LocalFile(LocalUrl("/tmp/"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isReadable());

    //Test with a non existent child
    localFile = LocalFile(LocalUrl("/bin/YouAreABoredPersonArentYou"));

    CPPUNIT_ASSERT_EQUAL(true, localFile.isReadable());

    //Test a non writable file not owned by the user nor its group
    localFile = LocalFile(LocalUrl("/root/"));

    CPPUNIT_ASSERT_EQUAL(false, localFile.isWritable());
}

void LocalFileTest::testGetValidPath() {
    //Test a valid url
    LocalFile localFile(LocalUrl("/bin/grep"));

    CPPUNIT_ASSERT_EQUAL(string("/bin/grep"), localFile.getValidPath());

    //Test an non existent url
    localFile = LocalFile(LocalUrl("/usr/SomeDummyFileYouWontHave"));

    CPPUNIT_ASSERT_EQUAL(string("/usr/"), localFile.getValidPath());

    //Test an url without access to it
    localFile = LocalFile(LocalUrl("/root/.bash_profile"));

    CPPUNIT_ASSERT_EQUAL(string("/root/"), localFile.getValidPath());

    //Test a valid relative url
    localFile = LocalFile(LocalUrl("./"));

    CPPUNIT_ASSERT_EQUAL(LocalFile::getCurrentWorkingDirectory(),
                         localFile.getValidPath());

    //Test an non existent relative url
    localFile = LocalFile(LocalUrl("../AFileInTheParentDirectory"));
    LocalUrl url(LocalFile::getCurrentWorkingDirectory());

    CPPUNIT_ASSERT_EQUAL(url.getParent(), localFile.getValidPath());
}
