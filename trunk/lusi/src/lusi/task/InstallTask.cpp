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

#include "InstallTask.h"
#include "../package/status/BuiltPackageStatus.h"
#include "../package/status/InstalledPackageStatus.h"

using lusi::package::Package;
using lusi::package::status::BuiltPackageStatus;
using lusi::package::status::InstalledPackageStatus;
using lusi::package::status::PackageStatus;

using namespace lusi::task;

//public:

InstallTask::InstallTask(Package *package,
                TaskConfiguration *taskConfiguration):
        Task("InstallTask", package, taskConfiguration) {
}

InstallTask::~InstallTask() {
}

const PackageStatus* InstallTask::needsPackageStatus() const {
    return BuiltPackageStatus::getInstance();
}

const PackageStatus* InstallTask::providesPackageStatus() const {
    return InstalledPackageStatus::getInstance();
}
