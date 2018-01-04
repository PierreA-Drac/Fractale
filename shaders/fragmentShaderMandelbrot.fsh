#version 130

uniform int   n_max;
uniform float z_max;
uniform bool  b_color;
uniform vec2  center;
uniform float scale;
in      vec2  texture_out;

void main()
{
    vec2 z;
    vec2 c;
    c.x = scale * (3.0 * texture_out.x - 2.0) + center.x;
    c.y = scale * (2.0 * texture_out.y - 1.0) + center.y;

    z = c;

    int i = 0;
    for (; i < n_max; ++i)
    {
        float x = z.x*z.x - z.y*z.y + c.x;
        float y = z.x*z.y + z.y*z.x + c.y;

        if (x*x + y*y > z_max)
            break;

        z.x = x;
        z.y = y;
    }

    vec4 color = vec4(0.0);

    if (i < n_max - 1) {
        if (b_color == false)
            color = vec4(1.0);
        else {
            color.x = sin(float(i) / 100.0);
            color.y = sin(float(i) / 70.0);
            color.z = cos(float(i) / 20.0 + 3.141 / 4.0);
        }
    }

    gl_FragColor = color;
}
