#ifndef MGLWIDGET_H
#define MGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>

class MGLWidgetUniformBlock : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit MGLWidgetUniformBlock(QWidget *parent = 0, const char* name="", bool full_screen=false);
    
signals:
    
public slots:

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:
    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;
};

#endif // MGLWIDGET_H
