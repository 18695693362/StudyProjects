#ifndef GOGLWIDGET_H
#define GOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions_4_1_Core>
#include "glm/gtc/matrix_transform.hpp"
#include "../../common/gtriangle.h"
#include "../../common/gcube.h"
#include "../../common/gcubeforlight.h"
#include "../../common/gcubeforshadow.h"
#include "../../common/gskybox.h"
#include "../../common/gcamera.h"
#include "../../common/glight.h"

class GOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_1_Core
{
    Q_OBJECT
public:
    static int GetWindowWidth();
    static int GetWindowHeight();
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
    static GOGLWidget* _main_window;

    void InitPointLight();
    void InitCubeForLight(GCubeForShadow &cube, int index, GLightBase &light);

    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    GTriangle       _triangle;
    GCube           _cube;
    GSkybox         _skybox;

    GCubeLight          _point_light;
    static const int    _kCubesCount = 6;
    GCubeForShadow    	_cubes[_kCubesCount];

    GLuint      _depth_tex_obj;
    GLuint		_depth_fbo;

    GCamera     _camera;
    QTimer*     _mouse_timer;
    QPoint      _mouse_pos;
};

#endif // GOGLWIDGET_H
