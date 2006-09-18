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

#include "TaskHelper.h"
#include "../../configuration/ConfigurationParameter.h"
#include "../../configuration/ConfigurationParameterMap.h"

using std::string;
using std::vector;

using lusi::configuration::ConfigurationParameter;
using lusi::configuration::ConfigurationParameterMap;
using lusi::configuration::InvalidConfigurationException;
using lusi::task::Task;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

TaskHelper::~TaskHelper() {
}

void TaskHelper::initConfigurationParameterMap() {
}

void TaskHelper::execute() throw (ExecuteTaskHelperException,
                                  InvalidConfigurationException) {
    ConfigurationParameterMap invalidConfiguration = getInvalidConfiguration();
    if (invalidConfiguration.getAll().size() > 0) {
        throw new InvalidConfigurationException(
                "Invalid configuration found when executing " + mName,
                invalidConfiguration);
    }
}

ConfigurationParameterMap TaskHelper::getInvalidConfiguration() {
    ConfigurationParameterMap invalidConfiguration;

    vector< SmartPtr<ConfigurationParameter> > configurationParameters =
        mConfigurationParameterMap.getAll();
    for (uint i=0; i<configurationParameters.size(); ++i) {
        if (configurationParameters[i]->isInvalid()) {
            invalidConfiguration.add(configurationParameters[i]);
        }
    }

    return invalidConfiguration;
}

/*
inline const string& TaskHelper::getName() const {
    return mName;
}

inline ConfigurationParameterMap& TaskHelper::getConfigurationParameterMap() {
    return mConfigurationParameterMap;
}
*/

//protected:

TaskHelper::TaskHelper(const string& name, Task* task) {
    mName = name;
    mTask = task;
}

/*
inline void TaskHelper::notifyTaskLogger(const std::string& message,
                                         LoggedEventType type) {
    mTask->getTaskLogger()->notifyEvent(message, type);
}

inline void TaskHelper::notifyTaskProgress(int value) {
    mTask->getTaskProgress()->notifyProgress(value);
}
*/
