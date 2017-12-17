#ifndef GSKYBOX_H
#define GSKYBOX_H

#include "gcubemaptexture.h"
#include "gmodel.h"

class GSkybox :public GModel
{
public:
    GSkybox();
    void Init(const char* pos_x, const char* neg_x, const char* pos_y, const char* neg_y, const char* pos_z, const char* neg_z, QImage::Format img_format);
    void Draw();

    void GetVertexData(GLfloat *&vertex_data, GLuint *&vertex_index_data, GLfloat *&vertex_color_data,
                       int &vertex_data_size, int &index_data_size, int &color_data_size,
                       int &vertex_pos_comp_count, int &vertex_color_comp_count);

private:
    GLint  _kPosAttribLocal;
    GLint  _kColorAttribLocal;
    GLint  _scaleUniformLocal;
    GLint  _colorUniformLocal;
    GLint  _moveUniformLocal;
    GLint  _viewMatrixUniformLocal;
    GLint  _projectionMatrixUniformLocal;

    GLint  _cubeSamplerVarUniformLocal;

    GLuint _vertex_buffer;
    GLuint _vertex_arr_obj;
    GLuint _vertex_index_buffer;
    GLuint _program;

    GCubemapTexture _cube_tex_obj;
};

#endif // GSKYBOX_H
