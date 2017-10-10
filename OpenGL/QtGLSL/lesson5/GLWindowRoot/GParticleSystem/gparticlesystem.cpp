#include "gparticlesystem.h"
#include "../../common/glhelper.h"
#include "../../common/glfuncdefine.h"
#include <glm/gtc/type_ptr.hpp>

enum EParticleType
{
    kEmitter = 1,
    kShell,
    kSecondaryShell
};

struct GParticle
{
    float type;
    glm::vec3 pos;
    glm::vec3 velocity;
    float age;  // ms
};

GParticleSystem::GParticleSystem()
{
    _cur_bo_idx = 0;
    _cur_tfo_idx = 1;
    _is_first = true;
    _time = 0;
}

GParticleSystem::~GParticleSystem()
{
}

void GParticleSystem::Init(const glm::vec3 &pos)
{
    static const int max_particle = 1000;
    GParticle particles[max_particle];
    memset(&particles, 0, sizeof(particles));

    particles[0].type = (float)EParticleType::kEmitter;
    particles[0].pos = pos;
    particles[0].velocity = glm::vec3(0.0,0.0001,0.0);
    particles[0].age = 0.0f;

    glGenTransformFeedbacks(2, _tfo_arr);
    glGenBuffers(2, _bo_arr);

    for(int i=0; i<2; i++)
    {
        glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _tfo_arr[i]);
        glBindBuffer(GL_ARRAY_BUFFER, _bo_arr[i]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(particles), particles, GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_TRANSFORM_FEEDBACK, 0, _bo_arr[i]);
    }

    InitUpdateShaderProg();
    InitRenderShaderProg();
}

void GParticleSystem::Draw(GCamera* camera)
{
    _time += 33;

    UpdateParticles(33);
    RenderParticles(camera);

    _cur_bo_idx = _cur_tfo_idx;
    _cur_tfo_idx = (_cur_tfo_idx + 1) & 0x1;
}

void GParticleSystem::InitUpdateShaderProg()
{
    GLHelper::SetDeleteShader(false);
    _update_prog = GLHelper::CreateShaderProgramWithFiles(
                ":ParticleSystemUpdate.vert",
                ":ParticleSystemUpdate.frag",
                ":ParticleSystemUpdate.geom");
    const char* varyings[] = {
        "go_type",
        "go_position",
        "go_velocity",
        "go_age"
    };
    glTransformFeedbackVaryings(_update_prog, 4, varyings, GL_INTERLEAVED_ATTRIBS);
    GLHelper::IsGLError();
    glLinkProgram(_update_prog);
    glUseProgram(_update_prog);

    _delta_ms_location = GLHelper::GetUniformLocal(_update_prog, "delta_ms");
    _time_location = GLHelper::GetUniformLocal(_update_prog, "time");
    _random_tex_location = GLHelper::GetUniformLocal(_update_prog, "random_tex");
    _launcher_lifetime_location = GLHelper::GetUniformLocal(_update_prog, "launcher_lifetime");
    _shell_lifetime_location = GLHelper::GetUniformLocal(_update_prog, "shell_lifetime");
    _secondary_shell_lifetime_location = GLHelper::GetUniformLocal(_update_prog, "secondary_shell_lifetime");

    glUniform1i(_random_tex_location, 3);
    glUniform1f(_launcher_lifetime_location, 100.f);
    glUniform1f(_shell_lifetime_location, 10000.f);
    glUniform1f(_secondary_shell_lifetime_location, 2500.f);

    _random_tex.Init(1000);
    _random_tex.Bind(GL_TEXTURE3);
    GLHelper::SetDeleteShader(true);
}

