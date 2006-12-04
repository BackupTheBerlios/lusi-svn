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

#ifndef LUSI_PACKAGE_STATUS_PACKAGESTATUS_H
#define LUSI_PACKAGE_STATUS_PACKAGESTATUS_H

namespace lusi {
namespace package {
namespace status {

/**
 * @class PackageStatus PackageStatus.h lusi/package/status/PackageStatus.h
 *
 * Interface that represents the status of a package.
 * The status is only a tag used to describe what can be done in a Package.
 * This tag is used when chaining Tasks, so once a Task is executed, the next
 * Task to be executed is selected depending on the status of the Package and
 * the status the Task can handle. For example, a BuiltPackageStatus means that
 * the Package is built and the InstallTask can be executed on it.
 *
 * New status can be added subclassing this interface. Derived classes must
 * follow Singleton Design Pattern.
 *
 * @todo operator=, copy constructor
 */
class PackageStatus {
public:

    /**
     * Destroys this PackageStatus.
     */
    virtual ~PackageStatus() {}

protected:

    /**
     * Creates a new PackageStatus.
     * Protected to avoid classes other than derived to create PackageStatus
     * objects.
     */
    PackageStatus() {}

private:

};

}
}
}

#endif
