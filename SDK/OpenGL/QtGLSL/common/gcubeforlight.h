#ifndef GCUBEFORLIGHT_H
#define GCUBEFORLIGHT_H
#include "gmodel.h"
#include "glhelper.h"
#include "gcube.h"
#include <string>
#include <array>
#include <vector>

class GCubeForLight : public GModel
{
public:
    GCubeForLight();
    void Init(const char* v_shader, const char* f_shader, GUniformType* uniform_types, int count=0);

    void Draw();

private:
    void SetLightInDraw();

    GLuint _vertex_buffer;
    GLuint _vertex_arr_obj;
    GLuint _program;
};

#endif // GCUBEFORLIGHT_H
