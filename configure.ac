#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([pam_automount], [1.0], [nicolas.constanty@epitech.eu])
LT_INIT([shared])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_SUBDIRS([src/PamAutoMount src/ParserCpp])
AC_PREFIX_DEFAULT (/usr)

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h malloc.h stdlib.h sys/ioctl.h sys/mount.h unistd.h libcrypsetup.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_CHECK_FUNCS([memset mkdir rmdir strdup strerror])


AC_OUTPUT(Makefile src/ParserCpp/Makefile src/PamAutoMount/Makefile)
