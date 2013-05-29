
#ifndef __ostream_hpp__
#define __ostream_hpp__

#include "IOStream.hpp"


/** @class OStream
 * @brief Output Stream
 *
 * Custom implementation of an output stream to the standard interfaces or files.
 */
class OStream : public IOStream
{
public:

    OStream( const char* p_name = 0 );
    ~OStream();

    /*OStream& operator << ( String& s );
    OStream& operator << ( const char* s );
    OStream& operator << ( unsigned int ui );
    OStream& operator << ( signed int si );
    OStream& operator << ( float f );
    OStream& operator << ( OStream& (*__pf) (OStream&) ) { return __pf(*this); }*/

protected:

};


///////////////////////////////////////////////////////////
// Linked objects
extern OStream sout;
extern OStream serr;

#endif // __iostream_hpp__
