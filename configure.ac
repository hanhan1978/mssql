#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([FULL-PACKAGE-NAME], [VERSION], [BUG-REPORT-ADDRESS])
AM_INIT_AUTOMAKE(mssql, 0.1)
AC_OUTPUT(Makefile src/Makefile)
AC_CONFIG_SRCDIR([src])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h sys/param.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_LIB(sybdb, dbopen, [], [
        echo "Error! freetds-devel is required."
        exit -1
        ])
AC_CHECK_LIB(ncurses, mvwin, [], [
        echo "Error! ncurses-devel is required."
        exit -1
        ])
AC_CHECK_LIB(readline, rl_digit_argument, [], [
        echo "Error! readline-devel is required." 
        exit -1
        ])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([gethostname strchr])

#AC_CONFIG_FILES([Makefile])
AC_OUTPUT