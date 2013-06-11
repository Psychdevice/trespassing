
#include "Shader.hpp"
#include "Array.hpp"
#include "String.hpp"
#include "FStream.hpp"
#include "OStream.hpp"

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

Shader::Shader( String p_shader )
{
	this->m_uniforms.add( String( "diffuse" ), 2 );
	this->m_uniforms.add( String( "normal" ), 10 );
	this->m_uniforms.add( String( "detail" ), 32 );

	sout << "diffuse == " << this->m_uniforms[ String( "diffuse" ) ] << endl;
	sout << "normal == " << this->m_uniforms[ String( "normal" ) ] << endl;
	sout << "detail == " << this->m_uniforms[ String( "detail" ) ] << endl;

	this->m_uniforms.clear();

	FStream file( p_shader, FACCESS_READ );

	while( !file.eos() )
	{
		String line = file.readln();
		if ( line.find( "#version" ) != String::npos )
		{
			Array<String> _list = line.split( " \t" );
			sout << "VERSION: " << _list[1] << endl;
		}
		sout << line << endl;
	}

	file.close();
}

Shader::~Shader()
{
}
