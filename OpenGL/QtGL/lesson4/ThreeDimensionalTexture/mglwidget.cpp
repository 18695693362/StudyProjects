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
#include "glextensions.h"
using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

#define kCheckImageWidth    16
#define kCheckImageHeight   16
#define kCheckImageDepth    16
static GLubyte check_image[kCheckImageDepth][kCheckImageHeight][kCheckImageWidth][3];
static GLuint texture_name;

void MakeCheckImage()
{
    for(int s=0; s<kCheckImageWidth; s++)
    {
        for(int t=0; t<kCheckImageHeight; t++)
        {
            for(int r=0; r<kCheckImageDepth; r++)
            {
                check_image[r][t][s][0] = s*17;
                check_image[r][t][s][1] = t*17;
                check_image[r][t][s][2] = r*17;
            }
        }
    }
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

    MakeCheckImage();
}


void MGLWidget::initializeGL()
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glGenTextures(1,&texture_name);
    glBindTexture(GL_TEXTURE_3D,texture_name);

    glTexImage3D(GL_PROXY_TEXTURE_3D,0,GL_RGB,kCheckImageWidth,kCheckImageHeight,
                 kCheckImageDepth,0,GL_RGB,GL_UNSIGNED_BYTE,NULL);
    GLint width;
    glGetTexLevelParameteriv(GL_PROXY_TEXTURE_3D,0,GL_TEXTURE_WIDTH,&width);
    glTexImage3D(GL_TEXTURE_3D,0,GL_RGB,kCheckImageWidth,kCheckImageHeight,
                 kCheckImageDepth,0,GL_RGB,GL_UNSIGNED_BYTE,check_image);

    glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_S,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_T,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_R,GL_CLAMP);
    glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, kDesignSizeW, 0.0, kDesignSizeH, -100, 100);
}

void MGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_3D);
    //glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glBindTexture(GL_TEXTURE_3D,texture_name);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 ); //this is default value
    gluLookAt(0.0,0.0,100.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );

    glRotatef(rotate_angle_x_,1,0,0);
    glRotatef(rotate_angle_y_,0,1,0);
    glRotatef(rotate_angle_z_,0,0,1);

    glTranslatef(kDesignSizeW/2,kDesignSizeH/2,0.0);
    glScalef(50.0,50.0,50.0);
    glBegin(GL_QUADS);
    {
        glTexCoord3f(0.0, 0.0, 0.0); glVertex3f(-2.25, -1.0, 0.0);
        glTexCoord3f(0.0, 1.0, 0.0); glVertex3f(-2.25, 1.0, 0.0);
        glTexCoord3f(1.0, 1.0, 1.0); glVertex3f(-0.25, 1.0, 0.0);
        glTexCoord3f(1.0, 0.0, 1.0); glVertex3f(-0.25, -1.0, 0.0);

        glTexCoord3f(0.0, 0.0, 1.0); glVertex3f(0.25, -1.0, 0.0);
        glTexCoord3f(0.0, 1.0, 1.0); glVertex3f(0.25, 1.0, 0.0);
        glTexCoord3f(1.0, 1.0, 0.0); glVertex3f(2.25, 1.0, 0.0);
        glTexCoord3f(1.0, 0.0, 0.0); glVertex3f(2.25, -1.0, 0.0);
    }
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_3D);
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
















