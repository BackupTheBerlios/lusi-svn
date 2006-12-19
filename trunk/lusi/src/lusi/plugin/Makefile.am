INCLUDES = -I$(top_srcdir)/src $(INCLTDL)

liblusiincludedir = $(includedir)/lusi/plugin
liblusiinclude_HEADERS = PluginLoader.h

noinst_LTLIBRARIES = libplugin.la
libplugin_la_SOURCES = PluginLoader.cpp

libplugin_la_LIBADD = $(LIBLTDL)

AM_CXXFLAGS = -DPLUGINDIR=\"$(libdir)/lusi/plugins\"
