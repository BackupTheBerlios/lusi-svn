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

#include <memory>

#include "TaskManagerTest.h"

#define protected public
#define private public
#include "TaskManager.h"
#include "helper/TaskHelperManager.h"
#undef private
#undef protected

#include "helper/TaskHelperTestImplementation.h"

#include "../package/Package.h"
#include "../package/PackageId.h"
#include "../package/status/PackageStatusTestImplementation.h"

#define firstPackageStatus ((const PackageStatus*) \
                PackageStatusTestImplementation::getFirstInstance())
#define secondPackageStatus ((const PackageStatus*) \
                PackageStatusTestImplementation::getSecondInstance())
#define thirdPackageStatus ((const PackageStatus*) \
                PackageStatusTestImplementation::getThirdInstance())

using std::auto_ptr;
using std::multimap;
using std::pair;
using std::string;
using std::vector;

using lusi::package::Package;
using lusi::package::PackageId;
using lusi::package::status::PackageStatus;
using lusi::package::status::PackageStatusTestImplementation;
using lusi::task::helper::TaskHelperManager;
using lusi::task::helper::createTaskHelperTestImplementation1;

using namespace lusi::task;

//public:

void TaskManagerTest::setUp() {
    mTaskManager = TaskManager::getInstance();
    mTaskManager->registerTask("Chew gimer stick cane",
                               firstPackageStatus,
                               secondPackageStatus);
    mTaskManager->registerTask("Watch House M.D.",
                               firstPackageStatus,
                               thirdPackageStatus);
    mTaskManager->registerTask("Milk the platypus",
                               secondPackageStatus,
                               thirdPackageStatus);

    TaskHelperManager::getInstance()->
            registerTaskHelper(createTaskHelperTestImplementation1,
                               "Chew gimer stick cane");
}

void TaskManagerTest::tearDown() {
    mTaskManager->mTasksByNeededPackageStatus.erase(firstPackageStatus);
    mTaskManager->mTasksByNeededPackageStatus.erase(secondPackageStatus);

    mTaskManager->mTasksByProvidedPackageStatus.erase(secondPackageStatus);
    mTaskManager->mTasksByProvidedPackageStatus.erase(thirdPackageStatus);

    TaskHelperManager::getInstance()->
                            mTaskHelperFactories.erase("Chew gimer stick cane");
}

void TaskManagerTest::testSingleton() {
    CPPUNIT_ASSERT(TaskManager::getInstance() != 0);

    CPPUNIT_ASSERT_EQUAL(TaskManager::getInstance(),
            TaskManager::getInstance());
}

void TaskManagerTest::testGetTask() {
    PackageId packageId("testPackage");
    auto_ptr<Package> package(new Package(packageId, firstPackageStatus));

    auto_ptr<Task> task(mTaskManager->getTask(package.get()));
    CPPUNIT_ASSERT(task.get() != 0);
    CPPUNIT_ASSERT_EQUAL(string("Chew gimer stick cane"), task->getId());
}

void TaskManagerTest::testRegisterTask() {
    typedef multimap<const PackageStatus*,
                     TaskManager::TaskData>::const_iterator iterator;
    //Test needed package status
    pair<iterator, iterator> range1 =
                mTaskManager->mTasksByNeededPackageStatus.equal_range(
                                                        firstPackageStatus);
    CPPUNIT_ASSERT(range1.first != range1.second);
    CPPUNIT_ASSERT_EQUAL(string("Chew gimer stick cane"),
                         range1.first->second.id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         range1.first->second.neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         range1.first->second.providedPackageStatus);
    ++range1.first;
    CPPUNIT_ASSERT_EQUAL(string("Watch House M.D."),
                         range1.first->second.id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         range1.first->second.neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         range1.first->second.providedPackageStatus);
    ++range1.first;
    CPPUNIT_ASSERT(range1.first == range1.second);

    pair<iterator, iterator> range2 =
                mTaskManager->mTasksByNeededPackageStatus.equal_range(
                                                        secondPackageStatus);
    CPPUNIT_ASSERT(range2.first != range2.second);
    CPPUNIT_ASSERT_EQUAL(string("Milk the platypus"),
                         range2.first->second.id);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         range2.first->second.neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         range2.first->second.providedPackageStatus);
    ++range2.first;
    CPPUNIT_ASSERT(range2.first == range2.second);



    //Test provided package status
    range1 = mTaskManager->mTasksByProvidedPackageStatus.equal_range(
                                                        secondPackageStatus);
    CPPUNIT_ASSERT(range1.first != range1.second);
    CPPUNIT_ASSERT_EQUAL(string("Chew gimer stick cane"),
                         range1.first->second.id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         range1.first->second.neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         range1.first->second.providedPackageStatus);
    ++range1.first;
    CPPUNIT_ASSERT(range1.first == range1.second);

    range2 = mTaskManager->mTasksByProvidedPackageStatus.equal_range(
                                                        thirdPackageStatus);
    CPPUNIT_ASSERT(range2.first != range2.second);
    CPPUNIT_ASSERT_EQUAL(string("Watch House M.D."),
                         range2.first->second.id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         range2.first->second.neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         range2.first->second.providedPackageStatus);
    ++range2.first;
    CPPUNIT_ASSERT_EQUAL(string("Milk the platypus"),
                         range2.first->second.id);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         range2.first->second.neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         range2.first->second.providedPackageStatus);
    ++range2.first;
    CPPUNIT_ASSERT(range2.first == range2.second);
}

