
#ifndef __ostream_hpp__
#define __ostream_hpp__

#include "String.hpp"
#include <stdint.h>

enum OStreamTypes
{
    OTYPE_STDOUT        = 0,
    OTYPE_STDERR        = 1,
    OTYPE_FILE          = 2
};

/** @class OStream
 * @brief Output Stream
 *
 * Custom implementation of an output stream to the standard interfaces or files.
 */
class OStream
{
public:

    OStream( OStreamTypes p_type = OTYPE_STDOUT, const char* p_name = 0 );
    ~OStream();

    OStream& operator << ( String& s );
    OStream& operator << ( const char* s );
    OStream& operator << ( unsigned int ui );
    OStream& operator << ( signed int si );
    OStream& operator << ( float f );
    OStream& operator << ( OStream& (*__pf) (OStream&) ) { return __pf(*this); }

	/** @brief Flush the stream
	 */
    OStream& flush();
    /** @brief Put a character into the stream
	 */
    OStream& put( char c );
    /** @brief Write raw data into the stream
	 */
    OStream& write( const char* p_block, size_t p_length );

protected:

    void*   m_stream;

};


///////////////////////////////////////////////////////////
// Global Scope functions
OStream& flush( OStream& );

inline OStream& endl( OStream& __os )
{
    return flush( __os.write( "\r\n", 2 ) );
}


///////////////////////////////////////////////////////////
// Linked objects
extern OStream sout;
extern OStream serr;

#endif // __iostream_hpp__
