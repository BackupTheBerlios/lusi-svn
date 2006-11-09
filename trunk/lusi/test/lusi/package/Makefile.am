SUBDIRS = status .
INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/package

noinst_HEADERS = PackageIdTest.h PackageTestSuite.h ProfileManagerTest.h \
	ResourceMapTest.h ResourceTestImplementation.h PackageTest.h ResourceTest.h \
	PackageManagerTest.h

if CPPUNIT
check_LTLIBRARIES = libpackagetest.la

libpackagetest_la_SOURCES = PackageIdTest.cpp PackageTestSuite.cpp \
	ProfileManagerTest.cpp ResourceMapTest.cpp ResourceTestImplementation.cpp PackageTest.cpp \
	ResourceTest.cpp PackageManagerTest.cpp
libpackagetest_la_LDFLAGS = -all-static
libpackagetest_la_LIBADD = $(top_builddir)/test/lusi/package/status/libstatustest.la
endif
