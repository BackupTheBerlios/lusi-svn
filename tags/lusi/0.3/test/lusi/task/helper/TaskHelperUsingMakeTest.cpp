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

#include "TaskHelperUsingMakeTest.h"

#define protected public
#define private public
#include "TaskHelperUsingMakeTestImplementation.h"
#undef private
#undef protected

#include "../TaskTestImplementation.h"
#include "../../configuration/ConfigurationParameterLocalUrl.h"
#include "../../package/Package.h"
#include "../../util/LocalUrl.h"

using std::string;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::task::TaskTestImplementation;
using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void TaskHelperUsingMakeTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mTaskHelperUsingMake = new TaskHelperUsingMakeTestImplementation(mTask);
}

void TaskHelperUsingMakeTest::tearDown() {
    delete mTaskHelperUsingMake;
    delete mTask;
}

void TaskHelperUsingMakeTest::testConstructor() {
    //Test the empty resource files used by default
    CPPUNIT_ASSERT_EQUAL(string(""),
                         mTaskHelperUsingMake->mPackageDirectory->getPath());

    //Test with resource files without a package directory
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/Makefile", LocalUrl("/Makefile"))));
    delete mTaskHelperUsingMake;
    mTaskHelperUsingMake = new TaskHelperUsingMakeTestImplementation(mTask);

    CPPUNIT_ASSERT_EQUAL(string(""),
                         mTaskHelperUsingMake->mPackageDirectory->getPath());

    //Test with resource files with a valid package directory
    mTask->getPackage()->getResourceFiles()->remove("/Makefile");
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/package/", LocalUrl("/package/"))));
    delete mTaskHelperUsingMake;
    mTaskHelperUsingMake = new TaskHelperUsingMakeTestImplementation(mTask);

    CPPUNIT_ASSERT_EQUAL(string("/package/"),
                         mTaskHelperUsingMake->mPackageDirectory->getPath());
}

void TaskHelperUsingMakeTest::testHasValidResources() {
    //Test the empty resource files used by default
    CPPUNIT_ASSERT_EQUAL(false, mTaskHelperUsingMake->hasValidResources());

    //Test with resource files without a package directory
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/Makefile", LocalUrl("/Makefile"))));
    delete mTaskHelperUsingMake;
    mTaskHelperUsingMake = new TaskHelperUsingMakeTestImplementation(mTask);

    CPPUNIT_ASSERT_EQUAL(false, mTaskHelperUsingMake->hasValidResources());

    //Test with resource files with a package directory but without a Makefile
    mTask->getPackage()->getResourceFiles()->remove("/Makefile");
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/package/", LocalUrl("/package/"))));
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/package/COPYING", LocalUrl("/package/COPYING"))));
    delete mTaskHelperUsingMake;
    mTaskHelperUsingMake = new TaskHelperUsingMakeTestImplementation(mTask);

    CPPUNIT_ASSERT_EQUAL(false, mTaskHelperUsingMake->hasValidResources());

    //Test with resource files with a Makefile in the package directory
    mTask->getPackage()->getResourceFiles()->add(
        SmartPtr<ConfigurationParameter>(new ConfigurationParameterLocalUrl(
            "/package/Makefile", LocalUrl("/package/Makefile"))));
    delete mTaskHelperUsingMake;
    mTaskHelperUsingMake = new TaskHelperUsingMakeTestImplementation(mTask);

    CPPUNIT_ASSERT_EQUAL(true, mTaskHelperUsingMake->hasValidResources());
}
