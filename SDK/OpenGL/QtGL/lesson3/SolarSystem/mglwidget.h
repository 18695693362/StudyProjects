#ifndef MGLWIDGET_H
#define MGLWIDGET_H

#include <QGLWidget>
#include <QtOpenGL>
#include "geometryengine.h"

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
    virtual void mousePressEvent(QMouseEvent *e);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void keyReleaseEvent(QKeyEvent *key);
    virtual void timerEvent(QTimerEvent *e);

private:
    enum RotateDirction
    {
        kInvalid,
        kX,
        kY,
        kZ
    };
    void    SetRotateDirction(RotateDirction dirction);
    void    DrawGeometry();

    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    GLfloat rotate_angle_x_;
    GLfloat rotate_angle_y_;
    GLfloat rotate_angle_z_;

    GLfloat sun_rotate_angle_x_;
    GLfloat sun_rotate_angle_y_;
    GLfloat sun_rotate_angle_z_;

    GLfloat earth_rotate_angle_x_;
    GLfloat earth_rotate_angle_y_;
    GLfloat earth_rotate_angle_z_;

    GLfloat earth_relative_sun_rotate_angle_x_;
    GLfloat earth_relative_sun_rotate_angle_y_;
    GLfloat earth_relative_sun_rotate_angle_z_;

    GLfloat moon_rotate_angle_x_;
    GLfloat moon_rotate_angle_y_;
    GLfloat moon_rotate_angle_z_;

    GLfloat moon_ralative_earth_rotate_angle_x_;
    GLfloat moon_ralative_earth_rotate_angle_y_;
    GLfloat moon_ralative_earth_rotate_angle_z_;

    GeometryEngine m_geometryEngine;

    QBasicTimer m_timer;

    QPointF m_mousePressPos;
    GLdouble m_curModleViewMatrix[16];
    GLdouble m_curProjectionMatrix[16];
    int      m_curViewPort[4];
};

#endif // MGLWIDGET_H
