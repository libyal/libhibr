AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	@LIBFUSE_CPPFLAGS@ \
	@LIBHIBR_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	hibrinfo \
	hibrmount

hibrinfo_SOURCES = \
	hibrinfo.c \
	hibrtools_getopt.c hibrtools_getopt.h \
	hibrtools_i18n.h \
	hibrtools_libbfio.h \
	hibrtools_libcerror.h \
	hibrtools_libclocale.h \
	hibrtools_libcnotify.h \
	hibrtools_libhibr.h \
	hibrtools_libuna.h \
	hibrtools_output.c hibrtools_output.h \
	hibrtools_signal.c hibrtools_signal.h \
	hibrtools_unused.h \
	info_handle.c info_handle.h

hibrinfo_LDADD = \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	../libhibr/libhibr.la \
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

hibrmount_SOURCES = \
	hibrmount.c \
	hibrtools_getopt.c hibrtools_getopt.h \
	hibrtools_i18n.h \
	hibrtools_libcdata.h \
	hibrtools_libcerror.h \
	hibrtools_libclocale.h \
	hibrtools_libcnotify.h \
	hibrtools_libcpath.h \
	hibrtools_libhibr.h \
	hibrtools_output.c hibrtools_output.h \
	hibrtools_signal.c hibrtools_signal.h \
	hibrtools_unused.h \
	mount_dokan.c mount_dokan.h \
	mount_file_entry.c mount_file_entry.h \
	mount_file_system.c mount_file_system.h \
	mount_fuse.c mount_fuse.h \
	mount_handle.c mount_handle.h

hibrmount_LDADD = \
	@LIBFUSE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libhibr/libhibr.la \
	@LIBCERROR_LIBADD@ \
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

