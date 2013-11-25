#include "mglwidget.h"
#ifdef Q_OS_WIN
#include <GL/glu.h>
#endif
#ifdef Q_OS_MAC
#include <OpenGL/glu.h>
#endif
#include <iostream>
#include <vector>
#include <string>
#include <QtGui>
using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

static GLubyte rasters[24] = {
    0xc0,0x00,0xc0,0x00,0xc0,0x00,0xc0,0x00,0xc0,0x00,
    0xFF,0x00,0xFF,0x00,
    0xc0,0x00,0xc0,0x00,0xc0,0x00,
    0xFF,0xc0,0xFF,0xc0,
};

#define kCheckImageWidth    64
#define kCheckImageHeight   64
static GLubyte check_image[kCheckImageWidth][kCheckImageHeight][4];
void MakeCheckImage()
{
    int c;
    for(int i=0; i<kCheckImageWidth; i++)
    {
        for(int j=0; j<kCheckImageHeight; j++)
        {
            c = (((i&0x8)==0) ^ ((j&0x8)==0)) * 255;
            check_image[i][j][0] = c;
            check_image[i][j][1] = c;
            check_image[i][j][2] = c;
            check_image[i][j][3] = 255;
        }
    }
}

MGLWidget::MGLWidget(QWidget *parent, const char* name, bool full_screen) :
    QGLWidget(parent)
{
    MakeCheckImage();

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
    glShadeModel(GL_FLAT); //GL_SMOOTH GL_FLAT
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_BLEND);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, kDesignSizeW, 0.0, kDesignSizeH, -1000, 1000);
}

void MGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 ); //this is default value
    gluLookAt(0.0,0.0,10.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );

    glRasterPos2d(100,100);
    glColor4f(1.0,0.0,0.0,1.0);
    glBitmap(10,12,0.0,0.0,0.0,0.0,rasters);

    glColor4f(0.0,1.0,0.0,1.0);
    glBitmap(10,12,100.0,0.0,0.0,0.0,rasters);

    glColor4f(1.0,1.0,0.0,1.0);
    glBitmap(10,12,0.0,100.0,0.0,0.0,rasters);

    glColor4f(1.0,0.0,1.0,1.0);
    glBitmap(10,12,100.0,100.0,0.0,0.0,rasters);

    glColor4f(0.0,1.0,1.0,1.0);
    glBitmap(10,12,0.0,0.0,11.0,0.0,rasters);
    glBitmap(10,12,0.0,0.0,11.0,0.0,rasters);
    glBitmap(10,12,0.0,0.0,11.0,0.0,rasters);

    glDrawPixels(kCheckImageWidth,kCheckImageHeight,GL_RGB,GL_UNSIGNED_BYTE,check_image);
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
    switch (key->key())
    {
    default:
        break;
    }

    updateGL();
}

void MGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    default:
        break;
    }
    updateGL();
}
















