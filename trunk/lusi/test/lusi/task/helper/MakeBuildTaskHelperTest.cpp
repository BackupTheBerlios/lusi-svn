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

#include <vector>

#include "MakeBuildTaskHelperTest.h"

#define protected public
#define private public
#include "MakeBuildTaskHelper.h"
#undef private
#undef protected

#include "../TaskTestImplementation.h"
#include "../../package/LocalFileResource.h"
#include "../../package/Package.h"
#include "../../package/ResourceMap.h"
#include "../../util/SmartPtr.h"

using std::string;

using lusi::package::LocalFileResource;
using lusi::package::Resource;
using lusi::task::TaskTestImplementation;
using lusi::util::Process;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

void MakeBuildTaskHelperTest::setUp() {
    mTask = new TaskTestImplementation("TaskTestImplementation");
    mMakeBuildTaskHelper = new MakeBuildTaskHelper(mTask);
}

void MakeBuildTaskHelperTest::tearDown() {
    delete mMakeBuildTaskHelper;
    delete mTask;
}

void MakeBuildTaskHelperTest::testConstructor() {
    CPPUNIT_ASSERT_EQUAL(string("MakeBuildTaskHelper"),
                         mMakeBuildTaskHelper->mName);
    CPPUNIT_ASSERT_EQUAL(mTask, mMakeBuildTaskHelper->mTask);
}

void MakeBuildTaskHelperTest::testGetProcess() {
    mTask->getPackage()->getResourceMap()->add(
            SmartPtr<Resource>(new LocalFileResource("/package/")));
    mTask->getPackage()->getResourceMap()->add(
        SmartPtr<Resource>(new LocalFileResource("/package/subDirectory/")));
    delete mMakeBuildTaskHelper;
    mMakeBuildTaskHelper = new MakeBuildTaskHelper(mTask);

    SmartPtr<Process> process(mMakeBuildTaskHelper->getProcess());

    CPPUNIT_ASSERT_EQUAL(string("/package/"), process->getWorkingDirectory());
    CPPUNIT_ASSERT_EQUAL(string("make"), process->getArguments()[0]);
    CPPUNIT_ASSERT_EQUAL((size_t)1, process->getArguments().size());
}
