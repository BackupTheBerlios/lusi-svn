INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/util

noinst_HEADERS = UtilTestSuite.h ProcessTest.h ProcessTestImplementation.h \
		ProcessObserverTestImplementation.h ProcessLinuxTest.h ProcessRunnerTest.h

if CPPUNIT
check_LTLIBRARIES = libutiltest.la

libutiltest_la_SOURCES = UtilTestSuite.cpp ProcessTest.cpp \
		ProcessTestImplementation.cpp ProcessObserverTestImplementation.cpp ProcessLinuxTest.cpp \
		ProcessRunnerTest.cpp
libutiltest_la_LDFLAGS = -all-static
endif
