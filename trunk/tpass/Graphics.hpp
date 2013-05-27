
#ifndef __graphics_hpp__
#define __graphics_hpp__

#include "Vector.hpp"
#include <stdint.h>

class String;
class OStream;
class Font;
class Texture;

class Graphics
{
public:

    Graphics();
    ~Graphics();

    /** @brief Create a font for use in the game engine.
     * @param p_fontname
     * @return Font*
     */
    Font* createFont( String& p_fontname );

    /** @brief Create a texture for use in the game engine.
     * @return Texture*
     */
    Texture* createTexture( String& p_filename );

	/** @brief Perform an action in response to a canvas resize event
	 */
    void eventResize( uint16_t p_width, uint16_t p_height );


private:

	OStream*	m_log;
    float   	m_projection[16];
    float   	m_world[16];
    float   	m_transform[16];

    Vector<Font>		m_font_list;
    Vector<Texture>		m_texture_list;

};

#endif // __graphics_hpp__
