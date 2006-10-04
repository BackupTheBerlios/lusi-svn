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

#include "ConfigurationParameterSimpleTest.h"

#define protected public
#define private public
#include "ConfigurationParameterSimpleTestImplementation.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterSimpleTest::setUp() {
    mConfigurationParameterSimple = new
            ConfigurationParameterSimpleTestImplementation("Test", "Test name",
                    ConfigurationParameter::RequiredPriority,
                    "A test parameter", "Default");
}

void ConfigurationParameterSimpleTest::tearDown() {
    delete mConfigurationParameterSimple;
}

void ConfigurationParameterSimpleTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterSimple->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterSimple->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterSimple->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterSimple->mInformation);
    CPPUNIT_ASSERT_EQUAL(string("Default"),
                         mConfigurationParameterSimple->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterSimple->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->mValueSet);

    //Test without setting the default value
    delete mConfigurationParameterSimple;
    mConfigurationParameterSimple =
            new ConfigurationParameterSimpleTestImplementation("Another test",
                    "Test name2", ConfigurationParameter::OptionalPriority,
                    "Another test parameter");

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterSimple->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterSimple->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterSimple->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterSimple->mInformation);
    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterSimple->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->mValueSet);
}

void ConfigurationParameterSimpleTest::testIsInvalid() {
    //Test with a required priority and value and default value not set
    mConfigurationParameterSimple->mDefaultValueSet = false;
    mConfigurationParameterSimple->mValueSet = false;

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterSimple->isInvalid());

    //Test with required priority, value set and default value not set
    mConfigurationParameterSimple->mValueSet = true;

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->isInvalid());

    //Test with required priority, value not set and default value set
    mConfigurationParameterSimple->mDefaultValueSet = false;
    mConfigurationParameterSimple->mDefaultValueSet = true;

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->isInvalid());

    //Test with recommended priority and value and default value not set
    mConfigurationParameterSimple->mDefaultValueSet = false;
    mConfigurationParameterSimple->mValueSet = false;
    mConfigurationParameterSimple->mPriorityType =
                            ConfigurationParameter::RecommendedPriority;

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->isInvalid());

    //Test with optional priority and value and default value not set
    mConfigurationParameterSimple->mPriorityType =
                            ConfigurationParameter::OptionalPriority;
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->isInvalid());
}

void ConfigurationParameterSimpleTest::testGetDefaultValue() {
    mConfigurationParameterSimple->mDefaultValue = "Some default value";

    CPPUNIT_ASSERT_EQUAL(string("Some default value"),
                         mConfigurationParameterSimple->getDefaultValue());
}

void ConfigurationParameterSimpleTest::testGetValue() {
    //Test with a set value and default value
    mConfigurationParameterSimple->mValue = "Some value";
    mConfigurationParameterSimple->mValueSet = true;

    CPPUNIT_ASSERT_EQUAL(string("Some value"),
                         mConfigurationParameterSimple->getValue());

    //Test with a set value and not set default value
    mConfigurationParameterSimple->mDefaultValueSet = false;

    CPPUNIT_ASSERT_EQUAL(string("Some value"),
                         mConfigurationParameterSimple->getValue());

    //Test with a not set value and a default value
    mConfigurationParameterSimple->mValueSet = false;
    mConfigurationParameterSimple->mDefaultValueSet = true;

    CPPUNIT_ASSERT_EQUAL(string("Default"),
                         mConfigurationParameterSimple->getValue());
}

void ConfigurationParameterSimpleTest::testIsDefaultValue() {
    //Test with default value and without value
    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterSimple->isDefaultValue());

    //Test with default value and with value equal to the default value
    mConfigurationParameterSimple->mValue = "Default";
    mConfigurationParameterSimple->mValueSet = true;

    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterSimple->isDefaultValue());

    //Test with a value different than the default value
    mConfigurationParameterSimple->mValue = "No default value";

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterSimple->isDefaultValue());

    //Test without default value
    mConfigurationParameterSimple->mDefaultValueSet = false;

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterSimple->isDefaultValue());
}

void ConfigurationParameterSimpleTest::testIsDefaultValueSet() {
    mConfigurationParameterSimple->mDefaultValueSet = true;

    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterSimple->isDefaultValueSet());


    mConfigurationParameterSimple->mDefaultValueSet = false;

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterSimple->isDefaultValueSet());
}

void ConfigurationParameterSimpleTest::testIsValueSet() {
    mConfigurationParameterSimple->mValueSet = true;

    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterSimple->isValueSet());


    mConfigurationParameterSimple->mValueSet = false;

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterSimple->isValueSet());
}

void ConfigurationParameterSimpleTest::testSetValue() {
    mConfigurationParameterSimple->setValue("Some value");

    CPPUNIT_ASSERT_EQUAL(string("Some value"),
                         mConfigurationParameterSimple->mValue);
    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterSimple->mValueSet);
}
