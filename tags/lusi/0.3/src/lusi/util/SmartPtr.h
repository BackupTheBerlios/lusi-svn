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

#ifndef LUSI_UTIL_SMARTPTR_H
#define LUSI_UTIL_SMARTPTR_H

#include <lusi/util/NullPointerException.h>

namespace lusi {
namespace util {

template<typename T>
class SmartPtr;

/**
 * Function that returns the contained pointer in a SmartPtr.
 * This approach is used instead of implicit conversion. Enforcing the use
 * of an explicit function may warn the programmer about something
 * dangerous, and avoiding those operations (for example, deleting the
 * pointer).
 *
 * @param smartPtr The SmartPtr to get its pointer.
 * @return The contained pointer in the SmartPtr.
 */
template<typename T>
T* getPtr(const SmartPtr<T>& smartPtr) {
    return smartPtr.mPointer;
}

/**
 * @class SmartPtr SmartPtr.h lusi/util/SmartPtr.h
 *
 * Smart pointer to handle pointers deallocation.
 * Smart pointers behave almost like normal pointers: the fields of the pointed
 * type can be accessed through -> operator, a reference to the pointed type
 * can be got with * operator and they can be compared to other smart pointers
 * and even raw pointers using == and != operators (however, "if (smartPointer)"
 * syntax isn't available to know if it's null or not).
 * However, pointer arithmetics isn't available. Neither implicit conversion to
 * raw pointers, although the contained raw pointer can be got using the
 * function getPtr(SmartPointer). Implicit conversion from raw pointers to smart
 * pointers through constructor is also disabled.
 * It has no support for pointers to arrays.
 *
 * The main difference comes when deallocating the pointed element. Smart
 * pointers take care of deleting the pointed element when there are no more
 * smart pointers to them. It can't handle, however, circular references.
 * So, if you have two classes that references each other, SmartPtr can't be
 * used in both of them.
 * As a rule of thumb, you will use a SmartPtr for agregations and even
 * compositions in the container side and a raw pointer in the containment
 * side. In pure associations, two raw pointers should be fine, as they usually
 * won't delete the other part of the association.
 *
 * SmartPtrs can be stored in C++ standard library containers, but they can't
 * be used as keys in indexed containers.
 *
 * Null pointers can be stored in SmartPtrs. If no pointer is specified when
 * creating a SmartPtr, it is set to a null pointer. Once created, the pointer
 * can only be modified using assignment operator.
 * A null pointer can be checked using isNull().
 * If pointer or reference operators are used on a null pointer, a
 * NullPointerException is thrown.
 *
 * A SmartPtr can be converted to another SmartPtr with a different type of the
 * contained pointer. However, it uses dynamic_cast to do the cast of the
 * pointers, so only the same casts are allowed (that is, between classes, but
 * not base data types). If the classes aren't a base class and a subclass, a
 * null pointer is returned.
 * Although the original SmartPtr and the casted SmartPtr are from different
 * types, the pointer is shared by both SmartPtr (if it isn't null). When the
 * last of them is deleted, the pointer is deleted.
 *
 * Due to the use of templates, everything is implemented in the header file. No
 * source file exists for this class.
 *
 * A great information source about smart pointers in C++ can be read in
 * "Modern C++ Design: Generic Programming and Design Patterns Applied" book
 * by Andrei Alexandrescu. The chapter about smart pointers can be read online
 * here: http://www.informit.com/articles/article.asp?p=31529&seqNum=1&rl=1
 */
template<typename T>
class SmartPtr {
template<typename Any> friend class SmartPtr;
template<typename Any> friend Any* getPtr(const SmartPtr<Any>&);
public:

    /**
     * Creates a new SmartPtr.
     * The SmartPtr gets control over the lifespan of the specified pointer. It
     * will be deleted when there are no more SmartPtr referencing it.
     * This constructor is explicit to avoid a smart pointer getting undesired
     * control over the lifespan of the pointer.
     *
     * @param pointer The pointer to manage. Null by default.
     */
    explicit SmartPtr(T* pointer = 0) {
        mPointer = pointer;
        mReferenceCount = new int(1);
    }

    /**
     * Creates a new SmartPtr from another SmartPtr (copy constructor).
     * The pointer is shared by both SmartPtr. When the last of them is deleted,
     * the pointer is deleted.
     *
     * @param smartPtr The SmartPtr to copy.
     */
    SmartPtr(const SmartPtr& smartPtr) {
        mPointer = smartPtr.mPointer;
        mReferenceCount = smartPtr.mReferenceCount;
        ++(*mReferenceCount);
    }

    /**
     * Destroys this SmartPtr.
     * If this is the last SmartPtr managing the pointer, the pointer is
     * deleted.
     */
    virtual ~SmartPtr() {
        deletePointer();
    }

    /**
     * Returns true if the contained pointer is null, false otherwise.
     *
     * @return True if the contained pointer is null, false otherwise.
     */
    bool isNull() const {
        return mPointer == 0;
    }

    /**
     * Assigns the contents of another smartPtr to this SmartPtr.
     * The previously managed pointer is handled as in the destructor. Then, the
     * new pointer is handled as in the copy constructor.
     *
     * @param smartPtr The SmartPtr to copy.
     * @return A reference to this SmartPtr.
     * @see SmartPtr(const SmartPtr&)
     */
    SmartPtr& operator=(const SmartPtr& smartPtr) {
        if (&smartPtr == this) {
            return *this;
        }

        deletePointer();

        mPointer = smartPtr.mPointer;
        mReferenceCount = smartPtr.mReferenceCount;
        ++(*mReferenceCount);

        return *this;
    }

