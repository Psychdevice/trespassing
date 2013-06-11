
#ifndef __shader_hpp__
#define __shader_hpp__

#include "Map.hpp"

class String;

class Shader
{
public:

	Shader();
	Shader( const Shader& p_copy );
	Shader( String p_shader );
	~Shader();

	void bind();

protected:

	unsigned int m_program;	// Shader Program
	unsigned int m_vshader;	// Vertex
	unsigned int m_gshader;	// Geometry
	unsigned int m_fshader;	// Fragment
	unsigned int m_cshader; // Tess Control
	unsigned int m_eshader; // Tess Evaluator
	Map< String, unsigned int > m_uniforms;
	Map< String, unsigned int > m_attributes;
};


#endif //__shader_hpp__
