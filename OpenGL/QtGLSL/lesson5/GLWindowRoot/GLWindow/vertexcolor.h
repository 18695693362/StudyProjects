#ifndef VERTEXCOLOR_H
#define VERTEXCOLOR_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include "glm/gtc/matrix_transform.hpp"
#include "../../common/gtriangle.h"

class VertexColor : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit VertexColor(QWidget *parent = 0, const char* name="", bool full_screen=false);
    struct VertexData
    {
        GLubyte color[4];
        GLfloat position[4];
    };

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:
    void GetVertexData(GLvoid *&vertex_data_ptr, int &size, int &vertex_count);
    enum AttribLocal
    {
        kPosAttribLocal,
        kColorAttribLocal,
    };
    GLuint  _vabuffer;
    GLuint  _vaobject;
    int     _vertex_count;
    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;
    GLint   _program;
    GTriangle _triangle;
};

#endif // VERTEXCOLOR_H
