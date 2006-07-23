INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/package/status

noinst_HEADERS = BuiltPackageStatusTest.h ConfiguredPackageStatusTest.h\
	InstalledPackageStatusTest.h PackageStatusTestSuite.h\
	PackedPackageStatusTest.h UnknownPackageStatusTest.h\
	UnpackedPackageStatusTest.h PackageStatusTestImplementation.h

if CPPUNIT
check_LTLIBRARIES = libstatustest.la

libstatustest_la_SOURCES = BuiltPackageStatusTest.cpp\
	ConfiguredPackageStatusTest.cpp InstalledPackageStatusTest.cpp\
	PackageStatusTestSuite.cpp PackedPackageStatusTest.cpp\
	UnknownPackageStatusTest.cpp UnpackedPackageStatusTest.cpp\
	PackageStatusTestImplementation.cpp
libstatustest_la_LDFLAGS = -all-static
endif
