
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
	this->m_uniforms.append( String( "diffuse" ), 2 );
	this->m_uniforms.append( String( "normal" ), 10 );
	this->m_uniforms.append( String( "detail" ), 32 );

	this->m_uniforms.remove( String( "normal" ) );

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
	// -- Detach and delete shaders
	if ( m_vshader ) { glDetachShader( m_program, m_vshader ); glDeleteShader( m_vshader ); }
	if ( m_fshader ) { glDetachShader( m_program, m_fshader ); glDeleteShader( m_fshader ); }
	if ( m_gshader ) { glDetachShader( m_program, m_gshader ); glDeleteShader( m_gshader ); }
	if ( m_cshader ) { glDetachShader( m_program, m_cshader ); glDeleteShader( m_cshader ); }
	if ( m_eshader ) { glDetachShader( m_program, m_eshader ); glDeleteShader( m_eshader ); }
	// -- Delete the program
	glDeleteProgram( m_program );
}
