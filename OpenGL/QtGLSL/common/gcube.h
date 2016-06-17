#ifndef GCUBE_H
#define GCUBE_H
#include <QtOpenGL>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

class GCube
{
public:
    GCube();
    void Init();

    void GetVertexData(GLfloat *&vertex_data, GLuint *&vertex_index_data, int &vertex_data_size, int &index_data_size, int &vertex_pos_comp_count);
    void Draw();

    void SetScale(float scale);
    float GetScale()
    {
        return _scale;
    }
    void SetColor(glm::vec4 color);
    glm::vec4 GetColor()
    {
        return _color;
    }
private:
    bool _is_inited;

    glm::vec4 _color;
    float     _scale;

    GLint  _kPosAttribLocal;
    GLint  _scaleUniformLocal;
    GLint  _colorUniformLocal;

    GLuint _vertex_buffer;
    GLuint _vertex_arr_obj;
    GLuint _vertex_index_buffer;
    GLuint _program;
};

#endif // GCUBE_H
