AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
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
	@LIBHIBR_DLL_IMPORT@

TESTS = \
	test_library.sh \
	test_hibrinfo.sh

check_SCRIPTS = \
	test_hibrinfo.sh \
	test_library.sh \
	test_manpage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	hibr_test_compressed_page_data \
	hibr_test_compressed_page_map \
	hibr_test_error \
	hibr_test_file \
	hibr_test_io_handle \
	hibr_test_notify \
	hibr_test_support

hibr_test_compressed_page_data_SOURCES = \
	hibr_test_compressed_page_data.c \
	hibr_test_libcerror.h \
	hibr_test_libhibr.h \
	hibr_test_macros.h \
	hibr_test_memory.c hibr_test_memory.h \
	hibr_test_unused.h

hibr_test_compressed_page_data_LDADD = \
	../libhibr/libhibr.la \
	@LIBCERROR_LIBADD@

hibr_test_compressed_page_map_SOURCES = \
	hibr_test_compressed_page_map.c \
	hibr_test_libcerror.h \
	hibr_test_libhibr.h \
	hibr_test_macros.h \
	hibr_test_memory.c hibr_test_memory.h \
	hibr_test_unused.h

hibr_test_compressed_page_map_LDADD = \
	../libhibr/libhibr.la \
	@LIBCERROR_LIBADD@

hibr_test_error_SOURCES = \
	hibr_test_error.c \
	hibr_test_libhibr.h \
	hibr_test_macros.h \
	hibr_test_unused.h

hibr_test_error_LDADD = \
	../libhibr/libhibr.la

hibr_test_file_SOURCES = \
	hibr_test_file.c \
	hibr_test_functions.c hibr_test_functions.h \
	hibr_test_getopt.c hibr_test_getopt.h \
	hibr_test_libcerror.h \
	hibr_test_libclocale.h \
	hibr_test_libcnotify.h \
	hibr_test_libhibr.h \
	hibr_test_libuna.h \
	hibr_test_macros.h \
	hibr_test_memory.c hibr_test_memory.h

hibr_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libhibr/libhibr.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

hibr_test_io_handle_SOURCES = \
	hibr_test_io_handle.c \
	hibr_test_libcerror.h \
	hibr_test_libhibr.h \
	hibr_test_macros.h \
	hibr_test_memory.c hibr_test_memory.h \
	hibr_test_unused.h

hibr_test_io_handle_LDADD = \
	../libhibr/libhibr.la \
	@LIBCERROR_LIBADD@

hibr_test_notify_SOURCES = \
	hibr_test_libcerror.h \
	hibr_test_libhibr.h \
	hibr_test_macros.h \
	hibr_test_notify.c \
	hibr_test_unused.h

hibr_test_notify_LDADD = \
	../libhibr/libhibr.la \
	@LIBCERROR_LIBADD@

hibr_test_support_SOURCES = \
	hibr_test_functions.c hibr_test_functions.h \
	hibr_test_getopt.c hibr_test_getopt.h \
	hibr_test_libbfio.h \
	hibr_test_libcerror.h \
	hibr_test_libclocale.h \
	hibr_test_libcnotify.h \
	hibr_test_libhibr.h \
	hibr_test_libuna.h \
	hibr_test_macros.h \
	hibr_test_memory.c hibr_test_memory.h \
	hibr_test_support.c

hibr_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../libhibr/libhibr.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

