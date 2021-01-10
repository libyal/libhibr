/*
 * Support functions
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

#if !defined( _LIBHIBR_SUPPORT_H )
#define _LIBHIBR_SUPPORT_H

#include <common.h>
#include <types.h>

#include "libhibr_extern.h"
#include "libhibr_libbfio.h"
#include "libhibr_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

#if !defined( HAVE_LOCAL_LIBHIBR )

LIBHIBR_EXTERN \
const char *libhibr_get_version(
             void );

LIBHIBR_EXTERN \
int libhibr_get_access_flags_read(
     void );

LIBHIBR_EXTERN \
int libhibr_get_access_flags_read_write(
     void );

LIBHIBR_EXTERN \
int libhibr_get_access_flags_write(
     void );

LIBHIBR_EXTERN \
int libhibr_get_codepage(
     int *codepage,
     libcerror_error_t **error );

LIBHIBR_EXTERN \
int libhibr_set_codepage(
     int codepage,
     libcerror_error_t **error );

#endif /* !defined( HAVE_LOCAL_LIBHIBR ) */

LIBHIBR_EXTERN \
int libhibr_check_file_signature(
     const char *filename,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )
LIBHIBR_EXTERN \
int libhibr_check_file_signature_wide(
     const wchar_t *filename,
     libcerror_error_t **error );
#endif

LIBHIBR_EXTERN \
int libhibr_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBHIBR_SUPPORT_H ) */

