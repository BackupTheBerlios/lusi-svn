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

#include "PackageStatusTestImplementation.h"

using namespace lusi::package::status;

//public:

const PackageStatusTestImplementation*
PackageStatusTestImplementation::getFirstInstance() {
    if (sFirstInstance == 0) {
        sFirstInstance = new PackageStatusTestImplementation();
    }

    return sFirstInstance;
}

const PackageStatusTestImplementation*
PackageStatusTestImplementation::getSecondInstance() {
    if (sSecondInstance == 0) {
        sSecondInstance = new PackageStatusTestImplementation();
    }

    return sSecondInstance;
}

const PackageStatusTestImplementation*
PackageStatusTestImplementation::getThirdInstance() {
    if (sThirdInstance == 0) {
        sThirdInstance = new PackageStatusTestImplementation();
    }

    return sThirdInstance;
}

PackageStatusTestImplementation::~PackageStatusTestImplementation() {
}

//private:

PackageStatusTestImplementation*
PackageStatusTestImplementation::sFirstInstance = 0;

PackageStatusTestImplementation*
PackageStatusTestImplementation::sSecondInstance = 0;

PackageStatusTestImplementation*
PackageStatusTestImplementation::sThirdInstance = 0;

PackageStatusTestImplementation::PackageStatusTestImplementation() {
}
