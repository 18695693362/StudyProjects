#version 410 core

layout(location = 0) in vec4 vi_position;
layout(location = 1) in vec4 vo_color;
out vec4 vo_f_color;

void main()
{
    //vs_fs_color = model_matrix[2];
    vo_f_color = vo_color;

    mat4 scale = mat4(0.5);
    scale[3].w = 1;
    gl_Position = vi_position * scale;
}
