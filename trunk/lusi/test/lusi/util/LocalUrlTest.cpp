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

#include "LocalUrlTest.h"

#define protected public
#define private public
#include "LocalUrl.h"
#undef private
#undef protected

using std::string;

using namespace lusi::util;

void LocalUrlTest::setUp() {
}

void LocalUrlTest::tearDown() {
}

void LocalUrlTest::testCopyConstructor() {
    LocalUrl localUrl("/usr/bin/psi");
    LocalUrl localUrlCopy(localUrl);

    CPPUNIT_ASSERT_EQUAL(string("/usr/bin/psi"), localUrlCopy.mPath);
}

void LocalUrlTest::testIsDirectory() {
    //Test a directory
    LocalUrl localUrl("Tabs/");

    CPPUNIT_ASSERT_EQUAL(true, localUrl.isDirectory());

    //Test a relative self directory
    localUrl = LocalUrl("./Tabs/");

    CPPUNIT_ASSERT_EQUAL(true, localUrl.isDirectory());

    //Test a relative parent directory
    localUrl = LocalUrl("../Tabs/");

    CPPUNIT_ASSERT_EQUAL(true, localUrl.isDirectory());

    //Test a simple file
    localUrl = LocalUrl("Tabs/Iron Maiden");

    CPPUNIT_ASSERT_EQUAL(false, localUrl.isDirectory());

    //Test a file
    localUrl = LocalUrl("Tabs/Wrathchild.bass");

    CPPUNIT_ASSERT_EQUAL(false, localUrl.isDirectory());
}

void LocalUrlTest::testIsRelative() {
    //Test a relative path
    LocalUrl localUrl("dani/");

    CPPUNIT_ASSERT_EQUAL(true, localUrl.isRelative());

    //Test a relative self directory
    localUrl = LocalUrl("./dani/");

    CPPUNIT_ASSERT_EQUAL(true, localUrl.isRelative());

    //Test a relative parent directory
    localUrl = LocalUrl("../dani/");

    CPPUNIT_ASSERT_EQUAL(true, localUrl.isRelative());

    //Test an absolute path
    localUrl = LocalUrl("/home/dani/");

    CPPUNIT_ASSERT_EQUAL(false, localUrl.isRelative());
}

void LocalUrlTest::testGetDirectory() {
    //Test a directory
    LocalUrl localUrl("Music/");

    CPPUNIT_ASSERT_EQUAL(string("Music/"), localUrl.getDirectory());

    //Test a relative self directory
    localUrl = LocalUrl("./Music/");

    CPPUNIT_ASSERT_EQUAL(string("Music/"), localUrl.getDirectory());

    //Test a relative parent directory
    localUrl = LocalUrl("../Music/");

    CPPUNIT_ASSERT_EQUAL(string("../Music/"), localUrl.getDirectory());

    //Test a file in a directory
    localUrl = LocalUrl("Images/Tux Jedi.png");

    CPPUNIT_ASSERT_EQUAL(string("Images/"), localUrl.getDirectory());

    //Test a nested directory
    localUrl = LocalUrl("/usr/bin/mozilla-firefox");

    CPPUNIT_ASSERT_EQUAL(string("/usr/bin/"), localUrl.getDirectory());

    //Test a simple file
    localUrl = LocalUrl("README");

    CPPUNIT_ASSERT_EQUAL(string(""), localUrl.getDirectory());
}

