#version 410 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec4 color;

out VERTEX
{
    vec3 normal;
    vec4 color;
} vertex;
void main()
{
    gl_Position = position;
    vertex.normal = normal;
    vertex.color = color;
}
