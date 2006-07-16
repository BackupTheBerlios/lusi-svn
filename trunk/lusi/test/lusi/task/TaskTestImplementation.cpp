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

#include "TaskTestImplementation.h"

using lusi::package::Package;

using namespace lusi::task;

//public:

TaskTestImplementation::TaskTestImplementation(const std::string& name,
                                Package* package,
                                TaskConfiguration* taskConfiguration):
                Task(name, package, taskConfiguration) {
}

TaskTestImplementation::~TaskTestImplementation() {
}

/*
inline const lusi::package::status::PackageStatus*
TaskTestImplementation::needsPackageStatus() const {
    return lusi::package::status::UnknownPackageStatus::getInstance();
}

inline const lusi::package::status::PackageStatus*
TaskTestImplementation::providesPackageStatus() const {
    return lusi::package::status::UnknownPackageStatus::getInstance();
}
*/
