/*
 * Library file type test program
 *
 * Copyright (C) 2012-2021, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <file_stream.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#if defined( TIME_WITH_SYS_TIME )
#include <sys/time.h>
#include <time.h>
#elif defined( HAVE_SYS_TIME_H )
#include <sys/time.h>
#else
#include <time.h>
#endif

#include "hibr_test_functions.h"
#include "hibr_test_getopt.h"
#include "hibr_test_libbfio.h"
#include "hibr_test_libcerror.h"
#include "hibr_test_libhibr.h"
#include "hibr_test_macros.h"
#include "hibr_test_memory.h"

#include "../libhibr/libhibr_file.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make hibr_test_file generate verbose output
#define HIBR_TEST_FILE_VERBOSE
 */

#define HIBR_TEST_FILE_READ_BUFFER_SIZE	4096

#if !defined( LIBHIBR_HAVE_BFIO )

LIBHIBR_EXTERN \
int libhibr_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_file_open_file_io_handle(
     libhibr_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libhibr_error_t **error );

#endif /* !defined( LIBHIBR_HAVE_BFIO ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int hibr_test_file_open_source(
     libhibr_file_t **file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "hibr_test_file_open_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( libhibr_file_initialize(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	result = libhibr_file_open_file_io_handle(
	          *file,
	          file_io_handle,
	          LIBHIBR_OPEN_READ,
	          error );

	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *file != NULL )
	{
		libhibr_file_free(
		 file,
		 NULL );
	}
	return( -1 );
}

/* Closes and frees a source file
 * Returns 1 if successful or -1 on error
 */
int hibr_test_file_close_source(
     libhibr_file_t **file,
     libcerror_error_t **error )
{
	static char *function = "hibr_test_file_close_source";
	int result            = 0;

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( libhibr_file_close(
	     *file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close file.",
		 function );

		result = -1;
	}
	if( libhibr_file_free(
	     file,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free file.",
		 function );

		result = -1;
	}
	return( result );
}

