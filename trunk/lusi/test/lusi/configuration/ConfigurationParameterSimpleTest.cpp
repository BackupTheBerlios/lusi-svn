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
#include "ConfigurationParameterSimple.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterSimpleTest::setUp() {
    mConfigurationParameterSimple = new ConfigurationParameterSimple("Test",
            ConfigurationParameter::RequiredPriority, "A test parameter",
            "Default");
}

void ConfigurationParameterSimpleTest::tearDown() {
    delete mConfigurationParameterSimple;
}

void ConfigurationParameterSimpleTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterSimple->mId);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterSimple->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterSimple->mInformation);
    CPPUNIT_ASSERT_EQUAL(string("Default"),
                         mConfigurationParameterSimple->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(string(""), mConfigurationParameterSimple->mValue);

    //Test without setting the information and default values
    delete mConfigurationParameterSimple;
    mConfigurationParameterSimple =
                new ConfigurationParameterSimple("Another test",
                            ConfigurationParameter::OptionalPriority);

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterSimple->mId);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterSimple->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string(""),
                         mConfigurationParameterSimple->mInformation);
    CPPUNIT_ASSERT_EQUAL(string(""),
                         mConfigurationParameterSimple->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(string(""), mConfigurationParameterSimple->mValue);
}

void ConfigurationParameterSimpleTest::testIsInvalid() {
    //Test with a required empty value
    mConfigurationParameterSimple->mDefaultValue = "";

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterSimple->isInvalid());

    //Test with required empty value and default value set
    mConfigurationParameterSimple->mDefaultValue = "Default";

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->isInvalid());

    //Test with recommended empty values
    mConfigurationParameterSimple->mDefaultValue = "";
    mConfigurationParameterSimple->mPriorityType =
                            ConfigurationParameter::RecommendedPriority;

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->isInvalid());

    //Test with optional empty values
    mConfigurationParameterSimple->mPriorityType =
                            ConfigurationParameter::OptionalPriority;
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterSimple->isInvalid());
}

void ConfigurationParameterSimpleTest::testGetValue() {
    //Test with a set value
    mConfigurationParameterSimple->mValue = "Some value";

    CPPUNIT_ASSERT_EQUAL(string("Some value"),
                         mConfigurationParameterSimple->getValue());

    //Test with a not set value and a default value
    mConfigurationParameterSimple->mValue = "";

    CPPUNIT_ASSERT_EQUAL(string("Default"),
                         mConfigurationParameterSimple->getValue());

    //Test with a not set value and a not set default value
    mConfigurationParameterSimple->mDefaultValue = "";

    CPPUNIT_ASSERT_EQUAL(string(""),
                         mConfigurationParameterSimple->getValue());
}

void ConfigurationParameterSimpleTest::testIsDefaultValue() {
    //Test with default value
    mConfigurationParameterSimple->mValue = "Default";

    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterSimple->isDefaultValue());

    //Test with a value different than the default value
    mConfigurationParameterSimple->mValue = "No default value";

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterSimple->isDefaultValue());

    //Test without default value and without value
    mConfigurationParameterSimple->mDefaultValue = "";
    mConfigurationParameterSimple->mValue = "";

    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterSimple->isDefaultValue());
}

void ConfigurationParameterSimpleTest::testSetValue() {
    mConfigurationParameterSimple->setValue("Some value");

    CPPUNIT_ASSERT_EQUAL(string("Some value"),
                         mConfigurationParameterSimple->mValue);
}
