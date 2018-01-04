attribute highp vec4 vertex;
attribute highp vec2 texture_in;
varying   highp vec2 texture_out;

void main()
{
    gl_Position = vertex;
    texture_out = texture_in;
}
