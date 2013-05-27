
#include "Graphics.hpp"
#include "String.hpp"
#include "OStream.hpp"
#include "Font.hpp"
#include "Texture.hpp"
#include "Vector.hpp"

#include <GL/gl.h>
#include <GL/glext.h>

Graphics::Graphics()
{
	m_log = new OStream( OTYPE_FILE, "video.log" );

	(*m_log) << "===================================" << "\r\n";
	(*m_log) << "== OpenGL Graphics Renderer" << "\r\n";
	(*m_log) << "== " << (char*)glGetString( GL_RENDERER ) << "\r\n";
	(*m_log) << "== " << (char*)glGetString( GL_VENDOR ) << "\r\n";
	(*m_log) << "===================================" << "\r\n";
	m_log->flush();

	GLint vMajor = 0;
	GLint vMinor = 0;

	glGetIntegerv( GL_MAJOR_VERSION, &vMajor );
	glGetIntegerv( GL_MINOR_VERSION, &vMinor );

	(*m_log) << "PROFILE: [ " << vMajor << "." << vMinor << " ]" << endl;
	(*m_log) << "PROFILE: [ " << (char*)glGetString( GL_VERSION ) << " ]" << endl;
}

Graphics::~Graphics()
{
	if ( m_log )
	{
		m_log->flush(); // -- Make sure we flush the stream out properly
		delete m_log;
	}

	m_font_list.clear();
	m_texture_list.clear();
}

Font* Graphics::createFont( String& p_fontname )
{
	const Font& font = m_font_list.push_back( Font() );

	OStream file( OTYPE_FILE, p_fontname );

	return const_cast<Font*>(&font);
}

Texture* Graphics::createTexture( String& p_filename )
{
	const Texture& texture = m_texture_list.push_back( Texture() );

	OStream file( OTYPE_FILE, p_filename );

	return const_cast<Texture*>(&texture);
}

void Graphics::eventResize( uint16_t p_width, uint16_t p_height )
{
	glViewport( 0, 0, p_width, p_height );
}
