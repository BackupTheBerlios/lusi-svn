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

#include "TaskTest.h"

#define protected public
#define private public
#include "Task.h"
#include "TaskConfiguration.h"
#include "TaskLogger.h"
#include "TaskProgress.h"
#undef private
#undef protected

#include "TaskLoggerObserverTestImplementation.h"
#include "TaskProgressObserverTestImplementation.h"
#include "helper/TaskHelperTestImplementation.h"
#include "../package/Package.h"
#include "../package/PackageId.h"
#include "../package/status/PackageStatusTestImplementation.h"

using std::string;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterMap;
using lusi::package::Package;
using lusi::package::PackageId;
using lusi::package::status::PackageStatus;
using lusi::package::status::PackageStatusTestImplementation;
using lusi::task::helper::TaskHelper;
using lusi::task::helper::TaskHelperTestImplementation;
using lusi::util::SmartPtr;

using namespace lusi::task;

//public:

void TaskTest::setUp() {
    mPackage = new Package(PackageId("testPackage"));
    mTask = new Task("MakeTests", mPackage,
                     PackageStatusTestImplementation::getFirstInstance(),
                     PackageStatusTestImplementation::getSecondInstance());

    mTask->mTaskHelpers.push_back(new TaskHelperTestImplementation(mTask, "1"));
    mTask->mTaskHelpers.push_back(new TaskHelperTestImplementation(mTask, "2",
                                                                   true));
    mTask->mTaskHelpers.push_back(new TaskHelperTestImplementation(mTask, "3",
                                                                   true));
    mTask->mTaskHelpersIterator = mTask->mTaskHelpers.begin();

    mTask->mTaskConfiguration->mConfiguration =
        new ConfigurationParameterMap("MakeTests", "",
            ConfigurationParameter::RequiredPriority, "");
}

void TaskTest::tearDown() {
    delete mTask;
    delete mPackage;
}

void TaskTest::testGetName() {
    CPPUNIT_ASSERT_EQUAL(string("MakeTests"), mTask->getName());
}

void TaskTest::testGetPackage() {
    CPPUNIT_ASSERT_EQUAL(mPackage, mTask->getPackage());
}

void TaskTest::testGetTaskConfiguration() {
    CPPUNIT_ASSERT_EQUAL(mTask->mTaskConfiguration,
                         mTask->getTaskConfiguration());
}

void TaskTest::testGetNeededPackageStatus() {
    CPPUNIT_ASSERT_EQUAL((const PackageStatus*)
            PackageStatusTestImplementation::getFirstInstance(),
            mTask->getNeededPackageStatus());
}

void TaskTest::testGetProvidedPackageStatus() {
    CPPUNIT_ASSERT_EQUAL((const PackageStatus*)
            PackageStatusTestImplementation::getSecondInstance(),
            mTask->getProvidedPackageStatus());
}

void TaskTest::testGetTaskLogger() {
    TaskLoggerObserverTestImplementation* observer =
            new TaskLoggerObserverTestImplementation();
    mTask->getTaskLogger()->attachObserver(observer);
    mTask->getTaskLogger()->notifyEvent("The Spanish omelette is ready",
                                        message);

    CPPUNIT_ASSERT_EQUAL(mTask, observer->getTask());

    delete observer;
}

void TaskTest::testGetTaskProgress() {
    TaskProgressObserverTestImplementation* observer =
            new TaskProgressObserverTestImplementation();
    mTask->getTaskProgress()->attachObserver(observer);
    mTask->getTaskProgress()->notifyProgress(100);

    CPPUNIT_ASSERT_EQUAL(mTask, observer->getTask());

    delete observer;
}

void TaskTest::testGetTaskHelperConfiguration() {
    //TaskHelper "2"
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT_EQUAL(
            getPtr(mTask->mCurrentTaskHelper->getConfigurationParameterMap()),
            getPtr(mTask->getTaskHelperConfiguration()));
    //TaskHelper "3"
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT_EQUAL(
            getPtr(mTask->mCurrentTaskHelper->getConfigurationParameterMap()),
            getPtr(mTask->getTaskHelperConfiguration()));
    //No more TaskHelpers
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterMap*)0,
                         getPtr(mTask->getTaskHelperConfiguration()));
}

void TaskTest::testGetInvalidConfiguration() {
    //TaskHelper "2"
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(
            mTask->mCurrentTaskHelper->getInvalidConfiguration()->getAll() ==
            mTask->getInvalidConfiguration()->getAll());
    //TaskHelper "3"
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(
            mTask->mCurrentTaskHelper->getInvalidConfiguration()->getAll() ==
            mTask->getInvalidConfiguration()->getAll());
    //No more TaskHelpers
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterMap*)0,
                         getPtr(mTask->getInvalidConfiguration()));
}

