
#include "Texture.hpp"
#include "String.hpp"
#include <stdlib.h>
#include <GL/gl.h>

Texture::Texture( )
{
	m_pool = 0;

	glGenTextures( 1, &m_id );
}

Texture::~Texture()
{
	glDeleteTextures( 1, &m_id );

	if ( m_pool )
	{
		free( m_pool );
	}
}

bool Texture::create( String p_file, TextureProperties p_properties, TextureFormats p_format )
{

	glBindTexture( GL_TEXTURE_2D, m_id );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, 0 );

	return true;
}

uint32_t Texture::id() const
{
	return m_id;
}

uint16_t Texture::width() const
{
	return m_width;
}

uint16_t Texture::height() const
{
	return m_height;
}
