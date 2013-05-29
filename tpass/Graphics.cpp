
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>

#include "Graphics.hpp"
#include "String.hpp"
#include "FStream.hpp"
#include "Font.hpp"
#include "Texture.hpp"
#include "Vector.hpp"

Graphics::Graphics()
{
	m_log = new FStream( "video.log", FACCESS_WRITE );

	(*m_log) << "======================================================================" << "\r\n";
	(*m_log) << "== OpenGL Graphics Renderer" << endl;
	(*m_log) << "== " << (char*)glGetString( GL_RENDERER ) << endl;
	(*m_log) << "== " << (char*)glGetString( GL_VENDOR ) << endl;
	(*m_log) << "======================================================================" << endl;
	//m_log->flush();

	glewInit();

	GLint vMajor = 0;
	GLint vMinor = 0;

	glGetIntegerv( GL_MAJOR_VERSION, &vMajor );
	glGetIntegerv( GL_MINOR_VERSION, &vMinor );

	(*m_log) << "PROFILE: [ " << vMajor << "." << vMinor << " ]" << endl;
	(*m_log) << "PROFILE: [ " << (char*)glGetString( GL_VERSION ) << " ]" << endl;

	glCreateProgram();
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

	FStream file( p_fontname, FACCESS_READ );

	return const_cast<Font*>(&font);
}

Texture* Graphics::createTexture( String& p_filename )
{
	const Texture& texture = m_texture_list.push_back( Texture() );

	FStream file( p_filename, FACCESS_READ );

	return const_cast<Texture*>(&texture);
}

void Graphics::eventResize( uint16_t p_width, uint16_t p_height )
{
	glViewport( 0, 0, p_width, p_height );
}