    /**
     * Returns a pointer to the referenced element.
     *
     * @return A pointer to the referenced element.
     * @throw NullPointerException If the pointer is null.
     */
    T* operator->() throw (NullPointerException) {
        checkNull();
        return mPointer;
    }

    /**
     * Returns a constant pointer to the referenced element.
     * This is an accessor method.
     *
     * @return A constant pointer to the referenced element.
     * @throw NullPointerException If the pointer is null.
     */
    const T* operator->() const throw (NullPointerException) {
        checkNull();
        return mPointer;
    }

    /**
     * Returns a reference to the pointed element.
     * This is an accessor method.
     *
     * @return A reference to the pointed element.
     * @throw NullPointerException If the pointer is null.
     */
    T& operator*() throw (NullPointerException) {
        checkNull();
        return *mPointer;
    }

    /**
     * Returns a constant reference to the pointed element.
     *
     * @return A constant reference to the pointed element.
     * @throw NullPointerException If the pointer is null.
     */
    const T& operator*() const throw (NullPointerException) {
        checkNull();
        return *mPointer;
    }

    /**
     * Returns true if the contained pointer is equal to the one of the
     * specified SmartPtr, false otherwise.
     * This is an accessor method.
     *
     * @param smartPtr The SmartPtr to compare to.
     * @return True if the contained pointer is equal to the one of the
     *         specified SmartPtr, false otherwise.
     */
    bool operator==(const SmartPtr& smartPtr) const {
        return mPointer == smartPtr.mPointer;
    }

    /**
     * Returns true if the pointer of the SmartPtr is equal to the one
     * specified, false otherwise.
     *
     * @param smartPtr The SmartPtr to compare with the pointer.
     * @param tPtr The pointer to compare with the SmartPtr.
     * @return True if the pointer of the SmartPtr is equal to the one
     *         specified, false otherwise.
     */
    friend inline bool operator==(const SmartPtr& smartPtr, const T* tPtr) {
        return smartPtr.mPointer == tPtr;
    }

    /**
     * Returns true if the pointer of the SmartPtr is equal to the one
     * specified, false otherwise.
     *
     * @param tPtr The pointer to compare with the SmartPtr.
     * @param smartPtr The SmartPtr to compare with the pointer.
     * @return True if the pointer of the SmartPtr is equal to the one
     *         specified, false otherwise.
     */
    friend inline bool operator==(const T* tPtr, const SmartPtr& smartPtr) {
        return tPtr == smartPtr.mPointer;
    }

    /**
     * Returns true if the contained pointer is different to the one of the
     * specified SmartPtr, false otherwise.
     * This is an accessor method.
     *
     * @param smartPtr The SmartPtr to compare to.
     * @return True if the contained pointer is different to the one of the
     *         specified SmartPtr, false otherwise.
     */
    bool operator!=(const SmartPtr& smartPtr) const {
        return mPointer != smartPtr.mPointer;
    }

    /**
     * Returns true if the pointer of the SmartPtr is different to the one
     * specified, false otherwise.
     *
     * @param smartPtr The SmartPtr to compare with the pointer.
     * @param tPtr The pointer to compare with the SmartPtr.
     * @return True if the pointer of the SmartPtr is different to the one
     *         specified, false otherwise.
     */
    friend inline bool operator!=(const SmartPtr& smartPtr, const T* tPtr) {
        return smartPtr.mPointer != tPtr;
    }

    /**
     * Returns true if the pointer of the SmartPtr is different to the one
     * specified, false otherwise.
     *
     * @param tPtr The pointer to compare with the SmartPtr.
     * @param smartPtr The SmartPtr to compare with the pointer.
     * @return True if the pointer of the SmartPtr is different to the one
     *         specified, false otherwise.
     */
    friend inline bool operator!=(const T* tPtr, const SmartPtr& smartPtr) {
        return tPtr != smartPtr.mPointer;
    }

    /**
     * Converts a SmartPtr of type T to a SmartPtr of type S.
     * The conversion is made using dynamic_cast, so it can be made only on
     * SmartPtr containing pointers to classes.
     * Although SmartPtr<T> and SmartPtr<S> are different types, the pointer is
     * shared by both SmartPtr. When the last of them is deleted, the pointer
     * is deleted.
     * If the type T can't be converted to type S, a null pointer is returned
     * (and, of course, it's not shared between them).
     */
    template<typename S>
    operator SmartPtr<S>() const {
        SmartPtr<S> smartPtr(0);
        S* pointer = dynamic_cast<S*>(mPointer);

        if (pointer != 0) {
            smartPtr.deletePointer();

            smartPtr.mPointer = pointer;
            smartPtr.mReferenceCount = mReferenceCount;
            ++(*mReferenceCount);
        }

        return smartPtr;
    }

private:

    /**
     * The managed pointer.
     */
    T* mPointer;

    /**
     * The number of SmartPtr that contain the managed pointer.
     */
    int* mReferenceCount;



    /**
     * Checks if the pointer is a null pointer and throws NullPointerException
     * in that case.
     *
     * @throw NullPointerException If the pointer is null.
     */
    void checkNull() const throw (NullPointerException) {
        if (isNull()) {
            throw NullPointerException();
        }
    }

    /**
     * Removes one reference from the count and deletes it and the pointer if
     * this is the last SmartPtr managing the pointer.
     */
    void deletePointer() {
        --(*mReferenceCount);

        if (*mReferenceCount == 0) {
            delete mPointer;
            delete mReferenceCount;
        }
    }
};

}
}

#endif
