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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONDIRECTORIES_H
#define LUSI_CONFIGURATION_CONFIGURATIONDIRECTORIES_H

#include <string>

#include <lusi/util/User.h>

namespace lusi {
namespace package {
class PackageId;
}
}

namespace lusi {
namespace task {
class Task;
}
}

namespace lusi {
namespace configuration {

/**
 * Class to get configuration paths.
 * The path to configuration directories and files are got using this class.
 * The root of all the paths is "$HOME/.lusi/", so they all depend on the user
 * specified when creating the object. By default, the user set is the current
 * user.
 *
 * None of the paths are guaranteed to exist. The paths are simply returned, but
 * no checks are made about their existence. That is let to the classes using
 * this class.
 */
class ConfigurationPaths {
public:

    /**
     * Creates a new ConfigurationPaths.
     *
     * @param user The user to get the paths for. Default is the current user.
     */
    ConfigurationPaths(
            const lusi::util::User& user = lusi::util::User::getCurrentUser());

    /**
     * Destroys this ConfigurationPaths.
     */
    virtual ~ConfigurationPaths();

    /**
     * Returns the path to the base configuration directory.
     * It is "$HOME/.lusi/".
     * The directory isn't guaranteed to exist.
     *
     * @return The base configuration directory.
     */
    std::string getBaseDirectory();

    /**
     * Returns the path to the base configuration directory for Packages.
     * It is "$HOME/.lusi/package/".
     * The directory isn't guaranteed to exist.
     *
     * @return The path to the base configuration directory for Packages.
     */
    std::string getPackagesBaseDirectory();

    /**
     * Returns the path to the configuration directory of the specified
     * PackageId.
     * It is "$HOME/.lusi/package/${packageName}/${packageVersion}/".
     * The directory isn't guaranteed to exist.
     *
     * @param packageId The PackageId to get the name and version from.
     * @return The path to the configuration directory of the specified
     *         PackageId.
     */
    std::string getPackageDirectory(
                            const lusi::package::PackageId& packageId);

    /**
     * Returns the path to the configuration file of the Package identified by
     * the specified PackageId.
     * It is
     * "$HOME/.lusi/package/${packageName}/${packageVersion}/package-data.xml".
     * The file isn't guaranteed to exist.
     *
     * @param packageId The PackageId to get the name and version from.
     * @return The path to the configuration file of the Package identified by
     *         the specified PackageId.
     */
    std::string getPackageFile(const lusi::package::PackageId& packageId);

    /**
     * Returns the path to the configuration file of the Profile identified by
     * the specified PackageId.
     * It is "$HOME/.lusi/package/${packageName}/${packageVersion}/profile.xml".
     * The file isn't guaranteed to exist.
     *
     * @param packageId The PackageId to get the name and version from.
     * @return The path to the configuration file of the Profile identified by
     *         the specified PackageId.
     */
    std::string getProfileFile(const lusi::package::PackageId& packageId);

    /**
     * Returns the path to the configuration file of the specified Task.
     * It is
     * "$HOME/.lusi/package/${packageName}/${packageVersion}/${taskId}.xml".
     * The file isn't guaranteed to exist.
     *
     * @param taskId The id of the Task to get the configuration for.
     * @param packageId The PackageId of the Task to get the configuration for.
     * @return The path to the configuration file of the specified Task.
     */
    std::string getTaskFile(const std::string& taskId,
                            const lusi::package::PackageId& packageId);

private:

    /**
     * The base directory for all the configuration paths ("$HOME/.lusi/").
     */
    std::string mBaseDirectory;



    /**
     * Copy constructor disabled.
     */
    ConfigurationPaths(const ConfigurationPaths& configurationPaths);

    /**
     * Assignment disabled.
     */
    ConfigurationPaths& operator=(const ConfigurationPaths& configurationPaths);

};

}
}

#endif
