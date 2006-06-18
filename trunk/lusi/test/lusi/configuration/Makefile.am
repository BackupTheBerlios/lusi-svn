INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/configuration

noinst_HEADERS = ConfigurationTestSuite.h

if CPPUNIT
check_LTLIBRARIES = libconfigurationtest.la

libconfigurationtest_la_LDFLAGS = -all-static
libconfigurationtest_la_SOURCES = ConfigurationTestSuite.cpp
endif
