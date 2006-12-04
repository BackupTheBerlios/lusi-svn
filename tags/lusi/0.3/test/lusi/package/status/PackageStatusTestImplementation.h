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

#ifndef LUSI_PACKAGE_STATUS_PACKAGESTATUSTESTIMPLEMENTATION_H
#define LUSI_PACKAGE_STATUS_PACKAGESTATUSTESTIMPLEMENTATION_H

#include <lusi/package/status/PackageStatus.h>

namespace lusi {
namespace package {
namespace status {

/**
 * Implementation of PackageStatus for testing purposes.
 * This class helps testing where PackageStatus objects are needed.
 */
class PackageStatusTestImplementation: public PackageStatus {
public:

    /**
     * Returns the first instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The first instance of this class.
     */
    static const PackageStatusTestImplementation* getFirstInstance();

    /**
     * Returns the second instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The second instance of this class.
     */
    static const PackageStatusTestImplementation* getSecondInstance();

    /**
     * Returns the third instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The third instance of this class.
     */
    static const PackageStatusTestImplementation* getThirdInstance();

    /**
     * Destroys this PackageStatusTestImplementation.
     */
    virtual ~PackageStatusTestImplementation();

protected:

private:

    /**
     * The first created instance of this class.
     * It's created when getFirstInstance() is called for first time.
     */
    static PackageStatusTestImplementation* sFirstInstance;

    /**
     * The second created instance of this class.
     * It's created when getSecondInstance() is called for first time.
     */
    static PackageStatusTestImplementation* sSecondInstance;

    /**
     * The third created instance of this class.
     * It's created when getThirdInstance() is called for first time.
     */
    static PackageStatusTestImplementation* sThirdInstance;




    /**
     * Creates a new PackageStatusTestImplementation.
     * Objects must be got with getInstance() methods.
     */
    PackageStatusTestImplementation();

    /**
     * Copy constructor disabled.
     */
    PackageStatusTestImplementation(
            const PackageStatusTestImplementation& installedPackageStatus);

    /**
     * Assignment disabled.
     */
    PackageStatusTestImplementation& operator=(
            const PackageStatusTestImplementation& installedPackageStatus);

};

}
}
}

#endif
