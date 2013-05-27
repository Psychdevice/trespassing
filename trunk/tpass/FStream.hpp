
#ifndef __fstream_hpp__
#define __fstream_hpp__

#include <stdint.h>


enum FStreamAccess
{
	FACCESS_READ		= 0,
	FACCESS_WRITE		= 1,
	FACCESS_BOTH		= 2
};


class String;

/** @class FStream
 * @brief File Stream
 *
 * Custom implementation of a file stream.
 */
class FStream
{
public:

    FStream( const char* p_name, FStreamAccess p_access = FACCESS_BOTH );
    ~FStream();

	// -- TEXT streaming
    FStream& operator << ( String& s );
    FStream& operator << ( const char* s );
    FStream& operator << ( unsigned int ui );
    FStream& operator << ( signed int si );
    FStream& operator << ( float f );
    FStream& operator << ( FStream& (*__pf) (FStream&) ) { return __pf(*this); }

	/** @brief Flush the stream
	 */
    FStream& flush();

	// -- BINARY streaming
    /** @brief Put a character into the stream
	 */
    char put( );

    /** @brief Get a character from the stream
	 */
    char get( );

    /** @brief Write raw data from the stream
	 */
    size_t write( const void* p_block, size_t p_length );
    /** @brief Read raw data from the stream
	 */
    size_t read( const void* p_block, size_t p_length );

protected:

    void*   m_stream;

};


#endif // __fstream_hpp__
