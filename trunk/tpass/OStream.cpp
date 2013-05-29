
#include "OStream.hpp"
#include "Exception.hpp"
#include <stdio.h>


/*
 * Create standard out and standard error streams, that are linked in OStream.hpp
 */
OStream sout( "stdout" );
OStream serr( "stderr" );


OStream::OStream( const char* p_name )
{
	m_stream = (void*)NULL;

	if ( !strcmp( p_name, "stdout" ) )
	{
		m_stream = (void*)stdout;
	}

	if ( !strcmp( p_name, "stderr" ) )
	{
		m_stream = (void*)stderr;
	}

    if ( p_name && !m_stream ) throw Exception( "OStream :: Failed to open the desired stream!" );
}

OStream::~OStream()
{
    if ( m_stream != (void*)stdout && m_stream != (void*)stderr )
    {
        fclose( (FILE*)m_stream );
        m_stream = (void*)NULL;
    }
}
