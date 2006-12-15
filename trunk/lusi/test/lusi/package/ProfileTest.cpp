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

#include "ProfileTest.h"

#define protected public
#define private public
#include "Profile.h"
#undef private
#undef protected

#include "Package.h"
#include "status/BuiltPackageStatus.h"
#include "status/ConfiguredPackageStatus.h"
#include "status/PackedPackageStatus.h"
#include "status/UnknownPackageStatus.h"
#include "status/UnpackedPackageStatus.h"
#include "../configuration/ConfigurationParameterLocalUrl.h"
#include "../configuration/ConfigurationParameterMap.h"
#include "../configuration/ConfigurationParameterString.h"
#include "../configuration/ConfigurationPaths.h"
#include "../util/LocalUrl.h"
#include "../util/SmartPtr.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterLocalUrl;
using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::ConfigurationParameterString;
using lusi::configuration::ConfigurationPaths;
using lusi::package::status::BuiltPackageStatus;
using lusi::package::status::ConfiguredPackageStatus;
using lusi::package::status::PackageStatus;
using lusi::package::status::PackedPackageStatus;
using lusi::package::status::UnknownPackageStatus;
using lusi::package::status::UnpackedPackageStatus;
using lusi::util::LocalUrl;
using lusi::util::SmartPtr;

using namespace lusi::package;

//public:

void ProfileTest::setUp() {
    mPackage = new Package(PackageId("testMe", "1.0"));
    mProfile = new Profile(mPackage);

    SmartPtr<ConfigurationParameterMap> packed(
        new ConfigurationParameterMap("packed"));
    packed->add(SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("taskId", "ExtractTask")));
    SmartPtr<ConfigurationParameterMap> packedResources(
        new ConfigurationParameterMap("resources"));
    SmartPtr<ConfigurationParameterMap> packedResourceFiles(
        new ConfigurationParameterMap("files"));
    packedResourceFiles->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("packedFile",
                                           LocalUrl("packedFile"))));
    packedResources->add(packedResourceFiles);
    packed->add(packedResources);
    mProfile->mConfiguration->add(packed);


    SmartPtr<ConfigurationParameterMap> unpacked(
        new ConfigurationParameterMap("unpacked"));
    unpacked->add(SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("taskId", "ConfigureTask")));
    SmartPtr<ConfigurationParameterMap> unpackedResources(
        new ConfigurationParameterMap("resources"));
    SmartPtr<ConfigurationParameterMap> unpackedResourceFiles(
        new ConfigurationParameterMap("files"));
    unpackedResourceFiles->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("directory",
                                           LocalUrl("directory"))));
    unpackedResourceFiles->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("directory/file",
                                           LocalUrl("directory/file"))));
    unpackedResources->add(unpackedResourceFiles);
    unpacked->add(unpackedResources);
    mProfile->mConfiguration->add(unpacked);

    SmartPtr<ConfigurationParameterMap> configured(
        new ConfigurationParameterMap("configured"));
    configured->add(SmartPtr<ConfigurationParameterString>(
        new ConfigurationParameterString("taskId", "")));
    SmartPtr<ConfigurationParameterMap> configuredResources(
        new ConfigurationParameterMap("resources"));
    SmartPtr<ConfigurationParameterMap> configuredResourceFiles(
        new ConfigurationParameterMap("files"));
    configuredResourceFiles->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("directory",
                                           LocalUrl("directory"))));
    configuredResourceFiles->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("directory/file",
                                           LocalUrl("directory/file"))));
    configuredResourceFiles->add(SmartPtr<ConfigurationParameterLocalUrl>(
        new ConfigurationParameterLocalUrl("directory/Makefile",
                                           LocalUrl("directory/Makefile"))));
    configuredResources->add(configuredResourceFiles);
    configured->add(configuredResources);
    mProfile->mConfiguration->add(configured);

    mProfile->mCurrentConfiguration = configured;
}

void ProfileTest::tearDown() {
    ConfigurationPaths paths;
    PackageId packageId(mPackage->getPackageId());

    struct stat fileStat;
    if (!stat(paths.getPackageDirectory(packageId).c_str(), &fileStat)) {
        unlink(paths.getPackageFile(packageId).c_str());
        unlink(paths.getProfileFile(packageId).c_str());
        rmdir(paths.getPackageDirectory(packageId).c_str());
        packageId = PackageId(packageId.getName());
        rmdir(paths.getPackageDirectory(packageId).c_str());
    }

    delete mProfile;
    delete mPackage;
}

