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
#include "../../configuration/ConfigurationParameterMap.h"

using std::string;

using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::InvalidConfigurationException;

using namespace lusi::task::helper;

TaskHelper* lusi::task::helper::createTaskHelperTestImplementation1(
                                        Task* task) {
    return new TaskHelperTestImplementation(task, "1", true);
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
                                    bool validResources /* = false*/):
                            TaskHelper(name, task) {
    mValidResources = validResources;
}

TaskHelperTestImplementation::~TaskHelperTestImplementation() {
}

/*
inline bool TaskHelperTestImplementation::hasValidResources() {
    return mValidResources;
}
*/
