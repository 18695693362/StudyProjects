#include "mglwidget.h"
#ifdef Q_OS_WIN
#include <GL/glu.h>
#endif
#ifdef Q_OS_MAC
#include <OpenGL/glu.h>
#endif
#include <QtMath>
#include <QtGui>
#include <iostream>
using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

enum EDrawType
{
    kDraw_Point,
    kDraw_Line,
    kDraw_Triangle,
    kDraw_Rect,
    kDraw_Polygon,
    kDraw_Circle,
    kDraw_InvalidMax
};

EDrawType g_draw_type = kDraw_Point;

GLdouble g_left_bottom_pos[]={0.0,0.0};
GLdouble g_left_top_pos[]={0.0,kDesignSizeH};
GLdouble g_right_bottom_pos[]={kDesignSizeW,0.0};
GLdouble g_right_top_pos[]={kDesignSizeW,kDesignSizeH};
GLdouble g_middle_pos[]={kDesignSizeW/2,kDesignSizeH/2};

void draw_point()
{
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    {
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2dv(g_middle_pos);
    }
    glEnd();
}

void draw_line()
{
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    {
        glColor3f(1.0f,0.0f,0.0f);
        glVertex2dv(g_left_bottom_pos);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2dv(g_right_top_pos);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex2dv(g_left_top_pos);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2dv(g_right_bottom_pos);
    }
    glEnd();
}

void draw_triangle()
{
    glLineWidth(2.0f);
    glBegin(GL_POLYGON);
    {
        double r = 150;
        GLdouble top[] = {kDesignSizeW/2,kDesignSizeH/2+r};
        GLdouble bottom_left[] = {kDesignSizeW/2-r,kDesignSizeH/2-r};
        GLdouble bottom_right[] = {kDesignSizeW/2+r,kDesignSizeH/2-r};

        glColor3f(1.0f,0.0f,0.0f);
        glVertex2dv(top);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2dv(bottom_left);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex2dv(bottom_right);
    }
    glEnd();
}

void draw_rect()
{
    glLineWidth(2.0f);
    glBegin(GL_POLYGON);
    {
        double half_d = 150;
        GLdouble top_left[] = {kDesignSizeW/2-half_d,kDesignSizeH/2+half_d};
        GLdouble top_right[] = {kDesignSizeW/2+half_d,kDesignSizeH/2+half_d};
        GLdouble bottom_left[] = {kDesignSizeW/2-half_d,kDesignSizeH/2-half_d};
        GLdouble bottom_right[] = {kDesignSizeW/2+half_d,kDesignSizeH/2-half_d};

        glColor3f(1.0f,0.0f,0.0f);
        glVertex2dv(top_left);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2dv(top_right);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex2dv(bottom_right);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2dv(bottom_left);
    }
    glEnd();
}

void draw_polygon()
{
    glLineWidth(2.0f);
    glBegin(GL_POLYGON);
    {
        double half_d = 100;
        GLdouble top_left[] = {kDesignSizeW/2-half_d,kDesignSizeH/2+half_d};
        GLdouble top_right[] = {kDesignSizeW/2+half_d,kDesignSizeH/2+half_d};
        GLdouble middle_right[] = {kDesignSizeW/2+half_d*2,kDesignSizeH/2};
        GLdouble bottom_left[] = {kDesignSizeW/2-half_d,kDesignSizeH/2-half_d};
        GLdouble bottom_right[] = {kDesignSizeW/2+half_d,kDesignSizeH/2-half_d};
        GLdouble middle_left[] = {kDesignSizeW/2-half_d*2,kDesignSizeH/2};

        glColor3f(1.0f,0.0f,0.0f);
        glVertex2dv(top_left);
        glColor3f(0.0f,1.0f,0.0f);
        glVertex2dv(top_right);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2dv(middle_right);
        glColor3f(0.0f,0.0f,1.0f);
        glVertex2dv(bottom_right);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex2dv(bottom_left);
        glColor3f(1.0f,1.0f,1.0f);
        glVertex2dv(middle_left);
    }
    glEnd();
}

