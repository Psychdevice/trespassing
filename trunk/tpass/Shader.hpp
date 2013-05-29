
#ifndef __shader_hpp__
#define __shader_hpp__

class String;

class Shader
{
public:

	Shader();
	Shader( const Shader& p_copy );
	Shader( String& p_vertex, String& p_fragment );
	~Shader();

	void bind();


protected:

	unsigned int m_program;
	unsigned int m_vshader;
	unsigned int m_fshader;
};


#endif //__shader_hpp__
