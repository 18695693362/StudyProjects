#ifndef TESTVBOBJECT_H
#define TESTVBOBJECT_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include "../../../common/vbm.h"
#include "../../../common/glhelper.h"

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
    GTriangle _triangle;
};

#endif // TESTVBOBJECT_H
