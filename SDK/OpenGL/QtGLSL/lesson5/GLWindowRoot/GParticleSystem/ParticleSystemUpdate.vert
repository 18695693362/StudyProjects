#version 410 core
layout (location = 0) in float vi_type;
layout (location = 1) in vec3 vi_position;
layout (location = 2) in vec3 vi_velocity;
layout (location = 3) in float vi_age;

out float vo_type;
out vec3 vo_position;
out vec3 vo_velocity;
out float vo_age;

void main()
{
    vo_type = vi_type;
    vo_position = vi_position;
    vo_velocity = vi_velocity;
    vo_age = vi_age;
}
