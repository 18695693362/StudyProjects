#version 410 core
uniform vec4 ambient;
in vec4 vo_color;
out vec4 fo_color;
void main()
{
    //fo_color = vo_color;
    vec4 scatteredLight = ambient;
    vec3 rgb = min(scatteredLight.xyz*vo_color.xyz,vec3(1.0));
    fo_color = vec4(rgb,vo_color.a);
}
