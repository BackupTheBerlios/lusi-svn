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

#include "ConfigurationParameterMapTest.h"

#define protected public
#define private public
#include "ConfigurationParameterMap.h"
#undef private
#undef protected

#include "ConfigurationParameterTestImplementation.h"

using std::string;

using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

void ConfigurationParameterMapTest::setUp() {
    mConfigurationParameterMap = new ConfigurationParameterMap("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter", ConfigurationParameterMap::AndPolicy);
}

void ConfigurationParameterMapTest::tearDown() {
    delete mConfigurationParameterMap;
}

void ConfigurationParameterMapTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterMap->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterMap->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterMap->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterMap->mInformation);
    CPPUNIT_ASSERT_EQUAL((size_t)0,
        mConfigurationParameterMap->mConfigurationParameters.getAll().size());
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterMap::AndPolicy,
                         mConfigurationParameterMap->mInvalidPolicy);

    //Test without setting the invalid policy
    delete mConfigurationParameterMap;
    mConfigurationParameterMap = new ConfigurationParameterMap("Test2",
                "Test name 2", ConfigurationParameter::RequiredPriority,
                "Another test parameter");

    CPPUNIT_ASSERT_EQUAL(string("Test2"), mConfigurationParameterMap->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name 2"),
                         mConfigurationParameterMap->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterMap->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterMap->mInformation);
    CPPUNIT_ASSERT_EQUAL((size_t)0,
        mConfigurationParameterMap->mConfigurationParameters.getAll().size());
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterMap::NoPolicy,
                         mConfigurationParameterMap->mInvalidPolicy);
}

void ConfigurationParameterMapTest::testIsInvalid() {
    SmartPtr<ConfigurationParameterTestImplementation> parameter1(
                        new ConfigurationParameterTestImplementation("1", "1",
                                ConfigurationParameter::RequiredPriority, "1"));
    SmartPtr<ConfigurationParameterTestImplementation> parameter2(
                        new ConfigurationParameterTestImplementation("2", "2",
                                ConfigurationParameter::RequiredPriority, "2"));
    SmartPtr<ConfigurationParameterTestImplementation> parameter3(
                        new ConfigurationParameterTestImplementation("3", "3",
                                ConfigurationParameter::RequiredPriority, "3"));

    //Test with no policy
    mConfigurationParameterMap->mInvalidPolicy =
                                        ConfigurationParameterMap::NoPolicy;

    //Test with an empty vector
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with an invalid parameter
    parameter1->setInvalid(true);
    mConfigurationParameterMap->add(parameter1);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with a valid parameter
    parameter1->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with two valid parameters and one invalid parameter
    parameter2->setInvalid(false);
    mConfigurationParameterMap->add(parameter2);

    parameter3->setInvalid(true);
    mConfigurationParameterMap->add(parameter3);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with three valid parameters
    parameter3->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());



    //Test with "and" policy
    mConfigurationParameterMap->remove("1");
    mConfigurationParameterMap->remove("2");
    mConfigurationParameterMap->remove("3");
    mConfigurationParameterMap->mInvalidPolicy =
                                        ConfigurationParameterMap::AndPolicy;

    //Test with an empty vector
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with an invalid parameter
    parameter1->setInvalid(true);
    mConfigurationParameterMap->add(parameter1);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterMap->isInvalid());

    //Test with a vector with a valid parameter
    parameter1->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with two valid parameters and one invalid parameter
    parameter2->setInvalid(false);
    mConfigurationParameterMap->add(parameter2);

    parameter3->setInvalid(true);
    mConfigurationParameterMap->add(parameter3);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterMap->isInvalid());

    //Test with a vector with three valid parameters
    parameter3->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());



    //Test with "or" policy
    mConfigurationParameterMap->remove("1");
    mConfigurationParameterMap->remove("2");
    mConfigurationParameterMap->remove("3");
    mConfigurationParameterMap->mInvalidPolicy =
                                        ConfigurationParameterMap::OrPolicy;

    //Test with an empty vector
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with an invalid parameter
    parameter1->setInvalid(true);
    mConfigurationParameterMap->add(parameter1);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterMap->isInvalid());

    //Test with a vector with a valid parameter
    parameter1->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with two valid parameters and one invalid parameter
    parameter2->setInvalid(false);
    mConfigurationParameterMap->add(parameter2);

    parameter3->setInvalid(true);
    mConfigurationParameterMap->add(parameter3);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->isInvalid());

    //Test with a vector with three invalid parameters
    parameter1->setInvalid(true);
    parameter2->setInvalid(true);
    parameter3->setInvalid(true);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterMap->isInvalid());
}

void ConfigurationParameterMapTest::testAdd() {
    SmartPtr<ConfigurationParameter> parameter1(
                        new ConfigurationParameterTestImplementation("1", "1",
                                ConfigurationParameter::RequiredPriority, "1"));

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterMap->add(parameter1));

    CPPUNIT_ASSERT_EQUAL(getPtr(parameter1),
        getPtr(mConfigurationParameterMap->mConfigurationParameters.get("1")));

    //Test adding twice
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->add(parameter1));
}

