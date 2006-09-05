INCLUDES = -I$(top_srcdir)/src -I$(top_srcdir)/src/lusi/configuration

noinst_HEADERS = ConfigurationTestSuite.h ConfigurationParameterTest.h \
	ConfigurationParameterTestImplementation.h ConfigurationParameterSimpleTest.h \
	ConfigurationParameterComposedTestImplementation.h ConfigurationParameterComposedTest.h ConfigurationParameterAndTest.h \
	ConfigurationParameterOrTest.h

if CPPUNIT
check_LTLIBRARIES = libconfigurationtest.la

libconfigurationtest_la_LDFLAGS = -all-static
libconfigurationtest_la_SOURCES = ConfigurationTestSuite.cpp \
	ConfigurationParameterTest.cpp ConfigurationParameterTestImplementation.cpp \
	ConfigurationParameterSimpleTest.cpp ConfigurationParameterComposedTestImplementation.cpp \
	ConfigurationParameterComposedTest.cpp ConfigurationParameterAndTest.cpp ConfigurationParameterOrTest.cpp
endif
