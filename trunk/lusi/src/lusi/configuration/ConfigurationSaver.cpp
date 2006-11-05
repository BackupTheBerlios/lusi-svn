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

#include "ConfigurationSaver.h"
#include "ConfigurationXmlSerializer.h"
#include "../util/LocalFile.h"
#include "../util/LocalUrl.h"

using lusi::util::LocalFile;
using lusi::util::LocalUrl;

using namespace lusi::configuration;

//public:

ConfigurationSaver::ConfigurationSaver() {
}

ConfigurationSaver::~ConfigurationSaver() {
}

void ConfigurationSaver::save(
                        ConfigurationParameterMap* configurationParameterMap,
                        const LocalUrl& localUrl) throw (PersistenceException) {
    if (localUrl.isDirectory() || localUrl.isRelative()) {
        throw PersistenceException("Invalid url: " + localUrl.getPath());
    }

    LocalFile directory(localUrl.getParent());
    if (!directory.exists() && !directory.mkdirs()) {
        throw PersistenceException(localUrl.getParent() +
                                        " couldn't be created");
    }

    xmlDocPtr doc = ConfigurationXmlSerializer().serialize(
                                                    configurationParameterMap);

    if (xmlSaveFileEnc(localUrl.getPath().c_str(), doc, "UTF-8") == -1) {
        xmlFreeDoc(doc);
        throw PersistenceException(localUrl.getPath() + " couldn't be saved");
    }

    xmlFreeDoc(doc);
}
