
#ifndef __types_h__
#define __types_h__

//////////////////////////////////////////////////////////////////
// Standard type includes to define types and related
// functions/macros
//////////////////////////////////////////////////////////////////

#include <stdint.h>

//////////////////////////////////////////////////////////////////
// ANSI / UNICODE definitions and inclusions
//////////////////////////////////////////////////////////////////

#if defined( UNICODE ) || defined( _UNICODE )
#	include <wchar.h>
// Type define the char_t name as 'wchar_t' for UNICODE streams
	typedef wchar_t     char_t;
// Make a macro that points to the UNICODE wcslen() function
#	define __string_length wcslen
// Define how many characters are possible with the char_t
#	define char_t_count	0xFFFF
#else
// Define ANSI just for the sake of completion and standards
#	define ANSI 1
#	define _ANSI 1
// Type define the char_t name as 'char' for ANSI streams
	typedef char        char_t;
// Make a macro that points to the ANSI strlen() function
#	define __string_length strlen
// Define how many characters are possible with the char_t
#	define char_t_count	0xFF
#endif

#endif // __types_h__
