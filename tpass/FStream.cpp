
#include "FStream.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include <stdio.h>

FStream::FStream( const char* p_name, FStreamAccess p_access )
{
	switch ( p_access )
	{
	case FACCESS_READ:
		{
			m_stream = (void*)fopen( p_name, "rb" );
		}
		break;

	case FACCESS_WRITE:
		{
			m_stream = (void*)fopen( p_name, "wb" );
		}
		break;

	case FACCESS_BOTH:
		{
			m_stream = (void*)fopen( p_name, "rb+" );
		}
		break;

	default:
		{
			throw Exception( "FStream :: Incorrect access flag was given!" );
		}
		break;
	}
}

FStream::~FStream()
{
	if ( m_stream )
	{
		fclose( (FILE*)m_stream );
		m_stream = (void*)NULL;
	}
}

void FStream::close(  )
{
	if ( m_stream )
	{
		fclose( (FILE*)m_stream );
		m_stream = (void*)NULL;
	}
}

String FStream::readln()
{
	if ( !m_stream ) throw Exception( "FStream :: Invalid stream in readln()\r\nThe stream is invalid, thus it may not even be open!" );
	String res;

	while (true)
	{
		if ( feof( (FILE*)m_stream ) ) break;
		char c = fgetc( (FILE*)m_stream );
		if ( c == '\r' ) continue; // CR Used in Windows
		if ( c == '\n' ) break;	// LF Linux/Windows/Mac EOL
		if ( c == '\0' ) break;	// Linux/C-String EOL
		res += c;
	}

	return res;
}

bool FStream::eos()
{
	if ( !m_stream ) throw Exception( "FStream :: Invalid stream in readln()\r\nThe stream is invalid, thus it may not even be open!" );

	if ( feof( (FILE*)m_stream ) )
	return true;
	else
	return false;
}
