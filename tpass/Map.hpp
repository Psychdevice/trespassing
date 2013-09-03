
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

		if ( !ptr ) throw Exception( "Map [] :: Failed to find the desired key!\nnewline1\nnewline2\nnewline3\nnewline4" );

		return val_default;
	}

	void append( key_type K, val_type V )
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

	void remove( key_type K )
	{
		// Single element scenario
		if ( this->first == this->last && this->first->key == K )
		{
			delete this->first;
			this->last = this->first = NULL;
			return;
		}

		node_t* ptr = this->first->next;

		while ( ptr )
		{
			if ( ptr->key == K )
			{
				if ( ptr->next == NULL )
				{
					this->last = ptr->prev;
					ptr->prev->next = NULL;
				}
				else
				{
					// -- Make the previous node point to the next node instead
					ptr->prev->next = ptr->next;
					// -- Make the next node point to the previous node instead
					ptr->next->prev = ptr->prev;
				}
				// -- Free the node from memory
				delete ptr;
				// -- Break the loop, we're done here.
				break;
			}
			ptr = ptr->next;
		}
	}

	val_type& find( const key_type K )
	{
		node_t* ptr = this->first;

		// -- Recursively iterate through the linked list of nodes
		while ( ptr )
		{
			if ( ptr->key == K )
				return ptr->value;
			ptr = ptr->next;
		}

		// -- It doesn't exist, for safeties sake return a default value
		return val_default;
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
			prev = P;
			next = N;
			key = K;
			value = V;
		}
	};

	node_t*		first;
	node_t*		last;

	val_type val_default;
};

#endif // __map_hpp__
