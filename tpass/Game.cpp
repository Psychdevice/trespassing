
#include "Game.hpp"

#include "Exception.hpp"
#include "String.hpp"
#include "Graphics.hpp"


#include "OStream.hpp"
#include <GL/glfw.h>

#include <stdio.h>

Game::Game( String p_name )
{
	sout << "Initialising Game: \"" << p_name << "\"" << endl;

    m_name = p_name;
    m_glfw = false;
	m_gfx = 0;

	// TODO (Rexhunter99#1#): Implement Linux set current working directory

    // -- Initialise GLFW
    if ( !glfwInit() )
    {
        throw Exception( "Failed to initialise GLFW" );
    }

    m_glfw = true;

    glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
    //glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 1 );
    //glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    if ( !glfwOpenWindow( 800, 600, 8,8,8,8, 24, 0, GLFW_WINDOW ) )
    {
		sout << "OpenGL Failed to initialise with core features, using legacy support..." << endl;

    	// -- High Quality mode failed, attempt compatability mode
    	glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 2 );
		glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 0 );
		glfwOpenWindowHint( GLFW_OPENGL_PROFILE, 0 );

		if ( !glfwOpenWindow( 800, 600, 8,8,8,0, 16, 0, GLFW_WINDOW ) )
		{
			throw Exception( "Game :: Failed to create the window with the desired OpenGL properties!" );
		}
    }

    // -- Request that V-Sync be disabled.
    /* Note that application level settings are overridden (most of the time) by the environement
    which are overriden by the window display manager and finally by the drivers.  Anything we call
    down here in the application will be requested, not demanded.*/
    glfwSwapInterval( 0 );


    m_gfx = new Graphics();

    m_frame_time = glfwGetTime();
}

Game::~Game()
{
	if ( m_gfx )
	{
		delete m_gfx;
	}

    if ( m_glfw )
    {
        glfwTerminate();
    }
}

bool Game::BeginStep()
{
    if ( !m_glfw ) throw Exception( "Game :: GLFW is not initialised!" );

    if ( !glfwGetWindowParam( GLFW_OPENED ) )
    {
        return false; // -- Either the window broke and didn't get opened, or we closed it at some point.
    }

    char buf[256];
    sprintf( buf, "%s - FPS[ %u ]", (const char*)m_name, m_framespersecond );

    glfwSetWindowTitle( buf );

    int r_width = 0, r_height = 0;
    glfwGetWindowSize( &r_width, &r_height );

    this->m_gfx->eventResize( r_width, r_height );

    glClearColor( 0.0f, 0.35f, 0.7f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );

    return true;
}

bool Game::Step()
{
    if ( !m_glfw ) throw Exception( "Game :: GLFW is not initialised!" );

    return true;
}

bool Game::EndStep()
{
    if ( !m_glfw ) throw Exception( "Game :: GLFW is not initialised!" );

    // -- Flip/Copy buffers - Triple Buffering doesn't flip, it shuffles the buffers.
    glfwSwapBuffers( );
    m_frames++;
    m_delta_frames++;
	double cur_time = glfwGetTime();

	if ( cur_time >= m_frame_time+1 ) // if 1 Second has passed
	{
		m_frame_time = cur_time;
		m_framespersecond = m_delta_frames;
		m_delta_frames = 0;
	}

    // -- Sleep for approximately 1ms
    glfwSleep( 1.0f / 1000.0f );

    return true;
}


Graphics* Game::graphics() const
{
	return this->m_gfx;
}