void LocalUrlTest::testGetExtension() {
    //A simple file
    LocalUrl localUrl("Project.xmi");

    CPPUNIT_ASSERT_EQUAL(string("xmi"), localUrl.getExtension());

    //A file in a directory
    localUrl = LocalUrl("Xera/Lliendes/01 - Lliendes.ogg");

    CPPUNIT_ASSERT_EQUAL(string("ogg"), localUrl.getExtension());

    //A file in a directory with a dot in its name
    localUrl = LocalUrl("Packages/Games/glob2-0.8.19/Makefile.am");

    CPPUNIT_ASSERT_EQUAL(string("am"), localUrl.getExtension());

    //A file with more dots than the one of the extension
    localUrl = LocalUrl("supertux-0.1.3.tar.bz2");

    CPPUNIT_ASSERT_EQUAL(string("bz2"), localUrl.getExtension());

    //A directory
    localUrl = LocalUrl("Games/trackballs-1.1.1/");

    CPPUNIT_ASSERT_EQUAL(string(""), localUrl.getExtension());

    //A file without extension
    localUrl = LocalUrl("/usr/bin/amarok");

    CPPUNIT_ASSERT_EQUAL(string(""), localUrl.getExtension());

    //A hidden file without extension
    localUrl = LocalUrl(".bash_history");

    CPPUNIT_ASSERT_EQUAL(string(""), localUrl.getExtension());

    //A hidden file without extension in a directory
    localUrl = LocalUrl("/home/dani/.bash_history");

    CPPUNIT_ASSERT_EQUAL(string(""), localUrl.getExtension());

    //A hidden file with extension
    localUrl = LocalUrl(".hidden.tar");

    CPPUNIT_ASSERT_EQUAL(string("tar"), localUrl.getExtension());
}

void LocalUrlTest::testGetFileName() {
    //Test a simple file
    LocalUrl localUrl("INSTALL");

    CPPUNIT_ASSERT_EQUAL(string("INSTALL"), localUrl.getFileName());

    //Test a file in a directory
    localUrl = LocalUrl("Images/Logo.svg");

    CPPUNIT_ASSERT_EQUAL(string("Logo.svg"), localUrl.getFileName());

    //Test a file in a relative self directory
    localUrl = LocalUrl("./Images/Logo.svg");

    CPPUNIT_ASSERT_EQUAL(string("Logo.svg"), localUrl.getFileName());

    //Test a file in a relative parent directory
    localUrl = LocalUrl("../Images/Logo.svg");

    CPPUNIT_ASSERT_EQUAL(string("Logo.svg"), localUrl.getFileName());

    //Test a nested directory
    localUrl = LocalUrl("/usr/bin/konsole");

    CPPUNIT_ASSERT_EQUAL(string("konsole"), localUrl.getFileName());

    //Test a directory
    localUrl = LocalUrl("Documents/");

    CPPUNIT_ASSERT_EQUAL(string(""), localUrl.getFileName());
}

void LocalUrlTest::testGetPath() {
    LocalUrl localUrl("Photo/It's me!.png");

    CPPUNIT_ASSERT_EQUAL(string("Photo/It's me!.png"), localUrl.getPath());
}

void LocalUrlTest::testAppendRelativePathToDirectory() {
    //Test with directory and a relative file to append
    LocalUrl localUrl("test/");
    LocalUrl localUrlToAppend("lusi/util/LocalUrlTest.h");
    localUrl.appendRelativePathToDirectory(localUrlToAppend);

    CPPUNIT_ASSERT_EQUAL(string("test/lusi/util/LocalUrlTest.h"),
                         localUrl.getPath());

    //Test with directory and a relative directory to append
    localUrl = LocalUrl("task/");
    localUrlToAppend = LocalUrl("helper/");
    localUrl.appendRelativePathToDirectory(localUrlToAppend);

    CPPUNIT_ASSERT_EQUAL(string("task/helper/"), localUrl.getPath());

    //Test with absolute directory and relative path to parent
    localUrl = LocalUrl("/etc/");
    localUrlToAppend = LocalUrl("../usr/");
    localUrl.appendRelativePathToDirectory(localUrlToAppend);

    CPPUNIT_ASSERT_EQUAL(string("/usr/"), localUrl.getPath());

    //Test with a directory and an absolute path to append
    localUrl = LocalUrl("public_html/");
    localUrlToAppend = LocalUrl("/etc/");
    localUrl.appendRelativePathToDirectory(localUrlToAppend);

    CPPUNIT_ASSERT_EQUAL(string("public_html/"), localUrl.getPath());

    //Test with a file and an relative path to append
    localUrl = LocalUrl("public_html/index.html");
    localUrlToAppend = LocalUrl("downloads.html");
    localUrl.appendRelativePathToDirectory(localUrlToAppend);

    CPPUNIT_ASSERT_EQUAL(string("public_html/index.html"), localUrl.getPath());

    //Test with a file and an absolute path to append
    localUrl = LocalUrl("public_html/index.html");
    localUrlToAppend = LocalUrl("/etc/");
    localUrl.appendRelativePathToDirectory(localUrlToAppend);

    CPPUNIT_ASSERT_EQUAL(string("public_html/index.html"), localUrl.getPath());
}

