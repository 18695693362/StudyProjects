#ifndef GPOINTLIGHT_H
#define GPOINTLIGHT_H
#include "gmodel.h"

class GLightBase : public GModel
{};

class GPointLight : public GLightBase
{
public:
    GPointLight();
    void Init();

    void GetVertexData(GLfloat *&vertex_data, GLuint *&vertex_index_data, GLfloat *&vertex_color_data,
                       int &vertex_data_size, int &index_data_size, int &color_data_size,
                       int &vertex_pos_comp_count, int &vertex_color_comp_count);
    void Draw();
private:
    GLint  _kPosAttribLocal;
    GLint  _kColorAttribLocal;
    GLint  _scaleUniformLocal;
    GLint  _colorUniformLocal;
    GLint  _moveUniformLocal;
    GLint  _viewMatrixUniformLocal;
    GLint  _projectionMatrixUniformLocal;

    GLuint _vertex_buffer;
    GLuint _vertex_arr_obj;
    GLuint _vertex_index_buffer;
    GLuint _program;
};

#endif // GPOINTLIGHT_H