/* Tests the libhibr_file_initialize function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_initialize(
     void )
{
	libcerror_error_t *error        = NULL;
	libhibr_file_t *file            = NULL;
	int result                      = 0;

#if defined( HAVE_HIBR_TEST_MEMORY )
	int number_of_malloc_fail_tests = 1;
	int number_of_memset_fail_tests = 1;
	int test_number                 = 0;
#endif

	/* Test regular cases
	 */
	result = libhibr_file_initialize(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhibr_file_free(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_file_initialize(
	          NULL,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = (libhibr_file_t *) 0x12345678UL;

	result = libhibr_file_initialize(
	          &file,
	          &error );

	file = NULL;

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_HIBR_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libhibr_file_initialize with malloc failing
		 */
		hibr_test_malloc_attempts_before_fail = test_number;

		result = libhibr_file_initialize(
		          &file,
		          &error );

		if( hibr_test_malloc_attempts_before_fail != -1 )
		{
			hibr_test_malloc_attempts_before_fail = -1;

			if( file != NULL )
			{
				libhibr_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			HIBR_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			HIBR_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			HIBR_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
	for( test_number = 0;
	     test_number < number_of_memset_fail_tests;
	     test_number++ )
	{
		/* Test libhibr_file_initialize with memset failing
		 */
		hibr_test_memset_attempts_before_fail = test_number;

		result = libhibr_file_initialize(
		          &file,
		          &error );

		if( hibr_test_memset_attempts_before_fail != -1 )
		{
			hibr_test_memset_attempts_before_fail = -1;

			if( file != NULL )
			{
				libhibr_file_free(
				 &file,
				 NULL );
			}
		}
		else
		{
			HIBR_TEST_ASSERT_EQUAL_INT(
			 "result",
			 result,
			 -1 );

			HIBR_TEST_ASSERT_IS_NULL(
			 "file",
			 file );

			HIBR_TEST_ASSERT_IS_NOT_NULL(
			 "error",
			 error );

			libcerror_error_free(
			 &error );
		}
	}
#endif /* defined( HAVE_HIBR_TEST_MEMORY ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libhibr_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libhibr_file_free function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libhibr_file_free(
	          NULL,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhibr_file_open function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_open(
     const system_character_t *source )
{
	char narrow_source[ 256 ];

	libcerror_error_t *error = NULL;
	libhibr_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = hibr_test_get_narrow_source(
	          source,
	          narrow_source,
	          256,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhibr_file_initialize(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libhibr_file_open(
	          file,
	          narrow_source,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_file_open(
	          NULL,
	          narrow_source,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_open(
	          file,
	          NULL,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_open(
	          file,
	          narrow_source,
	          -1,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libhibr_file_open(
	          file,
	          narrow_source,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libhibr_file_free(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libhibr_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Tests the libhibr_file_open_wide function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_open_wide(
     const system_character_t *source )
{
	wchar_t wide_source[ 256 ];

	libcerror_error_t *error = NULL;
	libhibr_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = hibr_test_get_wide_source(
	          source,
	          wide_source,
	          256,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhibr_file_initialize(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libhibr_file_open_wide(
	          file,
	          wide_source,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_file_open_wide(
	          NULL,
	          wide_source,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_open_wide(
	          file,
	          NULL,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_open_wide(
	          file,
	          wide_source,
	          -1,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libhibr_file_open_wide(
	          file,
	          wide_source,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libhibr_file_free(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libhibr_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Tests the libhibr_file_open_file_io_handle function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_open_file_io_handle(
     const system_character_t *source )
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libhibr_file_t *file             = NULL;
	size_t string_length             = 0;
	int result                       = 0;

	/* Initialize test
	 */
	result = libbfio_file_initialize(
	          &file_io_handle,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "file_io_handle",
	 file_io_handle );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	string_length = system_string_length(
	                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libbfio_file_set_name_wide(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#else
	result = libbfio_file_set_name(
	          file_io_handle,
	          source,
	          string_length,
	          &error );
#endif
	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhibr_file_initialize(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open
	 */
	result = libhibr_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_file_open_file_io_handle(
	          NULL,
	          file_io_handle,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_open_file_io_handle(
	          file,
	          NULL,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          -1,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Test open when already opened
	 */
	result = libhibr_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBHIBR_OPEN_READ,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	/* Clean up
	 */
	result = libhibr_file_free(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libbfio_handle_free(
	          &file_io_handle,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "file_io_handle",
	 file_io_handle );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libhibr_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( 0 );
}

/* Tests the libhibr_file_close function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_close(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libhibr_file_close(
	          NULL,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhibr_file_open and libhibr_file_close functions
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_open_close(
     const system_character_t *source )
{
	libcerror_error_t *error = NULL;
	libhibr_file_t *file     = NULL;
	int result               = 0;

	/* Initialize test
	 */
	result = libhibr_file_initialize(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libhibr_file_open_wide(
	          file,
	          source,
	          LIBHIBR_OPEN_READ,
	          &error );
#else
	result = libhibr_file_open(
	          file,
	          source,
	          LIBHIBR_OPEN_READ,
	          &error );
#endif

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhibr_file_close(
	          file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test open and close a second time to validate clean up on close
	 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libhibr_file_open_wide(
	          file,
	          source,
	          LIBHIBR_OPEN_READ,
	          &error );
#else
	result = libhibr_file_open(
	          file,
	          source,
	          LIBHIBR_OPEN_READ,
	          &error );
#endif

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhibr_file_close(
	          file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 0 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Clean up
	 */
	result = libhibr_file_free(
	          &file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "file",
	 file );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libhibr_file_free(
		 &file,
		 NULL );
	}
	return( 0 );
}

/* Tests the libhibr_file_signal_abort function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_signal_abort(
     libhibr_file_t *file )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test regular cases
	 */
	result = libhibr_file_signal_abort(
	          file,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_file_signal_abort(
	          NULL,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhibr_file_read_buffer function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_read_buffer(
     libhibr_file_t *file )
{
	uint8_t buffer[ HIBR_TEST_FILE_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	time_t timestamp         = 0;
	size64_t remaining_size  = 0;
	size64_t size            = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	off64_t read_offset      = 0;
	int number_of_tests      = 1024;
	int random_number        = 0;
	int result               = 0;
	int test_number          = 0;

	/* Determine size
	 */
	result = libhibr_file_get_media_size(
	          file,
	          &size,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libhibr_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = HIBR_TEST_FILE_READ_BUFFER_SIZE;

	if( size < HIBR_TEST_FILE_READ_BUFFER_SIZE )
	{
		read_size = (size_t) size;
	}
	read_count = libhibr_file_read_buffer(
	              file,
	              buffer,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( size > 8 )
	{
		/* Set offset to size - 8
		 */
		offset = libhibr_file_seek_offset(
		          file,
		          -8,
		          SEEK_END,
		          &error );

		HIBR_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 (int64_t) size - 8 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer on size boundary
		 */
		read_count = libhibr_file_read_buffer(
		              file,
		              buffer,
		              HIBR_TEST_FILE_READ_BUFFER_SIZE,
		              &error );

		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond size boundary
		 */
		read_count = libhibr_file_read_buffer(
		              file,
		              buffer,
		              HIBR_TEST_FILE_READ_BUFFER_SIZE,
		              &error );

		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	offset = libhibr_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	remaining_size = size;

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		HIBR_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		read_size = (size_t) random_number % HIBR_TEST_FILE_READ_BUFFER_SIZE;

#if defined( HIBR_TEST_FILE_VERBOSE )
		fprintf(
		 stdout,
		 "libhibr_file_read_buffer: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libhibr_file_read_buffer(
		              file,
		              buffer,
		              read_size,
		              &error );

		if( read_size > remaining_size )
		{
			read_size = (size_t) remaining_size;
		}
		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libhibr_file_get_offset(
		          file,
		          &offset,
		          &error );

		HIBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		HIBR_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		remaining_size -= read_count;

		if( remaining_size == 0 )
		{
			offset = libhibr_file_seek_offset(
			          file,
			          0,
			          SEEK_SET,
			          &error );

			HIBR_TEST_ASSERT_EQUAL_INT64(
			 "offset",
			 offset,
			 (int64_t) 0 );

			HIBR_TEST_ASSERT_IS_NULL(
			 "error",
			 error );

			read_offset = 0;

			remaining_size = size;
		}
	}
	/* Reset offset to 0
	 */
	offset = libhibr_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	read_count = libhibr_file_read_buffer(
	              NULL,
	              buffer,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libhibr_file_read_buffer(
	              file,
	              NULL,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libhibr_file_read_buffer(
	              file,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_HIBR_TEST_RWLOCK )

	/* Test libhibr_file_read_buffer with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	hibr_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libhibr_file_read_buffer(
	              file,
	              buffer,
	              HIBR_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	if( hibr_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		hibr_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		HIBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libhibr_file_read_buffer with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	hibr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libhibr_file_read_buffer(
	              file,
	              buffer,
	              HIBR_TEST_PARTITION_READ_BUFFER_SIZE,
	              &error );

	if( hibr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		hibr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		HIBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_HIBR_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhibr_file_read_buffer_at_offset function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_read_buffer_at_offset(
     libhibr_file_t *file )
{
	uint8_t buffer[ HIBR_TEST_FILE_READ_BUFFER_SIZE ];

	libcerror_error_t *error = NULL;
	time_t timestamp         = 0;
	size64_t remaining_size  = 0;
	size64_t size            = 0;
	size_t read_size         = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;
	off64_t read_offset      = 0;
	int number_of_tests      = 1024;
	int random_number        = 0;
	int result               = 0;
	int test_number          = 0;

	/* Determine size
	 */
	result = libhibr_file_get_media_size(
	          file,
	          &size,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test regular cases
	 */
	read_size = HIBR_TEST_FILE_READ_BUFFER_SIZE;

	if( size < HIBR_TEST_FILE_READ_BUFFER_SIZE )
	{
		read_size = (size_t) size;
	}
	read_count = libhibr_file_read_buffer_at_offset(
	              file,
	              buffer,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) read_size );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	if( size > 8 )
	{
		/* Read buffer on size boundary
		 */
		read_count = libhibr_file_read_buffer_at_offset(
		              file,
		              buffer,
		              HIBR_TEST_FILE_READ_BUFFER_SIZE,
		              size - 8,
		              &error );

		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 8 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		/* Read buffer beyond size boundary
		 */
		read_count = libhibr_file_read_buffer_at_offset(
		              file,
		              buffer,
		              HIBR_TEST_FILE_READ_BUFFER_SIZE,
		              size + 8,
		              &error );

		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 0 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Stress test read buffer
	 */
	timestamp = time(
	             NULL );

	srand(
	 (unsigned int) timestamp );

	for( test_number = 0;
	     test_number < number_of_tests;
	     test_number++ )
	{
		random_number = rand();

		HIBR_TEST_ASSERT_GREATER_THAN_INT(
		 "random_number",
		 random_number,
		 -1 );

		if( size > 0 )
		{
			read_offset = (off64_t) random_number % size;
		}
		read_size = (size_t) random_number % HIBR_TEST_FILE_READ_BUFFER_SIZE;

#if defined( HIBR_TEST_FILE_VERBOSE )
		fprintf(
		 stdout,
		 "libhibr_file_read_buffer_at_offset: at offset: %" PRIi64 " (0x%08" PRIx64 ") of size: %" PRIzd "\n",
		 read_offset,
		 read_offset,
		 read_size );
#endif
		read_count = libhibr_file_read_buffer_at_offset(
		              file,
		              buffer,
		              read_size,
		              read_offset,
		              &error );

		remaining_size = size - read_offset;

		if( read_size > remaining_size )
		{
			read_size = (size_t) remaining_size;
		}
		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) read_size );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		read_offset += read_count;

		result = libhibr_file_get_offset(
		          file,
		          &offset,
		          &error );

		HIBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		HIBR_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 offset,
		 read_offset );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	/* Test error cases
	 */
	read_count = libhibr_file_read_buffer_at_offset(
	              NULL,
	              buffer,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libhibr_file_read_buffer_at_offset(
	              file,
	              NULL,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libhibr_file_read_buffer_at_offset(
	              file,
	              buffer,
	              (size_t) SSIZE_MAX + 1,
	              0,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	read_count = libhibr_file_read_buffer_at_offset(
	              file,
	              buffer,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              -1,
	              &error );

	HIBR_TEST_ASSERT_EQUAL_SSIZE(
	 "read_count",
	 read_count,
	 (ssize_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_HIBR_TEST_RWLOCK )

	/* Test libhibr_file_read_buffer_at_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	hibr_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	read_count = libhibr_file_read_buffer_at_offset(
	              file,
	              buffer,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	if( hibr_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		hibr_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		HIBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libhibr_file_read_buffer_at_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	hibr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	read_count = libhibr_file_read_buffer_at_offset(
	              file,
	              buffer,
	              HIBR_TEST_FILE_READ_BUFFER_SIZE,
	              0,
	              &error );

	if( hibr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		hibr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) -1 );

		HIBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_HIBR_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhibr_file_seek_offset function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_seek_offset(
     libhibr_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	off64_t offset           = 0;

	/* Test regular cases
	 */
	offset = libhibr_file_seek_offset(
	          file,
	          0,
	          SEEK_END,
	          &error );

	HIBR_TEST_ASSERT_NOT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	size = (size64_t) offset;

	offset = libhibr_file_seek_offset(
	          file,
	          1024,
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 1024 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libhibr_file_seek_offset(
	          file,
	          -512,
	          SEEK_CUR,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 512 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset = libhibr_file_seek_offset(
	          file,
	          (off64_t) ( size + 512 ),
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) ( size + 512 ) );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Reset offset to 0
	 */
	offset = libhibr_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) 0 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	offset = libhibr_file_seek_offset(
	          NULL,
	          0,
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libhibr_file_seek_offset(
	          file,
	          -1,
	          SEEK_SET,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	offset = libhibr_file_seek_offset(
	          file,
	          -1,
	          SEEK_CUR,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	offset = libhibr_file_seek_offset(
	          file,
	          (off64_t) ( -1 * ( size + 1 ) ),
	          SEEK_END,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT64(
	 "offset",
	 offset,
	 (int64_t) -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

#if defined( HAVE_HIBR_TEST_RWLOCK )

	/* Test libhibr_file_seek_offset with pthread_rwlock_wrlock failing in libcthreads_read_write_lock_grab_for_write
	 */
	hibr_test_pthread_rwlock_wrlock_attempts_before_fail = 0;

	offset = libhibr_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	if( hibr_test_pthread_rwlock_wrlock_attempts_before_fail != -1 )
	{
		hibr_test_pthread_rwlock_wrlock_attempts_before_fail = -1;
	}
	else
	{
		HIBR_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		HIBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
	/* Test libhibr_file_seek_offset with pthread_rwlock_unlock failing in libcthreads_read_write_lock_release_for_write
	 */
	hibr_test_pthread_rwlock_unlock_attempts_before_fail = 0;

	offset = libhibr_file_seek_offset(
	          file,
	          0,
	          SEEK_SET,
	          &error );

	if( hibr_test_pthread_rwlock_unlock_attempts_before_fail != -1 )
	{
		hibr_test_pthread_rwlock_unlock_attempts_before_fail = -1;
	}
	else
	{
		HIBR_TEST_ASSERT_EQUAL_INT64(
		 "offset",
		 (int64_t) offset,
		 (int64_t) -1 );

		HIBR_TEST_ASSERT_IS_NOT_NULL(
		 "error",
		 error );

		libcerror_error_free(
		 &error );
	}
#endif /* defined( HAVE_HIBR_TEST_RWLOCK ) */

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhibr_file_get_offset function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_get_offset(
     libhibr_file_t *file )
{
	libcerror_error_t *error = NULL;
	off64_t offset           = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libhibr_file_get_offset(
	          file,
	          &offset,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_file_get_offset(
	          NULL,
	          &offset,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_get_offset(
	          file,
	          NULL,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* Tests the libhibr_file_get_media_size function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_file_get_media_size(
     libhibr_file_t *file )
{
	libcerror_error_t *error = NULL;
	size64_t media_size      = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libhibr_file_get_media_size(
	          file,
	          &media_size,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_file_get_media_size(
	          NULL,
	          &media_size,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	result = libhibr_file_get_media_size(
	          file,
	          NULL,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	return( 1 );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	return( 0 );
}

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc,
     wchar_t * const argv[] )
#else
int main(
     int argc,
     char * const argv[] )
#endif
{
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	libhibr_file_t *file             = NULL;
	system_character_t *source       = NULL;
	system_integer_t option          = 0;
	size_t string_length             = 0;
	int result                       = 0;

	while( ( option = hibr_test_getopt(
	                   argc,
	                   argv,
	                   _SYSTEM_STRING( "" ) ) ) != (system_integer_t) -1 )
	{
		switch( option )
		{
			case (system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_SYSTEM ".\n",
				 argv[ optind - 1 ] );

				return( EXIT_FAILURE );
		}
	}
	if( optind < argc )
	{
		source = argv[ optind ];
	}
#if defined( HAVE_DEBUG_OUTPUT ) && defined( HIBR_TEST_FILE_VERBOSE )
	libhibr_notify_set_verbose(
	 1 );
	libhibr_notify_set_stream(
	 stderr,
	 NULL );
#endif

	HIBR_TEST_RUN(
	 "libhibr_file_initialize",
	 hibr_test_file_initialize );

	HIBR_TEST_RUN(
	 "libhibr_file_free",
	 hibr_test_file_free );

#if !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 )
	if( source != NULL )
	{
		result = libbfio_file_initialize(
		          &file_io_handle,
		          &error );

		HIBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        HIBR_TEST_ASSERT_IS_NOT_NULL(
	         "file_io_handle",
	         file_io_handle );

	        HIBR_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		string_length = system_string_length(
		                 source );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libbfio_file_set_name_wide(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#else
		result = libbfio_file_set_name(
		          file_io_handle,
		          source,
		          string_length,
		          &error );
#endif
		HIBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

	        HIBR_TEST_ASSERT_IS_NULL(
	         "error",
	         error );

		result = libhibr_check_file_signature_file_io_handle(
		          file_io_handle,
		          &error );

		HIBR_TEST_ASSERT_NOT_EQUAL_INT(
		 "result",
		 result,
		 -1 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( result != 0 )
	{
		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_open",
		 hibr_test_file_open,
		 source );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_open_wide",
		 hibr_test_file_open_wide,
		 source );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_open_file_io_handle",
		 hibr_test_file_open_file_io_handle,
		 source );

		HIBR_TEST_RUN(
		 "libhibr_file_close",
		 hibr_test_file_close );

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_open_close",
		 hibr_test_file_open_close,
		 source );

		/* Initialize file for tests
		 */
		result = hibr_test_file_open_source(
		          &file,
		          file_io_handle,
		          &error );

		HIBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		HIBR_TEST_ASSERT_IS_NOT_NULL(
		 "file",
		 file );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_signal_abort",
		 hibr_test_file_signal_abort,
		 file );

#if defined( __GNUC__ ) && !defined( LIBHIBR_DLL_IMPORT )

		/* TODO: add tests for libhibr_file_open_read */

#endif /* defined( __GNUC__ ) && !defined( LIBHIBR_DLL_IMPORT ) */

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_read_buffer",
		 hibr_test_file_read_buffer,
		 file );

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_read_buffer_at_offset",
		 hibr_test_file_read_buffer_at_offset,
		 file );

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_seek_offset",
		 hibr_test_file_seek_offset,
		 file );

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_get_offset",
		 hibr_test_file_get_offset,
		 file );

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_get_media_size",
		 hibr_test_file_get_media_size,
		 file );

		/* Clean up
		 */
		result = hibr_test_file_close_source(
		          &file,
		          &error );

		HIBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 0 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "file",
		 file );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
	if( file_io_handle != NULL )
	{
		result = libbfio_handle_free(
		          &file_io_handle,
		          &error );

		HIBR_TEST_ASSERT_EQUAL_INT(
		 "result",
		 result,
		 1 );

		HIBR_TEST_ASSERT_IS_NULL(
	         "file_io_handle",
	         file_io_handle );

	        HIBR_TEST_ASSERT_IS_NULL(
	         "error",
	         error );
	}
#endif /* !defined( __BORLANDC__ ) || ( __BORLANDC__ >= 0x0560 ) */

	return( EXIT_SUCCESS );

on_error:
	if( error != NULL )
	{
		libcerror_error_free(
		 &error );
	}
	if( file != NULL )
	{
		libhibr_file_free(
		 &file,
		 NULL );
	}
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( EXIT_FAILURE );
}

