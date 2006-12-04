INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/task/helper

noinst_HEADERS = TaskHelperTestSuite.h TaskHelperManagerTest.h \
	TaskHelperTestImplementation.h BaseExtractTaskHelperTest.h BaseExtractTaskHelperTestImplementation.h \
	TarExtractTaskHelperTest.h TaskHelperUsingProcessTest.h TaskHelperUsingProcessTestImplementation.h \
	MakeBuildTaskHelperTest.h MakeInstallTaskHelperTest.h ConfigureConfigureTaskHelperTest.h \
	TaskHelperTest.h TaskHelperUsingMakeTest.h TaskHelperUsingMakeTestImplementation.h

if CPPUNIT
check_LTLIBRARIES = libhelpertest.la

libhelpertest_la_SOURCES = TaskHelperTestSuite.cpp TaskHelperManagerTest.cpp \
	TaskHelperTestImplementation.cpp BaseExtractTaskHelperTest.cpp \
	BaseExtractTaskHelperTestImplementation.cpp TarExtractTaskHelperTest.cpp TaskHelperUsingProcessTest.cpp \
	TaskHelperUsingProcessTestImplementation.cpp MakeBuildTaskHelperTest.cpp MakeInstallTaskHelperTest.cpp \
	ConfigureConfigureTaskHelperTest.cpp TaskHelperTest.cpp TaskHelperUsingMakeTest.cpp \
	TaskHelperUsingMakeTestImplementation.cpp
libhelpertest_la_LDFLAGS = -all-static
endif
