
#ifndef __fstream_hpp__
#define __fstream_hpp__

#include "IOStream.hpp"


enum FStreamAccess
{
	FACCESS_READ		= 0,
	FACCESS_WRITE		= 1,
	FACCESS_BOTH		= 2
};


class String;

class FStream : public IOStream
{
public:

    FStream( const char* p_name, FStreamAccess p_access = FACCESS_BOTH );
    ~FStream();

    void close();


protected:

};


#endif // __fstream_hpp__
