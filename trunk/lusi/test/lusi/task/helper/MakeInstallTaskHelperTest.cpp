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

#include <vector>

#include "MakeInstallTaskHelperTest.h"

#define protected public
#define private public
#include "MakeInstallTaskHelper.h"
#undef private
#undef protected

#include "../TaskTestImplementation.h"
#include "../../package/LocalFileResource.h"
#include "../../package/Package.h"
#include "../../package/ResourceMap.h"
#include "../../util/SmartPtr.h"

using std::string;

using lusi::configuration::ConfigurationParameterString;
using lusi::package::LocalFileResource;
using lusi::package::Resource;
using lusi::task::TaskTestImplementation;
using lusi::util::Process;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void MakeInstallTaskHelperTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mMakeInstallTaskHelper = new MakeInstallTaskHelper("MakeInstallTaskHelper",
                                                       mTask, "install");
}

void MakeInstallTaskHelperTest::tearDown() {
    delete mMakeInstallTaskHelper;
    delete mTask;
}

void MakeInstallTaskHelperTest::testConstructor() {
    CPPUNIT_ASSERT_EQUAL(string("MakeInstallTaskHelper"),
                         mMakeInstallTaskHelper->mName);
    CPPUNIT_ASSERT_EQUAL(mTask, mMakeInstallTaskHelper->mTask);
    CPPUNIT_ASSERT_EQUAL(string("install"),
                         mMakeInstallTaskHelper->mMakeTarget);
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterString*)0,
                         mMakeInstallTaskHelper->mUserName);
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterString*)0,
                         mMakeInstallTaskHelper->mPassword);
}

void MakeInstallTaskHelperTest::testGetProcess() {
    //Test with an install make target
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/package/")));
    mTask->getPackage()->getResourceMap()->add(
        SmartPtr<Resource>(new LocalFileResource("/package/subDirectory/")));
    delete mMakeInstallTaskHelper;
    mMakeInstallTaskHelper = new MakeInstallTaskHelper("MakeInstallTaskHelper",
                                                       mTask, "install");

    SmartPtr<Process> process(mMakeInstallTaskHelper->getProcess());

    CPPUNIT_ASSERT_EQUAL(string("/package/"), process->getWorkingDirectory());
    CPPUNIT_ASSERT_EQUAL(string("make"), process->getArguments()[0]);
    CPPUNIT_ASSERT_EQUAL(string("install"), process->getArguments()[1]);
    CPPUNIT_ASSERT_EQUAL((size_t)2, process->getArguments().size());

    //Test with an uninstall make target
    delete mMakeInstallTaskHelper;
    mMakeInstallTaskHelper = new MakeInstallTaskHelper("MakeInstallTaskHelper",
                                                       mTask, "uninstall");

    process = SmartPtr<Process>(mMakeInstallTaskHelper->getProcess());

    CPPUNIT_ASSERT_EQUAL(string("/package/"), process->getWorkingDirectory());
    CPPUNIT_ASSERT_EQUAL(string("make"), process->getArguments()[0]);
    CPPUNIT_ASSERT_EQUAL(string("uninstall"), process->getArguments()[1]);
    CPPUNIT_ASSERT_EQUAL((size_t)2, process->getArguments().size());
}
