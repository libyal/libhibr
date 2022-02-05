/*
 * The compressed page data definition of a Windows Hibernation File (hiberfil.sys)
 *
 * Copyright (C) 2012-2022, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _HIBR_COMPRESSED_PAGE_DATA_H )
#define _HIBR_COMPRESSED_PAGE_DATA_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct hibr_compressed_page_data_header hibr_compressed_page_data_header_t;

struct hibr_compressed_page_data_header
{
	/* The signature
	 * Consists of 8 bytes
	 * Contains: \x81\x81xpress
	 */
	uint8_t signature[ 8 ];

	/* The number of pages
	 * Consists of 1 byte
	 */
	uint8_t number_of_pages;

	/* The compressed data size
	 * Consists of 4 bytes
	 */
	uint8_t compressed_data_size[ 4 ];

	/* Unknown
	 * Consists of 19 bytes
	 */
	uint8_t unknown1[ 19 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _HIBR_COMPRESSED_PAGE_DATA_H ) */

