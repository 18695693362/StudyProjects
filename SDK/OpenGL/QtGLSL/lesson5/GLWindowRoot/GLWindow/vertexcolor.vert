#version 410 core
layout(location = 0) in vec2 vi_position;
layout(location = 1) in vec4 vi_color;
out vec4 vo_color;

void main()
{
    gl_Position = vec4(vi_position,0.0,1.0);
    vo_color = vi_color;
}
