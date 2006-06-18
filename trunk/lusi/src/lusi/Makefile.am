SUBDIRS = configuration package task
INCLUDES = -I$(top_srcdir)/src

liblusi_LTLIBRARIES = liblusi.la
liblusidir = $(libdir)/lusi

liblusiincludedir = $(includedir)/lusi
liblusiinclude_HEADERS = Module.h Installer.h Uninstaller.h

liblusi_la_SOURCES = Installer.cpp Uninstaller.cpp
liblusi_la_LIBADD = $(top_builddir)/src/lusi/configuration/libconfiguration.la \
	$(top_builddir)/src/lusi/package/libpackage.la $(top_builddir)/src/lusi/task/libtask.la
