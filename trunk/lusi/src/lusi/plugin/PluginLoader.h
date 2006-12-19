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

#ifndef LUSI_PLUGIN_PLUGINLOADER_H
#define LUSI_PLUGIN_PLUGINLOADER_H

namespace lusi {
namespace plugin {

/**
 * @class PluginLoader PluginLoader.h lusi/plugin/PluginLoader.h
 *
 * Loader for LUSI plugins.
 * LUSI plugins are used to extend the functionality of the base system. They
 * are dinamically loaded shared libraries. This class handles the loading of
 * plugins.
 *
 * The plugins are loaded from "$libdir/lusi/plugins", that is, the directory
 * "plugins" in the library directory of LUSI. All the available modules in that
 * directory can be loaded using loadPlugins(). This method must be called in
 * applications using LUSI so it can use the plugins.
 *
 * To successfully load a plugin, it must have an initializer function called
 * "void initializer()". This function must be a pure C function, so when being
 * used in C++ it must be enclosed with an "extern "C" { void initializer(); }".
 * This is due to name mangling in C++.
 */
class PluginLoader {
public:

    /**
     * Returns the instance of this class.
     * If the instance isn't already created, this method creates it.
     *
     * @return The only created instance of this class.
     */
    static PluginLoader* getInstance();

    /**
     * Destroys this BuiltPackageStatus.
     */
    virtual ~PluginLoader();

    /**
     * Loads all the available plugins.
     * The plugins are loaded from the directory "plugins" in the directory
     * where LUSI library was installed.
     */
    void loadPlugins();

private:

    /**
     * The only created instance of this class.
     * It's created when getInstance() is called for first time.
     */
    static PluginLoader* sInstance;



    /**
     * Creates a new BuiltPackageStatus.
     * Objects must be got with getInstance().
     *
     * @see getInstance()
     */
    PluginLoader();

    /**
     * Copy constructor disabled.
     */
    PluginLoader(const PluginLoader& pluginLoader);

    /**
     * Assignment disabled.
     */
    PluginLoader& operator=(const PluginLoader& pluginLoader);

};

}
}

#endif
