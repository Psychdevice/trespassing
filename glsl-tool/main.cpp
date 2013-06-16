
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>



class contents_t
{
public:

	std::string		name;
	uint32_t		type;
	size_t			offset;
	size_t			length;
	uint8_t			*data;

	contents_t() :
		name( "" ), type( 0 ), offset( 0 ), length( 0 ), data( 0 )
	{}
	~contents_t()
	{
		if ( data ) free( data );
	}
};

struct rtshader_s { // 4 + 2 + 2
	uint32_t	coin;
	uint8_t		version;
	uint8_t		encoded;
	uint8_t		glsl_major,
				glsl_minor;

	std::vector<contents_t>	tableofcontents;
} header;



int loadShader( char* in_file )
{
	FILE *fp = NULL;

	printf( "source file: \"%s\"\n", in_file );

	if ( (fp = fopen( in_file, "rb" )) )
	{
		contents_t temp_item;
		header.tableofcontents.push_back( temp_item );
		contents_t *item = &( header.tableofcontents[ header.tableofcontents.size()-1 ] );

		item->name		= in_file;
		item->type		= 0;
		item->offset	= 0;

		fseek( fp, 0, SEEK_END );
		item->length = ftell( fp );
		fseek( fp, 0, SEEK_SET );

		item->data = (uint8_t*)malloc( item->length );
		fread( item->data, item->length, 1, fp );

		fclose( fp );
	}
	else
	{
		printf( "error\t|\tFailed to open source file \"%s\"!\n", in_file );
		return 3;
	}

	return 0;
}


int main( int argc, char **argv )
{
	char		out_dest[256];
	FILE		*fp = 0;
	bool hasoutput = false;
	bool hasinputs = false;

	// -- Clear the memory for the header
	memset( &header, 0, sizeof(rtshader_s) );

	// -- Command line processing
	for ( int i=1; i<argc; i++ )
	{
		if ( !strncmp(argv[i], "-o", 2 ) )
		{
			strcpy( out_dest, argv[i+1] );
			i++;
			printf( "Destination File: \"%s\"\n", out_dest );
			hasoutput = true;
			continue;
		}
		if ( !strncmp(argv[i], "-v", 2 ) )
		{
			unsigned int major,minor;
			sscanf( argv[i+1], "%u.%u", &major, &minor );
			i++;
			header.glsl_major = major;
			header.glsl_minor = minor;

			printf( "Shader Version: %u.%u\n", major, minor );
			continue;
		}
		if ( !strncmp(argv[i], "-e", 2 ) )
		{
			header.encoded = atoi( argv[i+1] );
			i++;
			printf( "Encoding: %d\n", header.encoded );
			continue;
		}
		if ( !strncmp(argv[i], "-i", 2 ) )
		{
			loadShader( argv[i+1] );
			i++;
			hasinputs = true;
			continue;
		}
		if ( !strncmp(argv[i], "--input=", 8 ) )
		{
			char in_name[256];

			if ( strstr( argv[i], "\"" ) )
			{
				strncpy( in_name, argv[i] + 9, strlen(argv[i])-10 );
			}
			else
			{
				strcpy( in_name, argv[i] + 8 );
			}

			int ret = 0;

			if ( (ret = loadShader( in_name )) != 0 )
			{
				header.tableofcontents.clear();
				return ret;
			}

			hasinputs = true;
			continue;
		}
	}

	if ( !hasinputs )
	{
		printf( "error\t|\tThere are no shader source files to compile!  Aborting..." );
		return 1;
	}

	// -- Set up the binary blob file
	if ( hasoutput )
	{
		header.coin = ('R') + ('T'<<8) + ('3'<<16) + ('D'<<24);
		header.version		= 1;		// -- First version of this file format
		header.glsl_major	= 4;		// -- Default is 4.0 can be anything
		header.glsl_minor	= 0;		// --

		if ( (fp = fopen( out_dest, "wb" ) ) )
		{
			fwrite( &header, 8, 1, fp );

			fclose( fp );
		}
		else
		{
			printf( "Failed to open the destination output file for writing...\n" );
			return 2;
		}
	}

	header.tableofcontents.clear();

	system( "PAUSE" );
	return 0;
}
