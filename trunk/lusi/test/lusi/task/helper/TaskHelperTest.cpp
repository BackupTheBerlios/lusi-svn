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

#include "TaskHelperTest.h"

#define protected public
#define private public
#include "TaskHelperTestImplementation.h"
#undef private
#undef protected

#include "../TaskTestImplementation.h"
#include "../../configuration/ConfigurationParameterTestImplementation.h"

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationParameterTestImplementation;
using lusi::configuration::InvalidConfigurationException;
using lusi::task::Task;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void TaskHelperTest::setUp() {
    mTask = new TaskTestImplementation("Clean the angry dome");
    mTaskHelper = new TaskHelperTestImplementation(mTask, "Zoidberg'll do it");
}

void TaskHelperTest::tearDown() {
    delete mTaskHelper;
    delete mTask;
}

void TaskHelperTest::testExecute() {
    ConfigurationParameterTestImplementation* parameter1 =
            new ConfigurationParameterTestImplementation("anchovy", "Anchovy",
                    ConfigurationParameter::RequiredPriority, "MORE!");
    mTaskHelper->mConfigurationParameterMap.add(
                                SmartPtr<ConfigurationParameter>(parameter1));

    //Test with a valid parameter
    parameter1->setInvalid(false);
    CPPUNIT_ASSERT_NO_THROW(mTaskHelper->execute());

    //Test with an invalid parameter
    parameter1->setInvalid(true);
    CPPUNIT_ASSERT_THROW(mTaskHelper->execute(), InvalidConfigurationException);
}

void TaskHelperTest::testGetInvalidConfiguration() {
    ConfigurationParameterTestImplementation* parameter1 =
            new ConfigurationParameterTestImplementation("anchovy", "Anchovy",
                    ConfigurationParameter::RequiredPriority, "MORE!");
    mTaskHelper->mConfigurationParameterMap.add(
                                SmartPtr<ConfigurationParameter>(parameter1));
    ConfigurationParameterTestImplementation* parameter2 =
            new ConfigurationParameterTestImplementation("moultTime",
                    "Moult time", ConfigurationParameter::OptionalPriority,
                    "Shell to use from now on");
    mTaskHelper->mConfigurationParameterMap.add(
                                SmartPtr<ConfigurationParameter>(parameter2));
    ConfigurationParameterTestImplementation* parameter3 =
            new ConfigurationParameterTestImplementation(
                    "scrabbleAbbreviations", "Scrabble abbreviations",
                    ConfigurationParameter::RecommendedPriority,
                    "Do abbreviations count in Scrabble?");
    mTaskHelper->mConfigurationParameterMap.add(
                                SmartPtr<ConfigurationParameter>(parameter3));

    //Test when all the parameters are invalid
    SmartPtr<ConfigurationParameterMap> configuration =
                                mTaskHelper->getInvalidConfiguration();

    CPPUNIT_ASSERT_EQUAL((ConfigurationParameter*)parameter1,
                         getPtr(configuration->getAll()[0]));
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameter*)parameter2,
                         getPtr(configuration->getAll()[1]));
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameter*)parameter3,
                         getPtr(configuration->getAll()[2]));
    CPPUNIT_ASSERT_EQUAL((size_t)3, configuration->getAll().size());

    //Test when two parameters are invalid
    parameter2->setInvalid(false);
    configuration = mTaskHelper->getInvalidConfiguration();

    CPPUNIT_ASSERT_EQUAL((ConfigurationParameter*)parameter1,
                         getPtr(configuration->getAll()[0]));
    CPPUNIT_ASSERT_EQUAL((ConfigurationParameter*)parameter3,
                         getPtr(configuration->getAll()[1]));
    CPPUNIT_ASSERT_EQUAL((size_t)2, configuration->getAll().size());

    //Test when zero the parameters are invalid
    parameter1->setInvalid(false);
    parameter3->setInvalid(false);
    configuration = mTaskHelper->getInvalidConfiguration();

    CPPUNIT_ASSERT_EQUAL((size_t)0, configuration->getAll().size());
}
