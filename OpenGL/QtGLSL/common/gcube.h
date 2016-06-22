#ifndef GCUBE_H
#define GCUBE_H
#include <QtOpenGL>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include <functional>

class GCube
{
public:
    GCube();
    void Init();

    void GetVertexData(GLfloat *&vertex_data, GLuint *&vertex_index_data, GLfloat *&vertex_color_data,
                       int &vertex_data_size, int &index_data_size, int &color_data_size,
                       int &vertex_pos_comp_count, int &vertex_color_comp_count);
    void Draw();

    void SetTranslate(const glm::vec3& translate)
    {
        _translate = translate;
    }
    void SetScale(float scale)
    {
        _scale = scale;
    }
    float GetScale()
    {
        return _scale;
    }
    void SetColor(glm::vec4 color)
    {
        _color = color;
    }
    glm::vec4 GetColor()
    {
        return _color;
    }
    void SetViewMatrixGetter(std::function<void(glm::mat4x4&)> getter)
    {
        _view_matrix_getter = getter;
    }

    void SetProjectionMatrixGetter(std::function<void(glm::mat4x4&)> getter)
    {
        _projection_matrix_getter = getter;
    }
private:
    bool _is_inited;
    glm::vec3 _translate;
    glm::vec4 _color;
    float     _scale;
    std::function<void(glm::mat4x4&)> _view_matrix_getter;
    std::function<void(glm::mat4x4&)> _projection_matrix_getter;

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

#endif // GCUBE_H
