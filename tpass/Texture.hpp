
#ifndef __texture_hpp__
#define __texture_hpp__

#include <stdint.h>

class String;


/** @enum TextureFormats available texture formats
 *
 * Textures can be stored in many different ways with compression or without,
 * these enumerations identify different formats that have been coded in for
 * support in the graphics engine.
 */
enum TextureFormats
{
	TFORMAT_RGBA_8888		= 0,	/**< RGB 888 Bit compression for 24M colours and 8-Bits Alpha */
	TFORMAT_RGB_888			= 1,	/**< RGB 888 Bit compression for 24M colours */
	TFORMAT_RGBA_5551		= 2,	/**< RGB 555 Bit compression for 32K colours and 1-Bit Alpha */
	TFORMAT_RGB_565			= 3,	/**< RGB 565 Bit compression for 64K colours */
	TFORMAT_I_8				= 4		/**< Index 8-Bit for 256 colours */
};


/** @enum TextureProperties
 * @brief Properties of the texture
 *
 * Textures can have varying properties between each other that affect many aspects of how they are loaded,
 * used in rendering or how they are accessed and even if they are recoverable after being lost in VMEM
 */
enum TextureProperties
{
	TPROP_STORE_LOCAL			= 1,	/**< Store a copy of the texture data locally within SYSMEM */
	TPROP_AUTO_MIPMAP			= 2,	/**< Automatically generate MipMaps for this texture */
	TPROP_DEFAULT				= 0		/**< Use default properties */
};


/** @class Texture
 * @brief Texture container object
 *
 * Texture contains graphics textures stored in VMEM optimised for performance
 * and provides a unified interface to different formats to remove any issues
 * related to conversions and comparisons between formats.
 */
class Texture
{
public:

	Texture( );
	~Texture();

	bool create( String p_file, TextureProperties p_properties = TPROP_DEFAULT, TextureFormats p_format = TFORMAT_RGBA_8888 );

	/** @brief Return the id of the texture in VMEM
	 *
	 * @return uint32_t
	 *
	 * Returns a copy of the unique identifier of the texture, this copy does not
	 * directly influence the internal identifier and cannot overwrite it if written to.
	 */
	uint32_t id() const;
	/** @brief Return the widht of the texture in pixels
	 */
	uint16_t width() const;
	/** @brief Return the height of the texture in pixels
	 */
	uint16_t height() const;

private:
	uint32_t	m_id;
	uint16_t	m_width, m_height;
	void*		m_pool;
};

#endif // __texture_hpp__
