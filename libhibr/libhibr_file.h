/*
 * File functions
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

#if !defined( _LIBHIBR_INTERNAL_FILE_H )
#define _LIBHIBR_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include "libhibr_extern.h"
#include "libhibr_io_handle.h"
#include "libhibr_libbfio.h"
#include "libhibr_libcerror.h"
#include "libhibr_libfcache.h"
#include "libhibr_libfdata.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libhibr_internal_file libhibr_internal_file_t;

struct libhibr_internal_file
{
	/* The IO handle
	 */
	libhibr_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The compressed page data list
	 */
	libfdata_list_t *compressed_page_data_list;

	/* The compressed page data cache
	 */
	libfcache_cache_t *compressed_page_data_cache;

	/* The current (storage media) offset
	 */
	off64_t current_offset;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

LIBHIBR_EXTERN \
int libhibr_file_initialize(
     libhibr_file_t **file,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_file_free(
     libhibr_file_t **file,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_file_signal_abort(
     libhibr_file_t *file,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_file_open(
     libhibr_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBHIBR_EXTERN \
int libhibr_file_open_wide(
     libhibr_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBHIBR_EXTERN \
int libhibr_file_open_file_io_handle(
     libhibr_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_file_close(
     libhibr_file_t *file,
     libcerror_error_t **error );

int libhibr_file_open_read(
     libhibr_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
ssize_t libhibr_file_read_buffer(
         libhibr_file_t *file,
         void *buffer,
         size_t buffer_size,
         libcerror_error_t **error );

LIBHIBR_EXTERN \
ssize_t libhibr_file_read_buffer_at_offset(
         libhibr_file_t *file,
         void *buffer,
         size_t buffer_size,
         off64_t offset,
         libcerror_error_t **error );

LIBHIBR_EXTERN \
off64_t libhibr_file_seek_offset(
         libhibr_file_t *file,
         off64_t offset,
         int whence,
         libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_file_get_offset(
     libhibr_file_t *file,
     off64_t *offset,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_file_get_media_size(
     libhibr_file_t *file,
     size64_t *media_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBHIBR_INTERNAL_FILE_H ) */

