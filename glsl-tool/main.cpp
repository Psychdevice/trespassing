
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
	char out_dest[256];

	header.coin = ('R') + ('T'<<8) + ('3'<<16) + ('D'<<24);
	header.version		= 1;
	header.encoded		= 0; // 1 == XOR?
	header.glsl_major	= 4;
	header.glsl_minor	= 0;

	header.vertex_offset = 8; // -- Always begins after the coin and GLSL version

	return 0;
}
