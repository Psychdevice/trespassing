
#include "OStream.hpp"
#include "Exception.hpp"
#include <stdio.h>


/*
 * Create standard out and standard error streams, that are linked in OStream.hpp
 */
OStream sout( OTYPE_STDOUT );
OStream serr( OTYPE_STDERR );

/** @fn Flush the output stream
 *
 * Flushes the output stream from a global scope
 */
OStream& flush( OStream& __os )
{
    return __os.flush();
}

OStream::OStream( OStreamTypes p_type, const char* p_name )
{
    switch (p_type)
    {
    case OTYPE_STDOUT:
        m_stream = (void*)stdout;
        break;
    case OTYPE_STDERR:
        m_stream = (void*)stderr;
        break;
    case OTYPE_FILE:
        if ( !p_name )
            throw Exception( "OStream :: Invalid name for output stream!" );
        m_stream = (void*)fopen( p_name, "wb" );
        break;
    }

    if ( !m_stream )
        throw Exception( "OStream :: Failed to open the desired stream!" );
}

OStream::~OStream()
{
    if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );
    if ( m_stream != (void*)stdout && m_stream != (void*)stderr )
    {
        fclose( (FILE*)m_stream );
    }
}


OStream& OStream::operator<<( const char* s )
{
    if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );

    fwrite( s, strlen(s), 1, (FILE*)m_stream );

    return *this;
}

OStream& OStream::operator<<( String& s )
{
    if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );
    if ( s.length() == 0 )
        return *this;

    fwrite( (const char*)s, s.length(), 1, (FILE*)m_stream );

    return *this;
}

OStream& OStream::operator << ( signed int si )
{
	if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );

    fprintf( (FILE*)m_stream, "%d", si );

    return *this;
}

OStream& OStream::operator << ( unsigned int ui )
{
	if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );

    fprintf( (FILE*)m_stream, "%u", ui );

    return *this;
}

OStream& OStream::operator << ( float f )
{
	if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );

    fprintf( (FILE*)m_stream, "%f", f );

    return *this;
}

OStream& OStream::flush()
{
	if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );

    fflush( (FILE*)m_stream );

    return *this;
}

OStream& OStream::put( char c )
{
	if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );

    fputc( c, (FILE*)m_stream );

    return *this;
}

OStream& OStream::write( const char* p_block, size_t p_length )
{
	if ( !m_stream )
        throw Exception( "OStream :: Invalid stream!" );

    fwrite( (const void*)p_block, p_length, 1, (FILE*)m_stream );

    return *this;
}
