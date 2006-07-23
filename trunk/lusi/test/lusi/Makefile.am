SUBDIRS = configuration package task util
INCLUDES = -I$(top_srcdir)/src/lusi

# Rules for the test code (use `make check` to execute)
if CPPUNIT
TESTS = lusitest

check_PROGRAMS = lusitest

lusitest_SOURCES = LusiMainTest.cpp
lusitest_LDFLAGS = -no-install $(CPPUNIT_LIBS)
lusitest_LDADD = \
	$(top_builddir)/test/lusi/configuration/libconfigurationtest.la $(top_builddir)/test/lusi/package/libpackagetest.la \
	$(top_builddir)/test/lusi/task/libtasktest.la $(top_builddir)/test/lusi/util/libutiltest.la \
	$(top_builddir)/src/lusi/liblusi.la
endif
