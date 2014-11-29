/*
 * Input/Output (IO) handle functions
 *
 * Copyright (c) 2012-2014, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libhibr_compressed_page_data.h"
#include "libhibr_definitions.h"
#include "libhibr_io_handle.h"
#include "libhibr_libbfio.h"
#include "libhibr_libcerror.h"
#include "libhibr_libcnotify.h"
#include "libhibr_libfcache.h"
#include "libhibr_libfdata.h"
#include "libhibr_unused.h"

#include "hibr_file_header.h"

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int libhibr_io_handle_initialize(
     libhibr_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libhibr_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              libhibr_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( libhibr_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		goto on_error;
	}
	( *io_handle )->page_size = 4096;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int libhibr_io_handle_free(
     libhibr_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "libhibr_io_handle_free";

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int libhibr_io_handle_clear(
     libhibr_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "libhibr_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( libhibr_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->page_size = 4096;

	return( 1 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int libhibr_io_handle_read_file_header(
     libhibr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	uint8_t *page_data             = NULL;
	static char *function          = "libhibr_io_handle_read_file_header";
	ssize_t read_count             = 0;
	uint64_t page_size             = 0;
	uint32_t file_header_data_size = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint64_t value_64bit           = 0;
	uint32_t value_32bit           = 0;
#endif

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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading file header at offset: 0.\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		goto on_error;
	}
	page_data = (uint8_t *) memory_allocate(
	                         sizeof( uint8_t ) * io_handle->page_size );

	if( page_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file header data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              page_data,
	              io_handle->page_size,
	              error );

	if( read_count != (ssize_t) io_handle->page_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		goto on_error;
	}
/* TODO do empty page test */

	byte_stream_copy_to_uint32_little_endian(
	 ( (hibr_file_header_t *) page_data )->size,
	 file_header_data_size );

	if( file_header_data_size > 0 )
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: file header data:\n",
			 function );
			libcnotify_print_data(
			 page_data,
			 (size_t) file_header_data_size,
			 0 );
		}
#endif
/* TODO
		if( memory_compare(
		     ( (hibr_file_header_t *) page_data )->signature,
		     hibr_file_signature,
		     8 ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported file signature.",
			 function );

			goto on_error;
		}
*/
		if( file_header_data_size == sizeof( hibr_file_header_winxp_sp3_32bit_t ) )
		{
			io_handle->file_type = LIBHIBR_FILE_TYPE_WINDOWS_XP_SP3_32BIT;
		}
		else if( file_header_data_size == sizeof( hibr_file_header_win7_sp1_64bit_t ) )
		{
			io_handle->file_type = LIBHIBR_FILE_TYPE_WINDOWS_7_SP1_64BIT;
		}
		if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_SP3_32BIT )
		{
			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->page_size,
			 page_size );

			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->memory_blocks_page_number,
			 io_handle->memory_blocks_page_number );
		}
		else if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_7_SP1_64BIT )
		{
			byte_stream_copy_to_uint64_little_endian(
			 ( (hibr_file_header_win7_sp1_64bit_t *) page_data )->page_size,
			 page_size );
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: signature\t\t\t\t: %c%c%c%c\n",
			 function,
			 ( (hibr_file_header_t *) page_data )->signature[ 0 ],
			 ( (hibr_file_header_t *) page_data )->signature[ 1 ],
			 ( (hibr_file_header_t *) page_data )->signature[ 2 ],
			 ( (hibr_file_header_t *) page_data )->signature[ 3 ] );

			if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_SP3_32BIT )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->version,
				 value_32bit );
				libcnotify_printf(
				 "%s: version\t\t\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );
			}
			else if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_7_SP1_64BIT )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_win7_sp1_64bit_t *) page_data )->image_type,
				 value_32bit );
				libcnotify_printf(
				 "%s: image type\t\t\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );
			}
			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_file_header_t *) page_data )->checksum,
			 value_32bit );
			libcnotify_printf(
			 "%s: checksum\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 file_header_data_size );

			if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_SP3_32BIT )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown1,
				 value_64bit );
			}
			else if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_7_SP1_64BIT )
			{
				byte_stream_copy_to_uint64_little_endian(
				 ( (hibr_file_header_win7_sp1_64bit_t *) page_data )->unknown1,
				 value_64bit );
			}
			libcnotify_printf(
			 "%s: unknown1\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			libcnotify_printf(
			 "%s: page size\t\t\t\t: %" PRIu64 "\n",
			 function,
			 page_size );

			if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_SP3_32BIT )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->image_type,
				 value_32bit );
				libcnotify_printf(
				 "%s: image type\t\t\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown2,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown2\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );
			}
			byte_stream_copy_to_uint64_little_endian(
			 ( (hibr_file_header_t *) page_data )->system_time,
			 value_64bit );
			libcnotify_printf(
			 "%s: system time\t\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint64_little_endian(
			 ( (hibr_file_header_t *) page_data )->interrupt_time,
			 value_64bit );
			libcnotify_printf(
			 "%s: interrupt time\t\t\t: 0x%08" PRIx64 "\n",
			 function,
			 value_64bit );

			byte_stream_copy_to_uint32_little_endian(
			 ( (hibr_file_header_t *) page_data )->feature_flags,
			 value_32bit );
			libcnotify_printf(
			 "%s: feature flags\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: hibernation flags\t\t\t: 0x%02" PRIx8 "\n",
			 function,
			 ( (hibr_file_header_t *) page_data )->hibernation_flags );

			libcnotify_printf(
			 "%s: unknown3:\n",
			 function );
			libcnotify_print_data(
			 ( (hibr_file_header_t *) page_data )->unknown3,
			 3,
			 0 );

			if( io_handle->file_type == LIBHIBR_FILE_TYPE_WINDOWS_XP_SP3_32BIT )
			{
				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->number_of_page_table_entries,
				 value_32bit );
				libcnotify_printf(
				 "%s: number of page table entries\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown4,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown4\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint64_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown5,
				 value_64bit );
				libcnotify_printf(
				 "%s: unknown5\t\t\t\t: 0x%08" PRIx64 "\n",
				 function,
				 value_64bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->number_of_free_pages,
				 value_32bit );
				libcnotify_printf(
				 "%s: number of free pages\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown6,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown6\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown7,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown7\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->number_of_pages,
				 value_32bit );
				libcnotify_printf(
				 "%s: number of pages\t\t\t: %" PRIu32 "\n",
				 function,
				 value_32bit );

				libcnotify_printf(
				 "%s: memory blocks page number\t\t: 0x%08" PRIx32 "\n",
				 function,
				 io_handle->memory_blocks_page_number );

				byte_stream_copy_to_uint32_little_endian(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown9,
				 value_32bit );
				libcnotify_printf(
				 "%s: unknown9\t\t\t\t: 0x%08" PRIx32 "\n",
				 function,
				 value_32bit );

				libcnotify_printf(
				 "%s: unknown10:\n",
				 function );
				libcnotify_print_data(
				 ( (hibr_file_header_winxp_sp3_32bit_t *) page_data )->unknown10,
				 72,
				 0 );
			}
			else
			{
				libcnotify_printf(
				 "\n" );
			}
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	else if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: page data:\n",
		 function );
		libcnotify_print_data(
		 page_data,
		 io_handle->page_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
/* TODO print trailing data */

/* TODO page size sanity check */
	io_handle->page_size = (size_t) page_size;

/* TODO memory blocks page number sanity check */

	memory_free(
	 page_data );

	page_data = NULL;

	return( 1 );

on_error:
	if( page_data != NULL )
	{
		memory_free(
		 page_data );
	}
	return( -1 );
}

