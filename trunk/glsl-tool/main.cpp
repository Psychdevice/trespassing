
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct rtshader_s {
	uint32_t	coin;
	uint8_t		version;
	uint8_t		encoded;
	uint8_t		glsl_major,
				glsl_minor;

	uint32_t	vertex_offset;
	uint32_t	frag_offset;
	uint32_t	geom_offset;
	uint32_t	tesscontrol_offset;
	uint32_t	tesseval_offset;
} header;

int main( int argc, char **argv )
{
	char		out_dest[256];
	char		in_shader[256];
	size_t		vlength = 0,
				flength = 0;
	FILE		*fp = 0;
	uint8_t		*vshader = 0,
				*fshader = 0;

	// -- Command line processing
	for ( int i=1; i<argc; i++ )
	{
		if ( !strncmp(argv[i], "-o=", 3 ) )
		{
			strcpy( out_dest, argv[i] + 3 );
			printf( "Destination File: \"%s\"\n", out_dest );
		}
		if ( !strncmp(argv[i], "-v=", 3 ) )
		{
			sscanf( argv[i] + 3, "%d.%d", &header.glsl_major, &header.glsl_minor );
			printf( "Shader Version: \"%s\"\n", out_dest );
		}
		if ( !strncmp(argv[i], "-e=", 3 ) )
		{
			header.encoded = atoi( argv[i] + 3 );
			printf( "Encoding: %d\n", header.encoded );
		}
		if ( !strncmp(argv[i], "-vs=", 4 ) )
		{
			strcpy( in_shader, argv[i] + 4 );
			printf( "Vertex Shader: \"%s\"\n", in_shader );
			if ( (fp = fopen( in_shader, "rb" )) )
			{
				fseek( fp, 0, SEEK_END );
				vlength = ftell( fp );
				fseek( fp, 0, SEEK_SET );
				vshader = (uint8_t*)malloc( vlength );
				fread( vshader, vlength, 1, fp );
				fclose( fp );
			}
		}
		if ( !strncmp(argv[i], "-fs=", 4 ) )
		{
			strcpy( in_shader, argv[i] + 4 );
			printf( "Fragment Shader: \"%s\"\n", in_shader );
			if ( (fp = fopen( in_shader, "rb" )) )
			{
				fseek( fp, 0, SEEK_END );
				flength = ftell( fp );
				fseek( fp, 0, SEEK_SET );
				fshader = (uint8_t*)malloc( flength );
				fread( vshader, flength, 1, fp );
				fclose( fp );
			}
		}
	}

	// -- Set up the binary blob file header
	memset( &header, 0, sizeof(rtshader_s) );
	header.coin = ('R') + ('T'<<8) + ('3'<<16) + ('D'<<24);
	header.version		= 1;		// -- First version of this file format
	header.encoded		= 0;		// 1 == XOR? Leave as 0 (unencoded) for now
	header.glsl_major	= 4;		// -- Default is 4.0 can be anything
	header.glsl_minor	= 0;

	header.vertex_offset = 8; // -- Always begins after the coin and GLSL version
	header.frag_offset = header.vertex_offset + vlength;

	if ( (fp = fopen( out_dest, "wb" ) ) )
	{
		fclose( fp );
	}
	else
	{
		printf( "Failed to open the destination output file for writing...\n" );
	}

	if ( vshader ) free(vshader);
	if ( fshader ) free(fshader);

	return 0;
}
