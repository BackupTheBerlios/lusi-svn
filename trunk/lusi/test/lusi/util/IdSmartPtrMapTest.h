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

#ifndef LUSI_UTIL_IDSMARTPTRMAPTEST_H
#define LUSI_UTIL_IDSMARTPTRMAPTEST_H

#include <cppunit/extensions/HelperMacros.h>

#define protected public
#define private public
#include <lusi/util/IdSmartPtrMap.h>
#undef private
#undef protected

namespace lusi {
namespace util {
class Index;
}
}

namespace lusi {
namespace util {

/**
 * Test class for IdSmartPtrMap.
 *
 * @see IdSmartPtrMap
 */
class IdSmartPtrMapTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(IdSmartPtrMapTest);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testAdd);
    CPPUNIT_TEST(testGet);
    CPPUNIT_TEST(testGetAll);
    CPPUNIT_TEST(testRemove);
    CPPUNIT_TEST(testOperatorAssignment);
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
     * Checks if the pointed objects are shared by both maps.
     */
    void testCopyConstructor();

    /**
     * Checks if add() adds the element to the map and returns the adequate
     * boolean value.
     */
    void testAdd();

    /**
     * Checks if get() returns an already added element, or null if it wasn't
     * added.
     */
    void testGet();

    /**
     * Checks if getAll() returns a vector with all the added elements.
     */
    void testGetAll();

    /**
     * Checks if remove() removes an added element.
     */
    void testRemove();

    /**
     * Checks if the pointed objects are shared by both maps.
     */
    void testOperatorAssignment();

private:

    /**
     * The IdSmartPtrMap to test.
     */
    IdSmartPtrMap<Index>* mIdSmartPtrMap;

    /**
     * First index.
     */
    Index* mIndex1;

    /**
     * Second index.
     */
    Index* mIndex2;

    /**
     * Third index.
     */
    Index* mIndex3;

};

}
}

#endif
