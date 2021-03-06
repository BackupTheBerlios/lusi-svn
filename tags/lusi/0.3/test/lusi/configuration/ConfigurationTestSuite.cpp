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

#include "ConfigurationTestSuite.h"
#include "ConfigurationLoaderTest.h"
#include "ConfigurationMergerTest.h"
#include "ConfigurationParameterTest.h"
#include "ConfigurationParameterBoolTest.h"
#include "ConfigurationParameterDoubleTest.h"
#include "ConfigurationParameterIntTest.h"
#include "ConfigurationParameterLocalUrlTest.h"
#include "ConfigurationParameterMapTest.h"
#include "ConfigurationParameterSimpleTest.h"
#include "ConfigurationParameterStringTest.h"
#include "ConfigurationPathsTest.h"
#include "ConfigurationSaverTest.h"
#include "ConfigurationXmlDeserializerTest.h"
#include "ConfigurationXmlSerializerTest.h"

using namespace lusi::configuration;

//public:

ConfigurationTestSuite::ConfigurationTestSuite() {
    //Own namespace Tests
    addTest(ConfigurationLoaderTest::suite());
    addTest(ConfigurationMergerTest::suite());
    addTest(ConfigurationParameterTest::suite());
    addTest(ConfigurationParameterBoolTest::suite());
    addTest(ConfigurationParameterDoubleTest::suite());
    addTest(ConfigurationParameterIntTest::suite());
    addTest(ConfigurationParameterLocalUrlTest::suite());
    addTest(ConfigurationParameterMapTest::suite());
    addTest(ConfigurationParameterSimpleTest::suite());
    addTest(ConfigurationParameterStringTest::suite());
    addTest(ConfigurationPathsTest::suite());
    addTest(ConfigurationSaverTest::suite());
    addTest(ConfigurationXmlDeserializerTest::suite());
    addTest(ConfigurationXmlSerializerTest::suite());

    //Direct child namespaces TestSuites
}