void GParticleSystem::InitRenderShaderProg()
{
    GLHelper::SetDeleteShader(false);
    _render_prog = GLHelper::CreateShaderProgramWithFiles(
                ":ParticleSystemRender.vert",
                ":ParticleSystemRender.frag",
                ":ParticleSystemRender.geom");
    glLinkProgram(_render_prog);
    glUseProgram(_render_prog);

    _vp_mat_location = GLHelper::GetUniformLocal(_render_prog, "gVP");
    _eye_pos_location = GLHelper::GetUniformLocal(_render_prog, "gCameraPos");
    _color_map_location = GLHelper::GetUniformLocal(_render_prog, "gColorMap");
    _billboard_size_location = GLHelper::GetUniformLocal(_render_prog, "gBillboardSize");

    glUniform1i(_color_map_location, 0);
    glUniform1i(_billboard_size_location, 0.01);

    GLenum param_names[]  = {GL_TEXTURE_WRAP_S,GL_TEXTURE_WRAP_T,GL_TEXTURE_MIN_FILTER,GL_TEXTURE_MAG_FILTER};
    GLenum param_values[] = {GL_REPEAT,GL_REPEAT,GL_LINEAR,GL_LINEAR};
    GLHelper::LoadTexture(_fire_texture,GL_TEXTURE_2D,param_names,param_values,4,QImage::Format_RGB888,true,"fire_red.jpg");
    GLHelper::SetDeleteShader(true);
}

void GParticleSystem::UpdateParticles(int delta_ms)
{
    glUseProgram(_update_prog);
    glUniform1f(_time_location, _time);
    glUniform1f(_delta_ms_location, delta_ms);

    _random_tex.Bind(GL_TEXTURE3);

    glEnable(GL_RASTERIZER_DISCARD);
    glBindBuffer(GL_ARRAY_BUFFER, _bo_arr[_cur_bo_idx]);
    glBindTransformFeedback(GL_TRANSFORM_FEEDBACK, _tfo_arr[_cur_tfo_idx]);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(0, 1, GL_FLOAT,GL_FALSE,sizeof(GParticle),BUFF_OFFSET(0));
    glVertexAttribPointer(1, 3, GL_FLOAT,GL_FALSE,sizeof(GParticle),BUFF_OFFSET(4));
    glVertexAttribPointer(2, 3, GL_FLOAT,GL_FALSE,sizeof(GParticle),BUFF_OFFSET(16));
    glVertexAttribPointer(3, 1, GL_FLOAT,GL_FALSE,sizeof(GParticle),BUFF_OFFSET(28));

    glBeginTransformFeedback(GL_POINTS);
    if(_is_first)
    {
        glDrawArrays(GL_POINTS, 0, 1);
        _is_first = false;
    }
    else
    {
        glDrawTransformFeedback(GL_POINTS, _tfo_arr[_cur_bo_idx]);
    }
    glEndTransformFeedback();
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);

    glUseProgram(0);
}

void GParticleSystem::RenderParticles(GCamera *camera)
{
    glUseProgram(_render_prog);
    glm::mat4x4 view_mat;
    camera->GetViewMatrix(view_mat);
    glm::mat4x4 proj_mat;
    camera->GetCurProjectionMatrix(proj_mat);
    glm::mat4x4 vp_mat = proj_mat * view_mat;
    glUniformMatrix4fv(_vp_mat_location, 1, GL_FALSE,glm::value_ptr(vp_mat));
    //glUniformMatrix4fv(_vp_mat_location, 1, GL_FALSE,glm::value_ptr(glm::mat4(1.0)));
    glUniform3fv(_eye_pos_location, 1, glm::value_ptr(camera->GetPosition()));
    glBindTexture(_fire_texture, GL_TEXTURE_2D);

    glDisable(GL_RASTERIZER_DISCARD);
    glBindBuffer(GL_ARRAY_BUFFER, _bo_arr[_cur_tfo_idx]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(GParticle), BUFF_OFFSET(4));
    glDrawTransformFeedback(GL_POINTS, _tfo_arr[_cur_tfo_idx]);
    glDisableVertexAttribArray(0);

    glUseProgram(0);
}























