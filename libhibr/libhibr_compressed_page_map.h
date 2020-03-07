/*
 * Compressed page map functions
 *
 * Copyright (C) 2012-2020, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBHIBR_COMPRESSED_PAGE_MAP_H )
#define _LIBHIBR_COMPRESSED_PAGE_MAP_H

#include <common.h>
#include <types.h>

#include "libhibr_io_handle.h"
#include "libhibr_libbfio.h"
#include "libhibr_libcdata.h"
#include "libhibr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libhibr_compressed_page_map libhibr_compressed_page_map_t;

struct libhibr_compressed_page_map
{
	/* The next (memory block) page number
	 */
	uint64_t next_page_number;

	/* The entries array
	 */
	libcdata_array_t *entries_array;
};

int libhibr_compressed_page_map_initialize(
     libhibr_compressed_page_map_t **compressed_page_map,
     libcerror_error_t **error );

int libhibr_compressed_page_map_free(
     libhibr_compressed_page_map_t **compressed_page_map,
     libcerror_error_t **error );

int libhibr_compressed_page_map_read(
     libhibr_compressed_page_map_t *compressed_page_map,
     libhibr_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBHIBR_COMPRESSED_PAGE_MAP_H ) */

