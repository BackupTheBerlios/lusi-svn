INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/configuration
liblusiinclude_HEADERS = ConfigurationParameter.h ConfigurationParameterSimple.h \
	ConfigurationParameterMap.h ConfigurationParameterVisitor.h InvalidConfigurationException.h \
	ConfigurationParameterBool.h ConfigurationParameterDouble.h ConfigurationParameterInt.h \
	ConfigurationParameterLocalUrl.h ConfigurationParameterString.h

noinst_LTLIBRARIES = libconfiguration.la
libconfiguration_la_SOURCES = ConfigurationParameter.cpp \
	ConfigurationParameterMap.cpp InvalidConfigurationException.cpp \
	ConfigurationParameterBool.cpp ConfigurationParameterDouble.cpp ConfigurationParameterInt.cpp \
	ConfigurationParameterLocalUrl.cpp ConfigurationParameterString.cpp
