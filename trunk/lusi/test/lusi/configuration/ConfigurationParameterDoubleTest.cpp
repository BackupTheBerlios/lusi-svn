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

#include "ConfigurationParameterDoubleTest.h"

#define protected public
#define private public
#include "ConfigurationParameterDouble.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterDoubleTest::setUp() {
    mConfigurationParameterDouble = new ConfigurationParameterDouble("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter", 42.1729);
}

void ConfigurationParameterDoubleTest::tearDown() {
    delete mConfigurationParameterDouble;
}

void ConfigurationParameterDoubleTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterDouble->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterDouble->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterDouble->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterDouble->mInformation);
    CPPUNIT_ASSERT_EQUAL(42.1729, mConfigurationParameterDouble->mDefaultValue);
    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterDouble->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterDouble->mValueSet);

    //Test without setting the default value
    delete mConfigurationParameterDouble;
    mConfigurationParameterDouble =
            new ConfigurationParameterDouble("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter");

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterDouble->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterDouble->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterDouble->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterDouble->mInformation);
    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterDouble->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterDouble->mValueSet);
}
