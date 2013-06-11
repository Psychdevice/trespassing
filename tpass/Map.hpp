
#ifndef __map_hpp__
#define __map_hpp__

#include "Exception.hpp"

template <class A, class B>
class Pair
{
public:

	Pair(){}
	Pair( const A& a, const B& b ) :
		first( a ),
		second( b )
	{
	}
	~Pair(){}

	A first;
	B second;
};

template <typename key_type, class val_type>
class Map
{
	// TODO (Rexhunter99#1#): Finish implementing Map<>
	// NOTE (Rexhunter99#): Do not use Map<>
public:

	Map() :
		first( 0 ),
		last( 0 )
	{
	}
	~Map()
	{
		this->clear();
	}

	val_type& operator [] ( const key_type p_key )
	{
		node_t* ptr = this->first;
		while ( ptr )
		{
			if ( ptr->key == p_key )
				return ptr->value;
			ptr = ptr->next;
		}

		if ( !ptr ) throw Exception( "Map [] :: Failed to find the desired key!" );
	}

	void add( key_type K, val_type V )
	{
		if ( !this->last )
		{
			this->first = new node_t( K, V );
			this->last = this->first;
		}
		else
		{
			this->last->next = new node_t( K, V, this->last, 0 );
			this->last = this->last->next;
		}
	}

	void clear()
	{
		node_t* ptr = this->first;
		while ( ptr )
		{
			node_t* next = ptr->next;

			delete ptr;

			ptr = next;
		}
		this->first = 0;
		this->last = 0;
	}

private:

	class node_t
	{
	public:
		node_t*			prev;
		key_type		key;
		val_type		value;
		node_t*			next;

		node_t( key_type K, val_type V, node_t* P = 0, node_t* N = 0 )
		{
			prev = 0;
			next = 0;
			key = K;
			value = V;
		}
	};

	node_t*		first;
	node_t*		last;
};

#endif // __map_hpp__
