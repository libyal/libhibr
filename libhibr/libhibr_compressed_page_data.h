/*
 * Compressed page data functions
 *
 * Copyright (C) 2012-2024, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBHIBR_COMPRESSED_PAGE_DATA_H )
#define _LIBHIBR_COMPRESSED_PAGE_DATA_H

#include <common.h>
#include <types.h>

#include "libhibr_libbfio.h"
#include "libhibr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libhibr_compressed_page_data libhibr_compressed_page_data_t;

struct libhibr_compressed_page_data
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;

	/* The number of pages
	 */
	uint8_t number_of_pages;

	/* The compressed data size
	 */
	size_t compressed_data_size;

	/* The (alignment) padding size
	 */
	size_t padding_size;
};

int libhibr_compressed_page_data_initialize(
     libhibr_compressed_page_data_t **compressed_page_data,
     libcerror_error_t **error );

int libhibr_compressed_page_data_free(
     libhibr_compressed_page_data_t **compressed_page_data,
     libcerror_error_t **error );

int libhibr_compressed_page_data_read_header(
     libhibr_compressed_page_data_t *compressed_page_data,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int libhibr_compressed_page_data_read_file_io_handle(
     libhibr_compressed_page_data_t *compressed_page_data,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBHIBR_COMPRESSED_PAGE_DATA_H ) */

