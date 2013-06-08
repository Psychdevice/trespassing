
#include "String.hpp"
#include "Array.hpp"

String::~String()
{
    this->__clear();
}

// -- Equality Operators
bool String::operator == ( const String& p_string ) const
{
    // -- If the internal count storage is not equal then we can return that the strings are not equal
    if ( this->m_element_count != p_string.m_element_count )
    {
        return false;
    }

    // -- Do a memory comparison of the two strings, if it returns 0 then return true, otherwise they are not the same
    if ( memcmp( this->m_elements, p_string.m_elements, sizeof( char_t ) * this->m_element_count ) )
    {
        return false;
    }

    return true;
}

// -- Unequality Operators
bool String::operator != ( const String& p_string ) const
{
    // -- If the internal count storage is not equal then we can return that the strings are not equal
    if ( this->m_element_count != p_string.m_element_count )
    {
        return true;
    }

    // -- Do a memory comparison of the two strings, if it returns 0 then return true, otherwise they are not the same
    if ( memcmp( this->m_elements, p_string.m_elements, sizeof( char_t ) * this->m_element_count ) )
    {
        return true;
    }

    return false;
}

String& String::operator = ( const String& p_string )
{
    // -- Ignore self assignment
    if ( this->m_elements == p_string.m_elements ) return *this;


    if ( p_string.m_element_count != 0 )
    {
        // Free the data if it exists already (move to a function)
        this->__clear();

        // Set the number of elements
        this->m_element_count = p_string.m_element_count;

        // Allocate the memory
        this->m_elements = (char_t*)malloc( sizeof(char_t) * this->m_element_count );

        // Check if malloc failed and throw if it did
        if ( !this->m_elements ) throw Exception( "String :: Failed to allocate memory for the string!" );

        // Copy the string data over
        memcpy( this->m_elements, p_string.m_elements, sizeof( char_t ) * this->m_element_count );
    }
    else
	{
		// Free the data if it exists already (move to a function)
        this->__clear();
	}

    return *this;
}

// -- Assignment of C-Style string
String& String::operator = ( const char_t* p_string )
{
    // -- Ignore self assigment
    if ( this->m_elements == p_string ) return *this;

    if ( p_string != 0 )
    {
        // Free the data if it exists already
        this->__clear();

        // Set the number of elements
        this->m_element_count = __string_length( p_string ) + 1;

        // Allocate memory for the string data
        this->m_elements = (char_t*)malloc( sizeof(char_t) * this->m_element_count );

        // Check of malloc failed
        if ( !this->m_elements ) throw Exception( "String :: Failed to allocate memory for the string!" );

        // Copy the data over
        memcpy( this->m_elements, p_string, sizeof( char_t ) * this->m_element_count );
    }

    return *this;
}

String& String::operator + ( const char_t* p_string )
{
	*this += p_string;
    return *this;
}

String& String::operator + ( const String& p_string )
{
	*this += p_string;
    return *this;
}

void String::operator += ( const char_t* p_string )
{
    // -- Check if p_string is valid
    if ( p_string == 0 )
    {
        return;
    }

    // -- Store the length ( Memory VS Speed, I prefer speed for PCs )
    size_t len = __string_length( p_string ) + 1;

    // -- If we are NULL, we just copy the p_string
    if ( this->m_elements == 0 )
    {
        this->m_element_count = __string_length( p_string ) + 1;

        this->m_elements = (char_t*)malloc( sizeof(char_t) * this->m_element_count );

        if ( !this->m_elements ) throw Exception( "String :: Failed to allocate memory for the string!" );

        memcpy( this->m_elements, p_string, sizeof(char_t) * this->m_element_count );
    }
    else // -- Otherwise we need to concatenate p_string to ourself
    {
        // -- Store a copy of the data so we don't lose it
        char_t *temp = (char_t*)malloc( sizeof(char_t) * ( this->m_element_count + len - 1 ) );

        if ( !temp ) throw Exception( "String :: Failed to allocate memory for the string!" );

        memcpy( temp, this->m_elements, sizeof(char_t) * this->m_element_count );

        // -- Free the existing data then reassign the pointer
        free( this->m_elements );
        this->m_elements = temp;

        memcpy( &this->m_elements[this->m_element_count-1], p_string, sizeof(char_t) * len );

        this->m_element_count += len - 1;
    }

    return;
}

