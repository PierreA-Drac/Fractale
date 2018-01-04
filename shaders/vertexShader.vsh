#version 130

attribute vec4 vertex;
attribute vec2 texture_in;
out       vec2 texture_out;

void main()
{
    gl_Position = vertex;
    texture_out = texture_in;
}
