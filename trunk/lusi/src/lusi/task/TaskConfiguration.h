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

#ifndef LUSI_TASK_TASKCONFIGURATION_H
#define LUSI_TASK_TASKCONFIGURATION_H

#include <string>
#include <vector>

namespace lusi {
namespace configuration {
class ConfigurationParameterMap;
}
}

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
namespace util {
template<typename T>
class SmartPtr;
}
}

namespace lusi {
namespace task {

/**
 * @class TaskConfiguration TaskConfiguration.h lusi/task/TaskConfiguration.h
 *
 * Configuration for a Task.
 * The configuration contains the configuration of the successfully executed
 * TaskHelpers, in the same order the TaskHelpers were executed. It is used to
 * save and load the configuration used by the TaskHelpers of a Task, so it can
 * be reused if the same Task is executed again with the same Package (or a
 * similar version, as explained ahead).
 *
 * There are two types of TaskHelper configurations in this class. First, the
 * loaded configuration of the TaskHelpers, and second, the configuration of the
 * TaskHelpers to save.
 *
 * The loaded configuration contains the configuration of the TaskHelpers that
 * were executed the last time this Task was executed with this Package, with
 * the greatest previous version, with the smallest next version or without
 * version, if any.
 * These configurations can only be got. Moreover, they are the only type of
 * configurations that can be got.
 *
 * The configuration to save contains the configuration of the TaskHelpers that
 * were added since the instance of this class was created. That is, the
 * configuration of the TaskHelpers that were executed in the instance of the
 * associated Task.
 * These configurations can only be added. Moreover, they are the only type of
 * configurations that can be added. The method that saves the configuration,
 * save(), must be called explicitly.
 *
 * Only the configurations added are saved. Configurations that were loaded
 * are not saved again unless they are explicitly added. This behaviour
 * ensures that not used TaskHelper configurations aren't saved. If all the
 * TaskHelper configurations were saved (both loaded and explicitly added) this
 * could lead to, for example, keep the configurations for TaskHelpers of old
 * versions of a package that are no longer being used.
 *
 * The behaviour with undo Tasks is slightly different: when loading undo
 * tasks, the configuration loaded is that from the Task they revert its
 * changes, instead of the configuration of the Undo Task itself.
 * Undo Tasks configurations depends on the Task they revert instead of in the
 * configuration of the Undo Task itself because it must know what the Task did,
 * and also because using the Undo Task configuration itself won't have a lot of
 * sense: once you have undoed the Task, you can't do undo it again, so the
 * configuration has no point (which doesn't happen with normal Tasks, as they
 * can usually be executed as many times as desired).
 * Even then, Undo Task configurations is saved like it is saved with normal
 * Task configurations. Its purpose is merely informative for the advanced user,
 * as she can know what configuration was used to do the undo task.
 *
 * This class isn't meant to be created by any other class than Task.
 */
class TaskConfiguration {
public:

    /**
     * Creates a new TaskConfiguration.
     * It loads the configuration file.
     *
     * @param task The Task to use.
     */
    TaskConfiguration(Task* task);

    /**
     * Destroys this TaskConfiguration.
     */
    virtual ~TaskConfiguration();

    /**
     * Returns the ConfigurationParameterMap that contains the loaded
     * configuration for the specified TaskHelper.
     * If there is no configuration for the TaskHelper, a null smart pointer is
     * returned.
     *
     * @param taskHelperId The id of the TaskHelper to get its loaded
     *                     configuration.
     * @return The ConfigurationParameterMap that contains the loaded
     *         configuration for the specified TaskHelper.
     */
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
    getTaskHelperConfiguration(const std::string& taskHelperId);

    /**
     * Returns all the loaded configurations in the same order they were added.
     * The same order used to add the configurations when they were saved is
     * kept.
     * If no configuration could be loaded, an empty vector is returned.
     *
     * @return All the loaded configurations in the same order they were added.
     */
    std::vector<
    lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap> >
    getAllTaskHelperConfigurations();

    /**
     * Adds a new TaskHelper configuration to be saved.
     * Null pointers can't be used.
     *
     * @param taskHelperConfiguration The ConfigurationParameterMap to be saved.
     */
    void addTaskHelperConfiguration(
            lusi::util::SmartPtr<lusi::configuration::ConfigurationParameterMap>
                    taskHelperConfiguration);

    /**
     * Saves this TaskConfiguration to its configuration file in the hard disk.
     * The order used when adding the TaskHelper configurations is kept when
     * saving them.
     *
     * Only the configurations added are saved. Configurations that were loaded
     * are not saved again unless they are explicitly added. This behaviour
     * ensures that not used TaskHelper configurations aren't saved. If all the
     * TaskHelper configurations were saved (both loaded and explicitly added)
     * this could lead to, for example, keep the configurations for TaskHelpers
     * of old versions of a package that are no longer being used.
     *
     * Saving the TaskConfiguration may fail due to, most likely, external
     * factors, such as a lack of permissions or similar issues. Under normal
     * circumstances, this method should work ;)
     *
     * @return True if the TaskConfiguration was saved, false otherwise.
     */
    bool save();

protected:

private:

    /**
     * The loaded TaskHelper configurations.
     */
    lusi::configuration::ConfigurationParameterMap* mConfiguration;

    /**
     * The TaskHelper configurations to save.
     */
    lusi::configuration::ConfigurationParameterMap* mConfigurationToSave;

    /**
     * The Task this TaskConfiguration is for.
     */
    Task* mTask;



    /**
     * Loads the TaskHelper configurations from the hard disk.
     * First, the file for the exact version of the package is used. If it
     * can't be loaded, the greatest smaller version than the current version
     * is used. If it can't be loaded, the smaller greatest version than the
     * current version is used. It it can't be loaded, a package without
     * version is used. If it can't be loaded, nothing is loaded.
     */
    void load();

    /**
     * Loads a specific ConfigurationParameterMap in mConfiguration for the
     * Task based on the PackageId.
     * When loading undo tasks, the configuration loaded is that from the Task
     * they revert its changes, instead of the configuration of the Undo Task
     * itself.
     *
     * Loading the file may file due to various reasons: the file doesn't
     * exist, it can't be parsed, it doesn't follow the XML Schema of
     * ConfigurationParameters...
     *
     * @param packageId The PackageId used to select the file to load the
     *                  ConfigurationParameterMap from.
     * @return True if it was loaded, false otherwise.
     * @see ConfigurationPaths.getTaskFile(const string&, const PackageId&)
     */
    bool load(const lusi::package::PackageId& packageId);

    /**
     * Returns all the available versions of the Package of the Task.
     * The available versions are the direct child directories of the root
     * Package directory. The returned strings are the versions, not the
     * directory names, so the ending '/' is already removed.
     *
     * @return All the available versions of the Package of the Task.
     */
    std::vector<std::string> getPackageVersions();

    /**
     * Copy constructor disabled.
     */
    TaskConfiguration(const TaskConfiguration& task);

    /**
     * Assignment disabled.
     */
    TaskConfiguration& operator=(const TaskConfiguration& task);

};

}
}

#endif
