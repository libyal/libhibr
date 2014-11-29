/*
 * The file header definition of a Windows Hibernation File (hiberfil.sys)
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

#if !defined( _HIBR_FILE_HEADER_H )
#define _HIBR_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct hibr_file_header hibr_file_header_t;

struct hibr_file_header
{
	/* The signature
	 * Consists of 4 bytes
	 */
	uint8_t signature[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* Unknown
	 * Consists of 16 bytes
	 */
	uint8_t unknown2[ 16 ];

	/* The system time
	 * Consists of 8 bytes
	 */
	uint8_t system_time[ 8 ];

	/* The interrupt time
	 * Consists of 8 bytes
	 */
	uint8_t interrupt_time[ 8 ];

	/* The feature flags
	 * Consists of 4 bytes
	 */
	uint8_t feature_flags[ 4 ];

	/* The hibernation flags
	 * Consists of 1 byte
	 */
	uint8_t hibernation_flags;

	/* Unknown
	 * Consists of 3 bytes
	 */
	uint8_t unknown3[ 3 ];
};

typedef struct hibr_file_header_winxp_sp3_32bit hibr_file_header_winxp_sp3_32bit_t;

struct hibr_file_header_winxp_sp3_32bit
{
	/* The signature
	 * Consists of 4 bytes
	 */
	uint8_t signature[ 4 ];

	/* The version
	 * Consists of 4 bytes
	 */
	uint8_t version[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown1[ 4 ];

	/* The page size
	 * Consists of 4 bytes
	 */
	uint8_t page_size[ 4 ];

	/* The image type
	 * Consists of 4 bytes
	 */
	uint8_t image_type[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* The system time
	 * Consists of 8 bytes
	 */
	uint8_t system_time[ 8 ];

	/* The interrupt time
	 * Consists of 8 bytes
	 */
	uint8_t interrupt_time[ 8 ];

	/* The feature flags
	 * Consists of 4 bytes
	 */
	uint8_t feature_flags[ 4 ];

	/* The hibernation flags
	 * Consists of 1 byte
	 */
	uint8_t hibernation_flags;

	/* Unknown
	 * Consists of 3 bytes
	 */
	uint8_t unknown3[ 3 ];

	/* The number of page table entries
	 * Consists of 4 bytes
	 */
	uint8_t number_of_page_table_entries[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown4[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown5[ 8 ];

	/* The number of free pages
	 * Consists of 4 bytes
	 */
	uint8_t number_of_free_pages[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown6[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown7[ 4 ];

	/* The (total) number of pages
	 * Consists of 4 bytes
	 */
	uint8_t number_of_pages[ 4 ];

	/* The compressed hibernated memory blocks page number
	 * Consists of 4 bytes
	 */
	uint8_t memory_blocks_page_number[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* Unknown
	 * Consists of 72 bytes
	 */
	uint8_t unknown10[ 72 ];
};

typedef struct hibr_file_header_win7_sp1_64bit hibr_file_header_win7_sp1_64bit_t;

struct hibr_file_header_win7_sp1_64bit
{
	/* The signature
	 * Consists of 4 bytes
	 */
	uint8_t signature[ 4 ];

	/* The image type
	 * Consists of 4 bytes
	 */
	uint8_t image_type[ 4 ];

	/* The checksum
	 * Consists of 4 bytes
	 */
	uint8_t checksum[ 4 ];

	/* The size
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The page number
	 * Consists of 8 bytes
	 */
	uint8_t unknown1[ 8 ];

	/* The page size
	 * Consists of 8 bytes
	 */
	uint8_t page_size[ 8 ];

	/* The system time
	 * Consists of 8 bytes
	 */
	uint8_t system_time[ 8 ];

	/* The interrupt time
	 * Consists of 8 bytes
	 */
	uint8_t interrupt_time[ 8 ];

	/* The feature flags
	 * Consists of 4 bytes
	 */
	uint8_t feature_flags[ 4 ];

	/* The hibernation flags
	 * Consists of 1 byte
	 */
	uint8_t hibernation_flags;

	/* Unknown
	 * Consists of 3 bytes
	 */
	uint8_t unknown3[ 3 ];
};

#if defined( __cplusplus )
}
#endif

#endif

