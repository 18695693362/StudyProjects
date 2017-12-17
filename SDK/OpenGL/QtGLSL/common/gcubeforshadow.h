#ifndef GCUBEFORSHADOW_H
#define GCUBEFORSHADOW_H

#include <QOpenGLFunctions_4_1_Core>
#include "gmodel.h"
class GCubeForShadow:public GModel, protected QOpenGLFunctions_4_1_Core
{
public:
    GCubeForShadow();
    void Init(const char* v_shader, const char* f_shader, GUniformType* uniform_types, int count=0);

    enum GDrawState
    {
        kNoDraw,
        kDrawForShadow,
        kDraw
    };
    void Draw();

private:
    void DrawHelper(GDrawState state);
    void InitShodowShader();
    void SetUniformInDraw(GDrawState state);
    void SetLightInDraw();

    GLuint _vertex_buffer;
    GLuint _vertex_arr_obj;
    GLuint _program[2];

    const int _depth_tex_size = 1024;
    GLuint _depth_tex_obj;
    GLuint _depth_fbo;
};

#endif // GCUBEFORSHADOW_H
