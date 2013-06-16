

#ifndef __vector_hpp__
#define __vector_hpp__

#include "Exception.hpp"
#include <new>
#include <stdlib.h>
#include <string.h>


template < class T > class Array;


/** @class Vector<T>
 * @brief A container object that acts as a resizable C-Array with memory management
 */
template <class T>
class Vector
{
public:

	/** @brief Initialise an empty (NULL) vector
	 */
	Vector( ) :
        m_element_count(0),
        m_elements(0)
    {
    }

	/** @brief Initialise an empty vector of p_element_count elements.
	 * @param p_element_count The number of desired initial elements.
	 */
    Vector( size_t p_element_count ) :
        m_element_count(0),
        m_elements(0)
    {
        if ( p_element_count == 0 ) throw Exception( "Vector :: Invalid initial size, cannot initialse a Vector to 0 elements!" );

        this->m_element_count = p_element_count;
        this->m_elements = (T*)malloc( sizeof( T ) * p_element_count );

        for ( size_t i=0; i<m_element_count; i++ )
		{
			new (&this->m_elements[i]) T();
		}
        // Not sure I like using memset...
        //memset( m_elements, 0, sizeof(T) * m_element_count );
    }

	/** @brief Copy p_vector
	 * @param p_vector The Vector to copy
	 */
    Vector( const Vector<T>& p_vector ) :
        m_element_count(0),
        m_elements(0)
    {
        m_element_count = p_vector.m_element_count;
        m_elements = (T*)malloc( sizeof( T ) * m_element_count );

		// Don't memcpy, rely on the copy constructor.
        for ( size_t i=0; i<m_element_count; i++ )
		{
			new (&m_elements[ i ]) T( p_vector.m_elements[i] );
		}
    }

	/** @brief Copy Array<T> to Vector<T>
	 * @param p_array The Array<T> to copy
	 */
	Vector( const Array<T>& p_array ) :
        m_element_count( 0 ),
        m_elements(0)
	{
		m_element_count = p_array.size();
		m_elements = (T*)malloc( sizeof( T ) * m_element_count );

		// Assign the array elements over to the vector to avoid copying pointers
		for ( size_t i=0; i<p_array.size(); i++ )
		{
			new (&m_elements[i]) T(p_array[i]);
		}
	}

	/** @brief Copy a C-Array as the initial data for Vector<T>
	 */
	Vector( const T* p_array, size_t p_size ) :
        m_element_count( p_size ),
        m_elements(0)
	{
		m_elements = (T*)malloc( sizeof( T ) * m_element_count );

		// Assign the array elements over to the vector to avoid copying pointers
		for ( size_t i=0; i<p_size; i++ )
		{
			new (&m_elements[i]) T( p_array[i] );
		}
	}

    ~Vector()
    {
		this->clear();
	}

    // Equality
    bool operator == ( const Vector<T>& p_array )
    {
        if ( this->m_element_count != p_array.m_element_count )
        {
            return false;
        }

        if ( memcmp( this->m_elements, p_array.m_elements, sizeof(T) * this->m_element_count ) )
        {
            return false; // memcmp failed, so they are not the same
        }

		return true;
    }

    bool operator != ( const Vector& p_array )
    {
        if ( this->m_element_count != p_array.m_element_count )
        {
            return true;
        }

        if ( memcmp( this->m_elements, p_array.m_elements, sizeof(T) * this->m_element_count ) )
        {
            return true; // memcmp failed, so they are not the same
        }

        return false;
    }

    inline operator bool ()
    {
    	return ( m_element_count > 0 );
    }

    // Assignment
    Vector<T>& operator = ( const Vector<T>& p_vector )
    {
        m_element_count = p_vector.m_element_count;
        m_elements = (T*)malloc( sizeof( T ) * m_element_count );

		// Don't memcpy, rely on the copy constructor.
        for ( size_t i=0; i<m_element_count; i++ )
		{
			T* ptr = &m_elements[ i ];
			new (ptr) T( p_vector.m_elements[i] );
		}

        return *this;
    }

    // Vector assignment
    inline T& operator [] ( size_t p_index ) const
    {
    	if ( p_index >= m_element_count ) throw Exception( "Vector :: [] operator out of bounds" );
        return this->m_elements[ p_index ];
    }

    /**
	 * @brief Get the element at index p_index
	 * @param p_index The index of the element to retrieve
	 * @return T&
	 */
    T& at( size_t p_index ) const;

	/**
	 * @brief Return the number of elements
	 * @return size_t
	 * Return the number of elements used in the vector as an integer
	 */
    size_t size() const;

	/**
	 * @brief Push an element onto the back of the vector
	 * @param p_element
	 * @return T&
	 * Push an element onto the back of the vector, return a reference to this
	 */
    const T& push_back( const T& p_element )
	{
		if ( m_element_count == 0 )
		{
			m_elements = (T*)malloc( sizeof( T ) );
			m_element_count++;
			new (&m_elements[0]) T( p_element );
			return p_element;
		}
		else
		{
			// Allocate the new memory
			T* temp = (T*)malloc( sizeof( T ) * ( m_element_count + 1 ) );

			// MemCpy the existing memory over
			memcpy( temp, m_elements, sizeof( T ) * m_element_count );

			// Get the pointer...
			T* ptr = &temp[ m_element_count ];
			// Placement new the fuck out of it
			new (ptr) T( p_element );

			// Increment the counter
			m_element_count++;
			// Free the old memory
			free( m_elements );
			// Assign the new memory pointer to our internal pointer
			m_elements = temp;

			return m_elements[m_element_count-1];
		}
	}

    /**
	 * @brief Push an element onto the back of the vector
	 * @param p_element
	 * @return Vector<T>&
	 * Push an element onto the back of the vector, return a reference to this
	 */
    void pop_back( );

    /**
	 * @brief Insert an element into the vector
	 * @param p_element
	 * @param p_index
	 * @return Vector<T>&
	 */
    T& insert( const T& p_element, size_t p_index );

    /**
	 * @brief Erase an element from the vector
	 * @param p_index
	 */
    void erase( size_t p_index );

    /**
	 * @brief Erase an element from the vector
	 * @param p_start The beginning index
	 * @param p_end The ending index inclusive
	 */
    void erase( size_t p_start, size_t p_end );

    /**
	 * @brief Clear the vector
	 *
	 * Clear the vector of elements back to empty, free all memory and deconstruct all elements in the process.
	 */
	void clear()
	{
		if ( this->m_elements )
		{
			// Deconstruct all the elements
			for ( size_t i=0; i<this->m_element_count; i++ )
			{
				this->m_elements[i].~T();
			}
			// Free the memory
			free( this->m_elements );
			// Reset internals
			this->m_element_count = 0;
			this->m_elements = 0;
		}
	}

	/**
	 * @brief Get a pointer to the data inside the vector
	 * @return const T*
	 */
    const T* data( );

    class iterator
    {
	public:

		//operator T& ()

	protected:

    };

protected:

	friend class Array<T>;
    size_t      m_element_count;
    T*          m_elements;

private:

};

#endif // __vector_hpp__
