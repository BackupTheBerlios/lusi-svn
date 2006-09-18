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

#include "TaskLoggerObserverTestImplementation.h"

using std::string;

using namespace lusi::task;

//public:

TaskLoggerObserverTestImplementation::TaskLoggerObserverTestImplementation():
                                            TaskLoggerObserver() {
    mTask = 0;
    mMessage = string("");
    mAllMessages = string("");
}


TaskLoggerObserverTestImplementation::~TaskLoggerObserverTestImplementation() {
}

void TaskLoggerObserverTestImplementation::event(Task* task,
                                                 const string& message,
                                                 LoggedEventType type) {
    mTask = task;
    mMessage = message;
    mAllMessages += message;
    mEventType = type;
}

/*
inline Task* TaskLoggerObserverTestImplementation::getTask() {
    Task* task = mTask;
    mTask = 0;
    return task;
}

inline const std::string& TaskLoggerObserverTestImplementation::getMessage() const {
    return mMessage;
}

inline const std::string& TaskLoggerObserverTestImplementation::getAllMessages()
                                                                            const {
    return mAllMessages;
}

inline const LoggedEventType& TaskLoggerObserverTestImplementation::getEventType()
                                                                            const {
    return mEventType;
}
*/
