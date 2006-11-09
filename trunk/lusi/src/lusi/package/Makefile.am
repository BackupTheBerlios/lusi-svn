SUBDIRS = status
INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/package
liblusiinclude_HEADERS = LocalFileResource.h Package.h PackageId.h Profile.h \
	ProfileManager.h Resource.h ResourceMap.h PackageManager.h

noinst_LTLIBRARIES = libpackage.la
libpackage_la_SOURCES = LocalFileResource.cpp Package.cpp PackageId.cpp \
	Profile.cpp ProfileManager.cpp Resource.cpp ResourceMap.cpp PackageManager.cpp
libpackage_la_LIBADD = $(top_builddir)/src/lusi/package/status/libstatus.la
