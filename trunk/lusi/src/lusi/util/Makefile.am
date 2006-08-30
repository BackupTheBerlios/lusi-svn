INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/util
liblusiinclude_HEADERS = Process.h ProcessObserver.h ProcessException.h \
	ProcessRunner.h LocalUrl.h

noinst_HEADERS = ProcessLinux.h ProcessLinuxCommunication.h \
	PipeProcessLinuxCommunication.h PtyProcessLinuxCommunication.h OpenCommunicationChannelsException.h

noinst_LTLIBRARIES = libutil.la
libutil_la_SOURCES = Process.cpp ProcessLinux.cpp ProcessException.cpp \
	ProcessRunner.cpp LocalUrl.cpp ProcessLinuxCommunication.cpp \
	PipeProcessLinuxCommunication.cpp PtyProcessLinuxCommunication.cpp OpenCommunicationChannelsException.cpp