void String::operator += ( const String& p_string )
{
    // -- Check if p_string is valid
    if ( p_string.m_element_count == 0 || !p_string.m_elements )
    {
        return;
    }

    // -- If we are NULL, we just copy the p_string
    if ( this->m_elements == 0 )
    {
        this->m_elements = (char_t*)malloc( sizeof(char_t) * p_string.m_element_count );

        if ( !this->m_elements ) throw Exception( "String :: Failed to allocate memory for the string!" );

        memcpy( this->m_elements, p_string.m_elements, sizeof(char_t) * p_string.m_element_count );

        this->m_element_count = p_string.m_element_count;
    }
    else // -- Otherwise we need to concatenate p_string to ourself
    {
        // -- Store a copy of the data so we don't lose it
        char_t *temp = (char_t*)malloc( sizeof(char_t) * ( this->m_element_count + p_string.m_element_count ) );

        if ( !temp ) throw Exception( "String :: Failed to allocate memory for the string!" );

        memcpy( temp, this->m_elements, sizeof(char_t) * this->m_element_count );

        // -- Free the existing data then reassign the pointer
        free( this->m_elements );
        this->m_elements = temp;

        memcpy( this->m_elements + (this->m_element_count-1), p_string.m_elements, sizeof(char_t) * p_string.m_element_count );

        m_element_count += p_string.m_element_count - 1;
    }

    return;
}

void String::operator += ( char_t p_char )
{
    // -- Check if p_char is valid
    if ( p_char == 0 )
    {
        return;
    }

    // -- If we are NULL, we just copy the p_string
    if ( this->m_elements == 0 )
    {
        this->m_element_count = 2;

        this->m_elements = (char_t*)malloc( sizeof(char_t) * this->m_element_count );

        if ( !this->m_elements ) throw Exception( "String :: Failed to allocate memory for the string!" );

        this->m_elements[0] = p_char;
        this->m_elements[1] = 0;
    }
    else // -- Otherwise we need to concatenate p_char to ourself
    {
        // -- Store a copy of the data so we don't lose it
        char_t *temp = (char_t*)malloc( sizeof(char_t) * ( this->m_element_count + 1 ) );

        if ( !temp ) throw Exception( "String :: Failed to allocate memory for the string!" );

        memcpy( temp, this->m_elements, sizeof(char_t) * this->m_element_count );

        // -- Free the existing data then reassign the pointer
        free( this->m_elements );
        this->m_elements = temp;

        memcpy( &this->m_elements[this->m_element_count-1], &p_char, 1 );

        this->m_element_count += 1;
    }

    return;
}

char_t String::operator [] ( size_t i ) const
{
    if ( this->m_element_count == 0 ) throw Exception( "String :: Access Violation, attempted to read out of the string boundary." ); // Avoid access violation ( throw exception may be better )
    return this->m_elements[ i ];
}

String::operator const char_t* () const
{
    return this->m_elements;
}
String::operator char_t* () const
{
    return this->m_elements;
}

String::operator bool () const
{
    return ( this->m_element_count > 0 );
}

char_t String::at( size_t i ) const
{
    if ( this->m_element_count == 0 ) throw Exception( "String :: Access Violation, attempted to read out of the string boundary." ); // Avoid access violation ( throw exception may be better )
    return this->m_elements[ i ];
}

size_t String::length() const
{
    return this->m_element_count - 1;
}

String String::substr( size_t p_start, size_t p_length )
{
    String res = "";

    for ( size_t i=p_start; i<p_start+p_length; i++ )
    {
        res += this->at( i );
    }

    return res;
}

String String::token( const char_t* p_delimiters )
{
	String res;
	size_t len = strlen( p_delimiters );

	if ( this->m_token == 0xFFFFFFFF )
	{
		this->m_token = 0;
		return res;
	}

	for ( uint32_t i=this->m_token; i<=this->length()+1; i++ )
    {
        char_t v = this->at(i);

		if ( v == 0 )
		{
			this->m_token = 0xFFFFFFFF;
			return res;
		}

        for ( uint32_t c=0; c<=len; c++ )
        {
            if ( v == p_delimiters[c] )
			{
				this->m_token = i+1;
				return res;
			}
        }

        res += v;
    }

	this->m_token = 0;
	return String();
}

Array<String> String::split( const char_t* p_delimiters )
{
	// TODO (Rexhunter99#1#): Test this function
	// NOTE (Rexhunter99#): String::split() seems to work, requires stress testing though.
	String __temp = *this;
	size_t __count = 0;

    while ( true )
	{
		String tok = __temp.token( p_delimiters );

		if ( tok )
		{
			__count++;
		}
		else
		{
			break;
		}
	}

    Array<String> res( __count );
	__temp = *this;

	for ( size_t i=0; i<__count; i++ )
	{
		res[i] = __temp.token( p_delimiters );
	}

    return res;
}

bool String::empty() const
{
	return ( this->m_element_count == 0 );
}

void String::__clear()
{
    if ( this->m_elements )
    {
        free( this->m_elements );
        this->m_elements = 0;
        this->m_element_count = 0;
    }
}

size_t String::find( const char* p_string, size_t p_start )
{
	if ( this->clear() ) return String::npos;
	size_t p_slen = strlen( p_string );

	if ( )

	return -1;
}
