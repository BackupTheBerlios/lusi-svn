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

#include "Package.h"
#include "Profile.h"
#include "ProfileManager.h"
#include "ResourceMap.h"

using lusi::package::status::PackageStatus;

using namespace lusi::package;

//public:

Package::Package(PackageId* packageId,
                 const status::PackageStatus* packageStatus /*=
                        status::UnknownPackageStatus::getInstance()*/) {
    mPackageId = packageId;
    mPackageStatus = packageStatus;

    mProfile = ProfileManager::getInstance()->getProfile(packageId);
    mResourceMap = new ResourceMap();
}

Package::~Package() {
    delete mProfile;
    delete mResourceMap;
}

/*
inline PackageId* Package::getPackageId() {
    return mPackageId;
}

inline Profile* Package::getProfile() {
    return mProfile;
}

inline ResourceMap* Package::getResourceMap() {
    return mResourceMap;
}

inline const PackageStatus* Package::getPackageStatus() {
    return mPackageStatus;
}

inline void Package::setPackageStatus(const PackageStatus* packageStatus) {
    mPackageStatus = packageStatus;
}
*/
