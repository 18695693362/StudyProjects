#ifndef GSIMPLETRIANGLE_H
#define GSIMPLETRIANGLE_H

#include <QtOpenGL>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include <string>

class GSimpleTriangle
{
public:
    GSimpleTriangle(bool is_vertex_ccw=true);
    void Init(GLfloat* pos_data=nullptr, int size=0, int count=0);
    void Draw();
    void SetTranslate(const glm::vec3& translate)
    {
        _translate = translate;
    }
    glm::vec3 GetTranslate()
    {
        return _translate;
    }
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
    void GetVertexData(GLfloat *&vertex_data, int &size, int &count, int &pos_comp_count, int &color_comp_count);

private:
    bool   _is_vertex_ccw;
    bool   _is_inited;

    GLint  _kPosAttribLocal;
    GLint  _kColorAttribLocal;

    GLint  _scaleUniformLocal;
    GLint  _colorUniformLocal;
    GLint  _translateUniformLocal;

    int    _size;   // pos_data size
    int    _count;  // pos count

    GLuint _vaobject;
    GLuint _vbobject;
    GLuint _program;

    glm::vec3 _translate;
    glm::vec4 _color;
    float     _scale;
};

#endif // GSIMPLETRIANGLE_H
