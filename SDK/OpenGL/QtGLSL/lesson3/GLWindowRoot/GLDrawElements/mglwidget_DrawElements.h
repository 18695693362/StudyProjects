#ifndef MGLWIDGET_DRAWCM_H
#define MGLWIDGET_DRAWCM_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLExtraFunctions>
#include "glm/gtc/matrix_transform.hpp"

class MGLWidgetDrawElements : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit MGLWidgetDrawElements(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:
    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;
};

#endif // MGLWIDGET_DRAWCM_H
