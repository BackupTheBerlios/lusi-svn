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

#ifndef LUSI_PACKAGE_RESOURCEMAPTEST_H
#define LUSI_PACKAGE_RESOURCEMAPTEST_H

#include <cppunit/extensions/HelperMacros.h>

namespace lusi {
namespace package {
class Resource;
class ResourceMap;
}
}

namespace lusi {
namespace package {

/**
 * Test class for ResourceMap.
 *
 * @see ResourceMap
 */
class ResourceMapTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(ResourceMapTest);
    CPPUNIT_TEST(testAddResource);
    CPPUNIT_TEST(testGetResource);
    CPPUNIT_TEST(testGetAllResources);
    CPPUNIT_TEST(testRemoveResource);
    CPPUNIT_TEST_SUITE_END();

public:

    /**
     * Sets up context before running a test.
     */
    virtual void setUp();

    /**
     * Cleans up after the test run.
     */
    virtual void tearDown();

    /**
     * Checks if addResource() adds the element to the map and returns the
     * adequate boolean value.
     */
    void testAddResource();

    /**
     * Checks if getResource() returns an already added element, or null if it
     * wasn't added.
     */
    void testGetResource();

    /**
     * Checks if getAllResources() returns a vector with all the added elements.
     */
    void testGetAllResources();

    /**
     * Checks if removeResource()removes and deletes an added element.
     */
    void testRemoveResource();

    /**
     * TODO Check if destructor deletes all the added elements. Add it to tests
     */
    void testDestructor();

private:

    /**
     * The ResourceMap to test.
     */
    ResourceMap* mResourceMap;

    /**
     * First resource.
     */
    Resource* mResource1;

    /**
     * Second resource.
     */
    Resource* mResource2;

    /**
     * Third resource.
     */
    Resource* mResource3;

};

}
}

#endif
