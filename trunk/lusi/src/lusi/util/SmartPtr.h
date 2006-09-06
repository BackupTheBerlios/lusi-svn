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

namespace lusi {
namespace util {

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
 * Null pointers can be stored in SmartPtrs. However, you're advised against
 * doing it, as it doesn't make too much sense. Pointers can't be modified
 * once they're set (apart from using assignment operator), and there are no
 * checks against null pointers in reference nor pointer operators, which will
 * probably lead to a crash.
 *
 * Due to the use of templates, everything is implemented in the header file. No
 * source file exists for this class.
 *
 * A great information source about smart pointers in C++ can be read in
 * "Modern C++ Design: Generic Programming and Design Patterns Applied" book
 * by Andrei Alexandrescu. The chapter about smart pointers can be read online
 * here: http://www.informit.com/articles/article.asp?p=31529&seqNum=1&rl=1
 *
 * @todo Handle null pointers
 */
template<typename T>
class SmartPtr {
public:

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
    friend inline T* getPtr(const SmartPtr& smartPtr) {
        return smartPtr.mPointer;
    }

    /**
     * Creates a new SmartPtr.
     * The SmartPtr gets control over the lifespan of the specified pointer. It
     * will be deleted when it's no more SmartPtr referencing it.
     * This constructor is explicit to avoid a smart pointer getting undesired
     * control over the lifespan of the pointer.
     *
     * @param pointer The pointer to manage.
     */
    explicit SmartPtr(T* pointer) {
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
        dereference();
    }

    /**
     * Assigns the contents of another smartPtr to this SmartPtr.
     * The previously managed pointer is handled as in the destructor. Then, the
     * new pointer is handled as in the copy constructor.
     *
     * @param smartPtr The SmartPtr to copy.
     * @return A reference to this SmartPtr.
     */
    SmartPtr& operator=(const SmartPtr& smartPtr) {
        if (&smartPtr == this) {
            return *this;
        }

        dereference();

        mPointer = smartPtr.mPointer;
        mReferenceCount = smartPtr.mReferenceCount;
        ++(*mReferenceCount);

        return *this;
    }

    /**
     * Returns a pointer to the referenced element.
     *
     * @return A pointer to the referenced element.
     */
    T* operator->() {
        return mPointer;
    }

    /**
     * Returns a constant pointer to the referenced element.
     * This is an accessor method.
     *
     * @return A constant pointer to the referenced element.
     */
    const T* operator->() const {
        return mPointer;
    }

    /**
     * Returns a reference to the pointed element.
     * This is an accessor method.
     *
     * @return A reference to the pointed element.
     */
    T& operator*() {
        return *mPointer;
    }

    /**
     * Returns a constant reference to the pointed element.
     *
     * @return A constant reference to the pointed element.
     */
    const T& operator*() const {
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
     * Removes one reference from the count and deletes it and the pointer if
     * this is the last SmartPtr managing the pointer.
     */
    void dereference() {
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
