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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONSAVER_H
#define LUSI_CONFIGURATION_CONFIGURATIONSAVER_H

#include <lusi/configuration/PersistenceException.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterMap;
}
}

namespace lusi {
namespace util {
class LocalUrl;
}
}

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationSaver ConfigurationSaver.h \
 * lusi/configuration/ConfigurationSaver.h
 *
 * Saves ConfigurationParameterMaps to hard disk.
 * The ConfigurationParameterMap is serialized to XML and then saved in a file.
 *
 * The files saved can be loaded using ConfigurationLoader.
 * ConfigurationXmlSerializer is used to serialize the XML document. To save
 * the XML document to the file, libxml-2.0 is used (it's also used to
 * serialize the ConfigurationParameterMap).
 *
 * @see ConfigurationLoader
 */
class ConfigurationSaver {
public:

    /**
     * Creates a new ConfigurationSaver.
     */
    ConfigurationSaver();

    /**
     * Destroys this ConfigurationSaver.
     */
    virtual ~ConfigurationSaver();

    /**
     * Saves a ConfigurationParameterMap to the specified LocalUrl.
     * The LocalUrl must be the absolute path to a file. If it exists already,
     * it will be overwritten.
     * The user must have permissions to create the file and all the needed
     * directories (if any is needed to be created).
     *
     * If something fails when saving the file, a PersistenceException is
     * thrown.
     *
     * @param configurationParameterMap The ConfigurationParameterMap to save.
     * @param localUrl The path to save the ConfigurationParameterMap to.
     * @throws PersistenceException If the file couldn't be saved.
     * @see ConfigurationXmlSerializer
     */
    void save(ConfigurationParameterMap* configurationParameterMap,
            const lusi::util::LocalUrl& localUrl) throw (PersistenceException);

private:

    /**
     * Copy constructor disabled.
     */
    ConfigurationSaver(const ConfigurationSaver& configurationSaver);

    /**
     * Assignment disabled.
     */
    ConfigurationSaver& operator=(
                        const ConfigurationSaver& configurationSaver);

};

}
}

#endif
