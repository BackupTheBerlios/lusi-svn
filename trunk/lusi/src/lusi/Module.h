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

#ifndef LUSI_MODULE_H
#define LUSI_MODULE_H

namespace lusi {
namespace package {
class Package;
}
}

namespace lusi {

/**
 * @class Module Module.h lusi/Module.h
 *
 * Modules are "high level" actions to be executed by applications using the
 * library.
 * Modules are the main classes for applications using the library. Every
 * Module works over a Package provided by the application using the Module.
 * Each module has an specific mission, for example, install or uninstall a
 * Package. They follow the Strategy Design Pattern, and also resemble Façade,
 * as they abstract all the underlying execution of Tasks.
 *
 * Module is an interface which is implemented by the real classes doing all the
 * work.
 *
 * @todo operator=, copy constructor
 */
class Module {
public:

    /**
     * Destroys this Module.
     */
    virtual ~Module() {
    }

    /**
     * Executes this module.
     * Must be implemented in derived classes.
     *
     * @param package The Package to use.
     */
    virtual void execute(lusi::package::Package* package) = 0;

protected:

    /**
     * Creates a new Module.
     * Protected to avoid classes other than derived to create Module
     * objects.
     */
    Module() {
    }

private:

};

}

#endif
