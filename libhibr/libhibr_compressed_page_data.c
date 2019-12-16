/*
 * Compressed page data functions
 *
 * Copyright (C) 2012-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libhibr_compressed_page_data.h"
#include "libhibr_libbfio.h"
#include "libhibr_libcerror.h"
#include "libhibr_libcnotify.h"
#include "libhibr_libfwnt.h"

#include "hibr_compressed_page_data.h"

const uint8_t hibr_compressed_page_data_signature[ 8 ] = { 0x81, 0x81, 'x', 'p', 'r', 'e', 's', 's' };

/* Creates compressed page data
 * Make sure the value compressed_page_data is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libhibr_compressed_page_data_initialize(
     libhibr_compressed_page_data_t **compressed_page_data,
     libcerror_error_t **error )
{
	static char *function = "libhibr_compressed_page_data_initialize";

	if( compressed_page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page data.",
		 function );

		return( -1 );
	}
	if( *compressed_page_data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid compressed page data value already set.",
		 function );

		return( -1 );
	}
	*compressed_page_data = memory_allocate_structure(
	                         libhibr_compressed_page_data_t );

	if( *compressed_page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed page data.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *compressed_page_data,
	     0,
	     sizeof( libhibr_compressed_page_data_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear compressed page data.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *compressed_page_data != NULL )
	{
		memory_free(
		 *compressed_page_data );

		*compressed_page_data = NULL;
	}
	return( -1 );
}

/* Frees compressed page data
 * Returns 1 if successful or -1 on error
 */
int libhibr_compressed_page_data_free(
     libhibr_compressed_page_data_t **compressed_page_data,
     libcerror_error_t **error )
{
	static char *function = "libhibr_compressed_page_data_free";

	if( compressed_page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page data.",
		 function );

		return( -1 );
	}
	if( *compressed_page_data != NULL )
	{
		if( ( *compressed_page_data )->data != NULL )
		{
			memory_free(
			 ( *compressed_page_data )->data );
		}
		memory_free(
		 *compressed_page_data );

		*compressed_page_data = NULL;
	}
	return( 1 );
}

/* Reads compressed page data header
 * Returns 1 if successful, 0 if signature does not match or -1 on error
 */
int libhibr_compressed_page_data_read_header(
     libhibr_compressed_page_data_t *compressed_page_data,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	hibr_compressed_page_data_header_t header;

	uint8_t *compressed_data      = NULL;
	static char *function         = "libhibr_compressed_page_data_read_header";
	ssize_t read_count            = 0;
	uint32_t compressed_data_size = 0;

	if( compressed_page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading compressed page data header at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek compressed page data header offset: %" PRIi64 ".",
		 function,
		 file_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &header,
	              sizeof( hibr_compressed_page_data_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( hibr_compressed_page_data_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed page data header data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compressed page data header data:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &header,
		 sizeof( hibr_compressed_page_data_header_t ),
		 0 );
	}
#endif
	if( memory_compare(
	     header.signature,
	     hibr_compressed_page_data_signature,
	     8 ) != 0 )
	{
		return( 0 );
	}
	compressed_page_data->number_of_pages = header.number_of_pages;

	byte_stream_copy_to_uint32_little_endian(
	 header.compressed_data_size,
	 compressed_data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: signature\t\t\t: \\x%02" PRIx8 "\\x%02" PRIx8 "%c%c%c%c%c%c\n",
		 function,
		 header.signature[ 0 ],
		 header.signature[ 1 ],
		 header.signature[ 2 ],
		 header.signature[ 3 ],
		 header.signature[ 4 ],
		 header.signature[ 5 ],
		 header.signature[ 6 ],
		 header.signature[ 7 ] );

		libcnotify_printf(
		 "%s: number of pages\t\t: %" PRIu8 "\n",
		 function,
		 compressed_page_data->number_of_pages );

		libcnotify_printf(
		 "%s: unknown1:\n",
		 function );
		libcnotify_print_data(
		 header.unknown1,
		 19,
		 0 );
	}
#endif
	compressed_page_data->number_of_pages += 1;

/* TODO validate size ? */
	compressed_data_size >>= 2;
	compressed_data_size  += 1;

	compressed_page_data->compressed_data_size = (size_t) compressed_data_size;

	compressed_page_data->padding_size = (size_t) ( compressed_data_size & 0x00000007UL );

	if( compressed_page_data->padding_size != 0 )
	{
		compressed_page_data->padding_size = 8 - compressed_page_data->padding_size;
	}
/* TODO move page size into IO handle */
	compressed_page_data->data_size = (size_t) compressed_page_data->number_of_pages * 4096;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t: %" PRIzd "\n",
		 function,
		 compressed_page_data->data_size );

		libcnotify_printf(
		 "%s: compressed data size\t\t: %" PRIzd "\n",
		 function,
		 compressed_page_data->compressed_data_size );

		libcnotify_printf(
		 "%s: padding size\t\t\t: %" PRIzd "\n",
		 function,
		 compressed_page_data->padding_size );

		libcnotify_printf(
		 "\n" );
	}
#endif
	return( 1 );
}

/* Reads compressed page data header
 * Returns 1 if successful or -1 on error
 */
int libhibr_compressed_page_data_read(
     libhibr_compressed_page_data_t *compressed_page_data,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	hibr_compressed_page_data_header_t header;

	uint8_t *compressed_data      = NULL;
	static char *function         = "libhibr_compressed_page_data_read";
	size_t read_size              = 0;
	size_t uncompressed_data_size = 0;
	ssize_t read_count            = 0;

	if( compressed_page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page data.",
		 function );

		return( -1 );
	}
	if( libhibr_compressed_page_data_read_header(
	     compressed_page_data,
	     file_io_handle,
	     file_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed page data header.",
		 function );

		goto on_error;
	}
	file_offset += sizeof( hibr_compressed_page_data_header_t );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading compressed page data at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_size = compressed_page_data->compressed_data_size
	          + compressed_page_data->padding_size;

	compressed_data = (uint8_t *) memory_allocate(
	                               sizeof( uint8_t ) * read_size );

	if( compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              compressed_data,
	              read_size,
	              error );

	if( read_count != (ssize_t) read_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed data.",
		 function );

		goto on_error;
	}
/* TODO check compressed_page_data->data_size */
	compressed_page_data->data = (uint8_t *) memory_allocate(
	                                          sizeof( uint8_t ) * compressed_page_data->data_size );

	if( compressed_page_data->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	uncompressed_data_size = compressed_page_data->data_size;

	if( libfwnt_lzxpress_decompress(
	     compressed_data,
	     compressed_page_data->compressed_data_size,
	     compressed_page_data->data,
	     &uncompressed_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to decompress data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( compressed_page_data->padding_size > 0 )
		{
			libcnotify_printf(
			 "%s: alignment padding:\n",
			 function );
			libcnotify_print_data(
			 &( compressed_data[ compressed_page_data->compressed_data_size ] ),
			 compressed_page_data->padding_size,
			 0 );
		}
	}
#endif
	memory_free(
	 compressed_data );

	return( 1 );

on_error:
	if( compressed_page_data->data != NULL )
	{
		memory_free(
		 compressed_page_data->data );

		compressed_page_data->data = NULL;
	}
	if( compressed_data != NULL )
	{
		memory_free(
		 compressed_data );
	}
	return( -1 );
}

