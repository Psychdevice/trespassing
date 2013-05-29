
#ifndef __iostream_hpp__
#define __iostream_hpp__

#include <stddef.h>
#include <stdint.h>

class String;


class IOStream
{
public:

	IOStream();
    ~IOStream();

	// -- TEXT streaming
    virtual IOStream& operator << ( String& s );
    virtual IOStream& operator << ( const char* s );
    virtual IOStream& operator << ( unsigned int ui );
    virtual IOStream& operator << ( signed int si );
    virtual IOStream& operator << ( float f );
    IOStream& operator << ( IOStream& (*__pf) (IOStream&) ) { return __pf(*this); }

	/** @brief Flush the stream
	 */
    IOStream& flush();

	// -- BINARY streaming
    /** @brief Put a character into the stream
	 */
    IOStream& put( char p_char );

    /** @brief Get a character from the stream
	 */
    char get( );

    /** @brief Write raw data from the stream
	 */
    IOStream& write( const void* p_block, size_t p_length );
    /** @brief Read raw data from the stream
	 */
    IOStream& read( void* p_block, size_t p_length );

protected:

    void*   m_stream;

};


///////////////////////////////////////////////////////////
// Global Scope functions
IOStream& flush( IOStream& );

inline IOStream& endl( IOStream& __ios ) { return flush( __ios.write( "\r\n", 2 ) ); }

#endif // __iostream_hpp__
