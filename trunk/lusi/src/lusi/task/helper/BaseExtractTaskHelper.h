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

#ifndef LUSI_TASK_HELPER_BASEEXTRACTTASKHELPER_H
#define LUSI_TASK_HELPER_BASEEXTRACTTASKHELPER_H

#include <lusi/task/helper/TaskHelperUsingProcess.h>

#include <lusi/util/SmartPtr.h>

namespace lusi {
namespace configuration {
class ConfigurationParameterLocalUrl;
class ConfigurationParameterMap;
}
}

namespace lusi {
namespace package {
class LocalFileResource;
}
}

namespace lusi {
namespace task {
namespace helper {

/**
 * @class BaseExtractTaskHelper BaseExtractTaskHelper.h \
 * lusi/task/helper/BaseExtractTaskHelper.h
 *
 * Base TaskHelper for ExtractTask.
 * This class provides a default behaviour for TaskHelpers that extract the
 * contents of a packed Package. Real extracting is made by the Process created
 * when executing the TaskHelper.
 *
 * Derived classes must define hasValidResourceMap() method, as this
 * method depends on the specific extracter command used.
 * Moreover, derived classes must call fileExtracted(string) each time a file
 * is extracted.
 *
 * The configuration contains only the path where the package must be
 * extracted, as an optional parameter. This parameter is stored in
 * mExtractionDirectory. If a derived class needs a different configuration,
 * initConfigurationParameterMap() can be redefined.
 * getInvalidConfiguration() only checks for incomplete parameters. This
 * behaviour can also be redefined if needed.
 *
 * The Progress is updated by fileExtracted(string), provided a total number of
 * files to be extracted was set by derived class. Usually, it will be set in
 * getProcess() method, although isn't mandatory. If the total number of files
 * can't be known, the Progress only will be updated when extraction starts and
 * when it finishes.
 *
 * Also, getProcess() method must set all the needed arguments in the Process
 * to be executed to do the extraction.
 */
class BaseExtractTaskHelper: public TaskHelperUsingProcess {
public:

    /**
     * Destroys this BaseExtractTaskHelper.
     */
    virtual ~BaseExtractTaskHelper();

    /**
     * Extracts the package.
     * The generic implementation for ExtractTasks is execute parent method,
     * and then remove the packed file from the ResourceMap.
     *
     * Derived classes can, however, redefine this method if this default
     * implementation doesn't suit their needs.
     *
     * @throws ExecuteTaskHelperException If a problem happened when executing
     *                                    this TaskHelper.
     * @throws InvalidConfigurationException If the parameters are incomplete or
     *                                       invalid.
     */
    virtual void execute() throw (ExecuteTaskHelperException,
                            lusi::configuration::InvalidConfigurationException);

    /**
     * Inits the configuration parameters for this TaskHelper.
     * The configuration contains only the path where the package must be
     * extracted, as an optional parameter, with "extractionDirectory" id.
     * The default parameter contains the parent directory of the file to
     * extract. This parameter is stored in mExtractionDirectory.
     */
    virtual void initConfigurationParameterMap();

protected:

    /**
     * The packaged file to be unpacked.
     */
    lusi::util::SmartPtr<lusi::package::LocalFileResource> mFileToUnpack;

    /**
     * The directory where the file will be extracted.
     * If the configuration wasn't initialized yet, is is null.
     */
    lusi::configuration::ConfigurationParameterLocalUrl* mExtractionDirectory;



    /**
     * Creates a new BaseExtractTaskHelper.
     * The mFileToUnpack is got from the ResourceMap of the Package. The only
     * LocalFileResource in the ResourceMap is used. If the ResourceMap doesn't
     * contain any LocalFileResource, or more than one, a new LocalFileResource
     * is created with an empty id.
     *
     * @param name The name of the BaseExtractTaskHelper.
     * @param task The Task to help.
     */
    BaseExtractTaskHelper(const std::string& name, lusi::task::Task* task);

    /**
     * Returns the number of files to be extracted.
     * If the number of files to be extracted is unknown, 0 is returned.
     *
     * @return The number of files to be extracted.
     */
    int getNumberOfFilesToExtract() {
        return mNumberOfFilesToExtract;
    }

    /**
     * Sets the total number of files to be extracted.
     *
     * @param numberOfFilesToExtract The total number of files to extract.
     */
    void setNumberOfFilesToExtract(int numberOfFilesToExtract) {
        mNumberOfFilesToExtract = numberOfFilesToExtract;
    }

    /**
     * Notifies the extraction progress and adds a new Resource with the file to
     * the ResourceMap.
     * The progress is notified only if the number of files to be extracted was
     * set.
     * This method must be called by child classes whenever a new file is
     * extracted. The fileName must be the absolute path to the file.
     *
     * @param fileName The absolute path to the extracted file.
     */
    void fileExtracted(const std::string& fileName);

private:

    /**
     * The total number of files to extract.
     */
    int mNumberOfFilesToExtract;

    /**
     * The number of files currently extracted.
     */
    int mNumberOfFilesExtracted;



    /**
     * Copy constructor disabled.
     */
    BaseExtractTaskHelper(const BaseExtractTaskHelper& baseExtractTaskHelper);

    /**
     * Assignment disabled.
     */
    BaseExtractTaskHelper& operator=(
            const BaseExtractTaskHelper& baseExtractTaskHelper);

};

}
}
}

#endif
