INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/util
liblusiinclude_HEADERS = Process.h ProcessObserver.h ProcessException.h \
	ProcessRunner.h LocalUrl.h SuProcess.h SuProcessException.h SmartPtr.h \
	NullPointerException.h IdSmartPtrMap.h LocalFile.h Group.h User.h i18n.h

noinst_HEADERS = ProcessLinux.h ProcessLinuxCommunication.h \
	PipeProcessLinuxCommunication.h PtyProcessLinuxCommunication.h OpenCommunicationChannelsException.h \
	SuProcessLinux.h SuProcessLinuxConverser.h

noinst_LTLIBRARIES = libutil.la
libutil_la_SOURCES = Process.cpp ProcessLinux.cpp ProcessException.cpp \
	ProcessRunner.cpp LocalUrl.cpp ProcessLinuxCommunication.cpp \
	PipeProcessLinuxCommunication.cpp PtyProcessLinuxCommunication.cpp OpenCommunicationChannelsException.cpp \
	SuProcess.cpp SuProcessLinux.cpp SuProcessException.cpp SuProcessLinuxConverser.cpp \
	NullPointerException.cpp LocalFile.cpp User.cpp Group.cpp i18n.cpp

AM_CXXFLAGS = -DLOCALEDIR=\"$(datadir)/locale\"
