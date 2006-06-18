SUBDIRS = helper
INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/task
liblusiinclude_HEADERS = BuildTask.h ConfigureTask.h ExtractTask.h \
	InstallTask.h LoggedEventType.h TaskConfiguration.h TaskConfigurationManager.h Task.h \
	TaskLogger.h TaskLoggerObserver.h TaskManager.h TaskProgress.h \
	TaskProgressObserver.h

noinst_LTLIBRARIES = libtask.la
libtask_la_SOURCES = BuildTask.cpp ConfigureTask.cpp ExtractTask.cpp\
	InstallTask.cpp TaskConfiguration.cpp TaskConfigurationManager.cpp\
	Task.cpp TaskLogger.cpp TaskManager.cpp TaskProgress.cpp
libtask_la_LIBADD = $(top_builddir)/src/lusi/task/helper/libhelper.la
