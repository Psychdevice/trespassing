
#ifndef __game_hpp__
#define __game_hpp__

#include "String.hpp"

class Graphics;

/** @class Game
 * @brief Base Game class
 */
class Game
{
public:

    Game( String p_name );
    virtual ~Game();

    /** @brief Pre-Step processing
     * @return bool
     */
    virtual bool BeginStep();

    /** @brief Step processing
     * @return bool
     */
	virtual bool Step();

    /** @brief Post-Step processing
     * @return bool
     */
    virtual bool EndStep();

    /** @brief Return the graphics context for the game
     * @return Graphics*
     */
    Graphics*	graphics() const;

private:

    void __construct();
    String		m_name;
    Graphics*	m_gfx;
    bool		m_glfw;
    uint64_t	m_frames;
    double		m_frame_time;
    uint16_t	m_delta_frames;
    uint16_t	m_framespersecond;

};

#endif // __game_hpp__
