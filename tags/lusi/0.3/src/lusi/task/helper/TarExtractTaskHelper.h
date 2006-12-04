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

#ifndef LUSI_TASK_HELPER_TAREXTRACTTASKHELPER_H
#define LUSI_TASK_HELPER_TAREXTRACTTASKHELPER_H

#include <string>

#include <lusi/task/helper/BaseExtractTaskHelper.h>

namespace lusi {
namespace task {
namespace helper {

/**
 * Returns a new TarExtractTaskHelper.
 * Used to register TarExtractTaskHelper with Task names.
 *
 * @param task The Task to help.
 * @return The new TarExtractTaskHelper created.
 * @see TaskHelperManager
 */
TaskHelper* createTarExtractTaskHelper(lusi::task::Task* task);

/**
 * @class TarExtractTaskHelper TarExtractTaskHelper.h \
 * lusi/task/helper/TarExtractTaskHelper.h
 *
 * ExtractTaskHelper for tar command.
 * This ExtractTask implementation adds support for tar command. This command
 * extracts the contents of packed files supported by it.
 *
 * Resources that can be used with TarExtractTaskHelper are those with a packed
 * file with a format supported by tar, containing the Package.
 *
 * No specific configuration is needed, only the generic for
 * BaseExtractTaskHelpers.
 */
class TarExtractTaskHelper: public BaseExtractTaskHelper {
public:

    /**
     * Creates a new TarExtractTaskHelper.
     *
     * @param task The Task to help.
     */
    TarExtractTaskHelper(lusi::task::Task* task);

    /**
     * Destroys this TarExtractTaskHelper.
     */
    virtual ~TarExtractTaskHelper();

    /**
     * Returns true if the resources contain a packed file with the name of
     * the Package in a format supported by "tar" command (those are tar, gzip
     * and bzip2).
     *
     * @return True if the resources contain the packed Package.
     */
    virtual bool hasValidResources();

    /**
     * Called when new data is received in stdout.
     * The output is processed to notify the base class the name of each file
     * extracted.
     *
     * @param process A pointer to the process that received the data.
     * @param data The data received.
     * @see fileExtracted(std::string)
     */
    virtual void receivedStdout(lusi::util::Process* process,
                                const std::string& data);

protected:

    /**
     * Creates a new Process with PipeCommunication and sets the number of
     * files to be extracted and the arguments needed to start the process.
     * The directory to extract the files to is got from the configuration. If
     * it doesn't exist yet, it is created (with all its needed parents). If the
     * directory wasn't explicitly set, the parent directory of the file to
     * extract is used.
     * If the number of files to extract is greater than 0, the TaskProgress is
     * set to extended.
     *
     * @return The Process to set its arguments.
     * @see calculateNumberOfFilesToExtract()
     */
    virtual lusi::util::Process* getProcess();

private:

    /**
     * The format to use when invoking the tar command.
     * This format includes also the leading hyphen.
     */
    std::string mTarFormat;

    /**
     * Stores the received data in stdout.
     * The data stored is only temporal and it's removed when a complete file
     * name is available.
     * This attribute is used only in receivedStdout(Process*, const string&).
     *
     * @see receivedStdout(Process*, const string&)
     */
    std::string mReceivedData;



    /**
     * Returns the format to be used when invoking the tar command.
     * The format includes also the leading hyphen. It uses the extension of the
     * file to unpack to infer the format used when the file was compressed,
     * and use that same format with tar when extracting it.
     *
     * @return The format to be used when invoking the tar command.
     */
    std::string inferTarFormat();

    /**
     * Returns the total number of files to be extracted.
     * It lists all the files in the file to be extracted and then counts the
     * number of lines outputted.
     * If some error happens while calculating the number of files to extract,
     * it returns 0.
     *
     * @return The total number of files to be extracted, or 0 if there was an
     *         error.
     */
    int calculateNumberOfFilesToExtract();

    /**
     * Copy constructor disabled.
     */
    TarExtractTaskHelper(const TarExtractTaskHelper& tarExtractTaskHelper);

    /**
     * Assignment disabled.
     */
    TarExtractTaskHelper& operator=(
            const TarExtractTaskHelper& tarExtractTaskHelper);

};

}
}
}

#endif
