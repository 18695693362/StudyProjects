#include "mglwidget.h"
#include <GL/glu.h>
#include <iostream>
using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

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
    glOrtho(0.0f, kDesignSizeW, 0.0, kDesignSizeH, -100, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 ); //this is default value
    gluLookAt(0.0,0.0,10.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );
}

void MGLWidget::paintGL()
{
    static int counter = 0;
    counter++;

    GLdouble left_bottom_pos[]={0.0,0.0};
    GLdouble left_top_pos[]={0.0,kDesignSizeH};
    GLdouble right_bottom_pos[]={kDesignSizeW,0.0};
    GLdouble right_top_pos[]={kDesignSizeW,kDesignSizeH};
#define kMaxCounter 120

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPointSize(4.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    {
        if(counter <= kMaxCounter/2)
        {
            glColor3f(1.0f,0.0f,0.0f);
            glVertex2dv(left_bottom_pos);
            glColor3f(0.0f,0.0f,0.0f);
            glVertex2dv(right_top_pos);
        }
        else if(counter > kMaxCounter/2 && counter < kMaxCounter)
        {
            glColor3f(1.0f,0.0f,0.0f);
            glVertex2dv(left_top_pos);
            glColor3f(0.0f,0.0f,0.0f);
            glVertex2dv(right_bottom_pos);
        }
        else
        {
            counter = 0;
        }
    }
    glEnd();

    cout << counter << endl;
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



















