#version 410 core
struct GSLightProp
{
    bool        enable;
    int         type;
    vec3        color;
    vec3        dir;
    vec3        pos;
    vec3        ambient;
    float       shininess;
    float       strengthen;
    float       attenuation;
    float       linear_attenuation;
    float       quadratic_attenuation;
    float       spot_inner_cutoff;
    float       spot_outer_cutoff;
};
#define LIGHT_COUNT 3
uniform GSLightProp lights[LIGHT_COUNT];
in vec4 vo_color;
in vec3 vo_normal;
in vec3 vo_pos_in_view;
out vec4 fo_color;

vec3 CalcLight(vec3 obj_pos, vec3 obj_color, GSLightProp light_prop,vec3 normal);
void main()
{
    vec3 result_color = vec3(0.0,0.0,0.0);
    vec3 normal = normalize(vo_normal);
    for(int i=0; i<LIGHT_COUNT; i++)
    {
        result_color += CalcLight(vo_pos_in_view,vo_color.rgb,lights[i],normal, vo_pos_in_view);
    }

    fo_color = vec4(result_color,vo_color.a);
    //fo_color = vo_color;
}

vec3 CalcLight(vec3 obj_pos, vec3 obj_color, GSLightProp light_prop,vec3 normal, vec3 eye_dir)
{
    vec3 color = vec3(0.0,0.0,0.0);
    if(light_prop.enable)
    {
        if(light_prop.type == 0) // dir light
        {
            vec3 cur_light_dir = light_prop.dir;
            vec3 light_color = light_prop.color;
            vec3 ambient = light_prop.ambient;
            float diffuse = max(dot(-cur_light_dir,normal),0.0);
            float specular = diffuse;
            if(specular!=0.0)
            {
                specular = dot(reflect(cur_light_dir,normal),-eye_dir);
                specular = max(specular,0.0);
                specular = pow(specular,light_prop.shininess);
            }
            vec3 scratter_light = ambient + diffuse * light_color;
            vec3 reflected_light = specular * light_color;
            color = (obj_color * scratter_light + reflected_light);

            //color = vec3(specular,specular,specular);
            //color = scratter_light;
            //color = (obj_color * scratter_light + reflected_light);
        }
        else if(light_prop.type == 1) // point light
        {
            vec3 cur_light_dir = obj_pos-light_prop.pos;
            float light_distance = length(cur_light_dir);
            cur_light_dir = cur_light_dir / light_distance;
            vec3 light_color = light_prop.color;
            vec3 ambient = light_prop.ambient;
            float diffuse = max(dot(-cur_light_dir,normal),0.0);
            float specular = diffuse;
            if(specular!=0.0)
            {
                specular = dot(reflect(cur_light_dir,normal),-eye_dir);
                specular = max(specular,0.0);
                specular = pow(specular,light_prop.shininess);
            }
            float attenuation = 1 / (light_prop.attenuation +
                                     light_prop.linear_attenuation * light_distance +
                                     light_prop.quadratic_attenuation * light_distance + light_distance);

            vec3 scratter_light = ambient + diffuse * light_color * attenuation;
            vec3 reflected_light = specular * light_color * attenuation;
            color = (obj_color * scratter_light + reflected_light);
        }
        else if(light_prop.type == 2) // spot light
        {
            vec3 cur_light_dir = obj_pos-light_prop.pos;
            float light_distance = length(cur_light_dir);
            cur_light_dir = cur_light_dir / light_distance;
            vec3 light_color = light_prop.color;
            vec3 ambient = light_prop.ambient;
            float diffuse = max(dot(-cur_light_dir,normal),0.0);
            float specular = diffuse;
            if(specular!=0.0)
            {
                specular = dot(reflect(cur_light_dir,normal),-eye_dir);
                specular = max(specular,0.0);
                specular = pow(specular,light_prop.shininess);
            }
            float attenuation = 1 / (light_prop.attenuation +
                                     light_prop.linear_attenuation * light_distance +
                                     light_prop.quadratic_attenuation * light_distance + light_distance);

            float delta_inner_outer = light_prop.spot_inner_cutoff - light_prop.spot_outer_cutoff;
            float cur_light_cos = dot(cur_light_dir,light_prop.dir);
            float spot_attenuation = (cur_light_cos - light_prop.spot_outer_cutoff) / delta_inner_outer;
            spot_attenuation = clamp(spot_attenuation, 0, 1);
            attenuation *= spot_attenuation;

            vec3 scratter_light = ambient + diffuse * light_color * attenuation;
            vec3 reflected_light = specular * light_color * attenuation;
            color = (obj_color * scratter_light + reflected_light);
        }
    }
    return color;
}
