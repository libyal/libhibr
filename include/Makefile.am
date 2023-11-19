include_HEADERS = \
	libhibr.h

pkginclude_HEADERS = \
	libhibr/codepage.h \
	libhibr/definitions.h \
	libhibr/error.h \
	libhibr/extern.h \
	libhibr/features.h \
	libhibr/types.h

EXTRA_DIST = \
	libhibr.h.in \
	libhibr/definitions.h.in \
	libhibr/features.h.in \
	libhibr/types.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	-rm -f libhibr.h
	-rm -f libhibr/definitions.h
	-rm -f libhibr/features.h
	-rm -f libhibr/types.h
	-rm -f Makefile

