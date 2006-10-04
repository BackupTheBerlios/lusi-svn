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

#include "ConfigurationParameterStringTest.h"

#define protected public
#define private public
#include "ConfigurationParameterString.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterStringTest::setUp() {
    mConfigurationParameterString = new ConfigurationParameterString("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter", "ALF",
                ConfigurationParameterString::PasswordType);
}

void ConfigurationParameterStringTest::tearDown() {
    delete mConfigurationParameterString;
}

void ConfigurationParameterStringTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterString->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterString->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterString->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterString->mInformation);
    CPPUNIT_ASSERT_EQUAL(string("ALF"),
                         mConfigurationParameterString->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterString->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterString->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterString::PasswordType,
                         mConfigurationParameterString->mStringType);

    //Test without the string type
    delete mConfigurationParameterString;
    mConfigurationParameterString = new ConfigurationParameterString("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter", "ALF");

    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterString->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterString->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterString->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterString->mInformation);
    CPPUNIT_ASSERT_EQUAL(string("ALF"),
                         mConfigurationParameterString->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterString->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterString->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterString::NormalType,
                         mConfigurationParameterString->mStringType);

    //Test without setting the default value
    delete mConfigurationParameterString;
    mConfigurationParameterString =
            new ConfigurationParameterString("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter",
                    ConfigurationParameterString::PasswordType);

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterString->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterString->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterString->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterString->mInformation);
    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterString->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterString->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterString::PasswordType,
                         mConfigurationParameterString->mStringType);

    //Test without setting the default value nor the string type
    delete mConfigurationParameterString;
    mConfigurationParameterString =
            new ConfigurationParameterString("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter");

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterString->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterString->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterString->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterString->mInformation);
    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterString->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterString->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterString::NormalType,
                         mConfigurationParameterString->mStringType);
}

void ConfigurationParameterStringTest::testGetStringType() {
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterString::PasswordType,
                         mConfigurationParameterString->getStringType());

    mConfigurationParameterString->mStringType =
                                    ConfigurationParameterString::NormalType;

    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterString::NormalType,
                         mConfigurationParameterString->getStringType());
}
