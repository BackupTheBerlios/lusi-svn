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

#include "ConfigurationParameterOrTest.h"

#define protected public
#define private public
#include "ConfigurationParameterOr.h"
#undef private
#undef protected

#include "ConfigurationParameterTestImplementation.h"

using std::string;

using namespace lusi::configuration;

//public:

void ConfigurationParameterOrTest::setUp() {
    mConfigurationParameterOr = new ConfigurationParameterOr("Test",
                  ConfigurationParameter::RequiredPriority, "A test parameter");
}

void ConfigurationParameterOrTest::tearDown() {
    delete mConfigurationParameterOr;
}

void ConfigurationParameterOrTest::testConstructor() {
    //Test with all the values
    CPPUNIT_ASSERT_EQUAL(string("Test"), mConfigurationParameterOr->mId);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::RequiredPriority,
                         mConfigurationParameterOr->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string("A test parameter"),
                         mConfigurationParameterOr->mInformation);
    CPPUNIT_ASSERT_EQUAL((size_t)0,
            mConfigurationParameterOr->mConfigurationParameters.size());

    //Test without setting the information
    delete mConfigurationParameterOr;
    mConfigurationParameterOr = new ConfigurationParameterOr("Another test",
                                    ConfigurationParameter::OptionalPriority);

    CPPUNIT_ASSERT_EQUAL(string("Another test"),
                         mConfigurationParameterOr->mId);
    CPPUNIT_ASSERT_EQUAL(ConfigurationParameter::OptionalPriority,
                         mConfigurationParameterOr->mPriorityType);
    CPPUNIT_ASSERT_EQUAL(string(""), mConfigurationParameterOr->mInformation);
}

void ConfigurationParameterOrTest::testIsInvalid() {
    //Test with an empty vector
    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterOr->isInvalid());

    //Test with a vector with an invalid parameter
    ConfigurationParameterTestImplementation* configurationParameter1 =
            new ConfigurationParameterTestImplementation("Test1",
                    ConfigurationParameter::RequiredPriority);
    configurationParameter1->setInvalid(true);
    mConfigurationParameterOr->addConfigurationParameter(
                                                configurationParameter1);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterOr->isInvalid());

    //Test with a vector with a valid parameter
    configurationParameter1->setInvalid(false);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterOr->isInvalid());

    //Test with a vector with two valid parameters and one invalid parameter
    ConfigurationParameterTestImplementation* configurationParameter2 =
            new ConfigurationParameterTestImplementation("Test2",
                    ConfigurationParameter::RequiredPriority);
    configurationParameter2->setInvalid(false);
    mConfigurationParameterOr->addConfigurationParameter(
                                                configurationParameter2);

    ConfigurationParameterTestImplementation* configurationParameter3 =
            new ConfigurationParameterTestImplementation("Test3",
                    ConfigurationParameter::RequiredPriority);
    configurationParameter3->setInvalid(true);
    mConfigurationParameterOr->addConfigurationParameter(
                                                configurationParameter3);

    CPPUNIT_ASSERT_EQUAL(false, mConfigurationParameterOr->isInvalid());

    //Test with a vector with three invalid parameters
    configurationParameter1->setInvalid(true);
    configurationParameter2->setInvalid(true);
    configurationParameter3->setInvalid(true);

    CPPUNIT_ASSERT_EQUAL(true, mConfigurationParameterOr->isInvalid());
}
