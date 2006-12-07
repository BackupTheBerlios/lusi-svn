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

#include <sys/stat.h>
#include <fcntl.h>

#include <algorithm>

#include "LocalFileTest.h"

#define protected public
#define private public
#include "LocalFile.h"
#undef private
#undef protected

#include "Group.h"
#include "User.h"

using std::string;
using std::vector;

using namespace lusi::util;

//public:

void LocalFileTest::setUp() {
    mTestDirectoryPath = LocalFile::getCurrentWorkingDirectory() +
                                                    "created for LUSI tests/";
}

void LocalFileTest::tearDown() {
    struct stat fileStat;
    if (!stat(mTestDirectoryPath.c_str(), &fileStat)) {
        rmdir(string(mTestDirectoryPath + "directory/aSubDirectory/").c_str());
        rmdir(string(mTestDirectoryPath + "directory/").c_str());
        rmdir(string(mTestDirectoryPath + "anotherDirectory/").c_str());
        unlink(string(mTestDirectoryPath + "file").c_str());
        rmdir(mTestDirectoryPath.c_str());
    }
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

void LocalFileTest::testCopyConstructor() {
    LocalFile localFile(LocalUrl("/usr/bin/psi"));
    LocalFile localFileCopy(localFile);

    CPPUNIT_ASSERT_EQUAL(string("/usr/bin/psi"),
                         localFileCopy.mLocalUrl.getPath());
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

void LocalFileTest::testList() {
    //Tests /etc to look for fstab, passwd, rc.local, ld.so.conf.d/, locale/,
    //X11/
    LocalFile etc(LocalUrl("/etc/"));
    vector<string> list = etc.list();

    vector<string>::iterator file = find(list.begin(), list.end(), "fstab");
    if (file == list.end()) {
        CPPUNIT_FAIL("fstab not found in /etc/");
    }

    file = find(list.begin(), list.end(), "passwd");
    if (file == list.end()) {
        CPPUNIT_FAIL("passwd not found in /etc/");
    }

    file = find(list.begin(), list.end(), "rc.local");
    if (file == list.end()) {
        CPPUNIT_FAIL("rc.local not found in /etc/");
    }

    file = find(list.begin(), list.end(), "ld.so.conf.d/");
    if (file == list.end()) {
        CPPUNIT_FAIL("ld.so.conf.d/ not found in /etc/");
    }

    file = find(list.begin(), list.end(), "locale/");
    if (file == list.end()) {
        CPPUNIT_FAIL("locale/ not found in /etc/");
    }

    file = find(list.begin(), list.end(), "X11/");
    if (file == list.end()) {
        CPPUNIT_FAIL("X11/ not found in /etc/");
    }

    file = find(list.begin(), list.end(), ".");
    if (file != list.end()) {
        CPPUNIT_FAIL("Self reference (.) is listed");
    }

    file = find(list.begin(), list.end(), "./");
    if (file != list.end()) {
        CPPUNIT_FAIL("Self reference (./) is listed");
    }

    file = find(list.begin(), list.end(), "..");
    if (file != list.end()) {
        CPPUNIT_FAIL("Parent reference (..) is listed");
    }

    file = find(list.begin(), list.end(), "../");
    if (file != list.end()) {
        CPPUNIT_FAIL("Parent reference (../) is listed");
    }
}

void LocalFileTest::testMkdirs() {
    //Test with a non existent directory
    LocalFile file(mTestDirectoryPath + "directory/aSubDirectory/");

    CPPUNIT_ASSERT_EQUAL(true, file.mkdirs());
    CPPUNIT_ASSERT_EQUAL(true, file.exists());
    CPPUNIT_ASSERT_EQUAL(true, file.remove());

    //Test with an existent directory
    file = LocalFile(LocalFile::getCurrentWorkingDirectory());

    CPPUNIT_ASSERT_EQUAL(false, file.mkdirs());
    CPPUNIT_ASSERT_EQUAL(true, file.exists());

    //Test with a non existent file
    file = LocalFile(mTestDirectoryPath + "file");

    CPPUNIT_ASSERT_EQUAL(false, file.mkdirs());
    CPPUNIT_ASSERT_EQUAL(false, file.exists());
}

void LocalFileTest::testRenameTo() {
    //Test with an existent directory
    LocalFile file(mTestDirectoryPath + "directory/");

    LocalUrl renamedUrl(mTestDirectoryPath + "anotherDirectory/");

    CPPUNIT_ASSERT_EQUAL(true, file.mkdirs());
    CPPUNIT_ASSERT_EQUAL(true, file.renameTo(renamedUrl));
    CPPUNIT_ASSERT(renamedUrl == file.getLocalUrl());
    CPPUNIT_ASSERT_EQUAL(true, file.exists());

    //Test with an existent directory renaming to a non existent file
    LocalUrl renamedUrl2(mTestDirectoryPath + "aFile");

    CPPUNIT_ASSERT_EQUAL(false, file.renameTo(renamedUrl2));
    CPPUNIT_ASSERT(renamedUrl == file.getLocalUrl());
    CPPUNIT_ASSERT_EQUAL(true, file.exists());
    CPPUNIT_ASSERT_EQUAL(true, file.remove());

    //Test with a non existent file
    file = LocalFile(mTestDirectoryPath + "aFile");
    renamedUrl = LocalUrl(mTestDirectoryPath + "anotherFile");

    CPPUNIT_ASSERT_EQUAL(false, file.renameTo(renamedUrl));
    CPPUNIT_ASSERT(renamedUrl != file.getLocalUrl());
    CPPUNIT_ASSERT_EQUAL(false, file.exists());
}

void LocalFileTest::testRemove() {
    //Test with an existent empty directory
    LocalFile file(mTestDirectoryPath + "directory/");

    CPPUNIT_ASSERT_EQUAL(true, file.mkdirs());
    CPPUNIT_ASSERT_EQUAL(true, file.remove());
    CPPUNIT_ASSERT_EQUAL(false, file.exists());

    //Test with an existent file
    file = LocalFile(mTestDirectoryPath + "file");

    close(creat(file.getLocalUrl().getPath().c_str(), S_IRWXU));

    CPPUNIT_ASSERT_EQUAL(true, file.exists());
    CPPUNIT_ASSERT_EQUAL(true, file.remove());
    CPPUNIT_ASSERT_EQUAL(false, file.exists());

    //Test with a non existent file
    CPPUNIT_ASSERT_EQUAL(false, file.remove());

    //Test with a non empty directory
    file = LocalFile(LocalFile::getCurrentWorkingDirectory());

    CPPUNIT_ASSERT_EQUAL(false, file.remove());
}

void LocalFileTest::testOperatorAssignment() {
    LocalFile localFile(LocalUrl("/usr/local/bin/kdevelop"));
    LocalFile localFileCopy(LocalUrl("/"));

    CPPUNIT_ASSERT_EQUAL(&localFileCopy, &(localFileCopy = localFile));
    CPPUNIT_ASSERT_EQUAL(string("/usr/local/bin/kdevelop"),
                         localFileCopy.mLocalUrl.getPath());


    //Test self assignment
    CPPUNIT_ASSERT_EQUAL(&localFileCopy, &(localFileCopy = localFileCopy));
    CPPUNIT_ASSERT_EQUAL(string("/usr/local/bin/kdevelop"),
                         localFileCopy.mLocalUrl.getPath());
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
