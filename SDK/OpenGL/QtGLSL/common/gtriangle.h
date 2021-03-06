#ifndef GTRIANGLE_H
#define GTRIANGLE_H

#include <QtOpenGL>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include <string>

class GTriangle
{
public:
    GTriangle(std::string tex_name="wall.jpg");
    void Init(GLfloat* pos_data=nullptr, int size=0, int count=0);
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
    void GetPosData(GLfloat *&pos_data, int& size, int& count);
    void GetVertexData(GLfloat *&vertex_data, int &size, int &count, int &pos_comp_count, int &tex_coor_comp_count);

private:
    bool   _is_inited;

    GLint  _kPosAttribLocal;
    GLint  _kTexCoorAttribLocal;

    GLint  _scaleUniformLocal;
    GLint  _colorUniformLocal;
    int    _size;   // pos_data size
    int    _count;  // pos count

    GLuint _vaobject;
    GLuint _vabuffer;
    GLuint _texture;
    GLuint _program;

    glm::vec4 _color;
    float     _scale;

    std::string _tex_name;
};

#endif // GTRIANGLE_H
