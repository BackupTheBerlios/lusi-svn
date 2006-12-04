AC_INIT(configure.ac)

AC_CONFIG_AUX_DIR(config)
AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE(lusi, 0.3)

AC_LANG_CPLUSPLUS
AC_PROG_CXX
AM_PROG_LIBTOOL

dnl
dnl Checks for gettext
dnl
AM_GNU_GETTEXT([external])

dnl
dnl Checks for cppunit
dnl
AM_PATH_CPPUNIT(1.8.0,
                AM_CONDITIONAL(CPPUNIT, test "x$no_cppunit" = x)
                AC_DEFINE_UNQUOTED(HAVE_LIBCPPUNIT, 1, [Define if you have libcppunit])
                AC_SUBST(CPPUNIT_LIBS),
                AM_CONDITIONAL(CPPUNIT, test "x$no_cppunit" = x)
                AC_SUBST(CPPUNIT_LIBS)
)

dnl
dnl Checks for libxml2
dnl
PKG_CHECK_MODULES(LIBXML, libxml-2.0)
AC_SUBST(LIBXML_CFLAGS)
AC_SUBST(LIBXML_LIBS)

AC_OUTPUT(Makefile
          po/Makefile.in
          src/Makefile
          src/lusi/Makefile
          src/lusi/configuration/Makefile
          src/lusi/package/Makefile
          src/lusi/package/status/Makefile
          src/lusi/task/Makefile
          src/lusi/task/helper/Makefile
          src/lusi/util/Makefile
          test/Makefile
          test/lusi/Makefile
          test/lusi/configuration/Makefile
          test/lusi/package/Makefile
          test/lusi/package/status/Makefile
          test/lusi/task/Makefile
          test/lusi/task/helper/Makefile
          test/lusi/util/Makefile
          lusi.pc
)
