#version 410 core
uniform vec4 ambient;
uniform vec3 eye_dir;
uniform int  light0_type;
uniform vec3 light0_color;
uniform vec3 light0_pos;
uniform float light0_shininess;
uniform float light0_strength;
uniform float light0_attenuation;
uniform float light0_linear_attenuation;
uniform float light0_quadratic_attenuation;

in vec4 vo_color;
in vec3 vo_normal;
in vec3 vo_pos_in_view;
out vec4 fo_color;

void main()
{
    vec3 normal = normalize(vo_normal);

    vec3 light0_dir = vo_pos_in_view - light0_pos;
    float light0_distance = length(light0_dir);
    light0_dir = light0_dir / light0_distance;
    float diffuse = max(dot(normal, -light0_dir), 0.0);
    float specular = diffuse;
    if(specular != 0.0)
    {
        vec3 reflect_dir = reflect(light0_dir,normal);
        specular = max(pow(max(dot(-eye_dir,reflect_dir),0.0), light0_shininess), 0);
    }

    float attenuation = 1 / (light0_attenuation +
                             light0_linear_attenuation*light0_distance +
                             light0_quadratic_attenuation*light0_distance*light0_distance);

    vec3 scatteredLight = ambient.xyz + light0_color*diffuse*attenuation;
    vec3 reflectedLight = light0_color * specular * light0_strength * attenuation;

    vec3 rgb = min(vo_color.xyz*scatteredLight.xyz + reflectedLight ,vec3(1.0));
    fo_color = vec4(rgb,vo_color.a);

    //vec3 rgb_without_specular = min(vo_color.xyz*scatteredLight.xyz, vec3(1.0));
    //fo_color = vec4(rgb_without_specular,vo_color.a);

    //fo_color = vec4(light0_color,vo_color.a);
    //fo_color = vec4(-light0_dir,vo_color.a);
    //fo_color = vec4(ambient.xyz,vo_color.a);
    //fo_color = vec4(diffuse,diffuse,diffuse,1.0);
    //fo_color = vec4(normal,1.0);
    //fo_color = vo_color;
}
