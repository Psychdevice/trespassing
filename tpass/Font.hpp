
#ifndef __font_hpp__
#define __font_hpp__

#include "Types.h"

class Font
{
public:

	Font(){}
	~Font(){}

private:

	uint32_t	m_id;

	/** @struct CharStruct
	 *
	 * Structure of data relating to glyph dimensions and properties.
	 */
	struct CharStruct
	{
		uint32_t	left,top,right,bottom;
	} m_charstruct[ char_t_count ];

};

#endif // __font_hpp__
