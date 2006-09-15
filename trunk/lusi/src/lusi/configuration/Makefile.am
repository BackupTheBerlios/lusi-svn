INCLUDES = -I$(top_srcdir)/src

liblusiincludedir = $(includedir)/lusi/configuration
liblusiinclude_HEADERS = ConfigurationParameter.h ConfigurationParameterAnd.h \
	ConfigurationParameterComposed.h ConfigurationParameterOr.h ConfigurationParameterSimple.h \
	ConfigurationParametersSet.h ConfigurationParameterVisitor.h

noinst_LTLIBRARIES = libconfiguration.la
libconfiguration_la_SOURCES = ConfigurationParametersSet.cpp \
	ConfigurationParameter.cpp ConfigurationParameterAnd.cpp ConfigurationParameterComposed.cpp \
	ConfigurationParameterOr.cpp ConfigurationParameterSimple.cpp
