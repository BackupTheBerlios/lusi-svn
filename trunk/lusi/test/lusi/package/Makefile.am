SUBDIRS = status .
INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/package

noinst_HEADERS = PackageIdTest.h PackageTestSuite.h ProfileManagerTest.h

if CPPUNIT
check_LTLIBRARIES = libpackagetest.la

libpackagetest_la_SOURCES = PackageIdTest.cpp PackageTestSuite.cpp\
	ProfileManagerTest.cpp
libpackagetest_la_LDFLAGS = -all-static
libpackagetest_la_LIBADD = $(top_builddir)/test/lusi/package/status/libstatustest.la
endif
