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

#include "TaskConfigurationTest.h"

#define protected public
#define private public
#include "TaskConfiguration.h"
#include "Task.h"
#undef private
#undef protected

#include "../configuration/ConfigurationParameterTestImplementation.h"
#include "../package/Package.h"
#include "../package/PackageId.h"
#include "../package/status/PackageStatusTestImplementation.h"

using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationParameterTestImplementation;
using lusi::package::Package;
using lusi::package::PackageId;
using lusi::package::status::PackageStatusTestImplementation;
using lusi::util::SmartPtr;

using namespace lusi::task;

//public:

void TaskConfigurationTest::setUp() {
    mPackage = new Package(PackageId("testPackage"));
    mTask = new Task("MakeTests", mPackage,
                     PackageStatusTestImplementation::getFirstInstance(),
                     PackageStatusTestImplementation::getSecondInstance());
    mTaskConfiguration = mTask->mTaskConfiguration;
}

void TaskConfigurationTest::tearDown() {
    delete mTask;
    delete mPackage;
}

void TaskConfigurationTest::testConstructor() {
    //Test with a configuration not loaded
    CPPUNIT_ASSERT_EQUAL(mTask, mTaskConfiguration->mTask);
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterMap*)0,
                         mTaskConfiguration->mConfiguration);
    CPPUNIT_ASSERT(0 != mTaskConfiguration->mConfigurationToSave);
    CPPUNIT_ASSERT_EQUAL((size_t)0,
                    mTaskConfiguration->mConfigurationToSave->getAll().size());
}

void TaskConfigurationTest::testGetTaskHelperConfiguration() {
    //Test without a loaded configuration
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterMap*)0,
                   getPtr(mTaskConfiguration->getTaskHelperConfiguration("1")));

    //Test with a loaded configuration (simulated)
    mTaskConfiguration->mConfiguration = new
                    ConfigurationParameterMap("MakeTests", "",
                            ConfigurationParameter::RecommendedPriority, "");

    SmartPtr<ConfigurationParameterMap> configuration1(
                    new ConfigurationParameterMap("1", "1",
                            ConfigurationParameter::RequiredPriority, "1"));
    mTaskConfiguration->mConfiguration->add(configuration1);

    CPPUNIT_ASSERT_EQUAL(getPtr(configuration1),
                   getPtr(mTaskConfiguration->getTaskHelperConfiguration("1")));

    //Test with a parameter which is not a map
    SmartPtr<ConfigurationParameter> configuration2(
                    new ConfigurationParameterTestImplementation("2", "2",
                            ConfigurationParameter::RequiredPriority, "2"));
    mTaskConfiguration->mConfiguration->add(configuration2);

    CPPUNIT_ASSERT_EQUAL((ConfigurationParameterMap*)0,
                   getPtr(mTaskConfiguration->getTaskHelperConfiguration("2")));
    CPPUNIT_ASSERT_EQUAL(getPtr(configuration2),
                   getPtr(mTaskConfiguration->mConfiguration->get("2")));
}

void TaskConfigurationTest::testGetAllTaskHelperConfigurations() {
    //Test without a loaded configuration
    CPPUNIT_ASSERT_EQUAL((size_t)0,
                   mTaskConfiguration->getAllTaskHelperConfigurations().size());

    //Test with a loaded configuration (simulated)
    mTaskConfiguration->mConfiguration = new
                    ConfigurationParameterMap("MakeTests", "",
                            ConfigurationParameter::RecommendedPriority, "");

    SmartPtr<ConfigurationParameterMap> configuration1(
                    new ConfigurationParameterMap("1", "1",
                            ConfigurationParameter::RequiredPriority, "1"));
    SmartPtr<ConfigurationParameter> configuration2(
                    new ConfigurationParameterTestImplementation("2", "2",
                            ConfigurationParameter::RequiredPriority, "2"));
    SmartPtr<ConfigurationParameterMap> configuration3(
                    new ConfigurationParameterMap("3", "3",
                            ConfigurationParameter::RequiredPriority, "3"));

    mTaskConfiguration->mConfiguration->add(configuration3);
    mTaskConfiguration->mConfiguration->add(configuration1);
    mTaskConfiguration->mConfiguration->add(configuration2);

    vector< SmartPtr<ConfigurationParameterMap> > configurations =
                        mTaskConfiguration->getAllTaskHelperConfigurations();
    CPPUNIT_ASSERT_EQUAL((size_t)2, configurations.size());
    CPPUNIT_ASSERT_EQUAL(getPtr(configuration3), getPtr(configurations[0]));
    CPPUNIT_ASSERT_EQUAL(getPtr(configuration1), getPtr(configurations[1]));
}

void TaskConfigurationTest::testAddTaskHelperConfiguration() {
    SmartPtr<ConfigurationParameterMap> configuration1(
                        new ConfigurationParameterMap("1", "1",
                                ConfigurationParameter::RequiredPriority, "1"));

    mTaskConfiguration->addTaskHelperConfiguration(configuration1);
    CPPUNIT_ASSERT_EQUAL((size_t)1,
                    mTaskConfiguration->mConfigurationToSave->getAll().size());
    CPPUNIT_ASSERT(getPtr(configuration1) ==
                    getPtr(mTaskConfiguration->mConfigurationToSave->get("1")));
}
