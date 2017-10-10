#ifndef GOGLWIDGET_H
#define GOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLExtraFunctions>
#include "glm/gtc/matrix_transform.hpp"
#include "../../common/gtriangle.h"
#include "../../common/gcamera.h"
#include "gparticlesystem.h"

class GOGLWidget : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GOGLWidget(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

    void keyReleaseEvent(QKeyEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    GTriangle           _triangle;
    GCamera             _camera;
    GParticleSystem     _ps;

    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;
};

#endif // GOGLWIDGET_H
