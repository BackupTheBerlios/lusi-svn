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

#include "UtilTestSuite.h"
#include "LocalUrlTest.h"
#include "SmartPtrTest.h"
#include "IdSmartPtrMapTest.h"
#include "ProcessTest.h"
#include "ProcessLinuxCommunicationTest.h"
#include "PipeProcessLinuxCommunicationTest.h"
#include "PtyProcessLinuxCommunicationTest.h"
#include "ProcessLinuxTest.h"
#include "ProcessRunnerTest.h"
#include "SuProcessTest.h"
#include "SuProcessLinuxTest.h"
#include "SuProcessLinuxConverserTest.h"
#include "GroupTest.h"
#include "UserTest.h"
#include "LocalFileTest.h"

using namespace lusi::util;

//public:

UtilTestSuite::UtilTestSuite() {
    //Own namespace Tests
    addTest(LocalUrlTest::suite());
    addTest(SmartPtrTest::suite());
    addTest(IdSmartPtrMapTest::suite());
    addTest(ProcessTest::suite());
    addTest(ProcessLinuxCommunicationTest::suite());
    addTest(PipeProcessLinuxCommunicationTest::suite());
    addTest(PtyProcessLinuxCommunicationTest::suite());
    addTest(ProcessLinuxTest::suite());
    addTest(ProcessRunnerTest::suite());
    addTest(SuProcessTest::suite());
    addTest(SuProcessLinuxTest::suite());
    addTest(SuProcessLinuxConverserTest::suite());
    addTest(GroupTest::suite());
    addTest(UserTest::suite());
    addTest(LocalFileTest::suite());

    //Direct child namespaces TestSuites
}
