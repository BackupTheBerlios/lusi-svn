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

#ifndef LUSI_TASK_TASKLOGGER_H
#define LUSI_TASK_TASKLOGGER_H

#include <string>
#include <vector>

#include <lusi/task/LoggedEventType.h>

namespace lusi {
namespace task {
class TaskLoggerObserver;
}
}

namespace lusi {
namespace task {

/**
 * @todo Documentation
 */
class TaskLogger {
public:

    /**
     * Creates a new TaskLogger.
     */
    TaskLogger();

    /**
     * Destroys this TaskLogger.
     */
    virtual ~TaskLogger();

    void event(const std::string& message, LoggedEventType type);

    void addObserver(TaskLoggerObserver* observer);

    std::vector<TaskLoggerObserver*> getObservers();

    void removeObserver(TaskLoggerObserver* observer);

protected:

private:

};

}
}

#endif
