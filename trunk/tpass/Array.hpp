
#ifndef __array_hpp__
#define __array_hpp__

#include "Exception.hpp"
#include <new>
#include <stdlib.h>
#include <string.h>


template < class T > class Vector;


/** @class Array
 * @brief A container object that acts as a C-Array with memory management
 */
template < class T > class Array
{
public:

	/** @brief Initialise to p_element_count size
	 * @param p_element_count The number of elements
	 */
    Array( size_t p_element_count ) :
        m_element_count(0),
        m_elements(0)
    {
        if ( p_element_count == 0 ) throw Exception( "Array :: Invalid initial size, cannot initialse an Array to 0 elements!" );

        m_element_count = p_element_count;
        m_elements = (T*)malloc( sizeof( T ) * p_element_count );

        for ( size_t i=0; i<m_element_count; i++ )
		{
			new (&m_elements[ i ]) T();
		}
    }

	/** @brief Copy p_array to this
	 * @param p_array The array we wish to copy
	 */
    Array( const Array& p_array ) :
        m_element_count(0),
        m_elements(0)
    {
        this->m_element_count = p_array.m_element_count;
        this->m_elements = (T*)malloc( sizeof( T ) * p_array.m_element_count );
        for ( size_t i=0; i<p_array.size(); i++ )
		{
			new (&m_elements[ i ]) T(p_array[ i ]);
		}
    }

	/** @brief Copy C-Array contents
	 * @param p_array The C-Array
	 * @param p_count The number of elements in p_array
	 */
	Array( const T* p_array, size_t p_count ) :
        m_element_count( p_count ),
        m_elements(0)
	{
		this->m_elements = (T*)malloc( sizeof( T ) * this->m_element_count );
		for ( size_t i=0; i<p_count; i++ )
		{
			// -- copy the elements over from the C-Array to the internal array
			new (&this->m_elements[i]) T(p_array[ i ]);
		}
	}

    ~Array()
    {
        this->__clear();
    }

    // Equality
    bool operator == ( const Array& p_array )
    {
        if ( this->m_element_count != p_array.m_element_count )
        {
            return false;
        }

        if ( memcmp( this->m_elements, p_array.m_elements, sizeof(T) * this->m_element_count ) )
        {
            return false; // memcmp failed, so they are not the same
        }
        else
        {
            return true;
        }
    }

    bool operator != ( const Array& p_array )
    {
        if ( this->m_element_count != p_array.m_element_count )
        {
            return true;
        }

        if ( memcmp( this->m_elements, p_array.m_elements, sizeof(T) * this->m_element_count ) )
        {
            return true; // memcmp failed, so they are not the same
        }
        else
        {
            return false;
        }
    }

    // Assignment
    inline Array& operator = ( const Array& p_array )
    {

        if ( this->m_element_count >= p_array.m_element_count )
        {
            // What... in the fuck was I thinking?
            //memcpy( this->m_elements, p_array.m_elements, sizeof( T ) * p_array.m_element_count );

            // Better, much better!
            for ( size_t i=0; i<p_array.m_element_count; i++ )
			{
				new (&m_elements[ i ]) T( p_array[ i ]);
			}
        }

        return *this;
    }

    // Array assignment
    inline T& operator [] ( size_t p_index ) const
    {
    	if ( p_index >= m_element_count ) throw Exception( "Array :: [] operator out of bounds" );
        return this->m_elements[ p_index ];
    }

	/** @brief Return the number of elements
	 * @return size_t
	 */
    inline size_t size() const
    {
    	return m_element_count;
    }

	/** @brief Return a pointer to the data chunk
	 * @return const T*
	 */
    inline const T* data() const
    {
    	return m_elements;
    }

protected:

	friend class Vector<T>;
	/** @var The number of elements in the array
	 */
    size_t      m_element_count;
    /** @var The element data chunk
	 */
    T*          m_elements;

private:

	/*
	* Clear the array, deconstruct all the elements before freeing the data (C++ Standards)
	*/
	void __clear()
	{
		if ( this->m_elements )
        {
        	for ( size_t i=0; i<this->m_element_count; i++ )
        	{
        		this->m_elements[i].~T();
        	}
            free( this->m_elements );
            this->m_element_count = 0;
            this->m_elements = 0;
        }
	}

};

#endif // __array_hpp__
