
#include "Game.hpp"
#include "String.hpp"
#include "Exception.hpp"
#include "OStream.hpp"
#include "Array.hpp"
#include "Vector.hpp"

#include "Trespasser.hpp"

int main( int argc, char **argv )
{
	// -- Construct a Command Line Options String
	// TODO (Rexhunter99#1#): This current SIGSEGV's on me...
	/*String CmdLine;
	for ( int i=1; i<argc; i++ )
	{
		CmdLine += String( argv[i] );
		if ( i < argc-1 ) CmdLine += String( " " );
	}
	sout << "Command Line: \'" << CmdLine << "\'" << endl;*/

    try
    {
        Mesozoic* game = new Mesozoic( "Hunter: Mesozoic" );

        if ( !game )
        {
            throw Exception( "main :: Failed to initialise game instance!" );
        }

        while ( true )
        {
            if ( !game->BeginStep() ) break;
            if ( !game->Step() ) break;
            if ( !game->EndStep() ) break;
        }

        delete game;
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

    return 0;
}
