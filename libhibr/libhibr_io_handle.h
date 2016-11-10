/*
 * Input/Output (IO) handle functions
 *
 * Copyright (C) 2012-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBHIBR_IO_HANDLE_H )
#define _LIBHIBR_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "libhibr_libbfio.h"
#include "libhibr_libcerror.h"
#include "libhibr_libfcache.h"
#include "libhibr_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t *hibr_file_signature;

typedef struct libhibr_io_handle libhibr_io_handle_t;

struct libhibr_io_handle
{
	/* The file type
	 */
	int file_type;

	/* The page size
	 */
	size_t page_size;

	/* The compressed hibernated memory blocks page number
	 */
	uint32_t memory_blocks_page_number;
};

int libhibr_io_handle_initialize(
     libhibr_io_handle_t **io_handle,
     libcerror_error_t **error );

int libhibr_io_handle_free(
     libhibr_io_handle_t **io_handle,
     libcerror_error_t **error );

int libhibr_io_handle_clear(
     libhibr_io_handle_t *io_handle,
     libcerror_error_t **error );

int libhibr_io_handle_read_memory_image_information(
     libhibr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

int libhibr_io_handle_read_compressed_page_data(
     intptr_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfdata_list_element_t *list_element,
     libfcache_cache_t *cache,
     int element_data_file_index,
     off64_t element_data_offset,
     size64_t element_data_size,
     uint32_t element_data_flags,
     uint8_t read_flags,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBHIBR_IO_HANDLE_H ) */

