AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(datadir)/locale\" \
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
	@LIBFWNT_CPPFLAGS@

lib_LTLIBRARIES = libhibr.la

libhibr_la_SOURCES = \
	hibr_compressed_page_data.h \
	hibr_compressed_page_map.h \
	hibr_file_header.h \
	libhibr.c \
	libhibr_compressed_page_data.c libhibr_compressed_page_data.h \
	libhibr_compressed_page_map.c libhibr_compressed_page_map.h \
	libhibr_compression.c libhibr_compression.h \
	libhibr_debug.c libhibr_debug.h \
	libhibr_definitions.h \
	libhibr_error.c libhibr_error.h \
	libhibr_extern.h \
	libhibr_file.c libhibr_file.h \
	libhibr_i18n.c libhibr_i18n.h \
	libhibr_io_handle.c libhibr_io_handle.h \
	libhibr_libbfio.h \
	libhibr_libcdata.h \
	libhibr_libcerror.h \
	libhibr_libclocale.h \
	libhibr_libcnotify.h \
	libhibr_libcstring.h \
	libhibr_libfcache.h \
	libhibr_libfdata.h \
	libhibr_libuna.h \
	libhibr_notify.c libhibr_notify.h \
	libhibr_support.c libhibr_support.h \
	libhibr_types.h \
	libhibr_unused.h

libhibr_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFCACHE_LIBADD@ \
	@LIBFDATA_LIBADD@ \
	@LIBFWNT_LIBADD@

libhibr_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libhibr_definitions.h.in \
	libhibr.rc \
	libhibr.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f libhibr_definitions.h
	/bin/rm -f libhibr.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on libhibr ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libhibr_la_SOURCES)

