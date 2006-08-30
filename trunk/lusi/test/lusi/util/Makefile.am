INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/util

noinst_HEADERS = UtilTestSuite.h ProcessTest.h ProcessTestImplementation.h \
	ProcessObserverTestImplementation.h ProcessLinuxTest.h ProcessRunnerTest.h LocalUrlTest.h \
	ProcessLinuxCommunicationTest.h ProcessLinuxCommunicationTestImplementation.h \
	PipeProcessLinuxCommunicationTest.h BaseProcessLinuxCommunicationTest.h PtyProcessLinuxCommunicationTest.h

if CPPUNIT
check_LTLIBRARIES = libutiltest.la

libutiltest_la_SOURCES = UtilTestSuite.cpp ProcessTest.cpp \
	ProcessTestImplementation.cpp ProcessObserverTestImplementation.cpp ProcessLinuxTest.cpp \
	ProcessRunnerTest.cpp LocalUrlTest.cpp ProcessLinuxCommunicationTest.cpp \
	ProcessLinuxCommunicationTestImplementation.cpp PipeProcessLinuxCommunicationTest.cpp \
	BaseProcessLinuxCommunicationTest.cpp PtyProcessLinuxCommunicationTest.cpp
libutiltest_la_LDFLAGS = -all-static
endif