void ConfigurationParameterMapTest::testGet() {
    SmartPtr<ConfigurationParameter> parameter1(
                        new ConfigurationParameterTestImplementation("1", "1",
                                ConfigurationParameter::RequiredPriority, "1"));
    mConfigurationParameterMap->add(parameter1);

    CPPUNIT_ASSERT_EQUAL(
        getPtr(mConfigurationParameterMap->mConfigurationParameters.get("1")),
        getPtr(mConfigurationParameterMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter1),
                         getPtr(mConfigurationParameterMap->get("1")));
}

void ConfigurationParameterMapTest::testGetAll() {
    SmartPtr<ConfigurationParameter> parameter1(
                        new ConfigurationParameterTestImplementation("1", "1",
                                ConfigurationParameter::RequiredPriority, "1"));
    SmartPtr<ConfigurationParameter> parameter2(
                        new ConfigurationParameterTestImplementation("2", "2",
                                ConfigurationParameter::RequiredPriority, "2"));
    SmartPtr<ConfigurationParameter> parameter3(
                        new ConfigurationParameterTestImplementation("3", "3",
                                ConfigurationParameter::RequiredPriority, "3"));
    mConfigurationParameterMap->add(parameter1);
    mConfigurationParameterMap->add(parameter2);
    mConfigurationParameterMap->add(parameter3);

    CPPUNIT_ASSERT(
            mConfigurationParameterMap->mConfigurationParameters.getAll() ==
            mConfigurationParameterMap->getAll());
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter1),
                         getPtr(mConfigurationParameterMap->getAll()[0]));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter2),
                         getPtr(mConfigurationParameterMap->getAll()[1]));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter3),
                         getPtr(mConfigurationParameterMap->getAll()[2]));
}

void ConfigurationParameterMapTest::testRemove() {
    SmartPtr<ConfigurationParameter> parameter1(
                        new ConfigurationParameterTestImplementation("1", "1",
                                ConfigurationParameter::RequiredPriority, "1"));
    mConfigurationParameterMap->add(parameter1);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterMap->remove("1"));
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameter*)0,
        getPtr(mConfigurationParameterMap->mConfigurationParameters.get("1")));

    //Test removing twice
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterMap->remove("1"));
}

void ConfigurationParameterMapTest::testGetInvalidPolicy() {
    mConfigurationParameterMap->mInvalidPolicy =
                                        ConfigurationParameterMap::AndPolicy;
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterMap::AndPolicy,
                         mConfigurationParameterMap->getInvalidPolicy());

    mConfigurationParameterMap->mInvalidPolicy =
                                        ConfigurationParameterMap::NoPolicy;
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterMap::NoPolicy,
                         mConfigurationParameterMap->getInvalidPolicy());
}

void ConfigurationParameterMapTest::testMerge() {
    delete mConfigurationParameterMap;
    mConfigurationParameterMap = new ConfigurationParameterMap("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter");

    ConfigurationParameterMap configurationParameterMap("Test2",
                "Test name 2", ConfigurationParameter::RequiredPriority,
                "Another test parameter");

    SmartPtr<ConfigurationParameter> parameter1(
            new ConfigurationParameterTestImplementation("1", "1",
                    ConfigurationParameter::RequiredPriority, "1"));
    SmartPtr<ConfigurationParameter> parameter2(
            new ConfigurationParameterTestImplementation("2", "2",
                    ConfigurationParameter::RequiredPriority, "2"));
    SmartPtr<ConfigurationParameter> parameter3(
            new ConfigurationParameterTestImplementation("3", "3",
                    ConfigurationParameter::RequiredPriority, "3a"));
    SmartPtr<ConfigurationParameter> parameter3B(
            new ConfigurationParameterTestImplementation("3", "3",
                    ConfigurationParameter::RecommendedPriority, "3b"));

    mConfigurationParameterMap->add(parameter1);
    mConfigurationParameterMap->add(parameter3);
    configurationParameterMap.add(parameter2);
    configurationParameterMap.add(parameter3B);

    //Test keep merge
    mConfigurationParameterMap->merge(configurationParameterMap);

    CPPUNIT_ASSERT_EQUAL(getPtr(parameter1),
                         getPtr(mConfigurationParameterMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter2),
                         getPtr(mConfigurationParameterMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter3),
                         getPtr(mConfigurationParameterMap->get("3")));
    CPPUNIT_ASSERT_EQUAL((size_t)3,
                         mConfigurationParameterMap->getAll().size());

    //Test override merge
    SmartPtr<ConfigurationParameter> parameter4(
            new ConfigurationParameterTestImplementation("4", "4",
                    ConfigurationParameter::RequiredPriority, "4"));
    configurationParameterMap.add(parameter4);

    mConfigurationParameterMap->merge(configurationParameterMap,
                                ConfigurationParameterMap::OverrideParameters);


    CPPUNIT_ASSERT_EQUAL(getPtr(parameter1),
                         getPtr(mConfigurationParameterMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter2),
                         getPtr(mConfigurationParameterMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter3B),
                         getPtr(mConfigurationParameterMap->get("3")));
    CPPUNIT_ASSERT_EQUAL(getPtr(parameter4),
                         getPtr(mConfigurationParameterMap->get("4")));
    CPPUNIT_ASSERT_EQUAL((size_t)4,
                         mConfigurationParameterMap->getAll().size());
}
