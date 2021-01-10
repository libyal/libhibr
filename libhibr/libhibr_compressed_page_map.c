/*
 * Compressed page map functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libhibr_compressed_page_map.h"
#include "libhibr_definitions.h"
#include "libhibr_io_handle.h"
#include "libhibr_libbfio.h"
#include "libhibr_libcdata.h"
#include "libhibr_libcerror.h"
#include "libhibr_libcnotify.h"

#include "hibr_compressed_page_map.h"

/* Creates a compressed page map
 * Make sure the value compressed_page_map is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libhibr_compressed_page_map_initialize(
     libhibr_compressed_page_map_t **compressed_page_map,
     libcerror_error_t **error )
{
	static char *function = "libhibr_compressed_page_map_initialize";

	if( compressed_page_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page map.",
		 function );

		return( -1 );
	}
	if( *compressed_page_map != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid compressed page map value already set.",
		 function );

		return( -1 );
	}
	*compressed_page_map = memory_allocate_structure(
	                        libhibr_compressed_page_map_t );

	if( *compressed_page_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create compressed page map.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *compressed_page_map,
	     0,
	     sizeof( libhibr_compressed_page_map_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear compressed page map.",
		 function );

		goto on_error;
	}
/* TODO initialize array */
	return( 1 );

on_error:
	if( *compressed_page_map != NULL )
	{
		memory_free(
		 *compressed_page_map );

		*compressed_page_map = NULL;
	}
	return( -1 );
}

/* Frees a compressed page map
 * Returns 1 if successful or -1 on error
 */
int libhibr_compressed_page_map_free(
     libhibr_compressed_page_map_t **compressed_page_map,
     libcerror_error_t **error )
{
	static char *function = "libhibr_compressed_page_map_free";
	int result            = 1;

	if( compressed_page_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page map.",
		 function );

		return( -1 );
	}
	if( *compressed_page_map != NULL )
	{
/* TODO clear array */
		memory_free(
		 *compressed_page_map );

		*compressed_page_map = NULL;
	}
	return( result );
}

/* Reads compressed page map
 * Returns 1 if successful or -1 on error
 */
int libhibr_compressed_page_map_read_data(
     libhibr_compressed_page_map_t *compressed_page_map,
     libhibr_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function                     = "libhibr_compressed_page_map_read_data";
	size_t compressed_page_map_read_data_size = 0;
	uint32_t number_of_entries                = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                      = 0;
#endif

	if( compressed_page_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page map.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_32BIT )
	{
		compressed_page_map_read_data_size = sizeof( hibr_compressed_page_map_header_winxp_sp3_32bit_t );
	}
	else if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_7_64BIT )
	{
		compressed_page_map_read_data_size = sizeof( hibr_compressed_page_map_header_win7_sp1_64bit_t );
	}
	else
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid IO handle - unsupported file type.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( ( data_size < compressed_page_map_read_data_size )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: compressed page map header data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 compressed_page_map_read_data_size,
		 0 );
	}
#endif
	if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_32BIT )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (hibr_compressed_page_map_header_winxp_sp3_32bit_t *) data )->next_page_number,
		 compressed_page_map->next_page_number );

		byte_stream_copy_to_uint32_little_endian(
		 ( (hibr_compressed_page_map_header_winxp_sp3_32bit_t *) data )->number_of_entries,
		 number_of_entries );
	}
	else if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_7_64BIT )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (hibr_compressed_page_map_header_win7_sp1_64bit_t *) data )->next_page_number,
		 compressed_page_map->next_page_number );

		byte_stream_copy_to_uint32_little_endian(
		 ( (hibr_compressed_page_map_header_win7_sp1_64bit_t *) data )->number_of_entries,
		 number_of_entries );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_32BIT )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_compressed_page_map_header_winxp_sp3_32bit_t *) data )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: next page number\t\t\t: %" PRIu32 " (offset: 0x%08" PRIx64 ")\n",
		 function,
		 compressed_page_map->next_page_number,
		 compressed_page_map->next_page_number * io_handle->page_size );

		if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_7_64BIT )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_compressed_page_map_header_win7_sp1_64bit_t *) data )->unknown1,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_32BIT )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_compressed_page_map_header_winxp_sp3_32bit_t *) data )->unknown2,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "%s: number of entries\t\t\t: %" PRIu32 "\n",
		 function,
		 number_of_entries );

		if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_7_64BIT )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_compressed_page_map_header_win7_sp1_64bit_t *) data )->unknown2,
			 value_32bit );
			libcnotify_printf(
			 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );
		}
		libcnotify_printf(
		 "\n" );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

/* TODO */
	data_size = sizeof( hibr_compressed_page_map_header_win7_sp1_64bit_t )
	          + ( number_of_entries * sizeof( hibr_compressed_page_map_entry_t ) );

	return( 1 );
}

/* Reads compressed page map
 * Returns 1 if successful or -1 on error
 */
int libhibr_compressed_page_map_read_file_io_handle(
     libhibr_compressed_page_map_t *compressed_page_map,
     libhibr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t *page_data    = NULL;
	static char *function = "libhibr_compressed_page_map_read_file_io_handle";
	ssize_t read_count    = 0;

	if( compressed_page_map == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed page map.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( ( io_handle->page_size == 0 )
	 || ( io_handle->page_size > (size_t) MEMORY_MAXIMUM_ALLOCATION_SIZE ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle - page size value out of bounds.",
		 function );

		return( -1 );
	}
	page_data = (uint8_t *) memory_allocate(
	                         sizeof( uint8_t ) * io_handle->page_size );

	if( page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create page data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading compressed page map at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
	              file_io_handle,
	              page_data,
	              io_handle->page_size,
	              file_offset,
	              error );

	if( read_count != (ssize_t) io_handle->page_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read page data at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	if( libhibr_compressed_page_map_read_data(
	     compressed_page_map,
	     io_handle,
	     page_data,
	     io_handle->page_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read page.",
		 function );

		goto on_error;
	}
	memory_free(
	 page_data );

	return( 1 );

on_error:
	if( page_data != NULL )
	{
		memory_free(
		 page_data );
	}
	return( -1 );
}

