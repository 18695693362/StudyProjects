#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec3 normal;
out vec4 vo_color;

void main()
{
    gl_Position = vec4(position,1.0);
    vo_color = color;
}
