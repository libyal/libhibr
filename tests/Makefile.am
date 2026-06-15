AM_CPPFLAGS = \
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
	@LIBHIBR_DLL_IMPORT@

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_libhibr.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) libhibr

test_inputs_hibrinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) hibrinfo

test_library: \
	package.m4 \
	test_inputs_libhibr.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_tools: \
	package.m4 \
	test_inputs_hibrinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