void ProfileTest::testConstructor() {
    mProfile->save();
    delete mProfile;
    mProfile = new Profile(mPackage);

    CPPUNIT_ASSERT_EQUAL((size_t)4, mProfile->mConfiguration->getAll().size());
    CPPUNIT_ASSERT_EQUAL(string("configured"),
                         mProfile->mCurrentConfiguration->getId());

    //Test with a new Profile
    tearDown();
    mPackage = new Package(PackageId("lifeIsLikeABoxOfChocolates"));
    mProfile = new Profile(mPackage);

    CPPUNIT_ASSERT_EQUAL((size_t)1, mProfile->mConfiguration->getAll().size());
    CPPUNIT_ASSERT(mProfile->mCurrentConfiguration ==
                   mProfile->mConfiguration->getAll()[0]);
    CPPUNIT_ASSERT_EQUAL(string("unknown"),
                         mProfile->mCurrentConfiguration->getId());
    CPPUNIT_ASSERT(0 != mProfile->mCurrentConfiguration->get("taskId"));
    CPPUNIT_ASSERT_EQUAL(string(""),
                         ((SmartPtr<ConfigurationParameterString>)mProfile->
                            mCurrentConfiguration->get("taskId"))->getValue());
    CPPUNIT_ASSERT(0 != mProfile->mCurrentConfiguration->get("resources"));
    CPPUNIT_ASSERT_EQUAL((size_t)0,
                ((SmartPtr<ConfigurationParameterMap>)mProfile->
                    mCurrentConfiguration->get("resources"))->getAll().size());
}

void ProfileTest::testGetAllPackageStatus() {
    vector<const PackageStatus*> packageStatus =
                                        mProfile->getAllPackageStatus();
    CPPUNIT_ASSERT_EQUAL((size_t)4, packageStatus.size());
    CPPUNIT_ASSERT(UnknownPackageStatus::getInstance() == packageStatus[0]);
    CPPUNIT_ASSERT(PackedPackageStatus::getInstance() == packageStatus[1]);
    CPPUNIT_ASSERT(UnpackedPackageStatus::getInstance() == packageStatus[2]);
    CPPUNIT_ASSERT(ConfiguredPackageStatus::getInstance() == packageStatus[3]);

    //Test when the current PackageStatus isn't the last
    mProfile->mCurrentConfiguration = (SmartPtr<ConfigurationParameterMap>)
        mProfile->mConfiguration->get("packed");
    packageStatus = mProfile->getAllPackageStatus();

    CPPUNIT_ASSERT_EQUAL((size_t)2, packageStatus.size());
    CPPUNIT_ASSERT(UnknownPackageStatus::getInstance() == packageStatus[0]);
    CPPUNIT_ASSERT(PackedPackageStatus::getInstance() == packageStatus[1]);
}

void ProfileTest::testGetPackageStatus() {
    CPPUNIT_ASSERT(ConfiguredPackageStatus::getInstance() ==
                   mProfile->getPackageStatus());
}

void ProfileTest::testGetResources() {
    CPPUNIT_ASSERT(getPtr(mProfile->mCurrentConfiguration->get("resources")) ==
                   getPtr(mProfile->getResources()));
}

void ProfileTest::testGetTaskId() {
    CPPUNIT_ASSERT_EQUAL(string(""), mProfile->getTaskId());

    ((SmartPtr<ConfigurationParameterString>)mProfile->mCurrentConfiguration->
        get("taskId"))->setValue("GetSomeSleepTask");

    CPPUNIT_ASSERT_EQUAL(string("GetSomeSleepTask"), mProfile->getTaskId());
}

