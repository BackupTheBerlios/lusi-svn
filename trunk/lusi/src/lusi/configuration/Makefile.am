INCLUDES = -I$(top_srcdir)/src $(LIBXML_CFLAGS)

liblusiincludedir = $(includedir)/lusi/configuration
liblusiinclude_HEADERS = ConfigurationParameter.h ConfigurationParameterSimple.h \
	ConfigurationParameterMap.h ConfigurationParameterVisitor.h InvalidConfigurationException.h \
	ConfigurationParameterBool.h ConfigurationParameterDouble.h ConfigurationParameterInt.h \
	ConfigurationParameterLocalUrl.h ConfigurationParameterString.h ConfigurationXmlSerializer.h \
	ConfigurationXmlDeserializer.h ConfigurationSaver.h ConfigurationLoader.h \
	PersistenceException.h ConfigurationPaths.h ConfigurationMerger.h \
	ConfigurationCloner.h

noinst_LTLIBRARIES = libconfiguration.la
libconfiguration_la_SOURCES = ConfigurationParameter.cpp \
	ConfigurationParameterMap.cpp InvalidConfigurationException.cpp \
	ConfigurationParameterBool.cpp ConfigurationParameterDouble.cpp ConfigurationParameterInt.cpp \
	ConfigurationParameterLocalUrl.cpp ConfigurationParameterString.cpp ConfigurationXmlSerializer.cpp \
	ConfigurationXmlDeserializer.cpp ConfigurationSaver.cpp ConfigurationLoader.cpp \
	PersistenceException.cpp ConfigurationPaths.cpp ConfigurationMerger.cpp \
	ConfigurationCloner.cpp
libconfiguration_la_LIBADD = $(LIBXML_LIBS)
