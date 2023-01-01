/*
 * The error code definitions for libhibr
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

#if !defined( _LIBHIBR_ERROR_H )
#define _LIBHIBR_ERROR_H

#include <libhibr/types.h>

/* External error type definition hides internal structure
 */
typedef intptr_t libhibr_error_t;

/* The error domains
 */
enum LIBHIBR_ERROR_DOMAINS
{
	LIBHIBR_ERROR_DOMAIN_ARGUMENTS			= (int) 'a',
	LIBHIBR_ERROR_DOMAIN_CONVERSION			= (int) 'c',
	LIBHIBR_ERROR_DOMAIN_COMPRESSION		= (int) 'C',
	LIBHIBR_ERROR_DOMAIN_IO				= (int) 'I',
	LIBHIBR_ERROR_DOMAIN_INPUT			= (int) 'i',
	LIBHIBR_ERROR_DOMAIN_MEMORY			= (int) 'm',
	LIBHIBR_ERROR_DOMAIN_OUTPUT			= (int) 'o',
	LIBHIBR_ERROR_DOMAIN_RUNTIME			= (int) 'r'
};

/* The argument error codes
 * to signify errors regarding arguments passed to a function
 */
enum LIBHIBR_ARGUMENT_ERROR
{
	LIBHIBR_ARGUMENT_ERROR_GENERIC			= 0,

	/* The argument contains an invalid value
	 */
	LIBHIBR_ARGUMENT_ERROR_INVALID_VALUE		= 1,

	/* The argument contains a value less than zero
	 */
	LIBHIBR_ARGUMENT_ERROR_VALUE_LESS_THAN_ZERO	= 2,

	/* The argument contains a value zero or less
	 */
	LIBHIBR_ARGUMENT_ERROR_VALUE_ZERO_OR_LESS	= 3,

	/* The argument contains a value that exceeds the maximum
	 * for the specific type
	 */
	LIBHIBR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM	= 4,

	/* The argument contains a value that is too small
	 */
	LIBHIBR_ARGUMENT_ERROR_VALUE_TOO_SMALL		= 5,

	/* The argument contains a value that is too large
	 */
	LIBHIBR_ARGUMENT_ERROR_VALUE_TOO_LARGE		= 6,

	/* The argument contains a value that is out of bounds
	 */
	LIBHIBR_ARGUMENT_ERROR_VALUE_OUT_OF_BOUNDS	= 7,

	/* The argument contains a value that is not supported
	 */
	LIBHIBR_ARGUMENT_ERROR_UNSUPPORTED_VALUE	= 8,

	/* The argument contains a value that conficts with another argument
	 */
	LIBHIBR_ARGUMENT_ERROR_CONFLICTING_VALUE	= 9
};

/* The conversion error codes
 * to signify errors regarding conversions
 */
enum LIBHIBR_CONVERSION_ERROR
{
	LIBHIBR_CONVERSION_ERROR_GENERIC		= 0,

	/* The conversion failed on the input
	 */
	LIBHIBR_CONVERSION_ERROR_INPUT_FAILED		= 1,

	/* The conversion failed on the output
	 */
	LIBHIBR_CONVERSION_ERROR_OUTPUT_FAILED		= 2
};

/* The compression error codes
 * to signify errors regarding compression
 */
enum LIBHIBR_COMPRESSION_ERROR
{
	LIBHIBR_COMPRESSION_ERROR_GENERIC		= 0,

	/* The compression failed
	 */
	LIBHIBR_COMPRESSION_ERROR_COMPRESS_FAILED	= 1,

	/* The decompression failed
	 */
	LIBHIBR_COMPRESSION_ERROR_DECOMPRESS_FAILED	= 2
};

/* The input/output error codes
 * to signify errors regarding input/output
 */
enum LIBHIBR_IO_ERROR
{
	LIBHIBR_IO_ERROR_GENERIC			= 0,

	/* The open failed
	 */
	LIBHIBR_IO_ERROR_OPEN_FAILED			= 1,

	/* The close failed
	 */
	LIBHIBR_IO_ERROR_CLOSE_FAILED			= 2,

	/* The seek failed
	 */
	LIBHIBR_IO_ERROR_SEEK_FAILED			= 3,

	/* The read failed
	 */
	LIBHIBR_IO_ERROR_READ_FAILED			= 4,

	/* The write failed
	 */
	LIBHIBR_IO_ERROR_WRITE_FAILED			= 5,

