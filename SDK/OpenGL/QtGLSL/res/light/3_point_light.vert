#version 410 core

layout(location = 0) in vec3 vi_position;
layout(location = 1) in vec4 vi_color;
layout(location = 2) in vec3 vi_normal;
uniform vec3   trans_vec;
uniform mat4x4 view_matrix;
uniform mat4x4 projection_matrix;
uniform mat3x3 normal_matrix;
out vec4 vo_color;
out vec3 vo_normal;
out vec3 vo_pos_in_view;
void main()
{
    vec3 pos = vi_position + trans_vec;
    gl_Position = vec4(pos, 1.0);
    vec4 pos_in_view = view_matrix*gl_Position;
    gl_Position = projection_matrix*pos_in_view;
    vo_pos_in_view = pos_in_view.xyz;
    vo_normal = normal_matrix * vi_normal;
    vo_color = vi_color;
}
