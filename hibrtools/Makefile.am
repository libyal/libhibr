AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFCACHE_CPPFLAGS@ \
	@LIBFDATA_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBFUSE_CPPFLAGS@ \
	@LIBHIBR_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	hibrinfo \
	hibrmount

hibrinfo_SOURCES = \
	info_handle.c info_handle.h \
	hibrinfo.c \
	hibroutput.c hibroutput.h \
	hibrtools_libbfio.h \
	hibrtools_libcerror.h \
	hibrtools_libclocale.h \
	hibrtools_libcnotify.h \
	hibrtools_libcstring.h \
	hibrtools_libcsystem.h \
	hibrtools_libhibr.h \
	hibrtools_libuna.h

hibrinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../libhibr/libhibr.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

hibrmount_SOURCES = \
	mount_handle.c mount_handle.h \
	hibrmount.c \
	hibroutput.c hibroutput.h \
	hibrtools_libcerror.h \
	hibrtools_libclocale.h \
	hibrtools_libcnotify.h \
	hibrtools_libcstring.h \
	hibrtools_libcsystem.h \
	hibrtools_libhibr.h

hibrmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	../libhibr/libhibr.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on hibrinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(hibrinfo_SOURCES)
	@echo "Running splint on hibrmount ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(hibrmount_SOURCES)

