#version 410 core
uniform vec4 ambient;
uniform int  light0_type;
uniform vec3 light0_color;
uniform vec3 light0_pos;
uniform vec3 light0_dir;
uniform float light0_shininess;
uniform float light0_strength;
uniform float light0_attenuation;
uniform float light0_linear_attenuation;
uniform float light0_quadratic_attenuation;
uniform float light0_spot_inner_cutoff;
uniform float light0_spot_outer_cutoff;
uniform float light0_spot_exponent;

in vec4 vo_color;
in vec3 vo_normal;
in vec3 vo_pos_in_view;
out vec4 fo_color;

void main()
{
    vec3 normal = normalize(vo_normal);

    vec3 cur_light0_dir = vo_pos_in_view - light0_pos;
    float light0_distance = length(cur_light0_dir);
    cur_light0_dir = cur_light0_dir / light0_distance;
    float diffuse = max(dot(normal, -cur_light0_dir), 0.0);
    float specular = diffuse;
    if(specular != 0.0)
    {
        vec3 reflect_dir = reflect(cur_light0_dir,normal);
        specular = max(pow(max(dot(-vo_pos_in_view,reflect_dir),0.0), light0_shininess), 0);
    }

    float attenuation = 1 / (light0_attenuation +
                             light0_linear_attenuation*light0_distance +
                             light0_quadratic_attenuation*light0_distance*light0_distance);

/*
    inner_cutoff = 30 = 0.8660
    outer_cutoff = 60 = 0.5
    delta_innter_outer = 0.8660 - 0.5 = 0.366

    cur_light = 45 = 0.7071
    inner_cutoff - cur_light = 0.8660 - 0.7071 = 0.1589
    (inner_cutoff - cur_light) / delta_innter_outer = 0.1589/0.366 = 0.4341
    ##
    cur_light - outer_cutoff = 0.7071 - 0.5 = 0.2021
    (cur_light - outer_cutoff) / delta_innter_outer = 0.2021/0.366 = 0.5521

    cur_light = 15 = 0.9659
    inner_cutoff - cur_light = 0.8660 - 0.9659 = -0.0998
    (inner_cutoff - cur_light) / delta_innter_outer = -0.0998/0.366 = -0.2726
    ##
    cur_light - outer_cutoff = 0.9659 - 0.5 = 0.4659
    (cur_light - outer_cutoff) / delta_innter_outer = 0.4659/0.366 = 1.2729
*/

    float delta_innter_outer = light0_spot_inner_cutoff - light0_spot_outer_cutoff;
    float spot_cos = dot(cur_light0_dir,light0_dir);
    float spot_attenuation = clamp((spot_cos-light0_spot_outer_cutoff)/delta_innter_outer,0.0,1.0);
    attenuation *= spot_attenuation;

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

    //fo_color = vec4(spot_attenuation,spot_attenuation,spot_attenuation,1.0);
}
