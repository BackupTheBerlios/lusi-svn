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

#include <map>
#include <string>

#include "TaskHelperManagerTest.h"

#define protected public
#define private public
#include "TaskHelperManager.h"
#undef private
#undef protected

#include "TaskHelperTestImplementation.h"
#include "../TaskTestImplementation.h"

using std::multimap;
using std::pair;
using std::string;
using std::vector;

using namespace lusi::task::helper;

//public:

void TaskHelperManagerTest::setUp() {
    mTaskHelperManager = TaskHelperManager::getInstance();
    mTaskHelperManager->registerTaskHelper(createTaskHelperTestImplementation1,
                                           "Bath the iguana");
    mTaskHelperManager->registerTaskHelper(createTaskHelperTestImplementation2,
                                           "Bath the iguana");
    mTaskHelperManager->registerTaskHelper(createTaskHelperTestImplementation3,
                                           "Record Takeshi's Castle");
}

void TaskHelperManagerTest::tearDown() {
    mTaskHelperManager->mTaskHelperFactories.erase("Bath the iguana");
    mTaskHelperManager->mTaskHelperFactories.erase("Record Takeshi's Castle");
}

void TaskHelperManagerTest::testSingleton() {
    CPPUNIT_ASSERT(TaskHelperManager::getInstance() != 0);

    CPPUNIT_ASSERT_EQUAL(TaskHelperManager::getInstance(),
            TaskHelperManager::getInstance());
}

void TaskHelperManagerTest::testRegisterTaskHelper() {
    typedef multimap<string, TaskHelper* (*)(Task*)>::iterator iterator;
    pair<iterator, iterator> range1 =
                mTaskHelperManager->mTaskHelperFactories.equal_range(
                        "Bath the iguana");
    CPPUNIT_ASSERT(range1.first != range1.second);
    CPPUNIT_ASSERT(createTaskHelperTestImplementation1 == range1.first->second);
    ++range1.first;
    CPPUNIT_ASSERT(createTaskHelperTestImplementation2 == range1.first->second);
    ++range1.first;
    CPPUNIT_ASSERT(range1.first == range1.second);


    pair<iterator, iterator> range2 =
                mTaskHelperManager->mTaskHelperFactories.equal_range(
                        "Record Takeshi's Castle");
    CPPUNIT_ASSERT(range2.first != range2.second);
    CPPUNIT_ASSERT(createTaskHelperTestImplementation3 == range2.first->second);
    ++range2.first;
    CPPUNIT_ASSERT(range2.first == range2.second);
}

void TaskHelperManagerTest::testGetTaskHelpers() {
    Task* bathTask = new TaskTestImplementation("Bath the iguana", 0, 0);
    vector<TaskHelper*> bathHelpers = mTaskHelperManager->getTaskHelpers(
                                            bathTask);
    CPPUNIT_ASSERT_EQUAL(string("1"),
        dynamic_cast<TaskHelperTestImplementation*>(bathHelpers[0])->getName());
    CPPUNIT_ASSERT_EQUAL(string("2"),
        dynamic_cast<TaskHelperTestImplementation*>(bathHelpers[1])->getName());
    CPPUNIT_ASSERT(bathHelpers.size() == 2);

    delete bathHelpers[0];
    delete bathHelpers[1];


    Task* recordTask = new TaskTestImplementation("Record Takeshi's Castle", 0,
                                                  0);
    vector<TaskHelper*> recordHelpers = mTaskHelperManager->getTaskHelpers(
                                                recordTask);
    CPPUNIT_ASSERT_EQUAL(string("3"),
        dynamic_cast<TaskHelperTestImplementation*>
            (recordHelpers[0])->getName());
    CPPUNIT_ASSERT(recordHelpers.size() == 1);

    delete recordHelpers[0];


    //Not registered TaskHelper
    Task* unregisteredTask = new TaskTestImplementation("Clean my room", 0, 0);
    vector<TaskHelper*> unregisteredHelpers = mTaskHelperManager->getTaskHelpers(
                                                    unregisteredTask);
    CPPUNIT_ASSERT(unregisteredHelpers.size() == 0);
}
