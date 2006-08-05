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

using std::string;
using std::vector;

using lusi::package::LocalFileResource;

using namespace lusi::package;

//public:

void ResourceMapTest::setUp() {
    mResourceMap = new ResourceMap();
    mResource1 = new ResourceTestImplementation("1");
    mResource2 = new ResourceTestImplementation("2");
    mResource3 = new ResourceTestImplementation("3");

    mResourceMap->addResource(mResource1);
    mResourceMap->addResource(mResource2);
    mResourceMap->addResource(mResource3);
}

void ResourceMapTest::tearDown() {
    delete mResourceMap;
}

void ResourceMapTest::testAddResource() {
    CPPUNIT_ASSERT_EQUAL(mResourceMap->mMap.find(mResource1->getId())->second,
                         mResource1);
    CPPUNIT_ASSERT_EQUAL(mResourceMap->mMap.find(mResource2->getId())->second,
                         mResource2);
    CPPUNIT_ASSERT_EQUAL(mResourceMap->mMap.find(mResource3->getId())->second,
                         mResource3);

    //Test return value adding a resource
    Resource* resource = new ResourceTestImplementation("4");

    CPPUNIT_ASSERT_EQUAL(true, mResourceMap->addResource(resource));
    CPPUNIT_ASSERT_EQUAL(mResourceMap->mMap.find(resource->getId())->second,
                         resource);

    //Test adding an element with the same key of one already added
    resource = new ResourceTestImplementation(mResource1->getId());

    CPPUNIT_ASSERT_EQUAL(false, mResourceMap->addResource(resource));
    CPPUNIT_ASSERT_EQUAL(mResourceMap->mMap.find(mResource1->getId())->second,
                         mResource1);
    delete resource;
}

void ResourceMapTest::testGetResource() {
    CPPUNIT_ASSERT_EQUAL(mResource1,
                         mResourceMap->getResource(mResource1->getId()));
    CPPUNIT_ASSERT_EQUAL(mResource2,
                         mResourceMap->getResource(mResource2->getId()));
    CPPUNIT_ASSERT_EQUAL(mResource3,
                         mResourceMap->getResource(mResource3->getId()));

    //Test getting a not added Resource
    CPPUNIT_ASSERT_EQUAL((Resource*)0,
                         mResourceMap->getResource("4"));
}

void ResourceMapTest::testGetAllResources() {
    vector<Resource*> allResources = mResourceMap->getAllResources();

    CPPUNIT_ASSERT(allResources.size() == 3);
    CPPUNIT_ASSERT_EQUAL(mResource1, allResources[0]);
    CPPUNIT_ASSERT_EQUAL(mResource2, allResources[1]);
    CPPUNIT_ASSERT_EQUAL(mResource3, allResources[2]);
}

void ResourceMapTest::testGetAllResourcesByType() {
    vector<ResourceTestImplementation*> allResources =
            mResourceMap->getAllResourcesByType<ResourceTestImplementation>();

    CPPUNIT_ASSERT(allResources.size() == 3);
    CPPUNIT_ASSERT_EQUAL(dynamic_cast<ResourceTestImplementation*>(mResource1),
                         allResources[0]);
    CPPUNIT_ASSERT_EQUAL(dynamic_cast<ResourceTestImplementation*>(mResource2),
                         allResources[1]);
    CPPUNIT_ASSERT_EQUAL(dynamic_cast<ResourceTestImplementation*>(mResource3),
                         allResources[2]);

    //Test with a type not added
    vector<LocalFileResource*> allLocalFileResources =
                    mResourceMap->getAllResourcesByType<LocalFileResource>();
    CPPUNIT_ASSERT(allLocalFileResources.size() == 0);
}

void ResourceMapTest::testRemoveResource() {
    CPPUNIT_ASSERT_EQUAL(true,
                         mResourceMap->removeResource(mResource1->getId()));
    CPPUNIT_ASSERT_EQUAL(false,
                         mResourceMap->removeResource(mResource1->getId()));
    CPPUNIT_ASSERT_EQUAL((Resource*)0,
                         mResourceMap->getResource(mResource1->getId()));
    //TODO Check if deletes the removed element
}

void ResourceMapTest::testDestructor() {
//TODO Check if destructor deletes all the added elements. Add it to tests
}
