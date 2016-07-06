#version 410 core

layout(location = 0) in vec3 vi_position;
layout(location = 1) in vec4 vi_color;
layout(location = 2) in vec3 vi_normal;
uniform mat4x4 view_matrix;
uniform mat4x4 projection_matrix;
out vec4 vo_color;

void main()
{
    gl_Position = vec4(vi_position,1.0);
    gl_Position = projection_matrix*view_matrix*gl_Position;
    vo_color = vi_color;
}
