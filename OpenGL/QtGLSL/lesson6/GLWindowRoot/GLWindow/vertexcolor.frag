#version 410 core
in vec4 vo_color;
out vec4 fo_color;
void main()
{
    fo_color = vo_color;
}
