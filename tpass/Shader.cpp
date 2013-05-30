
#include "Shader.hpp"
#include "String.hpp"
#include "FStream.hpp"

#include <GL/glew.h>

Shader::Shader()
{
	this->m_program = 0;
	this->m_vshader = 0;
	this->m_fshader = 0;
}

Shader::Shader( const Shader& p_copy )
{
	this->m_program	= p_copy.m_program;
	this->m_vshader	= p_copy.m_vshader;
	this->m_fshader	= p_copy.m_fshader;
}

Shader::Shader( String& p_vertex, String& p_fragment )
{
	FStream file( p_vertex, FACCESS_READ );

	file.close();
}
