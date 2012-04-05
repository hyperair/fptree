#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([fptree], [0.1], [hyperair@gmail.com])
AC_CONFIG_SRCDIR([src/transactions.hh])
AC_CANONICAL_HOST

AM_INIT_AUTOMAKE([foreign dist-zip])

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])

AC_PROG_CXX

AC_TYPE_SIZE_T

case $host_os in
    *mingw32*|*cygwin*)
        is_windows=yes;
esac

AM_CONDITIONAL([WINDOWS], [test "$is_windows" = "yes"])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