void draw_circle()
{
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    {
        double half_d = 100;
        GLdouble pos[] = {kDesignSizeW,kDesignSizeH/2};
#define kPI         3.14159265
#define kPartsCount 360
#define kDeltaTheta kPI*2/kPartsCount
        glColor3f(1.0f,0.0f,0.0f);
        for(int i=0; i< kPartsCount; i++)
        {
            pos[0] = kDesignSizeW/2 + qCos(kDeltaTheta*i)*half_d;
            pos[1] = kDesignSizeH/2 + qSin(kDeltaTheta*i)*half_d;
            glVertex2dv(pos);
        }
    }
    glEnd();
}


MGLWidget::MGLWidget(QWidget *parent, const char* name, bool full_screen) :
    QGLWidget(parent)
{
    setGeometry( kDefaultX, kDefaultY, kDesignSizeW, kDesignSizeH );
    setMinimumSize(kMinWidth, kMinHeight);
    window_width_ = kDesignSizeW;
    window_height_= kDesignSizeH;

    setWindowTitle(name);

    is_full_screen_ = full_screen;
    if(is_full_screen_)
        showFullScreen();

    rotate_angle_x_ = 0.0f;
    rotate_angle_y_ = 0.0f;
    rotate_angle_z_ = 0.0f;
}


void MGLWidget::initializeGL()
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, kDesignSizeW, 0.0, kDesignSizeH, -1000, 1000);
}

void MGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 ); //this is default value
    gluLookAt(0.0,0.0,100.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );

    glTranslatef(g_middle_pos[0],g_middle_pos[1],0.0f);
    glRotatef(rotate_angle_x_,1,0,0);
    glRotatef(rotate_angle_y_,0,1,0);
    glRotatef(rotate_angle_z_,0,0,1);
    glTranslatef(-g_middle_pos[0],-g_middle_pos[1],0.0f);

    glLineWidth(2.0f);
    DrawGeometry();

    cout << endl;
    cout << " rotate_angle_x_:" << rotate_angle_x_;
    cout << " rotate_angle_y_:" << rotate_angle_y_;
    cout << " rotate_angle_z_:" << rotate_angle_z_;
    cout << endl;
}

void MGLWidget::resizeGL(int w, int h)
{
    if(w < kMinWidth || h < kMinHeight)
    {
        w = kMinWidth;
        h = kMinHeight;
    }
    window_width_ = w;
    window_height_= h;

    glViewport(0,0,window_width_,window_height_);
}

void MGLWidget::DrawGeometry()
{
    switch (g_draw_type)
    {
    case kDraw_Point:
    {
        draw_point();
        break;
    }
    case kDraw_Line:
    {
        draw_line();
        break;
    }
    case kDraw_Triangle:
    {
        draw_triangle();
        break;
    }
    case kDraw_Rect:
    {
        draw_rect();
        break;
    }
    case kDraw_Polygon:
    {
        draw_polygon();
        break;
    }
    case kDraw_Circle:
    {
        draw_circle();
        break;
    }
    default:
        break;
    }
}

void MGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    g_draw_type = (EDrawType)((int)g_draw_type+1);
    g_draw_type = (EDrawType)((int)g_draw_type%kDraw_InvalidMax);

    updateGL();
}

void MGLWidget::keyReleaseEvent(QKeyEvent *key)
{
    //initializeGL();
    switch (key->key())
    {
    case Qt::Key_0:
    {
        break;
    }
    case Qt::Key_Left:
    {
        rotate_angle_y_ += 15.0f;
        break;
    }
    case Qt::Key_Up:
    {
        rotate_angle_x_ += 15.0f;
        break;
    }
    case Qt::Key_Right:
    {
        rotate_angle_y_ -= 15.0f;
        break;
    }
    case Qt::Key_Down:
    {
        rotate_angle_x_ -= 15.0f;
        break;
    }
    default:
        break;
    }
    updateGL();
}








