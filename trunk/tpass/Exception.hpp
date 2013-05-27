
#ifndef __exception_hpp__
#define __exception_hpp__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

class Exception
{
public:


	Exception() :
		m_id( 0xFFFFFFFF ),
		m_line( 0 ),
		m_file( 0 ),
		m_string( 0 ),
		m_message( 0 )
	{
		m_string = strdup( "An unidentified exception has occured!" );
	}

	Exception( const char* p_string ) :
		m_id( 0 ),
		m_line( 0 ),
		m_file( 0 ),
		m_string( 0 ),
		m_message( 0 )
	{
		m_string = strdup( p_string );
	}

	Exception( unsigned int p_id, const char* p_string ) :
		m_id( p_id ),
		m_line( 0 ),
		m_file( 0 ),
		m_string( 0 ),
		m_message( 0 )
	{
		if ( p_string ) m_string = strdup( p_string );
	}

	Exception( unsigned int p_id, const char* p_string, unsigned int p_line = 0, const char* p_file = 0 ) :
		m_id( p_id ),
		m_line( p_line ),
		m_file( 0 ),
		m_string( 0 ),
		m_message( 0 )
	{
		if ( p_string ) m_string = strdup( p_string );
		if ( p_file  )	m_string = strdup( p_file );
	}

	~Exception()
	{
		if ( m_message ) free( m_message );
		if ( m_string ) free( m_string );
		if ( m_file )	free( m_file );
	}

    /** \brief Returns the numeric identifier of the Exception, usually<br>an error code.
     *
     * \return unsigned int
     *
     */
	inline unsigned int id()
	{
		return this->m_id;
	}

    /** \brief Returns the human readable Exception, usually<br>an simple message.
     *
     * \return const char*
     *
     */
	inline const char* what()
	{
		return this->m_string;
	}

    /** \brief Returns the file name the Exception occured in.
     *
     * \return const char*
     *
     */
	inline const char* file()
	{
		return this->m_file;
	}

    /** \brief Returns the line number the Exception occured on.
     *
     * \return unsigned int
     *
     */
	inline unsigned int line()
	{
		return this->m_line;
	}

	/** \brief Returns a pointer to a C-String that contains extended information about the exception
     *
     * \return const char*
     *
     */
	const char* message();

protected:

	unsigned int	m_id;
	unsigned int	m_line;
	char			*m_file;
	char 			*m_string;
	char			*m_message;
};

int32_t ExceptionDialog( Exception& e );

#endif // __exception_hpp__
