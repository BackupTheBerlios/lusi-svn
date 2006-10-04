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

#include "ConfigurationParameterBoolTest.h"

#define protected public
#define private public
#include "ConfigurationParameterBool.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterBoolTest::setUp() {
    mConfigurationParameterBool = new ConfigurationParameterBool("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter", true);
}

void ConfigurationParameterBoolTest::tearDown() {
    delete mConfigurationParameterBool;
}

void ConfigurationParameterBoolTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterBool->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterBool->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterBool->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterBool->mInformation);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterBool->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterBool->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterBool->mValueSet);

    //Test without setting the default value
    delete mConfigurationParameterBool;
    mConfigurationParameterBool =
            new ConfigurationParameterBool("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter");

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterBool->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterBool->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterBool->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterBool->mInformation);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterBool->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterBool->mValueSet);
}
