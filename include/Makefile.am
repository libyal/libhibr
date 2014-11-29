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
	/bin/rm -f libhibr.h
	/bin/rm -f libhibr/definitions.h
	/bin/rm -f libhibr/features.h
	/bin/rm -f libhibr/types.h
	/bin/rm -f Makefile

