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

static GLubyte charactor_f[24] = {
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

static GLfloat square_stencil_verties[][3] = {
    {0.0, 1.0, 0.0},
    {1.0, 0.0, 0.0},
    {0.0, -1.0, 0.0},
    {-1.0, 0.0, 0.0}
};

void InitStencilBuffer()
{
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS,0x1,0x1);
    glStencilOp(GL_REPLACE,GL_REPLACE,GL_REPLACE);
    glPushMatrix();
    {
        glTranslatef(kDesignSizeW/2,kDesignSizeH/2,0.0);
        glScalef(50,50,1.0);
        glBegin(GL_QUADS);
        glVertex3fv(square_stencil_verties[0]);
        glVertex3fv(square_stencil_verties[1]);
        glVertex3fv(square_stencil_verties[2]);
        glVertex3fv(square_stencil_verties[3]);
        glEnd();
    }
    glPopMatrix();
}

static GLfloat square_obj_verties[][3] = {
    {1.0, 1.0, 0.0},
    {1.0, -1.0, 0.0},
    {-1.0, -1.0, 0.0},
    {-1.0, 1.0, 0.0}
};

void PrintBufferBaseOnPixelInfo()
{
    GLint bits;
    glGetIntegerv(GL_RED_BITS,&bits);
    cout << "GL_RED_BITS    " << bits << endl;
    glGetIntegerv(GL_ALPHA_BITS,&bits);
    cout << "GL_ALPHA_BITS  " << bits << endl;
    glGetIntegerv(GL_INDEX_BITS,&bits);
    cout << "GL_INDEX_BITS  " << bits << endl;
    glGetIntegerv(GL_DEPTH_BITS,&bits);
    cout << "GL_DEPTH_BITS  " << bits << endl;
    glGetIntegerv(GL_STENCIL_BITS,&bits);
    cout << "GL_STENCIL_BITS        " << bits << endl;
    glGetIntegerv(GL_ACCUM_RED_BITS,&bits);
    cout << "GL_ACCUM_RED_BITS      " << bits << endl;
    glGetIntegerv(GL_ACCUM_ALPHA_BITS,&bits);
    cout << "GL_ACCUM_ALPHA_BITS    " << bits << endl;
    cout << endl;

    glGetIntegerv(GL_AUX_BUFFERS,&bits);
    cout << "GL_AUX_BUFFERS             " << bits << endl;
    glGetIntegerv(GL_MAX_COLOR_ATTACHMENTS,&bits);
    cout << "GL_MAX_COLOR_ATTACHMENTS   " << bits << endl;
    GLboolean enable;
    glGetBooleanv(GL_STEREO,&enable);
    cout << "GL_STEREO          " << (int)enable << endl;
    glGetBooleanv(GL_DOUBLEBUFFER,&enable);
    cout << "GL_DOUBLEBUFFER    " << (int)enable << endl;
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
    PrintBufferBaseOnPixelInfo();

    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glClearStencil(0x0);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_SCISSOR_TEST);
    glShadeModel(GL_FLAT); //GL_SMOOTH GL_FLAT
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_BLEND);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
}

void MGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    glStencilFunc(GL_NOTEQUAL,0x1,0x1);
    glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
    glColor3f(1.0,0.0,0.0);

    glPushMatrix();
    glTranslatef(kDesignSizeW/2,kDesignSizeH/2,0.0);
    glScalef(100,100,1.0);
    glBegin(GL_QUADS);
    glVertex3fv(square_obj_verties[0]);
    glVertex3fv(square_obj_verties[1]);
    glVertex3fv(square_obj_verties[2]);
    glVertex3fv(square_obj_verties[3]);
    glEnd();
    glPopMatrix();
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
    glScissor(window_width_/2,window_height_/2,
              window_width_/2,window_height_/2);
    glViewport(0,0,window_width_,window_height_);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, kDesignSizeW, 0.0, kDesignSizeH, -1000, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    InitStencilBuffer();

    gluLookAt(0.0,0.0,10.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );
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
















