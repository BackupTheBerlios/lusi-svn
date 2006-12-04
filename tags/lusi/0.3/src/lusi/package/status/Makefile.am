INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/package/status
liblusiinclude_HEADERS = BuiltPackageStatus.h ConfiguredPackageStatus.h \
	InstalledPackageStatus.h PackageStatus.h PackedPackageStatus.h UnknownPackageStatus.h \
	UnpackedPackageStatus.h

noinst_LTLIBRARIES = libstatus.la
libstatus_la_SOURCES = BuiltPackageStatus.cpp ConfiguredPackageStatus.cpp\
	InstalledPackageStatus.cpp PackedPackageStatus.cpp\
	UnknownPackageStatus.cpp UnpackedPackageStatus.cpp
