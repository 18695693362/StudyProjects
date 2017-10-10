#version 410 core

layout(points) in;
layout(points) out;
layout(max_vertices = 30) out;

in float vo_type[];
in vec3 vo_position[];
in vec3 vo_velocity[];
in float vo_age[];

out float go_type;
out vec3 go_position;
out vec3 go_velocity;
out float go_age;

uniform float delta_ms;
uniform float time;
uniform sampler1D random_tex;
uniform float launcher_lifetime;
uniform float shell_lifetime;
uniform float secondary_shell_lifetime;

#define PARTICLE_TYPE_LAUNCHER 0.0f
#define PARTICLE_TYPE_SHELL 1.0f
#define PARTICLE_TYPE_SECONDARY_SHELL 2.0f

vec3 GetRandomDir(float tex_coord)
{
     vec3 dir = texture(random_tex, tex_coord).xyz;
     dir -= vec3(0.5, 0.5, 0.5);
     return dir;
}

void main()
{
    float age = vo_age[0] + delta_ms;

    if (vo_type[0] == PARTICLE_TYPE_LAUNCHER) {
        if (age >= launcher_lifetime) {
            go_type = PARTICLE_TYPE_SHELL;
            go_position = vo_position[0];
            vec3 Dir = GetRandomDir(time/1000.0);
            Dir.y = max(Dir.y, 0.5);
            go_velocity = normalize(Dir) / 20.0;
            go_age = 0.0;
            EmitVertex();
            EndPrimitive();
            age = 0.0;
        }

        go_type = PARTICLE_TYPE_LAUNCHER;
        go_position = vo_position[0];
        go_velocity = vo_velocity[0];
        go_age = age;
        EmitVertex();
        EndPrimitive();
    }
    else {
        float DeltaTimeSecs = delta_ms / 1000.0f;
        float t1 = vo_age[0] / 1000.0;
        float t2 = age / 1000.0;
        vec3 DeltaP = DeltaTimeSecs * vo_velocity[0];
        vec3 DeltaV = vec3(DeltaTimeSecs) * (0.0, -9.81, 0.0);

        if (vo_type[0] == PARTICLE_TYPE_SHELL)  {
                if (age < shell_lifetime) {
                    go_type = PARTICLE_TYPE_SHELL;
                    go_position = vo_position[0] + DeltaP;
                    go_velocity = vo_velocity[0] + DeltaV;
                    go_age = age;
                    EmitVertex();
                    EndPrimitive();
                }
            else {
                for (int i = 0 ; i < 10 ; i++) {
                     go_type = PARTICLE_TYPE_SECONDARY_SHELL;
                     go_position = vo_position[0];
                     vec3 Dir = GetRandomDir((time + i)/1000.0);
                     go_velocity = normalize(Dir) / 20.0;
                     go_age = 0.0f;
                     EmitVertex();
                     EndPrimitive();
                }
            }
        }
        else {
            if (age < secondary_shell_lifetime) {
                go_type = PARTICLE_TYPE_SECONDARY_SHELL;
                go_position = vo_position[0] + DeltaP;
                go_velocity = vo_velocity[0] + DeltaV;
                go_age = age;
                EmitVertex();
                EndPrimitive();
            }
        }
    }
}




















