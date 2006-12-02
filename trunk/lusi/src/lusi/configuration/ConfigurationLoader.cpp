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

#include "ConfigurationLoader.h"
#include "ConfigurationXmlDeserializer.h"
#include "ConfigurationParameterMap.h"
#include "../util/LocalFile.h"
#include "../util/LocalUrl.h"

using lusi::util::LocalFile;
using lusi::util::LocalUrl;

using namespace lusi::configuration;

//public:

ConfigurationLoader::ConfigurationLoader() {
}

ConfigurationLoader::~ConfigurationLoader() {
}

ConfigurationParameterMap* ConfigurationLoader::load(
                        const LocalUrl& localUrl) throw (PersistenceException) {
    if (localUrl.isDirectory() || localUrl.isRelative()) {
        throw PersistenceException("Invalid url: " + localUrl.getPath());
    }

    if (!LocalFile(localUrl).exists()) {
        throw PersistenceException(localUrl.getPath() + " doesn't exist");
    }

    xmlDocPtr document = xmlParseFile(localUrl.getPath().c_str());
    if (!document) {
        throw PersistenceException(localUrl.getPath() + " couldn't be parsed");
    }

    xmlNodePtr node = xmlDocGetRootElement(document);
    if (!node) {
        xmlFreeDoc(document);
        throw PersistenceException(localUrl.getPath() + " is empty");
    }

    ConfigurationParameterMap* configuration =
                        ConfigurationXmlDeserializer().deserialize(document);

    xmlFreeDoc(document);

    return configuration;
}
