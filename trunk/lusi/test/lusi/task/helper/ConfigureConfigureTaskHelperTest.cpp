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

#include <memory>
#include <vector>

#include "ConfigureConfigureTaskHelperTest.h"

#define protected public
#define private public
#include "ConfigureConfigureTaskHelper.h"
#undef private
#undef protected

#include "../TaskConfiguration.h"
#include "../TaskTestImplementation.h"
#include "../../package/LocalFileResource.h"
#include "../../package/Package.h"
#include "../../package/PackageId.h"
#include "../../package/ResourceMap.h"
#include "../../util/LocalUrl.h"
#include "../../util/SmartPtr.h"

using std::auto_ptr;
using std::string;
using std::vector;

using lusi::package::LocalFileResource;
using lusi::package::Package;
using lusi::package::PackageId;
using lusi::package::Resource;
using lusi::task::TaskTestImplementation;
using lusi::task::TaskConfiguration;
using lusi::util::Process;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void ConfigureConfigureTaskHelperTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mConfigureConfigureTaskHelper = new ConfigureConfigureTaskHelper(mTask);
}

void ConfigureConfigureTaskHelperTest::tearDown() {
    delete mConfigureConfigureTaskHelper;
    delete mTask;
}

void ConfigureConfigureTaskHelperTest::testConstructor() {
    //Test the empty ResourceMap used by default
    CPPUNIT_ASSERT_EQUAL(string(""),
                mConfigureConfigureTaskHelper->mPackageDirectory->getPath());

    //Test with a ResourceMap without a package directory
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/configure")));
    delete mConfigureConfigureTaskHelper;
    mConfigureConfigureTaskHelper = new ConfigureConfigureTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(string(""),
                mConfigureConfigureTaskHelper->mPackageDirectory->getPath());

    //Test with a ResourceMap with a valid package directory
    mTask->getPackage()->getResourceMap()->remove("/configure");
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/package/")));
    delete mConfigureConfigureTaskHelper;
    mConfigureConfigureTaskHelper = new ConfigureConfigureTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(string("/package/"),
                mConfigureConfigureTaskHelper->mPackageDirectory->getPath());
}

void ConfigureConfigureTaskHelperTest::testHasValidResourceMap() {
    //Test the empty ResourceMap used by default
    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigureConfigureTaskHelper->hasValidResourceMap());

    //Test with a ResourceMap without a package directory
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/configure")));
    delete mConfigureConfigureTaskHelper;
    mConfigureConfigureTaskHelper = new ConfigureConfigureTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigureConfigureTaskHelper->hasValidResourceMap());

    //Test with a ResourceMap with a package directory but without a configure
    mTask->getPackage()->getResourceMap()->remove("/configure");
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/package/")));
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/package/COPYING")));
    delete mConfigureConfigureTaskHelper;
    mConfigureConfigureTaskHelper = new ConfigureConfigureTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigureConfigureTaskHelper->hasValidResourceMap());

    //Test with a ResourceMap with a configure script in the package directory
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/package/configure")));
    delete mConfigureConfigureTaskHelper;
    mConfigureConfigureTaskHelper = new ConfigureConfigureTaskHelper(mTask);

    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigureConfigureTaskHelper->hasValidResourceMap());
}

void ConfigureConfigureTaskHelperTest::testGetProcess() {
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/package/")));
    mTask->getPackage()->getResourceMap()->add(
        SmartPtr<Resource>(new LocalFileResource("/package/subDirectory/")));
    delete mConfigureConfigureTaskHelper;
    mConfigureConfigureTaskHelper = new ConfigureConfigureTaskHelper(mTask);
    mConfigureConfigureTaskHelper->initConfigurationParameterMap();

    auto_ptr<Process> process(mConfigureConfigureTaskHelper->getProcess());

    CPPUNIT_ASSERT_EQUAL(string("/package/"), process->getWorkingDirectory());
    CPPUNIT_ASSERT_EQUAL(string("/bin/sh"), process->getArguments()[0]);
    CPPUNIT_ASSERT_EQUAL(string("-c"), process->getArguments()[1]);
    CPPUNIT_ASSERT_EQUAL(string("./configure --prefix=/usr/local/"),
                         process->getArguments()[2]);
    CPPUNIT_ASSERT_EQUAL(vector<string>::size_type(3),
                         process->getArguments().size());
}
