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

#include "TaskHelperUsingProcess.h"
#include "../../util/Process.h"
#include "../../util/SmartPtr.h"

using std::string;

using lusi::configuration::InvalidConfigurationException;
using lusi::util::Process;
using lusi::util::ProcessException;
using lusi::util::SmartPtr;

using namespace lusi::task::helper;

//public:

TaskHelperUsingProcess::~TaskHelperUsingProcess() {
}

void TaskHelperUsingProcess::execute() throw (ExecuteTaskHelperException,
                                              InvalidConfigurationException) {
    TaskHelper::execute();

    SmartPtr<Process> process(getProcess());

    notifyTaskProgress(TaskProgress::UNSTARTED);

    notifyTaskLogger(getName() + ": executing process\n", message);
    if (!process->getWorkingDirectory().empty()) {
        notifyTaskLogger("cd " + process->getWorkingDirectory() + '\n',
                         message);
    }
    notifyTaskLogger(process->getArgumentsAsString() + '\n', message);

    process->attachObserver(this);

    try {
        process->start();
    } catch (ProcessException e) {
        throw ExecuteTaskHelperException(process->getArgumentsAsString() +
            string(" couldn't be executed: ") + e.what());
    }

    //Finished progress notification is sent when the process exits

    notifyTaskLogger(getName() + ": end process\n", message);

    checkProcessExecutionErrors(process);
}

void TaskHelperUsingProcess::receivedStdout(Process* process,
                                           const string& data) {
    notifyTaskLogger(data, message);
}

void TaskHelperUsingProcess::receivedStderr(Process* process,
                                           const string& data) {
    notifyTaskLogger(data, error);
}

void TaskHelperUsingProcess::processExited(Process* process) {
    notifyTaskProgress(TaskProgress::FINISHED);
}

//protected:

TaskHelperUsingProcess::TaskHelperUsingProcess(const string& name, Task* task):
                            TaskHelper(name, task) {
}

void TaskHelperUsingProcess::checkProcessExecutionErrors(
                SmartPtr<Process> process) throw (ExecuteTaskHelperException) {
    if (!process->normalExit() || process->getExitStatus() != 0) {
        throw ExecuteTaskHelperException("An error happened when executing " +
                                            process->getArgumentsAsString());
    }
}
