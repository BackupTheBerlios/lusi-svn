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

#include <ltdl.h>

#include "PluginLoader.h"

using namespace lusi::plugin;

namespace lusi {
namespace plugin {

/**
 * Loads the module.
 * This is a function to be used with lt_dlforeachfile, so it follows the
 * signature it needs.
 * The module is loaded from the specified filename, and the data isn't used.
 * Returned value is always 0, so lt_dlforeachfile will go on calling this
 * function with every filename until no more files can be loaded.
 *
 * The function "initializer" of the module is called when it is loaded. It
 * must do all the needed operations to initialize the module.
 *
 * @param filename The name of the file to laod the module from.
 * @param data Not used.
 * @return Always 0.
 */
int loadModule(const char* filename, lt_ptr data) {
    lt_dlhandle module = lt_dlopenext(filename);

    if (module) {
        typedef void initializer();

        //int cast is an ugly hack made to avoid an ISO C++ warning
        //See http://www.trilithium.com/johan/2004/12/problem-with-dlsym/
        initializer* init = reinterpret_cast<initializer*>(
                                    (int)lt_dlsym(module, "initializer"));
        if (init) {
            init();
        } else {
            lt_dlclose(module);
        }
    } else {
        lt_dlclose(module);
    }

    return 0;
}

}
}

//public:

PluginLoader* PluginLoader::getInstance() {
    if (sInstance == 0) {
        sInstance = new PluginLoader();
    }

    return sInstance;
}

PluginLoader::~PluginLoader() {
}

void PluginLoader::loadPlugins() {
    if (!lt_dlinit()) {
        lt_dlforeachfile(PLUGINDIR, loadModule, 0);
    }
}

//private:

PluginLoader* PluginLoader::sInstance = 0;

PluginLoader::PluginLoader() {
}
