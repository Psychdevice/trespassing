
#ifndef __model_hpp__
#define __model_hpp__

#include <stdint.h>

template <class T> class Vector;

class Model
{
public:

	typedef struct __vertex_s // 34-Bytes
	{
		float 		x,y,z;		// XYZ coordinate
		float 		nx,ny,nz;	// Normal vector
		float 		s,t;		// Texture UV components
		uint16_t	b;			// Bone index
	} vertex_t;

	typedef struct __face_s // 8-Bytes
	{
		uint16_t	a,b,c;		// Indices
		uint16_t	m;			// Material index
	} face_t;

	Model(){}
	~Model(){}

private:

	uint16_t			m_num_verts;
	uint16_t			m_num_faces;

	Vector<vertex_t>	m_vertices;
	Vector<face_t>		m_faces;

};

#endif // __model_hpp__
