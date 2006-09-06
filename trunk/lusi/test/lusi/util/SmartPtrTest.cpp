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
}

void SmartPtrTest::testCopyConstructor() {
    SmartPtr<int> smartPtr(*mSmartPtr);
    CPPUNIT_ASSERT_EQUAL(mSmartPtr->mPointer, smartPtr.mPointer);
    CPPUNIT_ASSERT_EQUAL(mSmartPtr->mReferenceCount, smartPtr.mReferenceCount);
    CPPUNIT_ASSERT_EQUAL(2, *mSmartPtr->mReferenceCount);
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
    string* hello = new string("Hello");
    SmartPtr<string> smartPtr(hello);

    CPPUNIT_ASSERT_EQUAL((size_t)5, smartPtr->size());
}

void SmartPtrTest::testOperatorReference() {
    CPPUNIT_ASSERT_EQUAL(*mInt, *(*mSmartPtr));
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

void SmartPtrTest::testDereference() {
    SmartPtr<int>* smartPtr = new SmartPtr<int>(*mSmartPtr);
    CPPUNIT_ASSERT_EQUAL(2, *mSmartPtr->mReferenceCount);
    delete smartPtr;

    CPPUNIT_ASSERT_EQUAL(1, *mSmartPtr->mReferenceCount);
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
