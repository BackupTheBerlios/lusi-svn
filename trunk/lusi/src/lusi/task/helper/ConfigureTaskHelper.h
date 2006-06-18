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

#ifndef LUSI_TASK_HELPER_CONFIGURETASKHELPER_H
#define LUSI_TASK_HELPER_CONFIGURETASKHELPER_H

#include <lusi/task/helper/TaskHelper.h>

namespace lusi {
namespace task {
namespace helper {

/**
 * @class ConfigureTaskHelper ConfigureTaskHelper.h \
 * lusi/task/helper/ConfigureTaskHelper.h
 *
 * Base TaskHelper for ConfigureTask.
 * All the TaskHelpers which provide an implementation for ConfigureTask must
 * inherit from this class.
 *
 * No default implementation is defined for this class. Everything must be done
 * in child classes.
 */
class ConfigureTaskHelper: public TaskHelper {
public:

    /**
     * Creates a new ConfigureTaskHelper.
     */
    ConfigureTaskHelper();

    /**
     * Destroys this ConfigureTaskHelper.
     */
    virtual ~ConfigureTaskHelper();

protected:

private:

    /**
     * Copy constructor disabled.
     */
    ConfigureTaskHelper(const ConfigureTaskHelper& configureTaskHelper);

    /**
     * Assignment disabled.
     */
    ConfigureTaskHelper& operator=(
            const ConfigureTaskHelper& configureTaskHelper);

};

}
}
}

#endif
