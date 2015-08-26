# Introduction #
Rexhunter99's Standard Template Library, is a custom built STL library specifically made for game engines, meant to be high performance, thus free of bloat and only includes things needed by a game engine.


# Components #
Current available types are:
  * Array< value\_type >
  * Vector< value\_type >
  * String - _Was templated for character types but is controlled by UNICODE definitions now_
  * [`Map< key\_type, value\_type >`](RSTL#Map_<K,V>.md)
  * OStream : IOStream
  * FStream : IOStream
  * Exception - _Evolving, current has provisions for various necessities_

## Array`<T>` ##
Constructors
  * Array( size\_t p\_size );
  * Array( const Array`<T>&` p\_array );
  * Array( const T`*` p\_array, size\_t p\_size );
Methods:
  * T`*` data();
  * size\_t size();
Proposed:
  * Array( const Vector`<T>&` p\_vector );
  * size\_t find( T p\_find );

## Vector`<T>` ##
Constructors:
  * Vector();
  * Vector( size\_t p\_size );
  * Vector( const Vector`<T>&` p\_vector );
  * Vector( const Array`<T>&` p\_array );
  * Vector( const T`*` p\_array, size\_t p\_size );
Methods:
  * void clear();
  * T`&` at( size\_t p\_index );
  * size\_t size();
  * T`*` data();
  * T`&` push\_back( const T`&` p\_element );
  * void pop\_back( );
  * T`&` insert( const T`&` p\_element, size\_t p\_index );
  * void erase( size\_t p\_index );
Proposed:
  * void erase( size\_t p\_start, size\_t p\_end );

## Map`<K,V>` ##
Constructors:
  * Map();
  * Map( const Map`<K,V>`& p\_map );
Methods:
  * append( K p\_key, V p\_value );
  * remove( K p\_key );
  * clear( );
  * V& find( K p\_key );