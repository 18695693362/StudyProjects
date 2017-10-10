#ifndef GPARTICLESYSTEM_H
#define GPARTICLESYSTEM_H
#include "glm/glm.hpp"
#include <QtOpenGL>
#include "../../common/gcamera.h"
#include "grandomtexture.h"

class GParticleSystem
{
public:
    GParticleSystem();
    ~GParticleSystem();
    void Init(const glm::vec3 &pos);
    void Draw(GCamera* camera);

private:
    void InitUpdateShaderProg();
    void InitRenderShaderProg();
    void UpdateParticles(int delta_ms);
    void RenderParticles(GCamera* camera);

    bool _is_first;
    int _cur_bo_idx;
    int _cur_tfo_idx;
    GLuint _bo_arr[2];
    GLuint _tfo_arr[2];
    GRandomTexture _random_tex;
    double _time;

    GLuint _update_prog;
    GLuint _delta_ms_location;
    GLuint _random_tex_location;
    GLuint _time_location;
    GLuint _launcher_lifetime_location;
    GLuint _shell_lifetime_location;
    GLuint _secondary_shell_lifetime_location;

    GLuint _render_prog;
    GLuint _fire_texture;
    GLuint _vp_mat_location;
    GLuint _eye_pos_location;
    GLuint _color_map_location;
    GLuint _billboard_size_location;
};

#endif // GPARTICLESYSTEM_H
