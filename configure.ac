# Process this file with autoconf to produce a configure script

AC_PREREQ(2.65)
AC_INIT([Cahd], [0.0.1], [elbert@t-matix.nl], [cahd])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Check for programs
AC_PROG_CC
AM_PROG_CC_C_O
AC_PROG_INSTALL
AC_PROG_LIBTOOL

# Check for libraries
AM_PATH_GLIB_2_0([2.20.0], [
    GUI_CFLAGS="$GUI_CFLAGS $GLIB_CFLAGS"
    GUI_LIBS="$GUI_LIBS $GLIB_LIBS"
    ], [AC_MSG_ERROR([You need Glib >= 2.20.0 to build $PACKAGE])])

AM_PATH_GTK_3_0([3.4.0], [
    GUI_CFLAGS="$GUI_CFLAGS $GTK_CFLAGS"
    GUI_LIBS="$GUI_LIBS $GTK_LIBS"
    ], [AC_MSG_ERROR([You need Gtk+ >= 3.4.0 to build $PACKAGE])])

# Add explicit linking flags
GUI_LIBS="$GUI_LIBS -pthread -lm -lz -lrt"

# Check for header files.
AC_CHECK_HEADERS([libintl.h locale.h netdb.h stdlib.h string.h sys/socket.h sys/time.h unistd.h fcntl.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T

AC_SUBST(GUI_LIBS)
AC_SUBST(GUI_CFLAGS)
AC_CONFIG_FILES([
    Makefile
    src/Makefile
    ])
AC_OUTPUT

echo configure complete, now type \'make\'.
echo
