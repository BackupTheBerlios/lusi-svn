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

#include "ConfigurationParameterComposedTest.h"

#define protected public
#define private public
#include "ConfigurationParameterComposedTestImplementation.h"
#undef private
#undef protected

#include "ConfigurationParameterTestImplementation.h"

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterComposedTest::setUp() {
    mConfigurationParameterComposed =
            new ConfigurationParameterComposedTestImplementation("Test",
                "Test name", ConfigurationParameter::RequiredPriority,
                    "A test parameter");
}

void ConfigurationParameterComposedTest::tearDown() {
    delete mConfigurationParameterComposed;
}

void ConfigurationParameterComposedTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterComposed->mId);
    CPPUNIT_ASSERT_EQUAL(string("Test name"),
                         mConfigurationParameterComposed->mName);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterComposed->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterComposed->mInformation);
    CPPUNIT_ASSERT_EQUAL((size_t)0,
            mConfigurationParameterComposed->mConfigurationParameters.size());
}

void ConfigurationParameterComposedTest::testAddConfigurationParameter() {
    ConfigurationParameter* configurationParameter =
            new ConfigurationParameterTestImplementation("id", "name",
                    ConfigurationParameter::RequiredPriority, "information");
    mConfigurationParameterComposed->addConfigurationParameter(
                                                configurationParameter);

    CPPUNIT_ASSERT_EQUAL(configurationParameter,
                mConfigurationParameterComposed->mConfigurationParameters[0]);
}

void ConfigurationParameterComposedTest::testGetConfigurationParameters() {
    mConfigurationParameterComposed->mConfigurationParameters.push_back(0);

    CPPUNIT_ASSERT(
        mConfigurationParameterComposed->getConfigurationParameters() ==
                mConfigurationParameterComposed->mConfigurationParameters);
}
