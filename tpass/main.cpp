
#include "Game.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include "OStream.hpp"
#include "Array.hpp"
#include "Vector.hpp"
#include "Shader.hpp"

#include "Trespasser.hpp"

int main( int argc, char **argv )
{
	// -- Construct a Command Line Options String
	String CmdLine;
	for ( int i=1; i<argc; i++ )
	{
		CmdLine += argv[i];
		if ( i < argc-1 ) CmdLine += " ";
	}
	sout << "Command Line: \'" << CmdLine << "\'" << endl;

    try
    {
		Trespasser game( "Trespasser" );

		Shader *test = new Shader( String("data/shaders/terrain-v.glsl") );
		delete test;

        while ( true )
        {
            if ( !game.BeginStep() ) break;
            if ( !game.Step() ) break;
            if ( !game.EndStep() ) break;
        }
    }
    catch( Exception &e )
    {
    	int32_t eret = ExceptionDialog( e );

        sout << "An exception occured!\n";
        sout << "\t" << e.what() << endl;

        if ( eret == 1 )
		{
			return e.id();
		}
		else if ( eret == 2 )
		{
			sout << "Can't ignore exception, it occurs in main(...)! Aborting..." << endl;
		}
    }
    catch (...)
    {
    	Exception e( "A fatal exception has occurred.\r\nThe exception is of an unknown type and was not handled appropriately,\r\nthis may have been an exception thrown by the user." );
    	ExceptionDialog( e );
    }

    return 0;
}
