#version 410 core
in VERTEX
{
    vec3 normal;
    vec4 color;
} vertex;
layout (location=0) out vec4 color;
void main()
{
    //color = vertex.color;
    color = vec4(1.0,0.0,0.0,1.0);
}