void ProfileTest::testSetResources() {
    SmartPtr<ConfigurationParameterMap> resources(
        new ConfigurationParameterMap("resources"));
    SmartPtr<ConfigurationParameterMap> resourceFiles(
        new ConfigurationParameterMap("otherFiles"));
    SmartPtr<ConfigurationParameterLocalUrl> anotherDirectory(
        new ConfigurationParameterLocalUrl("anotherDirectory",
                                           LocalUrl("anotherDirectory")));
    resourceFiles->add(anotherDirectory);
    resources->add(resourceFiles);

    mProfile->setResources(resources);

    SmartPtr<ConfigurationParameterMap> savedResources(
            mProfile->mCurrentConfiguration->get("resources"));
    CPPUNIT_ASSERT_EQUAL(false, savedResources.isNull());
    CPPUNIT_ASSERT(resources != savedResources);
    CPPUNIT_ASSERT_EQUAL(string("resources"), savedResources->getId());
    CPPUNIT_ASSERT_EQUAL((size_t)1, savedResources->getAll().size());

    SmartPtr<ConfigurationParameterMap> savedResourceFiles(
            savedResources->get("otherFiles"));
    CPPUNIT_ASSERT_EQUAL(false, savedResourceFiles.isNull());
    CPPUNIT_ASSERT(resourceFiles != savedResourceFiles);
    CPPUNIT_ASSERT_EQUAL(string("otherFiles"), savedResourceFiles->getId());
    CPPUNIT_ASSERT_EQUAL((size_t)1, savedResourceFiles->getAll().size());

    SmartPtr<ConfigurationParameterLocalUrl> savedAnotherDirectory(
            savedResourceFiles->get("anotherDirectory"));
    CPPUNIT_ASSERT_EQUAL(false, savedAnotherDirectory.isNull());
    CPPUNIT_ASSERT(anotherDirectory != savedAnotherDirectory);
    CPPUNIT_ASSERT_EQUAL(string("anotherDirectory"),
                         savedAnotherDirectory->getId());
}

void ProfileTest::testSetTaskId() {
    mProfile->setTaskId("SweepFloorTask");

    CPPUNIT_ASSERT_EQUAL(string("SweepFloorTask"),
                         ((SmartPtr<ConfigurationParameterString>)mProfile->
                            mCurrentConfiguration->get("taskId"))->getValue());
}

void ProfileTest::testAddPackageStatus() {
    //Test when the current PackageStatus is the last
    mProfile->addPackageStatus(BuiltPackageStatus::getInstance());

    vector< SmartPtr<ConfigurationParameter> > packageStatusList(
            mProfile->mConfiguration->getAll());
    CPPUNIT_ASSERT_EQUAL((size_t)5, packageStatusList.size());
    CPPUNIT_ASSERT(mProfile->mCurrentConfiguration == packageStatusList[4]);

    CPPUNIT_ASSERT_EQUAL(string("built"),
                         mProfile->mCurrentConfiguration->getId());

    SmartPtr<ConfigurationParameterString> taskId(
            mProfile->mCurrentConfiguration->get("taskId"));
    CPPUNIT_ASSERT_EQUAL(false, taskId.isNull());
    CPPUNIT_ASSERT_EQUAL(string(""), taskId->getValue());

    SmartPtr<ConfigurationParameterMap> resources(
            mProfile->mCurrentConfiguration->get("resources"));
    CPPUNIT_ASSERT_EQUAL(false, resources.isNull());
    CPPUNIT_ASSERT_EQUAL((size_t)0, resources->getAll().size());

    //Test when the next PackageStatus is different to the one to add
    mProfile->revertPackageStatus(UnpackedPackageStatus::getInstance());
    mProfile->addPackageStatus(BuiltPackageStatus::getInstance());

    packageStatusList = mProfile->mConfiguration->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)4, packageStatusList.size());
    CPPUNIT_ASSERT(mProfile->mCurrentConfiguration == packageStatusList[3]);

    CPPUNIT_ASSERT_EQUAL(string("built"),
                         mProfile->mCurrentConfiguration->getId());

    taskId = mProfile->mCurrentConfiguration->get("taskId");
    CPPUNIT_ASSERT_EQUAL(false, taskId.isNull());
    CPPUNIT_ASSERT_EQUAL(string(""), taskId->getValue());

    resources = mProfile->mCurrentConfiguration->get("resources");
    CPPUNIT_ASSERT_EQUAL(false, resources.isNull());
    CPPUNIT_ASSERT_EQUAL((size_t)0, resources->getAll().size());

    //Test when the next PackageStatus is the same to add
    ((SmartPtr<ConfigurationParameterMap>)mProfile->mCurrentConfiguration->
        get("resources"))->add(SmartPtr<ConfigurationParameterString>(
            new ConfigurationParameterString("aString")));
    ((SmartPtr<ConfigurationParameterString>)mProfile->mCurrentConfiguration->
        get("taskId"))->setValue("BuildTask");

    mProfile->revertPackageStatus(PackedPackageStatus::getInstance());
    mProfile->addPackageStatus(UnpackedPackageStatus::getInstance());


    packageStatusList = mProfile->mConfiguration->getAll();
    CPPUNIT_ASSERT_EQUAL((size_t)4, packageStatusList.size());
    CPPUNIT_ASSERT(mProfile->mCurrentConfiguration == packageStatusList[2]);
}

