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

#ifndef LUSI_TASK_HELPER_EXTRACTTASKHELPER_H
#define LUSI_TASK_HELPER_EXTRACTTASKHELPER_H

#include <string>

#include <lusi/task/helper/TaskHelper.h>

namespace lusi {
namespace configuration {
class ConfigurationParametersSet;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * @class ExtractTaskHelper ExtractTaskHelper.h \
 * lusi/task/helper/ExtractTaskHelper.h
 *
 * Base TaskHelper for ExtractTask.
 * All the TaskHelpers which provide an implementation for ExtractTask must
 * inherit from this class.
 *
 * This class provides a default behaviour for TaskHelpers that extract the
 * contents of a packed Package. Real extracting is left to derived classes
 * in method extract(string). Reverting the changes is implemented in revert()
 * (if derived classes adjust the behaviour of extract(string) to the
 * documentation), simply removing the extracted directory. However, if
 * execute() and revert() methods can be redefined if this behaviour doesn't
 * suit the needs of the derived class.
 *
 * Derived classes must define isValidResourceMap(ResourceMap) method, as this
 * method depends on the specific extracter command used. checkConfiguration()
 * returns a configuration that contains only the path where the package must
 * be extracted, as an optional parameter. It can also be redefined if the
 * derived class needs it.
 */
class ExtractTaskHelper: public TaskHelper {
public:

    /**
     * Creates a new ExtractTaskHelper.
     */
    ExtractTaskHelper();

    /**
     * Destroys this ExtractTaskHelper.
     */
    virtual ~ExtractTaskHelper();

    /**
     * Returns the generic configuration needed by ExtractTaskHelpers.
     * The default configuration contains only the path where the package must
     * be extracted, as an optional parameter.
     *
     * @return Returns the Configuration needed by this TaskHelper.
     */
    virtual lusi::configuration::ConfigurationParametersSet
                                            checkConfiguration();
    /**
     * Extracts the package.
     * The generic implementation for ExtractTasks is invoke the
     * extract(string) method, which extracts the package using the Resources
     * in the ResourceMap.
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @see extract(Resource, string)
     */
    virtual void execute();

    /**
     * Reverts the changes made when extracting the package.
     * The generic implementation for ExtractTasks is remove the base directory
     * created by execute().
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     */
    virtual void revert();

protected:

    /**
     * Extracts the Package to the specified path.
     * Extracts the Package using the ResourceMap of it. The specified path
     * includes the base directory for the package in it. If the packed Package
     * includes a base directory for all its files, the base directory in the
     * path should be ignored. If there's no base directory in the packed
     * Package, all the files should be extracted to the full specified path.
     *
     * The full name of the base directory of the Package once it was extracted
     * should be saved the TaskConfiguration, so it can be later retrieved to
     * be removed if needed.
     *
     * Must be implemented in derived classes.
     *
     * @param path The full path where the package should be extracted.
     */
    virtual void extract(std::string path) = 0;

private:

    /**
     * Copy constructor disabled.
     */
    ExtractTaskHelper(const ExtractTaskHelper& extractTaskHelper);

    /**
     * Assignment disabled.
     */
    ExtractTaskHelper& operator=(const ExtractTaskHelper& extractTaskHelper);

};

}
}
}

#endif
