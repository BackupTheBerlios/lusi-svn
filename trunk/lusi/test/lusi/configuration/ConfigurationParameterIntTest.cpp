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

#include "ConfigurationParameterIntTest.h"

#define protected public
#define private public
#include "ConfigurationParameterInt.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterIntTest::setUp() {
    mConfigurationParameterInt = new ConfigurationParameterInt("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter", 42);
}

void ConfigurationParameterIntTest::tearDown() {
    delete mConfigurationParameterInt;
}

void ConfigurationParameterIntTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterInt->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterInt->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterInt->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterInt->mInformation);
    CPPUNIT_ASSERT_EQUAL(42, mConfigurationParameterInt->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterInt->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterInt->mValueSet);

    //Test without setting the default value
    delete mConfigurationParameterInt;
    mConfigurationParameterInt =
            new ConfigurationParameterInt("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter");

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterInt->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterInt->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterInt->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterInt->mInformation);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterInt->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterInt->mValueSet);
}
