AM_CPPFLAGS = \
	-DLOCALEDIR=\"$(datadir)/locale\" \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
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
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFWNT_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBHIBR_DLL_EXPORT@

lib_LTLIBRARIES = libhibr.la

libhibr_la_SOURCES = \
	hibr_compressed_page_data.h \
	hibr_compressed_page_map.h \
	hibr_memory_image_information.h \
	libhibr.c \
	libhibr_compressed_page_data.c libhibr_compressed_page_data.h \
	libhibr_compressed_page_map.c libhibr_compressed_page_map.h \
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
	libhibr_libfcache.h \
	libhibr_libfdata.h \
	libhibr_libfdatetime.h \
	libhibr_libfwnt.h \
	libhibr_libuna.h \
	libhibr_notify.c libhibr_notify.h \
	libhibr_support.c libhibr_support.h \
	libhibr_types.h \
	libhibr_unused.h

libhibr_la_LIBADD = \
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
	@LIBFDATETIME_LIBADD@ \
	@LIBFWNT_LIBADD@

libhibr_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	libhibr_definitions.h.in \
	libhibr.rc \
	libhibr.rc.in

DISTCLEANFILES = \
	libhibr_definitions.h \
	libhibr.rc \
	Makefile \
	Makefile.in

sources-local: $(BUILT_SOURCES)

splint-local:
	@echo "Running splint on libhibr ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(libhibr_la_SOURCES)

