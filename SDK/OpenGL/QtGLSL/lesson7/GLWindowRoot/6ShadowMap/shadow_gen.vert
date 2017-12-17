#version 410 core

layout(location = 0) in vec3 vi_position;
layout(location = 1) in vec4 vi_color;
layout(location = 2) in vec3 vi_normal;
uniform mat4x4 view_matrix;
uniform mat4x4 projection_matrix;
void main(void)
{
    gl_Position = projection_matrix * view_matrix * vec4(vi_position,1.0);
}
