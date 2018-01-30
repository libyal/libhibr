/*
 * Library file type test program
 *
 * Copyright (C) 2012-2018, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
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

#include "hibr_test_getopt.h"
#include "hibr_test_libcerror.h"
#include "hibr_test_libclocale.h"
#include "hibr_test_libhibr.h"
#include "hibr_test_libuna.h"
#include "hibr_test_macros.h"
#include "hibr_test_memory.h"

#if defined( HAVE_WIDE_SYSTEM_CHARACTER ) && SIZEOF_WCHAR_T != 2 && SIZEOF_WCHAR_T != 4
#error Unsupported size of wchar_t
#endif

/* Define to make hibr_test_file generate verbose output
#define HIBR_TEST_FILE_VERBOSE
 */

/* Retrieves source as a narrow string
 * Returns 1 if successful or -1 on error
 */
int hibr_test_file_get_narrow_source(
     const system_character_t *source,
     char *narrow_string,
     size_t narrow_string_size,
     libcerror_error_t **error )
{
	static char *function     = "hibr_test_file_get_narrow_source";
	size_t narrow_source_size = 0;
	size_t source_length      = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result                = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( narrow_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid narrow string.",
		 function );

		return( -1 );
	}
	if( narrow_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid narrow string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          &narrow_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_size_from_utf32(
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_size_from_utf16(
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &narrow_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine narrow string size.",
		 function );

		return( -1 );
	}
#else
	narrow_source_size = source_length + 1;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( narrow_string_size < narrow_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: narrow string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf8_string_copy_from_utf32(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf8_string_copy_from_utf16(
		          (libuna_utf8_character_t *) narrow_string,
		          narrow_string_size,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_byte_stream_copy_from_utf32(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf32_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_byte_stream_copy_from_utf16(
		          (uint8_t *) narrow_string,
		          narrow_string_size,
		          libclocale_codepage,
		          (libuna_utf16_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
#else
	if( system_string_copy(
	     narrow_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set narrow string.",
		 function );

		return( -1 );
	}
	narrow_string[ source_length ] = 0;

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Retrieves source as a wide string
 * Returns 1 if successful or -1 on error
 */
int hibr_test_file_get_wide_source(
     const system_character_t *source,
     wchar_t *wide_string,
     size_t wide_string_size,
     libcerror_error_t **error )
{
	static char *function   = "hibr_test_file_get_wide_source";
	size_t source_length    = 0;
	size_t wide_source_size = 0;

#if !defined( HAVE_WIDE_SYSTEM_CHARACTER )
	int result              = 0;
#endif

	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
		 function );

		return( -1 );
	}
	if( wide_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid wide string.",
		 function );

		return( -1 );
	}
	if( wide_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid wide string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	source_length = system_string_length(
	                 source );

	if( source_length > (size_t) ( SSIZE_MAX - 1 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid source length value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	wide_source_size = source_length + 1;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_utf8(
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          &wide_source_size,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_size_from_byte_stream(
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          &wide_source_size,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to determine wide string size.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	if( wide_string_size < wide_source_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: wide string too small.",
		 function );

		return( -1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	if( system_string_copy(
	     wide_string,
	     source,
	     source_length ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}
	wide_string[ source_length ] = 0;
#else
	if( libclocale_codepage == 0 )
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_utf8(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_utf8(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (libuna_utf8_character_t *) source,
		          source_length + 1,
		          error );
#endif
	}
	else
	{
#if SIZEOF_WCHAR_T == 4
		result = libuna_utf32_string_copy_from_byte_stream(
		          (libuna_utf32_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#elif SIZEOF_WCHAR_T == 2
		result = libuna_utf16_string_copy_from_byte_stream(
		          (libuna_utf16_character_t *) wide_string,
		          wide_string_size,
		          (uint8_t *) source,
		          source_length + 1,
		          libclocale_codepage,
		          error );
#endif
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_CONVERSION,
		 LIBCERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to set wide string.",
		 function );

		return( -1 );
	}

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

	return( 1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Creates and opens a source file
 * Returns 1 if successful or -1 on error
 */
int hibr_test_file_open_source(
     libhibr_file_t **file,
     const system_character_t *source,
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
	if( source == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid source.",
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libhibr_file_open_wide(
	          *file,
	          source,
	          LIBHIBR_OPEN_READ,
	          error );
#else
	result = libhibr_file_open(
	          *file,
	          source,
	          LIBHIBR_OPEN_READ,
	          error );
#endif
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

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "error",
	 error );

	libcerror_error_free(
	 &error );

	file = NULL;

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
	result = hibr_test_file_get_narrow_source(
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
	result = hibr_test_file_get_wide_source(
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
	uint8_t buffer[ 16 ];

	libcerror_error_t *error = NULL;
	size64_t size            = 0;
	ssize_t read_count       = 0;
	off64_t offset           = 0;

	/* Determine size
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
	if( size > 16 )
	{
		read_count = libhibr_file_read_buffer(
		              file,
		              buffer,
		              16,
		              &error );

		HIBR_TEST_ASSERT_EQUAL_SSIZE(
		 "read_count",
		 read_count,
		 (ssize_t) 16 );

		HIBR_TEST_ASSERT_IS_NULL(
		 "error",
		 error );
	}
/* TODO read on size boundary */
/* TODO read beyond size boundary */

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
	              16,
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
	              16,
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
	int offset_is_set        = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libhibr_file_get_offset(
	          file,
	          &offset,
	          &error );

	HIBR_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	offset_is_set = result;

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

	if( offset_is_set != 0 )
	{
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
	}
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
	int media_size_is_set    = 0;
	int result               = 0;

	/* Test regular cases
	 */
	result = libhibr_file_get_media_size(
	          file,
	          &media_size,
	          &error );

	HIBR_TEST_ASSERT_NOT_EQUAL_INT(
	 "result",
	 result,
	 -1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	media_size_is_set = result;

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

	if( media_size_is_set != 0 )
	{
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
	}
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
	libcerror_error_t *error   = NULL;
	libhibr_file_t *file       = NULL;
	system_character_t *source = NULL;
	system_integer_t option    = 0;
	int result                 = 0;

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

#if defined( LIBHIBR_HAVE_BFIO )

		/* TODO add test for libhibr_file_open_file_io_handle */

#endif /* defined( LIBHIBR_HAVE_BFIO ) */

		HIBR_TEST_RUN(
		 "libhibr_file_close",
		 hibr_test_file_close );

		HIBR_TEST_RUN_WITH_ARGS(
		 "libhibr_file_open_close",
		 hibr_test_file_open_close,
		 source );

		/* Initialize test
		 */
		result = hibr_test_file_open_source(
		          &file,
		          source,
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

		/* TODO: add tests for libhibr_file_read_buffer_at_offset */

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
		hibr_test_file_close_source(
		 &file,
		 NULL );
	}
	return( EXIT_FAILURE );
}

