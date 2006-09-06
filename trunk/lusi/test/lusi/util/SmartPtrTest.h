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

#ifndef LUSI_UTIL_SMARTPTRTEST_H
#define LUSI_UTIL_SMARTPTRTEST_H

#include <cppunit/extensions/HelperMacros.h>

#define protected public
#define private public
#include <lusi/util/SmartPtr.h>
#undef private
#undef protected

namespace lusi {
namespace util {

/**
 * Test class for SmartPtr.
 *
 * @see SmartPtr
 */
class SmartPtrTest: public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(SmartPtrTest);
    CPPUNIT_TEST(testGetPtr);
    CPPUNIT_TEST(testConstructor);
    CPPUNIT_TEST(testCopyConstructor);
    CPPUNIT_TEST(testOperatorAssignment);
    CPPUNIT_TEST(testOperatorPointer);
    CPPUNIT_TEST(testOperatorReference);
    CPPUNIT_TEST(testOperatorEqual);
    CPPUNIT_TEST(testOperatorNotEqual);
    CPPUNIT_TEST(testDereference);
    CPPUNIT_TEST(testStdVector);
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
     * Tests if it returns the pointer in the SmartPtr.
     */
    void testGetPtr();

    /**
     * Tests if the refefence count is set to one and the pointer is set to the
     * one passed.
     */
    void testConstructor();

    /**
     * Tests if the reference count is incremented and the pointer is set to the
     * one in the copied SmartPtr.
     */
    void testCopyConstructor();

    /**
     * Tests if the new reference count and pointer are assigned like in copy
     * constructor.
     * @todo Check that previous values are deleted
     */
    void testOperatorAssignment();

    /**
     * Tests if the pointer returned is equal to the one contained.
     */
    void testOperatorPointer();

    /**
     * Tests if the reference returned is equal to the one of the pointer
     * contained.
     */
    void testOperatorReference();

    /**
     * Tests if two SmartPtr are equal, if are different, and the same checkings
     * between smart pointers and raw pointers.
     */
    void testOperatorEqual();

    /**
     * Tests if two SmartPtr are equal, if are different, and the same checkings
     * between smart pointers and raw pointers.
     */
    void testOperatorNotEqual();

    /**
     * Tests if the reference count is decreased by one.
     * @todo Check that the pointer and the reference count deleted when
     * reference count reaches 0.
     */
    void testDereference();

    /**
     * Tests the use of SmartPtr with std::vector.
     * If std::vector works, all the container classes in C++ standard library
     * will also work.
     */
    void testStdVector();

private:

    /**
     * The SmartPtr to test.
     */
    SmartPtr<int>* mSmartPtr;

    /**
     * The int to add to the SmartPtr.
     */
    int* mInt;

};

}
}

#endif
