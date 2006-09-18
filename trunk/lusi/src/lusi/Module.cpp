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

#include "Module.h"
#include "package/Package.h"
#include "task/Task.h"
#include "task/TaskManager.h"

using std::string;

using lusi::package::Package;
using lusi::task::NoTaskAvailableException;
using lusi::task::Task;
using lusi::task::TaskManager;

using namespace lusi;

//public:

Module::~Module() {
}

/*
inline Package* Module::getPackage() {
    return mPackage;
}
*/

int Module::getEstimatedNumberOfTasks() {
    return 0;
}

Task* Module::nextTask() throw (NoTaskAvailableException) {
    if (mPackage->getPackageStatus() == getFinalPackageStatus()) {
        return 0;
    }

    mCurrentTask = TaskManager::getInstance()->getTask(mPackage);

    if (mCurrentTask == 0) {
        throw NoTaskAvailableException("There are no more available taks");
    }

    return mCurrentTask;
}

//protected:

Module::Module(Package* package) {
    mPackage = package;
    mInitialPackageStatus = package->getPackageStatus();
}
