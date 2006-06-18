INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/configuration
liblusiinclude_HEADERS = ConfigurationParameter.h ConfigurationParameterAnd.h \
	ConfigurationParameterComposed.h ConfigurationParameterOr.h ConfigurationParameterPriority.h \
	ConfigurationParameterSimple.h ConfigurationParametersSet.h

noinst_LTLIBRARIES = libconfiguration.la
libconfiguration_la_SOURCES = ConfigurationParametersSet.cpp \
	ConfigurationParameter.cpp
