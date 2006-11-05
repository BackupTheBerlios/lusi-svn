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

#include <sys/stat.h>
#include <fcntl.h>

#include "ConfigurationSaverTest.h"

#define protected public
#define private public
#include "ConfigurationSaver.h"
#undef private
#undef protected

#include "ConfigurationLoader.h"
#include "ConfigurationParameterBool.h"
#include "ConfigurationParameterDouble.h"
#include "ConfigurationParameterInt.h"
#include "ConfigurationParameterLocalUrl.h"
#include "ConfigurationParameterMap.h"
#include "ConfigurationParameterString.h"
#include "../util/LocalFile.h"

using std::string;
using std::vector;

using lusi::util::LocalFile;
using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::configuration;

//public:

void ConfigurationSaverTest::setUp() {
    mTestDirectoryPath = LocalFile::getCurrentWorkingDirectory() +
                                                    "created for LUSI tests/";
}

void ConfigurationSaverTest::tearDown() {
    struct stat fileStat;
    if (!stat(mTestDirectoryPath.c_str(), &fileStat)) {
        unlink(string(mTestDirectoryPath + "file.xml").c_str());
        rmdir(mTestDirectoryPath.c_str());
    }
}

void ConfigurationSaverTest::testSave() {
    ConfigurationSaver saver;

    //Test loading the saved file with ConfigurationLoader
    SmartPtr<ConfigurationParameterMap> configuration(
        new ConfigurationParameterMap("mapId", "Map",
            ConfigurationParameter::OptionalPriority, "A map of parameters"));
    configuration->add(SmartPtr<ConfigurationParameterInt>(
        new ConfigurationParameterInt("intId", "Int",
            ConfigurationParameter::RequiredPriority, "An int value")));
    configuration->add(SmartPtr<ConfigurationParameterBool>(
        new ConfigurationParameterBool("boolId", "Bool",
            ConfigurationParameter::RequiredPriority, "A bool value")));
    configuration->add(SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("stringId", "String",
            ConfigurationParameter::RequiredPriority, "A string value")));

    SmartPtr<ConfigurationParameterMap> map(
        new ConfigurationParameterMap("mapId2", "Map2",
            ConfigurationParameter::OptionalPriority,
            "Another map of parameters"));
    configuration->add(map);
    map->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("localUrlId", "LocalUrl",
            ConfigurationParameter::RequiredPriority, "A LocalUrl value")));
    map->add(SmartPtr<ConfigurationParameterDouble>(
        new ConfigurationParameterDouble("doubleId", "Double",
            ConfigurationParameter::RequiredPriority, "A double value")));

    LocalUrl localUrl(mTestDirectoryPath + "file.xml");

    saver.save(getPtr(configuration), localUrl);

    SmartPtr<ConfigurationParameterMap> loadedConfiguration(
                                        ConfigurationLoader().load(localUrl));

    CPPUNIT_ASSERT(0 != getPtr(loadedConfiguration));
    CPPUNIT_ASSERT_EQUAL(configuration->getId(), loadedConfiguration->getId());
    vector< SmartPtr<ConfigurationParameter> > parameters =
                                                loadedConfiguration->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)4, parameters.size());
    CPPUNIT_ASSERT_EQUAL(string("intId"), parameters[0]->getId());
    CPPUNIT_ASSERT_EQUAL(string("boolId"), parameters[1]->getId());
    CPPUNIT_ASSERT_EQUAL(string("stringId"), parameters[2]->getId());
    CPPUNIT_ASSERT_EQUAL(string("mapId2"), parameters[3]->getId());
    parameters = ((SmartPtr<ConfigurationParameterMap>)parameters[3])->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)2, parameters.size());
    CPPUNIT_ASSERT_EQUAL(string("localUrlId"), parameters[0]->getId());
    CPPUNIT_ASSERT_EQUAL(string("doubleId"), parameters[1]->getId());

    //Test with a directory instead of a file
    localUrl = LocalUrl(mTestDirectoryPath);

    CPPUNIT_ASSERT_THROW(saver.save(getPtr(configuration), localUrl),
                         PersistenceException);

    //Test with a relative url
    localUrl = LocalUrl("created by LUSI tests/file.xml");

    CPPUNIT_ASSERT_THROW(saver.save(getPtr(configuration), localUrl),
                         PersistenceException);

    //Test with a parent directory that can't be created
    localUrl = LocalUrl("/root/doNotExecuteLusiTestAsRootYouMoron/file.xml");

    CPPUNIT_ASSERT_THROW(saver.save(getPtr(configuration), localUrl),
                         PersistenceException);
}
