
#ifndef __material_hpp__
#define __material_hpp__

class String;
class Effect;

/** @class Material
 * @brief Material container
 */
class Material
{
public:

	Material( String p_name = "Dummy", Effect* p_fx_foot = 0, Effect* p_fx_bullet = 0 ) :
		m_name( p_name ), m_fx_foot( p_fx_foot ), m_fx_bullet( p_fx_bullet )
	{}
	~Material(){}

private:

	String		m_name;
	Effect*		m_fx_foot;		/**< Graphic Effect that is created when a foot touches this material */
	Effect*		m_fx_bullet;	/**< Graphic Effect that is created when a bullet hits this material */

};

#endif // __material_hpp__
