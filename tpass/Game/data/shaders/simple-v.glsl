// Vertex Shader - file "simple"

#version 120

attribute vec3 in_Position;
attribute vec3 in_Color;

void main(void)
{
        gl_Position = vec4(in_Position, 1.0);
        gl_FrontColor = in_Color;
}

#version 140

in  vec3 in_Position;
in  vec3 in_Color;
out vec3 ex_Color;

void main(void)
{
        gl_Position = vec4(in_Position, 1.0);
        ex_Color = in_Color;
}