void ProfileTest::testRevertPackageStatus() {
    //Test with a previous PackageStatus
    mProfile->revertPackageStatus(PackedPackageStatus::getInstance());

    SmartPtr<ConfigurationParameterMap> packed(
                                    mProfile->mConfiguration->getAll()[1]);

    CPPUNIT_ASSERT(packed == mProfile->mCurrentConfiguration);

    SmartPtr<ConfigurationParameterString> taskId = packed->get("taskId");
    CPPUNIT_ASSERT_EQUAL(false, taskId.isNull());
    CPPUNIT_ASSERT_EQUAL(string("ExtractTask"), taskId->getValue());

    SmartPtr<ConfigurationParameterMap> resources = packed->get("resources");
    CPPUNIT_ASSERT_EQUAL(false, resources.isNull());
    CPPUNIT_ASSERT_EQUAL((size_t)1, resources->getAll().size());
    CPPUNIT_ASSERT_EQUAL(string("files"), resources->getAll()[0]->getId());

    SmartPtr<ConfigurationParameterMap> unpacked(
                                    mProfile->mConfiguration->getAll()[2]);

    taskId = unpacked->get("taskId");
    CPPUNIT_ASSERT_EQUAL(false, taskId.isNull());
    CPPUNIT_ASSERT_EQUAL(string("ConfigureTask"), taskId->getValue());

    resources = unpacked->get("resources");
    CPPUNIT_ASSERT_EQUAL(false, resources.isNull());
    CPPUNIT_ASSERT_EQUAL((size_t)0, resources->getAll().size());

    SmartPtr<ConfigurationParameterMap> configured(
                                    mProfile->mConfiguration->getAll()[3]);

    taskId = configured->get("taskId");
    CPPUNIT_ASSERT_EQUAL(false, taskId.isNull());
    CPPUNIT_ASSERT_EQUAL(string(""), taskId->getValue());

    resources = configured->get("resources");
    CPPUNIT_ASSERT_EQUAL(false, resources.isNull());
    CPPUNIT_ASSERT_EQUAL((size_t)0, resources->getAll().size());

    //Test with a PackageStatus not present
    mProfile->revertPackageStatus(BuiltPackageStatus::getInstance());

    CPPUNIT_ASSERT(packed == mProfile->mCurrentConfiguration);

    //Test with a PackageStatus after the current one
    mProfile->revertPackageStatus(ConfiguredPackageStatus::getInstance());

    CPPUNIT_ASSERT(packed == mProfile->mCurrentConfiguration);
}

void ProfileTest::testLoadSave() {
    mProfile->save();

    mProfile->mCurrentConfiguration = SmartPtr<ConfigurationParameterMap>();
    delete mProfile->mConfiguration;
    mProfile->mConfiguration = new ConfigurationParameterMap("profile");

    mProfile->load();
    CPPUNIT_ASSERT((ConfigurationParameterMap*)0 != mProfile->mConfiguration);
    CPPUNIT_ASSERT_EQUAL(false, mProfile->mCurrentConfiguration.isNull());
    CPPUNIT_ASSERT_EQUAL(string("configured"),
                         mProfile->mCurrentConfiguration->getId());

    //Save/load with reverted PackageStatus
    mProfile->revertPackageStatus(PackedPackageStatus::getInstance());
    mProfile->save();

    mProfile->mCurrentConfiguration = SmartPtr<ConfigurationParameterMap>();
    delete mProfile->mConfiguration;
    mProfile->mConfiguration = new ConfigurationParameterMap("profile");

    mProfile->load();
    CPPUNIT_ASSERT((ConfigurationParameterMap*)0 != mProfile->mConfiguration);
    CPPUNIT_ASSERT_EQUAL(false, mProfile->mCurrentConfiguration.isNull());
    CPPUNIT_ASSERT_EQUAL(string("packed"),
                         mProfile->mCurrentConfiguration->getId());
}
