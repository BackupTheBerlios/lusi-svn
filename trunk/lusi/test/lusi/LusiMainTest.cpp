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

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

#include "configuration/ConfigurationTestSuite.h"
#include "package/PackageTestSuite.h"
#include "task/TaskTestSuite.h"

using lusi::configuration::ConfigurationTestSuite;
using lusi::package::PackageTestSuite;
using lusi::task::TaskTestSuite;

/**
 * Executes a TextTestRunner with all the tests for LUSI.
 * It adds the TestSuites created in direct child directories, which contain
 * also the tests for their subdirectories recursively.
 *
 * If any test fails, main returns 1.
 */
int main(int argc, char **argv) {
    CppUnit::TextTestRunner runner;

    runner.addTest(new ConfigurationTestSuite());
    runner.addTest(new PackageTestSuite());
    runner.addTest(new TaskTestSuite());

    bool wasSuccessful = runner.run("", false);
    return wasSuccessful? 0 : 1;
}
