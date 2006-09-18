INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/task/helper
liblusiinclude_HEADERS = ConfigureConfigureTaskHelper.h BaseExtractTaskHelper.h \
	MakeBuildTaskHelper.h MakeInstallTaskHelper.h TarExtractTaskHelper.h TaskHelper.h \
	TaskHelperManager.h TaskHelperUsingMake.h TaskHelperUsingProcess.h \
	ExecuteTaskHelperException.h

noinst_LTLIBRARIES = libhelper.la
libhelper_la_SOURCES = ConfigureConfigureTaskHelper.cpp \
	BaseExtractTaskHelper.cpp MakeBuildTaskHelper.cpp MakeInstallTaskHelper.cpp \
	TarExtractTaskHelper.cpp TaskHelper.cpp TaskHelperManager.cpp TaskHelperUsingProcess.cpp \
	TaskHelperUsingMake.cpp ExecuteTaskHelperException.cpp
