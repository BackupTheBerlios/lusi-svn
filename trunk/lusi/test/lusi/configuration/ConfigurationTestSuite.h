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

#ifndef LUSI_CONFIGURATION_CONFIGURATIONTESTSUITE_H
#define LUSI_CONFIGURATION_CONFIGURATIONTESTSUITE_H

#include <cppunit/TestSuite.h>

namespace lusi {
namespace configuration {

/**
 * TestSuite for namespace lusi::configuration
 * When a new Test is created in this namespace, it must be added to the
 * constructor of this class.
 *
 * It's used from parent namespaces to get all the tests in
 * lusi::configuration namespace.
 */
class ConfigurationTestSuite: public CppUnit::TestSuite {
public:

    /**
     * Adds all the Tests from its same namespace and all TestSuites from
     * direct child namespaces.
     */
    ConfigurationTestSuite();

};

}
}

#endif
