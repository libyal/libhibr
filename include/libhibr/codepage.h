/*
 * Codepage definitions for libhibr
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

#if !defined( _LIBHIBR_CODEPAGE_H )
#define _LIBHIBR_CODEPAGE_H

#include <libhibr/types.h>

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage definitions
 */
enum LIBHIBR_CODEPAGES
{
	LIBHIBR_CODEPAGE_ASCII				= 20127,

	LIBHIBR_CODEPAGE_ISO_8859_1			= 28591,
	LIBHIBR_CODEPAGE_ISO_8859_2			= 28592,
	LIBHIBR_CODEPAGE_ISO_8859_3			= 28593,
	LIBHIBR_CODEPAGE_ISO_8859_4			= 28594,
	LIBHIBR_CODEPAGE_ISO_8859_5			= 28595,
	LIBHIBR_CODEPAGE_ISO_8859_6			= 28596,
	LIBHIBR_CODEPAGE_ISO_8859_7			= 28597,
	LIBHIBR_CODEPAGE_ISO_8859_8			= 28598,
	LIBHIBR_CODEPAGE_ISO_8859_9			= 28599,
	LIBHIBR_CODEPAGE_ISO_8859_10			= 28600,
	LIBHIBR_CODEPAGE_ISO_8859_11			= 28601,
	LIBHIBR_CODEPAGE_ISO_8859_13			= 28603,
	LIBHIBR_CODEPAGE_ISO_8859_14			= 28604,
	LIBHIBR_CODEPAGE_ISO_8859_15			= 28605,
	LIBHIBR_CODEPAGE_ISO_8859_16			= 28606,

	LIBHIBR_CODEPAGE_KOI8_R				= 20866,
	LIBHIBR_CODEPAGE_KOI8_U				= 21866,

	LIBHIBR_CODEPAGE_WINDOWS_874			= 874,
	LIBHIBR_CODEPAGE_WINDOWS_932			= 932,
	LIBHIBR_CODEPAGE_WINDOWS_936			= 936,
	LIBHIBR_CODEPAGE_WINDOWS_949			= 949,
	LIBHIBR_CODEPAGE_WINDOWS_950			= 950,
	LIBHIBR_CODEPAGE_WINDOWS_1250			= 1250,
	LIBHIBR_CODEPAGE_WINDOWS_1251			= 1251,
	LIBHIBR_CODEPAGE_WINDOWS_1252			= 1252,
	LIBHIBR_CODEPAGE_WINDOWS_1253			= 1253,
	LIBHIBR_CODEPAGE_WINDOWS_1254			= 1254,
	LIBHIBR_CODEPAGE_WINDOWS_1255			= 1255,
	LIBHIBR_CODEPAGE_WINDOWS_1256			= 1256,
	LIBHIBR_CODEPAGE_WINDOWS_1257			= 1257,
	LIBHIBR_CODEPAGE_WINDOWS_1258			= 1258
};

#define LIBHIBR_CODEPAGE_US_ASCII			LIBHIBR_CODEPAGE_ASCII

#define LIBHIBR_CODEPAGE_ISO_WESTERN_EUROPEAN		LIBHIBR_CODEPAGE_ISO_8859_1
#define LIBHIBR_CODEPAGE_ISO_CENTRAL_EUROPEAN		LIBHIBR_CODEPAGE_ISO_8859_2
#define LIBHIBR_CODEPAGE_ISO_SOUTH_EUROPEAN		LIBHIBR_CODEPAGE_ISO_8859_3
#define LIBHIBR_CODEPAGE_ISO_NORTH_EUROPEAN		LIBHIBR_CODEPAGE_ISO_8859_4
#define LIBHIBR_CODEPAGE_ISO_CYRILLIC			LIBHIBR_CODEPAGE_ISO_8859_5
#define LIBHIBR_CODEPAGE_ISO_ARABIC			LIBHIBR_CODEPAGE_ISO_8859_6
#define LIBHIBR_CODEPAGE_ISO_GREEK			LIBHIBR_CODEPAGE_ISO_8859_7
#define LIBHIBR_CODEPAGE_ISO_HEBREW			LIBHIBR_CODEPAGE_ISO_8859_8
#define LIBHIBR_CODEPAGE_ISO_TURKISH			LIBHIBR_CODEPAGE_ISO_8859_9
#define LIBHIBR_CODEPAGE_ISO_NORDIC			LIBHIBR_CODEPAGE_ISO_8859_10
#define LIBHIBR_CODEPAGE_ISO_THAI			LIBHIBR_CODEPAGE_ISO_8859_11
#define LIBHIBR_CODEPAGE_ISO_BALTIC			LIBHIBR_CODEPAGE_ISO_8859_13
#define LIBHIBR_CODEPAGE_ISO_CELTIC			LIBHIBR_CODEPAGE_ISO_8859_14