/* Reads compressed page data
 * Callback function for the compressed page data list
 * Returns 1 if successful or -1 on error
 */
int libhibr_io_handle_read_compressed_page_data(
     intptr_t *io_handle LIBHIBR_ATTRIBUTE_UNUSED,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *list_element,
     libfcache_cache_t *cache,
     int element_data_file_index LIBHIBR_ATTRIBUTE_UNUSED,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags LIBHIBR_ATTRIBUTE_UNUSED,
     uint8_t read_flags LIBHIBR_ATTRIBUTE_UNUSED,
     libcerror_error_t **error )
{
	libhibr_compressed_page_data_t *compressed_page_data = NULL;
	static char *function                                = "libhibr_io_handle_read_compressed_page_data";

	LIBHIBR_UNREFERENCED_PARAMETER( io_handle );
	LIBHIBR_UNREFERENCED_PARAMETER( element_data_file_index );
	LIBHIBR_UNREFERENCED_PARAMETER( element_data_flags );
	LIBHIBR_UNREFERENCED_PARAMETER( read_flags );

	if( element_data_size > (size64_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid element data size value exceeds maximum.",
		 function );

		goto on_error;
	}
	if( libhibr_compressed_page_data_initialize(
	     &compressed_page_data,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create compressed page data.",
		 function );

		goto on_error;
	}
	if( libhibr_compressed_page_data_read(
	     compressed_page_data,
	     file_io_handle,
             element_data_offset,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read compressed page data.",
		 function );

		goto on_error;
	}
	if( libfdata_list_element_set_element_value(
	     list_element,
	     (intptr_t *) file_io_handle,
	     cache,
	     (intptr_t *) compressed_page_data,
	     (int (*)(intptr_t **, libcerror_error_t **)) &libhibr_compressed_page_data_free,
	     LIBFDATA_LIST_ELEMENT_VALUE_FLAG_MANAGED,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set compressed page data as element value.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( compressed_page_data != NULL )
	{
		libhibr_compressed_page_data_free(
		 &compressed_page_data,
		 NULL );
	}
	return( -1 );
}