void TaskTest::testNextTaskHelper() {
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(mTask->mCurrentTaskHelper != 0);
    CPPUNIT_ASSERT_EQUAL(string("2"), mTask->mCurrentTaskHelper->getName());
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(mTask->mCurrentTaskHelper != 0);
    CPPUNIT_ASSERT_EQUAL(string("3"), mTask->mCurrentTaskHelper->getName());
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(mTask->mCurrentTaskHelper == 0);
    //Try to go out of bounds
    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(mTask->mCurrentTaskHelper == 0);

    //Test with no available taskHelpers
    delete mTask;
    mTask = new Task("MakeTests", mPackage,
                     PackageStatusTestImplementation::getFirstInstance(),
                     PackageStatusTestImplementation::getSecondInstance());

    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(mTask->mCurrentTaskHelper == 0);

    //Test with only one available taskHelper, but without valid resources
    delete mTask;
    mTask = new Task("MakeTests", mPackage,
                     PackageStatusTestImplementation::getFirstInstance(),
                     PackageStatusTestImplementation::getSecondInstance());

    mTask->mTaskHelpers.push_back(new TaskHelperTestImplementation(mTask, "1"));
    mTask->mTaskHelpersIterator = mTask->mTaskHelpers.begin();

    mTask->nextTaskHelper();
    CPPUNIT_ASSERT(mTask->mCurrentTaskHelper == 0);
}

void TaskTest::testSortTaskHelpers() {
    //Test with no loaded TaskHelpers
    mTask->sortTaskHelpers();

    CPPUNIT_ASSERT_EQUAL(string("1"), mTask->mTaskHelpers[0]->getName());
    CPPUNIT_ASSERT_EQUAL(string("2"), mTask->mTaskHelpers[1]->getName());
    CPPUNIT_ASSERT_EQUAL(string("3"), mTask->mTaskHelpers[2]->getName());

    //Test with one loaded TaskHelper
    restartTestObjects();

    SmartPtr<ConfigurationParameterMap> configuration1(
        new ConfigurationParameterMap("1", "",
            ConfigurationParameter::OptionalPriority, ""));
    mTask->mTaskConfiguration->mConfiguration->add(configuration1);

    mTask->sortTaskHelpers();

    CPPUNIT_ASSERT_EQUAL(string("1"), mTask->mTaskHelpers[0]->getName());
    CPPUNIT_ASSERT_EQUAL(string("2"), mTask->mTaskHelpers[1]->getName());
    CPPUNIT_ASSERT_EQUAL(string("3"), mTask->mTaskHelpers[2]->getName());

    //Test with two loaded TaskHelpers
    restartTestObjects();

    SmartPtr<ConfigurationParameterMap> configuration3(
        new ConfigurationParameterMap("3", "",
            ConfigurationParameter::OptionalPriority, ""));
    mTask->mTaskConfiguration->mConfiguration->add(configuration3);
    mTask->mTaskConfiguration->mConfiguration->add(configuration1);

    mTask->sortTaskHelpers();

    CPPUNIT_ASSERT_EQUAL(string("3"), mTask->mTaskHelpers[0]->getName());
    CPPUNIT_ASSERT_EQUAL(string("1"), mTask->mTaskHelpers[1]->getName());
    CPPUNIT_ASSERT_EQUAL(string("2"), mTask->mTaskHelpers[2]->getName());

    //Test with three loaded TaskHelpers, the first of them not available in the
    //TaskHelpers list
    restartTestObjects();

    SmartPtr<ConfigurationParameterMap> configuration4(
        new ConfigurationParameterMap("4", "",
            ConfigurationParameter::OptionalPriority, ""));
    SmartPtr<ConfigurationParameterMap> configuration2(
        new ConfigurationParameterMap("2", "",
            ConfigurationParameter::OptionalPriority, ""));
    mTask->mTaskConfiguration->mConfiguration->add(configuration4);
    mTask->mTaskConfiguration->mConfiguration->add(configuration2);
    mTask->mTaskConfiguration->mConfiguration->add(configuration3);

    mTask->sortTaskHelpers();

    CPPUNIT_ASSERT_EQUAL(string("2"), mTask->mTaskHelpers[0]->getName());
    CPPUNIT_ASSERT_EQUAL(string("3"), mTask->mTaskHelpers[1]->getName());
    CPPUNIT_ASSERT_EQUAL(string("1"), mTask->mTaskHelpers[2]->getName());

    //Test with three loaded TaskHelpers, the last of them not available in the
    //TaskHelpers list
    restartTestObjects();

    mTask->mTaskConfiguration->mConfiguration->add(configuration3);
    mTask->mTaskConfiguration->mConfiguration->add(configuration2);
    mTask->mTaskConfiguration->mConfiguration->add(configuration4);

    mTask->sortTaskHelpers();

    CPPUNIT_ASSERT_EQUAL(string("3"), mTask->mTaskHelpers[0]->getName());
    CPPUNIT_ASSERT_EQUAL(string("2"), mTask->mTaskHelpers[1]->getName());
    CPPUNIT_ASSERT_EQUAL(string("1"), mTask->mTaskHelpers[2]->getName());
}

//private:

void TaskTest::restartTestObjects() {
    tearDown();
    setUp();
}
