/*
 * The memory image information definition of a Windows Hibernation File (hiberfil.sys)
 *
 * Copyright (C) 2012-2023, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _HIBR_MEMORY_IMAGE_INFORMATION_H )
#define _HIBR_MEMORY_IMAGE_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct hibr_memory_image_information hibr_memory_image_information_t;

struct hibr_memory_image_information
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
};

typedef struct hibr_memory_image_information_winxp_32bit hibr_memory_image_information_winxp_32bit_t;

struct hibr_memory_image_information_winxp_32bit
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

	/* The page number
	 * Consists of 4 bytes
	 */
	uint8_t page_number[ 4 ];

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
	uint8_t unknown1[ 4 ];

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
	uint8_t unknown2[ 3 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

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

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown9[ 4 ];

	/* Unknown
	 * Consists of 72 bytes
	 */
	uint8_t unknown10[ 72 ];
};

typedef struct hibr_memory_image_information_winxp_64bit hibr_memory_image_information_winxp_64bit_t;

struct hibr_memory_image_information_winxp_64bit
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

	/* The page number
	 * Consists of 8 bytes
	 */
	uint8_t page_number[ 8 ];

	/* The page size
	 * Consists of 4 bytes
	 */
	uint8_t page_size[ 4 ];

	/* The image type
	 * Consists of 4 bytes
	 */
	uint8_t image_type[ 4 ];

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
	uint8_t unknown1[ 3 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown4[ 8 ];

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

	/* Unknown
	 * Consists of 4 bytes
	 */
	uint8_t unknown8[ 4 ];

	/* The (total) number of pages
	 * Consists of 8 bytes
	 */
	uint8_t number_of_pages[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown9[ 8 ];

	/* Unknown
	 * Consists of 8 bytes
	 */
	uint8_t unknown10[ 8 ];

	/* Unknown
	 * Consists of 72 bytes
	 */
	uint8_t unknown11[ 72 ];
};

typedef struct hibr_memory_image_information_win7_32bit hibr_memory_image_information_win7_32bit_t;

struct hibr_memory_image_information_win7_32bit
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
	 * Consists of 4 bytes
	 */
	uint8_t page_number[ 4 ];

	/* The page size
	 * Consists of 4 bytes
	 */
	uint8_t page_size[ 4 ];

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

typedef struct hibr_memory_image_information_win7_64bit hibr_memory_image_information_win7_64bit_t;

struct hibr_memory_image_information_win7_64bit
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
	uint8_t page_number[ 8 ];

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

#endif /* !defined( _HIBR_MEMORY_IMAGE_INFORMATION_H ) */

