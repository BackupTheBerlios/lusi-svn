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

#include "ConfigurationParameterLocalUrlTest.h"

#define protected public
#define private public
#include "ConfigurationParameterLocalUrl.h"
#undef private
#undef protected

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterLocalUrlTest::setUp() {
    mConfigurationParameterLocalUrl = new ConfigurationParameterLocalUrl("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                "A test parameter", string("/home/"),
                ConfigurationParameterLocalUrl::DirectoryType);
}

void ConfigurationParameterLocalUrlTest::tearDown() {
    delete mConfigurationParameterLocalUrl;
}

void ConfigurationParameterLocalUrlTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterLocalUrl->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterLocalUrl->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterLocalUrl->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterLocalUrl->mInformation);
    CPPUNIT_ASSERT_EQUAL(string("/home/"),
                    mConfigurationParameterLocalUrl->mDefaultValue.getPath());
    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterLocalUrl->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterLocalUrl->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterLocalUrl::DirectoryType,
                         mConfigurationParameterLocalUrl->mUrlType);

    //Test without the url type
    delete mConfigurationParameterLocalUrl;
    mConfigurationParameterLocalUrl =
            new ConfigurationParameterLocalUrl("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter", string("/home/"));

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterLocalUrl->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterLocalUrl->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterLocalUrl->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterLocalUrl->mInformation);
    CPPUNIT_ASSERT_EQUAL(string("/home/"),
                    mConfigurationParameterLocalUrl->mDefaultValue.getPath());
    CPPUNIT_ASSERT_EQUAL(true,
                         mConfigurationParameterLocalUrl->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterLocalUrl->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterLocalUrl::AllType,
                         mConfigurationParameterLocalUrl->mUrlType);


    //Test without setting the default value
    delete mConfigurationParameterLocalUrl;
    mConfigurationParameterLocalUrl =
            new ConfigurationParameterLocalUrl("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter",
                    ConfigurationParameterLocalUrl::DirectoryType);

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterLocalUrl->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterLocalUrl->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterLocalUrl->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterLocalUrl->mInformation);
    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterLocalUrl->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterLocalUrl->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterLocalUrl::DirectoryType,
                         mConfigurationParameterLocalUrl->mUrlType);

    //Test without setting the default value nor the url type
    delete mConfigurationParameterLocalUrl;
    mConfigurationParameterLocalUrl =
            new ConfigurationParameterLocalUrl("Another test", "Test name2",
                    ConfigurationParameter::OptionalPriority,
                    "Another test parameter");

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterLocalUrl->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name2"),
                         mConfigurationParameterLocalUrl->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterLocalUrl->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("Another test parameter"),
                         mConfigurationParameterLocalUrl->mInformation);
    CPPUNIT_ASSERT_EQUAL(false,
                         mConfigurationParameterLocalUrl->mDefaultValueSet);
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterLocalUrl->mValueSet);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterLocalUrl::AllType,
                         mConfigurationParameterLocalUrl->mUrlType);
}

void ConfigurationParameterLocalUrlTest::testGetUrlType() {
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterLocalUrl::DirectoryType,
                         mConfigurationParameterLocalUrl->getUrlType());

    mConfigurationParameterLocalUrl->mUrlType =
                                    ConfigurationParameterLocalUrl::FileType;

    CPPUNIT_ASSERT_EQUAL(ConfigurationParameterLocalUrl::FileType,
                         mConfigurationParameterLocalUrl->getUrlType());
}
