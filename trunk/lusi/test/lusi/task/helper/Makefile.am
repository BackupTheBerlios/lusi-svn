INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/task/helper

noinst_HEADERS = TaskHelperTestSuite.h

if CPPUNIT
check_LTLIBRARIES = libhelpertest.la

libhelpertest_la_SOURCES = TaskHelperTestSuite.cpp
libhelpertest_la_LDFLAGS = -all-static
endif
