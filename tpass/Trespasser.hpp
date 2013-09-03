
#ifndef __trespasser_hpp__
#define __trespasser_hpp__

#include "Player.hpp"
#include "Array.hpp"
#include "Vector.hpp"
#include "Game.hpp"
#include "Creature.hpp"
#include "Material.hpp"

/** @class Trespasser
 * @brief Custom implementation of the Game
 *
 * Our custom implementation of the Game class which overrides default behaviour of
 * Game in order to implement an actual game.  Overriding methods is optional.
 */
class Trespasser : public Game
{
public:

    Trespasser( String p_name ) : Game( p_name )
    {
		m_players = Vector<Player>( 16 );
		m_creatures = Vector<Creature>();
		m_materials = Vector<Material>();

		// TODO: These cause a SIGSEGV due to poor code in STL... Rexhunter99 is fixing!
		m_materials.push_back( Material( "Dirt" ) );
		m_materials.push_back( Material( "Grass" ) );
		m_materials.push_back( Material( "Sand" ) );
		m_materials.push_back( Material( "Water" ) );
		m_materials.push_back( Material( "Flesh" ) );
		m_materials.push_back( Material( "Wood" ) );
    }

    ~Trespasser()
    {
    	m_players.clear();
    	m_creatures.clear();
    	m_materials.clear();
    }

private:

	Vector<Player>		m_players;
	Vector<Creature>	m_creatures;
	Vector<Material>	m_materials;

};

#endif // __trespasser_hpp__
