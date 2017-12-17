#version 410 core

layout(location = 0) in vec3 vi_position;
layout(location = 1) in vec4 vi_color;
uniform vec3   trans_vec;
uniform float  scale;
uniform vec4   color;
uniform mat4x4 view_matrix;
uniform mat4x4 projection_matrix;
out vec4 vo_color;
void main()
{
    vec3 pos = vi_position * scale + trans_vec;
    gl_Position = vec4(pos, 1.0);
    vec4 pos_in_view = view_matrix*gl_Position;
    gl_Position = projection_matrix*pos_in_view;
    vo_color = color;
}
