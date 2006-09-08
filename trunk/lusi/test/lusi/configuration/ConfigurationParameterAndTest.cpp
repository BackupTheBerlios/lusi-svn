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

#include "ConfigurationParameterAndTest.h"

#define protected public
#define private public
#include "ConfigurationParameterAnd.h"
#undef private
#undef protected

#include "ConfigurationParameterTestImplementation.h"

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterAndTest::setUp() {
    mConfigurationParameterAnd = new ConfigurationParameterAnd("Test",
                  ConfigurationParameter::RequiredPriority, "A test parameter");
}

void ConfigurationParameterAndTest::tearDown() {
    delete mConfigurationParameterAnd;
}

void ConfigurationParameterAndTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterAnd->mId);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterAnd->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterAnd->mInformation);
    CPPUNIT_ASSERT_EQUAL((size_t)0,
            mConfigurationParameterAnd->mConfigurationParameters.size());

    //Test without setting the information
    delete mConfigurationParameterAnd;
    mConfigurationParameterAnd = new ConfigurationParameterAnd("Another test",
                                    ConfigurationParameter::OptionalPriority);

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterAnd->mId);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterAnd->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string(""), mConfigurationParameterAnd->mInformation);
}

void ConfigurationParameterAndTest::testIsInvalid() {
    //Test with an empty vector
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterAnd->isInvalid());

    //Test with a vector with an invalid parameter
    ConfigurationParameterTestImplementation* configurationParameter1 =
            new ConfigurationParameterTestImplementation("Test1",
                    ConfigurationParameter::RequiredPriority);
    configurationParameter1->setInvalid(true);
    mConfigurationParameterAnd->addConfigurationParameter(
                                                configurationParameter1);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterAnd->isInvalid());

    //Test with a vector with a valid parameter
    configurationParameter1->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterAnd->isInvalid());

    //Test with a vector with two valid parameters and one invalid parameter
    ConfigurationParameterTestImplementation* configurationParameter2 =
            new ConfigurationParameterTestImplementation("Test2",
                    ConfigurationParameter::RequiredPriority);
    configurationParameter2->setInvalid(false);
    mConfigurationParameterAnd->addConfigurationParameter(
                                                configurationParameter2);

    ConfigurationParameterTestImplementation* configurationParameter3 =
            new ConfigurationParameterTestImplementation("Test3",
                    ConfigurationParameter::RequiredPriority);
    configurationParameter3->setInvalid(true);
    mConfigurationParameterAnd->addConfigurationParameter(
                                                configurationParameter3);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterAnd->isInvalid());

    //Test with a vector with three valid parameters
    configurationParameter3->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterAnd->isInvalid());
}
