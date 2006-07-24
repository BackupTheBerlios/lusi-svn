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

#ifndef LUSI_TASK_TASKTESTIMPLEMENTATION_H
#define LUSI_TASK_TASKTESTIMPLEMENTATION_H

#include <lusi/task/Task.h>

namespace lusi {
namespace task {

/**
 * Implementation of Task for testing purposes.
 * This class helps testing where Task objects are needed.
 */
class TaskTestImplementation: public Task {
public:

    /**
     * Creates a new TakeTestImplementation.
     *
     * @param name The name of the Task.
     * @param package The Package to use.
     * @param taskConfiguration The TaskConfiguration to use.
     */
    TaskTestImplementation(const std::string& name,
                           lusi::package::Package* package,
                           TaskConfiguration* taskConfiguration);

    /**
     * Destroys this TaskTestImplementation.
     */
    virtual ~TaskTestImplementation();

};

}
}

#endif
