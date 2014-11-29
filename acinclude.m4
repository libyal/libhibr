dnl Function to detect if libhibr dependencies are available
AC_DEFUN([AX_LIBHIBR_CHECK_LOCAL],
 [dnl Check for internationalization functions in libhibr/libhibr_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