	/* Access denied
	 */
	LIBHIBR_IO_ERROR_ACCESS_DENIED			= 6,

	/* The resource is invalid i.e. a missing file
	 */
	LIBHIBR_IO_ERROR_INVALID_RESOURCE		= 7,

	/* The ioctl failed
	 */
	LIBHIBR_IO_ERROR_IOCTL_FAILED			= 8,

	/* The unlink failed
	 */
	LIBHIBR_IO_ERROR_UNLINK_FAILED			= 9
};

/* The input error codes
 * to signify errors regarding handing input data
 */
enum LIBHIBR_INPUT_ERROR
{
	LIBHIBR_INPUT_ERROR_GENERIC			= 0,

	/* The input contains invalid data
	 */
	LIBHIBR_INPUT_ERROR_INVALID_DATA		= 1,

	/* The input contains an unsupported signature
	 */
	LIBHIBR_INPUT_ERROR_SIGNATURE_MISMATCH		= 2,

	/* A checksum in the input did not match
	 */
	LIBHIBR_INPUT_ERROR_CHECKSUM_MISMATCH		= 3,

	/* A value in the input did not match a previously
	 * read value or calculated value
	 */
	LIBHIBR_INPUT_ERROR_VALUE_MISMATCH		= 4
};

/* The memory error codes
 * to signify errors regarding memory
 */
enum LIBHIBR_MEMORY_ERROR
{
	LIBHIBR_MEMORY_ERROR_GENERIC			= 0,

	/* There is insufficient memory available
	 */
	LIBHIBR_MEMORY_ERROR_INSUFFICIENT		= 1,

	/* The memory failed to be copied
	 */
	LIBHIBR_MEMORY_ERROR_COPY_FAILED		= 2,

	/* The memory failed to be set
	 */
	LIBHIBR_MEMORY_ERROR_SET_FAILED			= 3
};

/* The output error codes
 */
enum LIBHIBR_OUTPUT_ERROR
{
	LIBHIBR_OUTPUT_ERROR_GENERIC			= 0,

	/* There is insuficient space to write the output
	 */
	LIBHIBR_OUTPUT_ERROR_INSUFFICIENT_SPACE		= 1
};

/* The runtime error codes
 * to signify errors regarding runtime processing
 */
enum LIBHIBR_RUNTIME_ERROR
{
	LIBHIBR_RUNTIME_ERROR_GENERIC			= 0,

	/* The value is missing
	 */
	LIBHIBR_RUNTIME_ERROR_VALUE_MISSING		= 1,

	/* The value was already set
	 */
	LIBHIBR_RUNTIME_ERROR_VALUE_ALREADY_SET		= 2,

	/* The creation and/or initialization of an internal structure failed
	 */
	LIBHIBR_RUNTIME_ERROR_INITIALIZE_FAILED		= 3,

	/* The resize of an internal structure failed
	 */
	LIBHIBR_RUNTIME_ERROR_RESIZE_FAILED		= 4,

	/* The free and/or finalization of an internal structure failed
	 */
	LIBHIBR_RUNTIME_ERROR_FINALIZE_FAILED		= 5,

	/* The value could not be determined
	 */
	LIBHIBR_RUNTIME_ERROR_GET_FAILED		= 6,

	/* The value could not be set
	 */
	LIBHIBR_RUNTIME_ERROR_SET_FAILED		= 7,

	/* The value could not be appended/prepended
	 */
	LIBHIBR_RUNTIME_ERROR_APPEND_FAILED		= 8,

	/* The value could not be copied
	 */
	LIBHIBR_RUNTIME_ERROR_COPY_FAILED		= 9,

	/* The value could not be removed
	 */
	LIBHIBR_RUNTIME_ERROR_REMOVE_FAILED		= 10,

	/* The value could not be printed
	 */
	LIBHIBR_RUNTIME_ERROR_PRINT_FAILED		= 11,

	/* The value was out of bounds
	 */
	LIBHIBR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS	= 12,

	/* The value exceeds the maximum for its specific type
	 */
	LIBHIBR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM	= 13,

	/* The value is unsupported
	 */
	LIBHIBR_RUNTIME_ERROR_UNSUPPORTED_VALUE		= 14,

	/* An abort was requested
	 */
	LIBHIBR_RUNTIME_ERROR_ABORT_REQUESTED		= 15
};

#endif /* !defined( _LIBHIBR_ERROR_H ) */

