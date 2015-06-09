#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.65)
AC_INIT([Cahd], [0.0.1], [elbert@t-matix.com], [cahd])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C_O

AM_PATH_GLIB_2_0([2.20.0], [
	 GUI_CFLAGS="$GUI_CFLAGS $GLIB_CFLAGS"
	 GUI_LIBS="$GUI_LIBS $GLIB_LIBS"
	], [AC_MSG_ERROR([You need Glib >= 2.20.0 to build $PACKAGE])])

PKG_CHECK_MODULES(gthread, [gthread-2.0],,
	[AC_MSG_ERROR([You need ghread-2.0 to build $PACKAGE])])
GUI_CFLAGS="$GUI_CFLAGS $gthread_CFLAGS"
GUI_LIBS="$GUI_LIBS $gthread_LIBS"

AM_PATH_GTK_3_0([3.4.0], [
	 GUI_CFLAGS="$GUI_CFLAGS $GTK_CFLAGS"
	 GUI_LIBS="$GUI_LIBS $GTK_LIBS"
	], [AC_MSG_ERROR([You need Gtk+ >= 3.4.0 to build $PACKAGE])])

PKG_CHECK_MODULES(gtksourceview, [gtksourceview-3.0 >= 3.4.0],,
	[AC_MSG_ERROR([You need gtksourceview3 >= 3.4.0 to build $PACKAGE])])
GUI_CFLAGS="$GUI_CFLAGS $gtksourceview_CFLAGS"
GUI_LIBS="$GUI_LIBS $gtksourceview_LIBS"

# Add explicit linking flags
GUI_LIBS="$GUI_LIBS -pthread -lm -lz -lrt"

# Checks for header files.
AC_CHECK_HEADERS([netdb.h stdlib.h string.h sys/socket.h sys/time.h unistd.h fcntl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

# Checks for library functions.
AC_CHECK_FUNCS([gethostbyname memset socket strstr])

AC_SUBST(GUI_LIBS)
AC_SUBST(GUI_CFLAGS)
AC_CONFIG_FILES([Makefile
		 src/Makefile
         tests/Makefile
		 ])
AC_OUTPUT

echo configure complete, now type \'make\'.
echo
