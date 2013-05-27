
#ifndef __player_hpp__
#define __player_hpp__


class String;

/** @class Player
 *
 * The player container object that encapsulates the entire player data structure for local client and remote client.
 */
enum PlayerRank
{
	PRANK_NOVICE		= 0,
	PRANK_INTERMEDIATE,
	PRANK_EXPERIENCED,
	PRANK_PROFESSIONAL,
	PRANK_VETERAN,
	PRANK_MASTER
};

/** @class Player
 *
 * The player container object that encapsulates the entire player data structure for local client and remote client.
 */
class Player
{
public:

	Player()
	{
	}
	Player( const Player& p_player )
	{
		m_name		= p_player.m_name;
		m_health	= p_player.m_health;
		m_x			= p_player.m_x;
		m_y			= p_player.m_y;
		m_z			= p_player.m_z;
		m_yaw		= p_player.m_yaw;
		m_pitch		= p_player.m_pitch;
		m_roll		= p_player.m_roll;
		m_rank		= p_player.m_rank;
	}
	~Player()
	{
	}

protected:

	String		m_name;		/**< Name of the player */
	uint8_t		m_health;	/**< Maximum Health == 100 */
	float		m_x, m_y, m_z;
	float		m_yaw, m_pitch, m_roll; // Roll is used for the camera only
	uint32_t	m_credits;
	PlayerRank	m_rank;

};

#endif // __player_hpp__
