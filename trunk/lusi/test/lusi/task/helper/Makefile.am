INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/task/helper

noinst_HEADERS = TaskHelperTestSuite.h TaskHelperManagerTest.h \
	TaskHelperTestImplementation.h

if CPPUNIT
check_LTLIBRARIES = libhelpertest.la

libhelpertest_la_SOURCES = TaskHelperTestSuite.cpp TaskHelperManagerTest.cpp \
	TaskHelperTestImplementation.cpp
libhelpertest_la_LDFLAGS = -all-static
endif
