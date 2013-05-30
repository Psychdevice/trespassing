
#include "FStream.hpp"
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
