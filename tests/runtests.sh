#!/bin/sh
# Script to run tests
#
# Version: 20201121

if test -f ${PWD}/libhibr/.libs/libhibr.1.dylib && test -f ./pyhibr/.libs/pyhibr.so;
then
	install_name_tool -change /usr/local/lib/libhibr.1.dylib ${PWD}/libhibr/.libs/libhibr.1.dylib ./pyhibr/.libs/pyhibr.so;
fi

make check CHECK_WITH_STDERR=1;
RESULT=$?;

if test ${RESULT} -ne 0 && test -f tests/test-suite.log;
then
	cat tests/test-suite.log;
fi
exit ${RESULT};