#define LIBHIBR_CODEPAGE_ISO_LATIN_1			LIBHIBR_CODEPAGE_ISO_8859_1
#define LIBHIBR_CODEPAGE_ISO_LATIN_2			LIBHIBR_CODEPAGE_ISO_8859_2
#define LIBHIBR_CODEPAGE_ISO_LATIN_3			LIBHIBR_CODEPAGE_ISO_8859_3
#define LIBHIBR_CODEPAGE_ISO_LATIN_4			LIBHIBR_CODEPAGE_ISO_8859_4
#define LIBHIBR_CODEPAGE_ISO_LATIN_5			LIBHIBR_CODEPAGE_ISO_8859_9
#define LIBHIBR_CODEPAGE_ISO_LATIN_6			LIBHIBR_CODEPAGE_ISO_8859_10
#define LIBHIBR_CODEPAGE_ISO_LATIN_7			LIBHIBR_CODEPAGE_ISO_8859_13
#define LIBHIBR_CODEPAGE_ISO_LATIN_8			LIBHIBR_CODEPAGE_ISO_8859_14
#define LIBHIBR_CODEPAGE_ISO_LATIN_9			LIBHIBR_CODEPAGE_ISO_8859_15
#define LIBHIBR_CODEPAGE_ISO_LATIN_10			LIBHIBR_CODEPAGE_ISO_8859_16

#define LIBHIBR_CODEPAGE_KOI8_RUSSIAN			LIBHIBR_CODEPAGE_KOI8_R
#define LIBHIBR_CODEPAGE_KOI8_UKRAINIAN			LIBHIBR_CODEPAGE_KOI8_U

#define LIBHIBR_CODEPAGE_WINDOWS_THAI			LIBHIBR_CODEPAGE_WINDOWS_874
#define LIBHIBR_CODEPAGE_WINDOWS_JAPANESE		LIBHIBR_CODEPAGE_WINDOWS_932
#define LIBHIBR_CODEPAGE_WINDOWS_CHINESE_SIMPLIFIED	LIBHIBR_CODEPAGE_WINDOWS_936
#define LIBHIBR_CODEPAGE_WINDOWS_KOREAN			LIBHIBR_CODEPAGE_WINDOWS_949
#define LIBHIBR_CODEPAGE_WINDOWS_CHINESE_TRADITIONAL	LIBHIBR_CODEPAGE_WINDOWS_950
#define LIBHIBR_CODEPAGE_WINDOWS_CENTRAL_EUROPEAN	LIBHIBR_CODEPAGE_WINDOWS_1250
#define LIBHIBR_CODEPAGE_WINDOWS_CYRILLIC		LIBHIBR_CODEPAGE_WINDOWS_1251
#define LIBHIBR_CODEPAGE_WINDOWS_WESTERN_EUROPEAN	LIBHIBR_CODEPAGE_WINDOWS_1252
#define LIBHIBR_CODEPAGE_WINDOWS_GREEK			LIBHIBR_CODEPAGE_WINDOWS_1253
#define LIBHIBR_CODEPAGE_WINDOWS_TURKISH		LIBHIBR_CODEPAGE_WINDOWS_1254
#define LIBHIBR_CODEPAGE_WINDOWS_HEBREW			LIBHIBR_CODEPAGE_WINDOWS_1255
#define LIBHIBR_CODEPAGE_WINDOWS_ARABIC			LIBHIBR_CODEPAGE_WINDOWS_1256
#define LIBHIBR_CODEPAGE_WINDOWS_BALTIC			LIBHIBR_CODEPAGE_WINDOWS_1257
#define LIBHIBR_CODEPAGE_WINDOWS_VIETNAMESE		LIBHIBR_CODEPAGE_WINDOWS_1258

#if defined( __cplusplus )
}
#endif

#endif

