
#ifndef __string_hpp__
#define __string_hpp__

#include "Exception.hpp"
#include "Types.h"
#include <stdlib.h>
#include <string.h>

//////////////////////////////////////////////////////////////////
// Forward declarations
// [ NOTE ] Do this to avoid including key headers throughout
// the source-code, willy nilly.  Helps de-bloat our work.
//////////////////////////////////////////////////////////////////

template < class T > class Array;

/** @class String
 * @brief String container object, stores an array of n( length+1 ) characters
 */
class String
{
public:

	/** @brief Default constructor, initialises an empty string
     */
    String() :
        m_element_count(0),
        m_elements(0),
        m_token(0)
    {
		m_elements = 0;
		m_element_count = 0;
    }

	/** @brief Copy C-String constructor, copies p_string's contents,
     * @param p_string
     */
    String( const char_t* p_string ) :
        m_element_count(0),
        m_elements(0),
        m_token(0)
    {
        if ( __string_length( p_string ) > 0 )
        {
            this->m_element_count = __string_length( p_string ) + 1;
            this->m_elements = (char_t*)malloc( sizeof(char_t) * this->m_element_count );
            if ( !this->m_elements ) throw Exception( "String :: Failed to allocate memory for the string!" );
            memcpy( this->m_elements, p_string, sizeof(char_t) * this->m_element_count );
        }
    }

	/** @brief Copy String constructor, copies p_string's contents
     * @param p_string
     */
    String( const String& p_string ) :
        m_element_count(0),
        m_elements(0),
        m_token(0)
    {
        if ( p_string.m_element_count > 0 )
        {
            this->m_elements = (char_t*)malloc( sizeof(char_t) * p_string.m_element_count );
            this->m_element_count = p_string.m_element_count;
            memcpy( this->m_elements, p_string.m_elements, sizeof(char_t) * p_string.m_element_count );
        }
    }

    ~String();

    // -- Equality Operators
    bool operator == ( const String& p_string ) const;

    // -- Unequality Operators
    bool operator != ( const String& p_string ) const;

    String& operator = ( const String& p_string );

	// -- Assignment of C-Style string
    String& operator = ( const char_t* p_string );
    String& operator + ( const char_t* p_string );
    String& operator + ( const String& p_string );
    void operator += ( const char_t* p_string );
    void operator += ( const String& p_string );
    void operator += ( char_t p_char );
    char_t operator [] ( size_t i ) const;

    // -- Dereference Operator(s)
    operator const char_t* () const;
    operator char_t* () const;
    operator bool () const;

	/** @brief Returns the character at i in the string
     *
     * @return char_t
     *
     */
    char_t at( size_t i ) const;

	/** @brief Returns the length of the string, not including NULL terminator
     *
     * @return size_t
     *
     */
    size_t length() const;

    /** @brief Returns true if the string is empty, false if it contains data
     *
     * @return bool
     *
     */
    bool empty() const;

	/** @brief Copy a sub-string starting at p_start and ending at p_end, inclusive of both.
     *
     * @param p_start	The beginning index
     * @param p_end		The ending index
     * @return String
     *
     */
    String substr( size_t p_start, size_t p_end );

	/** @brief A sequence of calls to this function split this into tokens, which are sequences of contiguous characters separated by any of the characters that are part of p_delimiters.
     *
     * @param p_delimiters	A list of character delimiters
     * @return String
     *
     */
	String token( const char_t* p_delimiters );

	/** @brief Splits the string into an array of sub-strings that were separated by characters in p_delimiters
     *
     * @param p_delimiters	A list of character delimiters
     * @return Array<String>
     *
     */
    Array<String> split( const char_t* p_delimiters );

protected:

    size_t		m_element_count;
    char_t*		m_elements;
    size_t		m_token;

private:

	void __clear();

};

#endif // __string_hpp__
