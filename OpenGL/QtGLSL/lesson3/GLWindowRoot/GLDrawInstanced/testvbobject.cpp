#include "testvbobject.h"
#include <iostream>
#include "../../../common/glhelper.h"
#include "glm/glm.hpp"
#include "glm/fwd.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <QOpenGLDebugMessage>
#include <QDebug>

using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

#define BUFF_OFFSET(offset) ((void*)(offset))

TestVBObject::TestVBObject(QWidget *parent, const char* name, bool full_screen) :
    QOpenGLWidget(parent)
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

void TestVBObject::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    program = GLHelper::CreateShaderProgramWithFiles(":/vertex_TestVBObject.vert",":/fragment_TestVBObject.frag");
    glUseProgram(program);

//    string vbm_path = GLHelper::GetAbsPathRelativeGResPath("armadillo_low.vbm");
//    vbobject.LoadFromVBM(vbm_path.c_str(),0,1,2);

    glGenVertexArrays(ObjectNum,vaoject);
    glBindVertexArray(vaoject[Triangle]);
    GLfloat pos_data[] = {
        -1.0, -1.0,  0.0,  1.0,
         0.0,  1.0,  0.0,  1.0,
         1.0, -1.0,  0.0,  1.0
    };
    glGenBuffers(BufferNum,buffers);
    glBindBuffer(GL_ARRAY_BUFFER,buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos_data), pos_data, GL_STATIC_DRAW);

    glVertexAttribPointer(PosAttribLocal,4,GL_FLOAT,GL_FALSE,0,BUFF_OFFSET(0));
    glEnableVertexAttribArray(PosAttribLocal);
}

void TestVBObject::paintGL()
{
    //glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    //vbobject.Render(0,0);

    glBindVertexArray(vaoject[Triangle]);
    glDrawArrays(GL_TRIANGLES,0,3);

    glFlush();
}

void TestVBObject::resizeGL(int w, int h)
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




















