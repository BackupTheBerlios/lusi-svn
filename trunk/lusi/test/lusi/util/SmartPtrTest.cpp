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

#include <string>
#include <vector>

#include "SmartPtrTest.h"

using std::string;
using std::vector;

namespace lusi {
namespace util {

/**
 * Base class to test conversion.
 */
class Base {
public:
    Base(int baseInt) {
        mBaseInt = baseInt;
    }

    /**
     * Needed for dynamic_cast to work.
     */
    virtual void dummy() {
    }

    int mBaseInt;
};

/**
 * Derived class to test conversion.
 */
class Derived: public Base {
public:
    Derived(int baseInt, int derivedInt): Base(baseInt) {
        mDerivedInt = derivedInt;
    }

    int mDerivedInt;
};

}
}

using namespace lusi::util;

//public:

void SmartPtrTest::setUp() {
    mInt = new int(42);
    mSmartPtr = new SmartPtr<int>(mInt);
}

void SmartPtrTest::tearDown() {
    delete mSmartPtr;
}

void SmartPtrTest::testGetPtr() {
    CPPUNIT_ASSERT_EQUAL(mInt, getPtr(*mSmartPtr));
}

void SmartPtrTest::testConstructor() {
    CPPUNIT_ASSERT_EQUAL(mInt, mSmartPtr->mPointer);
    CPPUNIT_ASSERT_EQUAL(1, *mSmartPtr->mReferenceCount);

    //Test default constructor
    SmartPtr<int> smartPtr;
    CPPUNIT_ASSERT_EQUAL((int*)0, smartPtr.mPointer);
    CPPUNIT_ASSERT_EQUAL(1, *smartPtr.mReferenceCount);
}

void SmartPtrTest::testCopyConstructor() {
    SmartPtr<int> smartPtr(*mSmartPtr);
    CPPUNIT_ASSERT_EQUAL(mSmartPtr->mPointer, smartPtr.mPointer);
    CPPUNIT_ASSERT_EQUAL(mSmartPtr->mReferenceCount, smartPtr.mReferenceCount);
    CPPUNIT_ASSERT_EQUAL(2, *mSmartPtr->mReferenceCount);
}

void SmartPtrTest::testIsNull() {
    //Test if the smart pointer isn't null
    CPPUNIT_ASSERT_EQUAL(false, mSmartPtr->isNull());

    //Test if the smart pointer is null
    SmartPtr<int> smartPtr;
    CPPUNIT_ASSERT_EQUAL(true, smartPtr.isNull());
}

void SmartPtrTest::testOperatorAssignment() {
    int* intPtr = new int(108);
    SmartPtr<int> smartPtr(intPtr);
    *mSmartPtr = smartPtr;

    CPPUNIT_ASSERT_EQUAL(smartPtr.mPointer, mSmartPtr->mPointer);
    CPPUNIT_ASSERT_EQUAL(smartPtr.mReferenceCount, mSmartPtr->mReferenceCount);
    CPPUNIT_ASSERT_EQUAL(2, *smartPtr.mReferenceCount);

    //Test self assignment
    *mSmartPtr = smartPtr;
    CPPUNIT_ASSERT_EQUAL(smartPtr.mPointer, mSmartPtr->mPointer);
    CPPUNIT_ASSERT_EQUAL(smartPtr.mReferenceCount, mSmartPtr->mReferenceCount);
    CPPUNIT_ASSERT_EQUAL(2, *smartPtr.mReferenceCount);
}

void SmartPtrTest::testOperatorPointer() {
    SmartPtr<string> smartPtr(new string("Hello"));

    CPPUNIT_ASSERT_EQUAL((size_t)5, smartPtr->size());

    //Test with a null pointer
    smartPtr = SmartPtr<string>(0);
    CPPUNIT_ASSERT_THROW(smartPtr->size(), NullPointerException);

    //Test with a const SmartPtr
    const SmartPtr<string> smartPtrConst(new string("World"));
    CPPUNIT_ASSERT_EQUAL((size_t)5, smartPtrConst->size());

    //Test with a const null pointer
    const SmartPtr<string> smartPtrConst2(0);
    CPPUNIT_ASSERT_THROW(smartPtrConst2->size(), NullPointerException);
}

void SmartPtrTest::testOperatorReference() {
    CPPUNIT_ASSERT_EQUAL(*mInt, *(*mSmartPtr));

    //Test with a null pointer
    *mSmartPtr = SmartPtr<int>(0);
    CPPUNIT_ASSERT_THROW(*(*mSmartPtr), NullPointerException);

    //Test with a const SmartPtr
    const SmartPtr<int> smartPtrConst(new int(42));
    CPPUNIT_ASSERT_EQUAL(42, *smartPtrConst);

    //Test with a const null pointer
    const SmartPtr<int> smartPtrConst2(0);
    CPPUNIT_ASSERT_THROW(*smartPtrConst2, NullPointerException);
}

