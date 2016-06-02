#ifndef GOGLWIDGET_H
#define GOGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLDebugLogger>
#include <QOpenGLFunctions>
#include "glm/gtc/matrix_transform.hpp"
#include "../../common/gtriangle.h"

class GOGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit GOGLWidget(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:
    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    GTriangle _triangle;
};

#endif // GOGLWIDGET_H
