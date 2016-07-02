#ifndef GOGLWIDGET_H
#define GOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include "glm/gtc/matrix_transform.hpp"
#include "../../common/gtriangle.h"
#include "../../common/gcube.h"
#include "../../common/gcubeforlight.h"
#include "../../common/gskybox.h"
#include "../../common/gcamera.h"

class GOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GOGLWidget(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    GTriangle       _triangle;
    GCube           _cube;
    GSkybox         _skybox;
    GCubeForLight   _cube_for_light;

    GCamera     _camera;
    QTimer*     _mouse_timer;
    QPoint      _mouse_pos;
};

#endif // GOGLWIDGET_H
