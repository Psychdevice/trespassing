
#include "Vector.hpp"


template<class T>
T& Vector<T>::at( size_t p_index ) const
{
	if ( p_index >= m_element_count ) throw Exception( "Vector :: Index is out of bounds!" );
	return this->m_elements[ p_index ];
}

template<class T>
size_t Vector<T>::size() const
{
	return this->m_element_count;
}

template<class T>
void Vector<T>::pop_back( )
{
	if ( m_element_count == 0 )
	{
		return;
	}
	else
	{
		// Allocate the new memory
		T* temp = (T*)malloc( sizeof( T ) * ( m_element_count - 1 ) );

		// MemCpy the existing memory over
		memcpy( temp, m_elements, sizeof( T ) * ( m_element_count - 1 ) );

		// Deconstruct the back element
		m_elements[m_element_count-1].~T();

		// Increment the counter
		m_element_count--;
		// Free the old memory
		free( m_elements );
		// Assign the new memory pointer to our internal pointer
		m_elements = temp;
	}
	return;
}

template<class T>
T& Vector<T>::insert( const T& p_element, size_t p_index )
{
	if ( p_index > m_element_count )
	{
		throw Exception( "Vector :: p_index out of bounds." );
		return p_element;
	}
	else if ( m_element_count == 0 )
	{
		m_elements = (T*)malloc( sizeof( T ) );
		m_element_count++;
		m_elements[0] = p_element;
		return p_element;
	}
	else
	{
		T* temp = (T*)malloc( sizeof(T) * m_element_count + 1 );

		// Copy the left half of the vector into temp
		memcpy( temp, m_elements, sizeof(T) * p_index-1 );
		// Copy the new element in after the left half
		temp[p_index] = p_element;
		// Copy the right half of the vector into temp
		memcpy( &temp[p_index+1], &m_elements[p_index], sizeof(T) * (m_element_count-p_index) );

		free( m_elements );
		m_elements = temp;
		return p_element;
	}
}

template<class T>
void Vector<T>::erase( size_t p_index )
{
	if ( m_element_count == 0 )
	{
		return;
	}
	else if ( p_index >= m_element_count )
	{
		throw Exception( "Vector :: Index is out of bounds!" );
	}
	else
	{
		T* temp = (T*)malloc( sizeof(T) * ( m_element_count - 1 ) );

		m_elements[p_index].~T();

		memcpy( temp, m_elements, sizeof(T) * ( p_index - 1 ) );
		memcpy( &temp[p_index], &m_elements[p_index], sizeof(T) * ( m_element_count - p_index - 1 ) );

		free( m_elements );
		m_elements = temp;
	}
	return;
}

template <class T>
const T* Vector<T>::data()
{
	return const_cast<T*>(this->m_elements);
}
