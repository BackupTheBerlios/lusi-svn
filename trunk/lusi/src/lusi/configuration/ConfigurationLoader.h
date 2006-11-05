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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONLOADER_H
#define LUSI_CONFIGURATION_CONFIGURATIONLOADER_H

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
 * @class ConfigurationLoader ConfigurationLoader.h \
 * lusi/configuration/ConfigurationLoader.h
 *
 * Loads ConfigurationParameterMaps from hard disk.
 * The file containing the serialized ConfigurationParameterMap is parsed and
 * deserialized to obtain the ConfigurationParameterMap.
 *
 * It can open only XML files saved with ConfigurationSaver (or manually, but
 * following the same schema). ConfigurationXmlDeserializer is used to
 * deserialize the XML document. To parse the file to obtain the XML document,
 * libxml-2.0 is used (it's also used to deserialize the document).
 *
 * @see ConfigurationSaver
 */
class ConfigurationLoader {
public:

    /**
     * Creates a new ConfigurationLoader.
     */
    ConfigurationLoader();

    /**
     * Destroys this ConfigurationLoader.
     */
    virtual ~ConfigurationLoader();

    /**
     * Loads a ConfigurationParameterMap from the specified LocalUrl.
     * The LocalUrl must contain the absolute path of an XML file following the
     * same schema used when they are saved through ConfigurationSaver.
     * The returned ConfigurationParameterMap must be deleted when it is no
     * longer needed.
     *
     * If the file couldn't be parsed or is empty, a PersistenceException is
     * thrown.
     *
     * @param localUrl The path to the file to load.
     * @return The ConfigurationParameterMap loaded from the file.
     * @throws PersistenceException If the file couldn't be loaded.
     * @see ConfigurationXmlDeserializer
     */
    ConfigurationParameterMap* load(const lusi::util::LocalUrl& localUrl)
                                                throw (PersistenceException);

private:

    /**
     * Copy constructor disabled.
     */
    ConfigurationLoader(const ConfigurationLoader& configurationLoader);

    /**
     * Assignment disabled.
     */
    ConfigurationLoader& operator=(
                        const ConfigurationLoader& configurationLoader);

};

}
}

#endif
