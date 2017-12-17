#ifndef MULTISAMPLINGGLWIDGET_H
#define MULTISAMPLINGGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "../../common/gsimpletriangle.h"

class MultiSamplingGLWidget : public QOpenGLWidget, private QOpenGLExtraFunctions
{
public:
    MultiSamplingGLWidget(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:
    GSimpleTriangle _triangle1;
    GSimpleTriangle _triangle2;

    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;
};

#endif // MULTISAMPLINGGLWIDGET_H
