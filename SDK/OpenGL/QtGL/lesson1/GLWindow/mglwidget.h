#ifndef MGLWIDGET_H
#define MGLWIDGET_H

#include <QGLWidget>

class MGLWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MGLWidget(QWidget *parent = 0, const char* name="", bool full_screen=false);
    
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
