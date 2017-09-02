/*
 * Library compressed_page_data type test program
 *
 * Copyright (C) 2012-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

#include "hibr_test_libcerror.h"
#include "hibr_test_libhibr.h"
#include "hibr_test_macros.h"
#include "hibr_test_memory.h"
#include "hibr_test_unused.h"

#include "../libhibr/libhibr_compressed_page_data.h"

#if defined( __GNUC__ ) && !defined( LIBHIBR_DLL_IMPORT )

/* Tests the libhibr_compressed_page_data_initialize function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_compressed_page_data_initialize(
     void )
{
	libcerror_error_t *error                             = NULL;
	libhibr_compressed_page_data_t *compressed_page_data = NULL;
	int result                                           = 0;

#if defined( HAVE_HIBR_TEST_MEMORY )
	int number_of_malloc_fail_tests                      = 1;
	int number_of_memset_fail_tests                      = 1;
	int test_number                                      = 0;
#endif

	/* Test regular cases
	 */
	result = libhibr_compressed_page_data_initialize(
	          &compressed_page_data,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NOT_NULL(
	 "compressed_page_data",
	 compressed_page_data );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	result = libhibr_compressed_page_data_free(
	          &compressed_page_data,
	          &error );

	HIBR_TEST_ASSERT_EQUAL_INT(
	 "result",
	 result,
	 1 );

	HIBR_TEST_ASSERT_IS_NULL(
	 "compressed_page_data",
	 compressed_page_data );

	HIBR_TEST_ASSERT_IS_NULL(
	 "error",
	 error );

	/* Test error cases
	 */
	result = libhibr_compressed_page_data_initialize(
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

	compressed_page_data = (libhibr_compressed_page_data_t *) 0x12345678UL;

	result = libhibr_compressed_page_data_initialize(
	          &compressed_page_data,
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

	compressed_page_data = NULL;

#if defined( HAVE_HIBR_TEST_MEMORY )

	for( test_number = 0;
	     test_number < number_of_malloc_fail_tests;
	     test_number++ )
	{
		/* Test libhibr_compressed_page_data_initialize with malloc failing
		 */
		hibr_test_malloc_attempts_before_fail = test_number;

		result = libhibr_compressed_page_data_initialize(
		          &compressed_page_data,
		          &error );

		if( hibr_test_malloc_attempts_before_fail != -1 )
		{
			hibr_test_malloc_attempts_before_fail = -1;

			if( compressed_page_data != NULL )
			{
				libhibr_compressed_page_data_free(
				 &compressed_page_data,
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
			 "compressed_page_data",
			 compressed_page_data );

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
		/* Test libhibr_compressed_page_data_initialize with memset failing
		 */
		hibr_test_memset_attempts_before_fail = test_number;

		result = libhibr_compressed_page_data_initialize(
		          &compressed_page_data,
		          &error );

		if( hibr_test_memset_attempts_before_fail != -1 )
		{
			hibr_test_memset_attempts_before_fail = -1;

			if( compressed_page_data != NULL )
			{
				libhibr_compressed_page_data_free(
				 &compressed_page_data,
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
			 "compressed_page_data",
			 compressed_page_data );

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
	if( compressed_page_data != NULL )
	{
		libhibr_compressed_page_data_free(
		 &compressed_page_data,
		 NULL );
	}
	return( 0 );
}

/* Tests the libhibr_compressed_page_data_free function
 * Returns 1 if successful or 0 if not
 */
int hibr_test_compressed_page_data_free(
     void )
{
	libcerror_error_t *error = NULL;
	int result               = 0;

	/* Test error cases
	 */
	result = libhibr_compressed_page_data_free(
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

#endif /* defined( __GNUC__ ) && !defined( LIBHIBR_DLL_IMPORT ) */

/* The main program
 */
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
int wmain(
     int argc HIBR_TEST_ATTRIBUTE_UNUSED,
     wchar_t * const argv[] HIBR_TEST_ATTRIBUTE_UNUSED )
#else
int main(
     int argc HIBR_TEST_ATTRIBUTE_UNUSED,
     char * const argv[] HIBR_TEST_ATTRIBUTE_UNUSED )
#endif
{
	HIBR_TEST_UNREFERENCED_PARAMETER( argc )
	HIBR_TEST_UNREFERENCED_PARAMETER( argv )

#if defined( __GNUC__ ) && !defined( LIBHIBR_DLL_IMPORT )

	HIBR_TEST_RUN(
	 "libhibr_compressed_page_data_initialize",
	 hibr_test_compressed_page_data_initialize );

	HIBR_TEST_RUN(
	 "libhibr_compressed_page_data_free",
	 hibr_test_compressed_page_data_free );

	/* TODO: add tests for libhibr_compressed_page_data_read_header */

	/* TODO: add tests for libhibr_compressed_page_data_read */

#endif /* defined( __GNUC__ ) && !defined( LIBHIBR_DLL_IMPORT ) */

	return( EXIT_SUCCESS );

on_error:
	return( EXIT_FAILURE );
}

