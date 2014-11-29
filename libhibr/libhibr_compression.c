/*
 * Compression functions
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

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "libhibr_compression.h"
#include "libhibr_libcerror.h"

/* Decompresses XPRESS compressed-data
 * Returns 1 on success or -1 on error
 */
int libhibr_compression_xpress_decompress(
     const uint8_t *compressed_data,
     size_t compressed_data_size,
     uint8_t *uncompressed_data,
     size_t uncompressed_data_size,
     libcerror_error_t **error )
{
	static char *function                  = "libhibr_compression_xpress_decompress";
	size_t compressed_data_iterator        = 0;
	size_t compression_iterator            = 0;
	size_t compression_shared_byte_index   = 0;
	size_t uncompressed_data_iterator      = 0;
	uint32_t compression_indicator         = 0;
	uint32_t compression_indicator_bitmask = 0;
	uint16_t compression_size              = 0;
	uint16_t compression_tuple             = 0;
	int16_t compression_offset             = 0;

	if( compressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid compressed data.",
		 function );

		return( -1 );
	}
	if( compressed_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid compressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( uncompressed_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid uncompressed data.",
		 function );

		return( -1 );
	}
	if( uncompressed_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid uncompressed data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	compressed_data_iterator = 0;

	while( compressed_data_iterator < compressed_data_size )
	{
                byte_stream_copy_to_uint32_little_endian(
                 &( compressed_data[ compressed_data_iterator ] ),
                 compression_indicator );

		compressed_data_iterator += 4;

		for( compression_indicator_bitmask = 0x80000000UL;
		     compression_indicator_bitmask > 0;
		     compression_indicator_bitmask >>= 1 )
		{
			if( compressed_data_iterator >= compressed_data_size )
			{
				break;
			}
			/* If the indicator bit is 0 the data is uncompressed
			 * or 1 if the data is compressed
			 */
			if( ( compression_indicator & compression_indicator_bitmask ) != 0 )
			{
				if( ( compressed_data_iterator + 1 ) >= compressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: compressed data too small.",
					 function );

					return( -1 );
				}
		                byte_stream_copy_to_uint16_little_endian(
		                 &( compressed_data[ compressed_data_iterator ] ),
		                 compression_tuple );

				compressed_data_iterator += 2;

				/* The compression tuple contains:
				 * 0 - 2	the size
				 * 3 - 15	the offset - 1
				 */
				compression_size   = ( compression_tuple & 0x0007 );
				compression_offset = ( compression_tuple >> 3 ) + 1;

				/* Check for a first level extended size
				 * stored in the 4-bits of a shared extended compression size byte
				 * the size is added to the previous size
				 */
				if( compression_size == 0x07 )
				{
					if( compression_shared_byte_index == 0 )
					{
						if( compressed_data_iterator >= compressed_data_size )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
							 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
							 "%s: compressed data too small.",
							 function );

							return( -1 );
						}
						compression_size += compressed_data[ compressed_data_iterator ] & 0x0f;

						compression_shared_byte_index = compressed_data_iterator++;
					}
					else
					{
						compression_size += compressed_data[ compression_shared_byte_index ] >> 4;

						compression_shared_byte_index = 0;
					}
				}
				/* Check for a second level extended size
				 * stored in the 8-bits of the next byte
				 * the size is added to the previous size
				 */
				if( compression_size == ( 0x07 + 0x0f ) )
				{
					if( compressed_data_iterator >= compressed_data_size )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
						 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
						 "%s: compressed data too small.",
						 function );

						return( -1 );
					}
					compression_size += compressed_data[ compressed_data_iterator++ ];
				}
				/* Check for a third level extended size
				 * stored in the 16-bits of the next two bytes
				 * the previous size is ignored
				 */
				if( compression_size == ( 0x07 + 0x0f + 0xff ) )
				{
					if( ( compressed_data_iterator + 1 ) >= compressed_data_size )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
						 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
						 "%s: compressed data too small.",
						 function );

						return( -1 );
					}
			                byte_stream_copy_to_uint16_little_endian(
			                 &( compressed_data[ compressed_data_iterator ] ),
			                 compression_size );
		
					compressed_data_iterator += 2;
				}
				/* The size value is stored as
				 * size - 3
				 */
				if( compression_size > 0xfffb )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
					 "%s: compression size value out of bounds.",
					 function );

					return( -1 );
				}
				compression_size += 3;

				compression_iterator = uncompressed_data_iterator - compression_offset;

				while( compression_size > 0 )
				{
					if( compression_iterator > uncompressed_data_iterator )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
						 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
						 "%s: compression iterator: %" PRIzd " out of bounds: %" PRIzd ".",
						 function,
						 compression_iterator,
						 uncompressed_data_iterator );

						return( -1 );
					}
					if( uncompressed_data_iterator > uncompressed_data_size )
					{
						libcerror_error_set(
						 error,
						 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
						 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
						 "%s: uncompressed data too small.",
						 function );

						return( -1 );
					}
					uncompressed_data[ uncompressed_data_iterator++ ] = uncompressed_data[ compression_iterator++ ];

					compression_size--;
				}
			}
			else
			{
				if( compressed_data_iterator >= compressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: compressed data too small.",
					 function );

					return( -1 );
				}
				if( uncompressed_data_iterator > uncompressed_data_size )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
					 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
					 "%s: uncompressed data too small.",
					 function );

					return( -1 );
				}
				uncompressed_data[ uncompressed_data_iterator++ ] = compressed_data[ compressed_data_iterator++ ];
			}
		}
	}
	return( 1 );
}

