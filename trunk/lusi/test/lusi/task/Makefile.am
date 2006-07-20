SUBDIRS = helper
INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/task

noinst_HEADERS = TaskManagerTest.h TaskTestSuite.h TaskTestImplementation.h \
	TaskLoggerObserverTestImplementation.h TaskLoggerTest.h TaskProgressObserverTestImplementation.h \
	TaskProgressTest.h

if CPPUNIT
check_LTLIBRARIES = libtasktest.la

libtasktest_la_SOURCES = TaskManagerTest.cpp TaskTestSuite.cpp \
	TaskTestImplementation.cpp TaskLoggerObserverTestImplementation.cpp TaskLoggerTest.cpp \
	TaskProgressObserverTestImplementation.cpp TaskProgressTest.cpp
libtasktest_la_LDFLAGS = -all-static
libtasktest_la_LIBADD = $(top_builddir)/test/lusi/task/helper/libhelpertest.la
endif
