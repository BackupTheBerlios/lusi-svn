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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONPARAMETERLOCALURL_H
#define LUSI_CONFIGURATION_CONFIGURATIONPARAMETERLOCALURL_H

#include <lusi/configuration/ConfigurationParameterSimple.h>

#include <lusi/util/LocalUrl.h>

namespace lusi {
namespace configuration {

/**
 * @class ConfigurationParameterLocalUrl ConfigurationParameterLocalUrl.h \
 * lusi/configuration/ConfigurationParameterLocalUrl.h
 *
 * A simple parameter of configuration using LocalUrl values.
 * A default value can be specified when creating the LocalUrl parameter, so
 * it's used if the normal value isn't set.
 * Both the normal value and the default value are LocalUrls.
 *
 * The url can have an specific type from the enumeration UrlType. It makes
 * possible to difference two url values with different meaning, for example,
 * for files and directories.
 * No checks are made in the value nor the default value to assure that they are
 * from the specified type.
 *
 * @todo Add a way to check for valid and invalid values using restrictions.
 */
class ConfigurationParameterLocalUrl:
            public ConfigurationParameterSimple<lusi::util::LocalUrl> {
public:

    /**
     * The type of the url.
     */
    enum UrlType {
        AllType,
        FileType,
        DirectoryType
    };

    /**
     * Creates a new ConfigurationParameterLocalUrl.
     * This constructor doesn't set the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param urlType The type of the url, all by default.
     */
    ConfigurationParameterLocalUrl(const std::string& id,
                                   const std::string& name,
                                   PriorityType priorityType,
                                   const std::string& information,
                                   UrlType urlType = AllType);

    /**
     * Creates a new ConfigurationParameterLocalUrl.
     * This constructor sets the default value.
     *
     * @param id The id.
     * @param name The name.
     * @param priorityType The type of priority.
     * @param information The information about this ConfigurationParameter.
     * @param defaultValue The default value.
     * @param urlType The type of the url, all by default.
     */
    ConfigurationParameterLocalUrl(const std::string& id,
                                   const std::string& name,
                                   PriorityType priorityType,
                                   const std::string& information,
                                   const lusi::util::LocalUrl& defaultValue,
                                   UrlType urlType = AllType);

    /**
     * Destroys this ConfigurationParameterLocalUrl.
     */
    virtual ~ConfigurationParameterLocalUrl();

    /**
     * Accepts a visitor.
     *
     * @param visitor The ConfigurationParameterVisitor to accept.
     */
    virtual void accept(ConfigurationParameterVisitor* visitor);

    /**
     * Returns the type of the url.
     *
     * @return The type of the url.
     */
    UrlType getUrlType() const {
        return mUrlType;
    }

protected:

private:

    /**
     * The type of the LocalUrl.
     */
    UrlType mUrlType;



    /**
     * Copy constructor disabled.
     */
    ConfigurationParameterLocalUrl(
        const ConfigurationParameterLocalUrl& configurationParameterLocalUrl);

    /**
     * Assignment disabled.
     */
    ConfigurationParameterLocalUrl& operator=(
        const ConfigurationParameterLocalUrl& configurationParameterLocalUrl);

};

}
}

#endif
