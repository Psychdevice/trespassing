
#ifndef __creature_hpp__
#define __creature_hpp__

#include <stdint.h>


class String;
class Model;


enum CreatureState
{
	// TODO (Rexhunter99#1#): Finish adding all the basic states
	CSTATE_DEAD			= 0,
	CSTATE_WANDER,
	CSTATE_ATTACK1,
	CSTATE_ATTACK2,
	CSTATE_ATTACK3,
	CSTATE_ATTACK4,
	CSTATE_EAT,
	CSTATE_DRINK,
	CSTATE_GOTO_SLEEP,
	CSTATE_SLEEP,
	CSTATE_WAKEUP,

	CSTATE_ENDOFDEFINED
};

/** @class CreatureInfo
 * @brief Container for information about the creature
 */
class CreatureInfo
{
public:

	String		m_name;
	Model*		m_model;				/**< The 3D model associated with this creature */

	uint16_t	m_health;				/**< The health of the creature 0 to (2^16)-1 */
	uint16_t	m_value;				/**< The value of the creature in credits */

	float		m_base_scale;			/**< The base scale of the creature 1.0 == 1 metre */
	float		m_range_scale;			/**< The additional scale of the creature 1.0 == 1 metre */

	float		m_view_range;			/**< Distance in metres this creature can see */
	float		m_hear_range;			/**< Distance in metres that sound alerts this creature */
	float		m_scent_range;			/**< Distance in metres that smell alerts this creature */

	float		m_anger_influence;		/**< Anger multiplier, 0.0 will prevent anger */
	float		m_hunger_influence;		/**< Hunger multiplier, 0.0 will prevent hunger */
	float		m_fear_influence;		/**< Fear multiplier, 0.0 will prevent fear */
	float		m_pain_influence;		/**< Pain tolerance, 0.0 will prevent pain */
};

/** @class Creature
 * @brief Base Creature object with valid properties and methods
 */
class Creature
{
public:

	/** @brief Initialise the Creature with appropriate information
	 * @param p_info A pointer to the CreatureInfo object stored elsewhere in the application
	 */
	Creature( CreatureInfo* p_info ) :
		m_info( p_info )
	{
		m_health	= p_info->m_health;
		m_anger		= 0.0f;
		m_hunger	= 0.0f;
		m_fear		= 0.0f;
		m_pain		= 0.0f;
	}
	~Creature(){}

protected:

	/** @var m_info
	 * @brief Pointer to the information object
	 */
	CreatureInfo	*m_info;

	/** @var m_health
	 * @brief The creature's health level
	 */
	uint16_t		m_health;

	float			m_x, m_y, m_z;

	/** @var m_yaw
	 * @brief The creature's horizontal angle
	 */
	float			m_yaw;

	/** @var m_pitch
	 * @brief The creature's vertical angle
	 */
	float			m_pitch;

	/** @var m_scale
	 * @brief The creature's scale multiplier
	 */
	float			m_scale;

	// -- Emotion Levels
	float			m_anger;
	float			m_hunger;
	float			m_fear;
	float			m_pain;

};

#endif // __creature_hpp__