void SmartPtrTest::testOperatorEqual() {
    SmartPtr<int> smartPtr(*mSmartPtr);

    //Test between the SmartPtr and a copy of it
    CPPUNIT_ASSERT(*mSmartPtr == smartPtr);

    //Test between the SmartPtr and its pointer
    CPPUNIT_ASSERT(mInt == *mSmartPtr);

    //Test between the SmartPtr and a different SmartPtr
    int* intPtr = new int(42);
    smartPtr = SmartPtr<int>(intPtr);

    CPPUNIT_ASSERT(!(*mSmartPtr == smartPtr));

    //Test between the SmartPtr and a different pointer (with the same value)
    CPPUNIT_ASSERT(!(intPtr == *mSmartPtr));
}

void SmartPtrTest::testOperatorNotEqual() {
    //Test between the SmartPtr and a different SmartPtr
    int* intPtr = new int(42);
    SmartPtr<int> smartPtr(intPtr);

    CPPUNIT_ASSERT(*mSmartPtr != smartPtr);

    //Test between the SmartPtr and a different pointer (with the same value)
    CPPUNIT_ASSERT(intPtr != *mSmartPtr);

    //Test between the SmartPtr and a copy of it
    smartPtr = SmartPtr<int>(*mSmartPtr);

    CPPUNIT_ASSERT(!(*mSmartPtr != smartPtr));

    //Test between the SmartPtr and its pointer
    CPPUNIT_ASSERT(!(mInt != *mSmartPtr));

}

void SmartPtrTest::testOperatorConversion() {
    SmartPtr<Derived> derivedPtr(new Derived(42, 108));

    //Test from derived type to base
    SmartPtr<Base> basePtr = (SmartPtr<Base>)derivedPtr;

    CPPUNIT_ASSERT_EQUAL((Base*)derivedPtr.mPointer, basePtr.mPointer);
    CPPUNIT_ASSERT_EQUAL(derivedPtr.mReferenceCount, basePtr.mReferenceCount);
    CPPUNIT_ASSERT_EQUAL(2, *derivedPtr.mReferenceCount);

    //Test from base type to derived
    SmartPtr<Derived> derivedPtr2 = (SmartPtr<Derived>)basePtr;

    CPPUNIT_ASSERT_EQUAL(derivedPtr.mPointer, derivedPtr2.mPointer);
    CPPUNIT_ASSERT_EQUAL(derivedPtr.mReferenceCount,
                         derivedPtr2.mReferenceCount);
    CPPUNIT_ASSERT_EQUAL(3, *derivedPtr.mReferenceCount);
    CPPUNIT_ASSERT_EQUAL(derivedPtr->mBaseInt, derivedPtr2->mBaseInt);
    CPPUNIT_ASSERT_EQUAL(derivedPtr->mDerivedInt, derivedPtr2->mDerivedInt);

    //Test an invalid conversion
    SmartPtr<SmartPtrTest> nullPtr = (SmartPtr<SmartPtrTest>) derivedPtr;
    CPPUNIT_ASSERT(nullPtr.isNull());
}

void SmartPtrTest::testDeletePointer() {
    SmartPtr<int> smartPtr(*mSmartPtr);
    CPPUNIT_ASSERT_EQUAL(2, *smartPtr.mReferenceCount);
    smartPtr.deletePointer();

    CPPUNIT_ASSERT_EQUAL(1, *smartPtr.mReferenceCount);

    //Restores values to avoid crash
    smartPtr.mPointer = mSmartPtr->mPointer;
    smartPtr.mReferenceCount = mSmartPtr->mPointer;
    ++smartPtr.mReferenceCount;
}

void SmartPtrTest::testStdVector() {
    int* intPtr1 = new int(1);
    int* intPtr2 = new int(9);
    int* intPtr3 = new int(7);
    SmartPtr<int>* smartPtr1 = new SmartPtr<int>(intPtr1);
    SmartPtr<int>* smartPtr2 = new SmartPtr<int>(intPtr2);
    SmartPtr<int>* smartPtr3 = new SmartPtr<int>(intPtr3);
    SmartPtr<int>* smartPtr4 = new SmartPtr<int>(*smartPtr3);

    vector< SmartPtr<int> > smartPtrs;
    smartPtrs.push_back(*smartPtr2);
    smartPtrs.push_back(*smartPtr3);
    smartPtrs.insert(smartPtrs.begin(), *smartPtr1);
    smartPtrs.push_back(*smartPtr4);

    delete smartPtr1;
    delete smartPtr2;
    delete smartPtr3;
    delete smartPtr4;

    CPPUNIT_ASSERT_EQUAL(intPtr1, getPtr(smartPtrs[0]));
    CPPUNIT_ASSERT_EQUAL(intPtr2, getPtr(smartPtrs[1]));
    CPPUNIT_ASSERT_EQUAL(intPtr3, getPtr(smartPtrs[2]));
    CPPUNIT_ASSERT_EQUAL(intPtr3, getPtr(smartPtrs[3]));
    CPPUNIT_ASSERT_EQUAL((size_t)4, smartPtrs.size());
}
