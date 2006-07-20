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

#include "TaskHelperTestImplementation.h"
#include "../../configuration/ConfigurationParametersSet.h"

using std::string;

using lusi::configuration::ConfigurationParametersSet;
using lusi::package::ResourceMap;

using namespace lusi::task::helper;

TaskHelper* lusi::task::helper::createTaskHelperTestImplementation1(
                                        Task* task) {
    return new TaskHelperTestImplementation(task, "1");
}

TaskHelper* lusi::task::helper::createTaskHelperTestImplementation2(
                                        Task* task) {
    return new TaskHelperTestImplementation(task, "2");
}

TaskHelper* lusi::task::helper::createTaskHelperTestImplementation3(
                                        Task* task) {
    return new TaskHelperTestImplementation(task, "3");
}

//public:

TaskHelperTestImplementation::TaskHelperTestImplementation(Task* task,
                                    const string& name,
                                    bool validResourceMap /* = false*/):
                            TaskHelper(name, task) {
    mValidResourceMap = validResourceMap;
}

TaskHelperTestImplementation::~TaskHelperTestImplementation() {
}

/*
inline bool TaskHelperTestImplementation::hasValidResourceMap() {
    return mValidResourceMap;
}
*/

ConfigurationParametersSet TaskHelperTestImplementation::checkConfiguration() {
}

void TaskHelperTestImplementation::execute() {
}

void TaskHelperTestImplementation::revert() {
}

/*
inline const string& getName() const {
    return mName;
}
*/
