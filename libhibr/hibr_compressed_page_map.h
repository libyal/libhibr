/*
 * The compressed page map definition of a Windows Hibernation File (hiberfil.sys)
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

#if !defined( _HIBR_COMPRESSED_PAGE_MAP_H )
#define _HIBR_COMPRESSED_PAGE_MAP_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct hibr_compressed_page_map_header_winxp_sp3_32bit hibr_compressed_page_map_header_winxp_sp3_32bit_t;

struct hibr_compressed_page_map_header_winxp_sp3_32bit
{
	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The next (memory block) page number
	 * Consists of 4 bytes
	 */
	uint8_t next_page_number[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];
};

typedef struct hibr_compressed_page_map_header_win7_sp1_64bit hibr_compressed_page_map_header_win7_sp1_64bit_t;

struct hibr_compressed_page_map_header_win7_sp1_64bit
{
	/* The next (memory block) page number
	 * Consists of 4 bytes
	 */
	uint8_t next_page_number[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The number of entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_entries[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];
};

typedef struct hibr_compressed_page_map_entry hibr_compressed_page_map_entry_t;

struct hibr_compressed_page_map_entry
{
	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown2[ 8 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _HIBR_COMPRESSED_PAGE_MAP_H ) */