void TaskManagerTest::testGetTasksByPackageStatus() {
    typedef TaskManager::TaskData TaskData;
    //Test needed package status
    vector<TaskData> neededStatus1 = mTaskManager->getTasksByPackageStatus(
                                firstPackageStatus,
                                mTaskManager->mTasksByNeededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(string("Chew gimer stick cane"),
                         neededStatus1[0].id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         neededStatus1[0].neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         neededStatus1[0].providedPackageStatus);
    CPPUNIT_ASSERT_EQUAL(string("Watch House M.D."),
                         neededStatus1[1].id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         neededStatus1[1].neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         neededStatus1[1].providedPackageStatus);
    CPPUNIT_ASSERT(neededStatus1.size() == 2);

    vector<TaskData> neededStatus2 = mTaskManager->getTasksByPackageStatus(
                                secondPackageStatus,
                                mTaskManager->mTasksByNeededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(string("Milk the platypus"),
                         neededStatus2[0].id);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         neededStatus2[0].neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         neededStatus2[0].providedPackageStatus);
    CPPUNIT_ASSERT(neededStatus2.size() == 1);


    //Not registered needed package status
    vector<TaskData> neededStatus3 = mTaskManager->getTasksByPackageStatus(
                                thirdPackageStatus,
                                mTaskManager->mTasksByNeededPackageStatus);
    CPPUNIT_ASSERT(neededStatus3.size() == 0);



    //Test provided package status
    vector<TaskData> providedStatus1 = mTaskManager->getTasksByPackageStatus(
                                secondPackageStatus,
                                mTaskManager->mTasksByProvidedPackageStatus);
    CPPUNIT_ASSERT_EQUAL(string("Chew gimer stick cane"),
                         providedStatus1[0].id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         providedStatus1[0].neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         providedStatus1[0].providedPackageStatus);
    CPPUNIT_ASSERT(providedStatus1.size() == 1);

    vector<TaskData> providedStatus2 = mTaskManager->getTasksByPackageStatus(
                                thirdPackageStatus,
                                mTaskManager->mTasksByProvidedPackageStatus);
    CPPUNIT_ASSERT_EQUAL(string("Watch House M.D."),
                         providedStatus2[0].id);
    CPPUNIT_ASSERT_EQUAL(firstPackageStatus,
                         providedStatus2[0].neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         providedStatus2[0].providedPackageStatus);
    CPPUNIT_ASSERT_EQUAL(string("Milk the platypus"),
                         providedStatus2[1].id);
    CPPUNIT_ASSERT_EQUAL(secondPackageStatus,
                         providedStatus2[1].neededPackageStatus);
    CPPUNIT_ASSERT_EQUAL(thirdPackageStatus,
                         providedStatus2[1].providedPackageStatus);
    CPPUNIT_ASSERT(providedStatus2.size() == 2);


    //Not registered provided package status
    vector<TaskData> providedStatus3 = mTaskManager->getTasksByPackageStatus(
                                firstPackageStatus,
                                mTaskManager->mTasksByProvidedPackageStatus);
    CPPUNIT_ASSERT(providedStatus3.size() == 0);
}
