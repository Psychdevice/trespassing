#version 410

// Input Position coordinate
in vec4 position;
// Texture sample for terrain data
uniform sampler2D terrain;

void main(void)
{
	// The texture-coordinate of the terrain data
    vec2 texcoord = position.xy;
    // The height of the terrain vertex at this point
    float height = texture(terrain, texcoord).a;
    // The combined location
    gl_Position = vec4( position.x, position.y, height, 1.0 );
}
