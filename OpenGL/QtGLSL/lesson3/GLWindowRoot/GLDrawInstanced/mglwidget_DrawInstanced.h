#ifndef MGLWIDGET_DRAWCM_H
#define MGLWIDGET_DRAWCM_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include "glm/gtc/matrix_transform.hpp"
#include "../../../common/vbm.h"
class MGLWidgetDrawInstanced : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MGLWidgetDrawInstanced(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

protected slots:
    void messageLogged(const QOpenGLDebugMessage &msg);

private:
    void _InitOpenGLLogging();
    void _UpdateTransformMatrix(unsigned int type,glm::mat4 matrix);

    QOpenGLDebugLogger* gl_logger_;
    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    VBObject vbobject;
};

#endif // MGLWIDGET_DRAWCM_H
