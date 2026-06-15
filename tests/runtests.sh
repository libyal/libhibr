#!/bin/sh
# Script to run tests
#
# Version: 20260609

if test -f ${PWD}/libhibr/.libs/libhibr.1.dylib && test -f ./pyhibr/.libs/pyhibr.so
then
	install_name_tool -change /usr/local/lib/libhibr.1.dylib ${PWD}/libhibr/.libs/libhibr.1.dylib ./pyhibr/.libs/pyhibr.so
fi

make check-build > /dev/null

make check $@
RESULT=$?

if test ${RESULT} -ne 0
then
	find . -name \*.log -path \*.dir/\*/\*.log -print -exec cat {} \;
fi
exit ${RESULT}

