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

    glClearColor(0.0f,0.0f,0.8f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    //program = GLHelper::CreateShaderProgramWithFiles(":/vertex_TestVBObject.vert",":/fragment_TestVBObject.frag");
    //glUseProgram(program);

    //string vbm_path = GLHelper::GetAbsPathRelativeGResPath("armadillo_low.vbm");
    //vbobject.LoadFromVBM(vbm_path.c_str(),0,1,2);

    program = GLHelper::CreateShaderProgramWithFiles(":/vertex_DrawInstanced.vert",":/fragment_DrawInstanced.frag");
    glUseProgram(program);
    {
        glGenVertexArrays(1,&_vaobject_id);
        glBindVertexArray(_vaobject_id);

        glGenBuffers(1,&_vabuffer_id);
        glBindBuffer(GL_ARRAY_BUFFER,_vabuffer_id);

        static GLfloat vertex_data[] = {
            -1.0, -1.0,  0.0,  1.0,
             0.0,  1.0,  0.0,  1.0,
             1.0, -1.0,  0.0,  1.0
        };
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

        //glVertexAttribPointer(0,4,GL_FLOAT,GL_FALSE,0,vertex_data);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    }
    glUseProgram(0);

    _triangle.Init(NULL);
    _triangle.SetScale(0.3);
}

void TestVBObject::paintGL()
{
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    {
        glBindVertexArray(_vaobject_id);
        //glDrawArraysInstanced(GL_TRIANGLES,0,6,_kInstanceCount);
        //glDrawArrays(GL_TRIANGLES,0,6);
        glDrawArrays(GL_TRIANGLES,0,3);

        glBindVertexArray(0);
    }
    glUseProgram(0);

    //glUseProgram(program);
    //vbobject.Render(0,0);

    _triangle.Draw();

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




















