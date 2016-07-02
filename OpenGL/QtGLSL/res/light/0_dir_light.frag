#version 410 core
uniform vec4 ambient;
uniform vec3 eye_dir;
uniform vec3 light0_color;
uniform vec3 light0_dir;
uniform float light0_shininess;
uniform float light0_strength;

in vec4 vo_color;
in vec3 vo_normal;
out vec4 fo_color;

void main()
{
    vec3 normal = normalize(vo_normal);

    float diffuse = max(dot(normal, -light0_dir), 0.0);
    float specular = diffuse;
    if(specular != 0.0)
    {
        vec3 reflect_dir = reflect(-light0_dir,normal);
        specular = max(pow(max(dot(-eye_dir,reflect_dir),0.0), light0_shininess), 0);
    }

    vec3 scatteredLight = ambient.xyz + light0_color*diffuse;
    vec3 reflectedLight = light0_color * specular * light0_strength;

    vec3 rgb = min(vo_color.xyz*scatteredLight.xyz + reflectedLight ,vec3(1.0));
    fo_color = vec4(rgb,vo_color.a);

    vec3 rgb_without_specular = min(vo_color.xyz*scatteredLight.xyz, vec3(1.0));
    fo_color = vec4(rgb_without_specular,vo_color.a);
    //fo_color = vec4(light0_color,vo_color.a);
    //fo_color = vec4(-light0_dir,vo_color.a);
    //fo_color = vec4(ambient.xyz,vo_color.a);
    //fo_color = vec4(diffuse,diffuse,diffuse,1.0);
    //fo_color = vec4(normal,1.0);
    //fo_color = vo_color;
}
