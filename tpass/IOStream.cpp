

#include "IOStream.hpp"
#include "Exception.hpp"
#include "String.hpp"
#include <stdio.h>

/** @fn Flush the output stream
 *
 * Flushes the output stream from a global scope
 */
IOStream& flush( IOStream& __os )
{
    return __os.flush();
}

IOStream::IOStream( )
{
	this->m_stream = 0;
}

IOStream::~IOStream()
{
}


IOStream& IOStream::operator<<( const char* s )
{
    if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    fwrite( s, strlen(s), 1, (FILE*)m_stream );

    return *this;
}

IOStream& IOStream::operator<<( String& s )
{
    if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    if ( s.empty() )
        return *this;

    fwrite( (const char*)s, s.length(), 1, (FILE*)m_stream );

    return *this;
}

IOStream& IOStream::operator << ( signed int si )
{
	if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    fprintf( (FILE*)m_stream, "%d", si );

    return *this;
}

IOStream& IOStream::operator << ( unsigned int ui )
{
	if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    fprintf( (FILE*)m_stream, "%u", ui );

    return *this;
}

IOStream& IOStream::operator << ( float f )
{
	if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    fprintf( (FILE*)m_stream, "%f", f );

    return *this;
}

IOStream& IOStream::flush()
{
	if ( !m_stream )
        throw Exception( "IOStream :: Invalid stream!" );

    fflush( (FILE*)m_stream );

    return *this;
}

IOStream& IOStream::put( char p_char )
{
	if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    fputc( p_char, (FILE*)m_stream );

    return *this;
}

char IOStream::get( )
{
	if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    return fgetc( (FILE*)m_stream );
}

IOStream& IOStream::write( const void* p_block, size_t p_length )
{
	if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    fwrite( p_block, p_length, 1, (FILE*)m_stream );

    return *this;
}

IOStream& IOStream::read( void* p_block, size_t p_length )
{
	if ( !m_stream ) throw Exception( "IOStream :: Invalid stream!" );

    fread( p_block, p_length, 1, (FILE*)m_stream );

    return *this;
}