void LocalUrlTest::testOperatorAssignment() {
    LocalUrl localUrl("/usr/local/bin/kdevelop");
    LocalUrl localUrlCopy = localUrl;

    CPPUNIT_ASSERT_EQUAL(string("/usr/local/bin/kdevelop"), localUrlCopy.mPath);


    //Test self assignment
    localUrlCopy = localUrlCopy;

    CPPUNIT_ASSERT_EQUAL(string("/usr/local/bin/kdevelop"), localUrlCopy.mPath);
}

void LocalUrlTest::testOperatorEqual() {
    //Test with equal urls
    LocalUrl localUrl("/usr/bin/konqueror");
    LocalUrl localUrl2("/usr/bin/konqueror");

    CPPUNIT_ASSERT(localUrl == localUrl2);

    //Test with different urls
    localUrl = LocalUrl("/usr/local/lib/kfolding_panelapplet.so");

    CPPUNIT_ASSERT(!(localUrl == localUrl2));

    //Test with different urls only in case
    localUrl = LocalUrl("/usr/bin/Konqueror");

    CPPUNIT_ASSERT(!(localUrl == localUrl2));
}

void LocalUrlTest::testOperatorDifferent() {
    //Test with equal urls
    LocalUrl localUrl("/usr/bin/konqueror");
    LocalUrl localUrl2("/usr/bin/konqueror");

    CPPUNIT_ASSERT(!(localUrl != localUrl2));

    //Test with different urls
    localUrl = LocalUrl("/usr/local/lib/kfolding_panelapplet.so");

    CPPUNIT_ASSERT(localUrl != localUrl2);

    //Test with different urls only in case
    localUrl = LocalUrl("/usr/bin/Konqueror");

    CPPUNIT_ASSERT(localUrl != localUrl2);
}

void LocalUrlTest::testCleanPath() {
    LocalUrl localUrl("");

    //Test with simple file
    CPPUNIT_ASSERT_EQUAL(string("LocalUrlTest.h"),
                         localUrl.cleanPath("LocalUrlTest.h"));

    //Test with file in a directory
    CPPUNIT_ASSERT_EQUAL(string("util/LocalUrlTest.h"),
                         localUrl.cleanPath("util/LocalUrlTest.h"));

    //Test with absolute directory
    CPPUNIT_ASSERT_EQUAL(string("/etc/fstab"),
                         localUrl.cleanPath("/etc/fstab"));

    //Test with relative directory to self
    CPPUNIT_ASSERT_EQUAL(string("util/"),
                         localUrl.cleanPath("./util/"));

    //Test with file in a directory relative to self
    CPPUNIT_ASSERT_EQUAL(string("util/LocalUrlTest.h"),
                         localUrl.cleanPath("./util/LocalUrlTest.h"));

    //Test with file in a directory relative to parent
    CPPUNIT_ASSERT_EQUAL(string("../util/LocalUrlTest.h"),
                         localUrl.cleanPath("../util/LocalUrlTest.h"));

    //Test with file in a directory nested with a directory relative to parent
    CPPUNIT_ASSERT_EQUAL(string("util/LocalUrlTest.h"),
                         localUrl.cleanPath("task/../util/LocalUrlTest.h"));

    //Test with file in an absolute directory nested with a directory relative
    //to parent
    CPPUNIT_ASSERT_EQUAL(string("/etc/fstab"),
                         localUrl.cleanPath("/usr/../etc/fstab"));

    //Test with directory in an absolute directory relative to parent
    CPPUNIT_ASSERT_EQUAL(string("/etc/"),
                         localUrl.cleanPath("/../../../etc/"));

    //Test with mixed relative directories to parent and self
    CPPUNIT_ASSERT_EQUAL(string("../lusi/Makefile.am"),
             localUrl.cleanPath("./task/../util/../../lusi/./Makefile.am"));

    //Test with absolute and mixed relative directories to parent and self
    CPPUNIT_ASSERT_EQUAL(string("/usr/bin/"),
                         localUrl.cleanPath("/.././../etc/../usr/bin/./"));
}
