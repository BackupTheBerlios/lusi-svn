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

#include "ResourceMapTest.h"

#define protected public
#define private public
#include "ResourceMap.h"
#undef private
#undef protected

#include "ResourceTestImplementation.h"
#include "LocalFileResource.h"

using std::vector;

using lusi::package::LocalFileResource;
using lusi::util::SmartPtr;

using namespace lusi::package;

//public:

void ResourceMapTest::setUp() {
    mResourceMap = new ResourceMap();
    mResource1 = new ResourceTestImplementation("1");
    mResource2 = new ResourceTestImplementation("2");
    mResource3 = new ResourceTestImplementation("3");

    mResourceMap->add(SmartPtr<Resource>(mResource1));
    mResourceMap->add(SmartPtr<Resource>(mResource2));
    mResourceMap->add(SmartPtr<Resource>(mResource3));
}

void ResourceMapTest::tearDown() {
    delete mResourceMap;
}

void ResourceMapTest::testCopyConstructor() {
    ResourceMap resourceMap(*mResourceMap);

    //Tests the original map
    CPPUNIT_ASSERT_EQUAL(mResource1, getPtr(mResourceMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(mResource2, getPtr(mResourceMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(mResource3, getPtr(mResourceMap->get("3")));

    //Tests the copied map
    CPPUNIT_ASSERT_EQUAL(mResource1, getPtr(resourceMap.get("1")));
    CPPUNIT_ASSERT_EQUAL(mResource2, getPtr(resourceMap.get("2")));
    CPPUNIT_ASSERT_EQUAL(mResource3, getPtr(resourceMap.get("3")));
}

void ResourceMapTest::testGetAllResourcesByType() {
    vector< SmartPtr<ResourceTestImplementation> > allResources =
            mResourceMap->getAllResourcesByType<ResourceTestImplementation>();

    CPPUNIT_ASSERT_EQUAL((size_t)3, allResources.size());
    CPPUNIT_ASSERT_EQUAL(dynamic_cast<ResourceTestImplementation*>(mResource1),
                         getPtr(allResources[0]));
    CPPUNIT_ASSERT_EQUAL(dynamic_cast<ResourceTestImplementation*>(mResource2),
                         getPtr(allResources[1]));
    CPPUNIT_ASSERT_EQUAL(dynamic_cast<ResourceTestImplementation*>(mResource3),
                         getPtr(allResources[2]));

    //Test with a type not added
    vector< SmartPtr<LocalFileResource> > allLocalFileResources =
                    mResourceMap->getAllResourcesByType<LocalFileResource>();
    CPPUNIT_ASSERT(allLocalFileResources.size() == 0);
}

void ResourceMapTest::testOperatorAssignment() {
    ResourceMap resourceMap;
    resourceMap = *mResourceMap;

    //Tests the original map
    CPPUNIT_ASSERT_EQUAL(mResource1, getPtr(mResourceMap->get("1")));
    CPPUNIT_ASSERT_EQUAL(mResource2, getPtr(mResourceMap->get("2")));
    CPPUNIT_ASSERT_EQUAL(mResource3, getPtr(mResourceMap->get("3")));

    //Tests the copied map
    CPPUNIT_ASSERT_EQUAL(mResource1, getPtr(resourceMap.get("1")));
    CPPUNIT_ASSERT_EQUAL(mResource2, getPtr(resourceMap.get("2")));
    CPPUNIT_ASSERT_EQUAL(mResource3, getPtr(resourceMap.get("3")));

    //Test self assignment
    resourceMap = resourceMap;

    CPPUNIT_ASSERT_EQUAL(mResource1, getPtr(resourceMap.get("1")));
    CPPUNIT_ASSERT_EQUAL(mResource2, getPtr(resourceMap.get("2")));
    CPPUNIT_ASSERT_EQUAL(mResource3, getPtr(resourceMap.get("3")));
}
