dnl  ----------------
dnl | initialization |--------------------------------------------------------
dnl  ----------------

AC_INIT(uba,0.0.1,mailto:herzi@gnome-de.org)
AC_CONFIG_SRCDIR(configure.ac)
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME,AC_PACKAGE_VERSION)

dnl  -----------------
dnl | build framework |-------------------------------------------------------
dnl  -----------------

CXX=no
F77=no
AC_PROG_LIBTOOL

dnl  ----------------------
dnl | package dependencies |--------------------------------------------------
dnl  ----------------------

PKG_CHECK_MODULES(UBA,[gtk+-2.0])

dnl  -------------------
dnl | testing framework |-----------------------------------------------------
dnl  -------------------

PKG_CHECK_MODULES(CHECK,[check >= 0.9.4],:,[
		  ifdef([AM_PATH_CHECK],[AM_PATH_CHECK],[AC_MSG_RESULT([no, testing is disabled])])
		  ])

AM_CONDITIONAL([HAVE_CHECK],[test "x$CHECK_CFLAGS" != "x" -o "x$CHECK_LIBS" != "x"])

dnl  ---------------------
dnl | write configuration |---------------------------------------------------
dnl  ---------------------

AC_CONFIG_FILES([
	Makefile
	tests/Makefile
	uba/Makefile
])

AC_OUTPUT
