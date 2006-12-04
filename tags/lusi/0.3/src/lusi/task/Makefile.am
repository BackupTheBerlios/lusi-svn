SUBDIRS = helper
INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/task
liblusiinclude_HEADERS = LoggedEventType.h TaskConfiguration.h \
	Task.h TaskLogger.h TaskLoggerObserver.h TaskManager.h TaskProgress.h \
	TaskProgressObserver.h ExecuteTaskException.h NoTaskAvailableException.h

noinst_LTLIBRARIES = libtask.la
libtask_la_SOURCES = TaskConfiguration.cpp \
	Task.cpp TaskLogger.cpp TaskManager.cpp TaskProgress.cpp \
	ExecuteTaskException.cpp NoTaskAvailableException.cpp
libtask_la_LIBADD = $(top_builddir)/src/lusi/task/helper/libhelper.la
