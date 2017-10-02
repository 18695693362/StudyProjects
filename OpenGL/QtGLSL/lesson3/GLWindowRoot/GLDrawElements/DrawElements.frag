#version 410 core

in vec4 vo_f_color;
layout (location=0) out vec4 color;
void main()
{
    color = vo_f_color;
}
