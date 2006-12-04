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

#include "ConfigurationParameterTest.h"

#define protected public
#define private public
#include "ConfigurationParameterTestImplementation.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterTest::setUp() {
    mConfigurationParameter = new ConfigurationParameterTestImplementation(
        "Test", "Test name", ConfigurationParameter::RequiredPriority,
        "A test parameter");
}

void ConfigurationParameterTest::tearDown() {
    delete mConfigurationParameter;
}

void ConfigurationParameterTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameter->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"), mConfigurationParameter->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameter->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameter->mInformation);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameter->mSerializable);

    //Test with the id
    delete mConfigurationParameter;
    mConfigurationParameter = new ConfigurationParameterTestImplementation(
        "Test2");

    CPPUNIT_ASSERT_EQUAL(string("Test2"), mConfigurationParameter->mId);
    CPPUNIT_ASSERT_EQUAL(string(""), mConfigurationParameter->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::NoPriority,
                         mConfigurationParameter->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string(""), mConfigurationParameter->mInformation);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameter->mSerializable);
}

void ConfigurationParameterTest::testGetId() {
    mConfigurationParameter->mId = "SomethingUnique";

    CPPUNIT_ASSERT_EQUAL(string("SomethingUnique"),
                         mConfigurationParameter->getId());
}

void ConfigurationParameterTest::testGetName() {
    mConfigurationParameter->mId = "Only a name";

    CPPUNIT_ASSERT_EQUAL(string("Only a name"),
                         mConfigurationParameter->getId());
}

void ConfigurationParameterTest::testGetInformation() {
    mConfigurationParameter->mInformation = "Informative text";

    CPPUNIT_ASSERT_EQUAL(string("Informative text"),
                         mConfigurationParameter->getInformation());
}

void ConfigurationParameterTest::testGetPriorityType() {
    mConfigurationParameter->mPriorityType =
                            ConfigurationParameter::RecommendedPriority;

    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RecommendedPriority,
                         mConfigurationParameter->getPriorityType());
}

void ConfigurationParameterTest::testIsSerializable() {
    mConfigurationParameter->mSerializable = false;

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameter->isSerializable());
}

void ConfigurationParameterTest::testSetSerializable() {
    mConfigurationParameter->setSerializable(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameter->mSerializable);
}
