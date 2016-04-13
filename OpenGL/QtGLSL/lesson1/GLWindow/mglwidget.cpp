#include "mglwidget.h"
#include <iostream>
#include "../../common/glhelper.h"

using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

#define BUFF_OFFSET(offset) ((void*)(offset))

enum VAO_IDs {
    Triangles,
    NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer,
    NumBuffers
};
enum Attrib_IDs {
    vPosition
};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

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

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    glGenVertexArrays(NumVAOs, VAOs);
    glBindVertexArray(VAOs[Triangles]);
    GLfloat vertices[NumVertices][2] = {
        {-0.90, -0.90},
        { 0.85, -0.90},
        {-0.90,  0.85},
        { 0.90, -0.85},
        { 0.90,  0.90},
        {-0.85,  0.90},
    };

    glGenBuffers(NumBuffers,Buffers);
    glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint program = GLHelper::CreateShaderProgramWithFiles(":/vertex.vert",":/fragment.frag");
    glUseProgram(program);
    glVertexAttribPointer(vPosition,2,GL_FLOAT,GL_FALSE,0,BUFF_OFFSET(0));
    glEnableVertexAttribArray(vPosition);
}

void MGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    glFlush();
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



















