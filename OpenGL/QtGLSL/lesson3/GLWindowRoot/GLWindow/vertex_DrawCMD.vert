#version 410 core

uniform mat4 model_matrix;
uniform mat4 projection_matrix;

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
out vec4 vs_fs_color;

void main()
{
    mat4x4 translate = mat4x4(
                vec4(0.1,   0,   0,   0),
                vec4(  0, 0.1,   0,   0),
                vec4(  0,   0, 0.1,   0),
                vec4(  0,   0,   0,   1));
    vs_fs_color = color;
    //gl_Position = position;
    gl_Position = translate * position;
    //gl_Position = model_matrix*position;
    //gl_Position = projection_matrix*(model_matrix*position);
}
