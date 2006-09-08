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

#include "IdSmartPtrMapTest.h"

using std::string;
using std::vector;

namespace lusi {
namespace util {

/**
 * Class used in tests with the interface needed for IdSmartPtrMaps.
 */
class Index {
public:

    Index(const string& id) {
        mId = id;
    }

    virtual ~Index() {
    }

    string getId() const {
        return mId;
    }

private:

    string mId;

};

}
}

using namespace lusi::util;

//public:

void IdSmartPtrMapTest::setUp() {
    mIdSmartPtrMap = new IdSmartPtrMap<Index>();
    mIndex1 = new Index("1");
    mIndex2 = new Index("2");
    mIndex3 = new Index("3");

    mIdSmartPtrMap->add(SmartPtr<Index>(mIndex1));
    mIdSmartPtrMap->add(SmartPtr<Index>(mIndex2));
    mIdSmartPtrMap->add(SmartPtr<Index>(mIndex3));
}

void IdSmartPtrMapTest::tearDown() {
    delete mIdSmartPtrMap;
}

void IdSmartPtrMapTest::testAdd() {
    CPPUNIT_ASSERT_EQUAL(
                    getPtr(mIdSmartPtrMap->mMap.find(mIndex1->getId())->second),
                    mIndex1);
    CPPUNIT_ASSERT_EQUAL(
                    getPtr(mIdSmartPtrMap->mMap.find(mIndex2->getId())->second),
                    mIndex2);
    CPPUNIT_ASSERT_EQUAL(
                    getPtr(mIdSmartPtrMap->mMap.find(mIndex3->getId())->second),
                    mIndex3);

    //Test return value adding a resource
    Index* index = new Index("4");

    CPPUNIT_ASSERT_EQUAL(true, mIdSmartPtrMap->add(SmartPtr<Index>(index)));
    CPPUNIT_ASSERT_EQUAL(
                    getPtr(mIdSmartPtrMap->mMap.find(index->getId())->second),
                    index);

    //Test adding an element with the same key of one already added
    index = new Index(mIndex1->getId());

    CPPUNIT_ASSERT_EQUAL(false, mIdSmartPtrMap->add(SmartPtr<Index>(index)));
    CPPUNIT_ASSERT_EQUAL(
                    getPtr(mIdSmartPtrMap->mMap.find(mIndex1->getId())->second),
                    mIndex1);
}

void IdSmartPtrMapTest::testGet() {
    CPPUNIT_ASSERT_EQUAL(mIndex1,
                         getPtr(mIdSmartPtrMap->get(mIndex1->getId())));
    CPPUNIT_ASSERT_EQUAL(mIndex2,
                         getPtr(mIdSmartPtrMap->get(mIndex2->getId())));
    CPPUNIT_ASSERT_EQUAL(mIndex3,
                         getPtr(mIdSmartPtrMap->get(mIndex3->getId())));

    //Test getting a not added Index
    CPPUNIT_ASSERT_EQUAL((Index*)0,
                         getPtr(mIdSmartPtrMap->get("4")));
}

void IdSmartPtrMapTest::testGetAll() {
    vector< SmartPtr<Index> > allElements = mIdSmartPtrMap->getAll();

    CPPUNIT_ASSERT_EQUAL((size_t)3, allElements.size());
    CPPUNIT_ASSERT_EQUAL(mIndex1, getPtr(allElements[0]));
    CPPUNIT_ASSERT_EQUAL(mIndex2, getPtr(allElements[1]));
    CPPUNIT_ASSERT_EQUAL(mIndex3, getPtr(allElements[2]));
}

void IdSmartPtrMapTest::testRemove() {
    string id = mIndex1->getId();
    CPPUNIT_ASSERT_EQUAL(true, mIdSmartPtrMap->remove(id));
    CPPUNIT_ASSERT_EQUAL(false, mIdSmartPtrMap->remove(id));
    CPPUNIT_ASSERT_EQUAL((Index*)0, getPtr(mIdSmartPtrMap->get(id)));
}
