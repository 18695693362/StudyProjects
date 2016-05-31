#ifndef TESTVBOBJECT_H
#define TESTVBOBJECT_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include "../../../common/vbm.h"


class TestVBObject : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit TestVBObject(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:
    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    GLint  program;
    VBObject vbobject;

    enum ObjectType {
        Triangle,
        ObjectNum
    };
    GLuint vaoject[ObjectNum];
    enum AttribLocal{
        PosAttribLocal,
        NormalAttribLocal,
        ColorAtrribLocal,
        AttribLocalNum
    };
    GLint attrib_locals[AttribLocalNum];
    enum BufferType{
        ArrayBuffer,
        BufferNum
    };
    GLuint buffers[BufferNum];
};

#endif // TESTVBOBJECT_H
