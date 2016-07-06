#ifndef GOGLWIDGET_H
#define GOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include <QCheckBox>
#include "glm/gtc/matrix_transform.hpp"
#include "../../common/gtriangle.h"
#include "../../common/gcube.h"
#include "../../common/gcubeforlight.h"
#include "../../common/gskybox.h"
#include "../../common/gcamera.h"
#include "../../common/glight.h"

class GOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GOGLWidget(QWidget *parent = 0, const char* name="", bool full_screen=false);
    ~GOGLWidget();

public slots:
    void OnSelectedLight();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void keyReleaseEvent(QKeyEvent * event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
private:
    void InitLights();
    void InitLight(GLightBase &light, int index);
    void InitCubes();
    void InitCube(GCubeForLight &cube, int index);
    void InitCubeForLight(GCubeForLight &cube, int index, GLightBase &light);

    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    GTriangle       _triangle;
    GCube           _cube;
    GSkybox         _skybox;

    GCubeLight          _cube_light;

    static const int    _kLightsCount = 3;
    GLightBase*         _lights[_kLightsCount];
    QCheckBox*          _lights_switchers[_kLightsCount];

    static const int    _kCubesCount = 6;
    GCubeForLight       _cubes[_kCubesCount];

    GCamera     _camera;
    QTimer*     _mouse_timer;
    QPoint      _mouse_pos;

    QLayout*  _layout;
};

#endif // GOGLWIDGET_H
