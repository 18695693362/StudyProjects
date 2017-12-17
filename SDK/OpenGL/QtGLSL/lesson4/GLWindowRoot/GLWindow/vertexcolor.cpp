#include "vertexcolor.h"
#include <iostream>
#include "../../../common/glhelper.h"
#include "glm/glm.hpp"
#include "glm/fwd.hpp"
//#include "glm/gtc/matrix_transform.hpp"
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

VertexColor::VertexColor(QWidget *parent, const char* name, bool full_screen) :
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

void VertexColor::initializeGL()
{
    initializeOpenGLFunctions();
    _triangle.Init(nullptr);

    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    _program = GLHelper::CreateShaderProgramWithFiles(":vertexcolor.vert",":vertexcolor.frag");
    glUseProgram(_program);
    {
        glGenBuffers(1,&_vabuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _vabuffer);
        GLvoid* vertex_data;
        int vertex_data_size;
        GetVertexData(vertex_data,vertex_data_size,_vertex_count);
        glBufferData(GL_ARRAY_BUFFER,vertex_data_size,vertex_data,GL_STATIC_DRAW);

        glGenVertexArrays(1,&_vaobject);
        glBindVertexArray(_vaobject);
        glVertexAttribPointer(AttribLocal::kPosAttribLocal,2,GL_FLOAT,GL_FALSE,sizeof(VertexData),BUFF_OFFSET(sizeof(VertexData::color)));
        glEnableVertexAttribArray(AttribLocal::kPosAttribLocal);
        glVertexAttribPointer(AttribLocal::kColorAttribLocal,4,GL_UNSIGNED_BYTE,GL_TRUE,sizeof(VertexData),BUFF_OFFSET(0));
        glEnableVertexAttribArray(AttribLocal::kColorAttribLocal);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    }
    glUseProgram(0);
}

void VertexColor::paintGL()
{
    //glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //_triangle.Draw();
    glUseProgram(_program);
    {
        glBindVertexArray(_vaobject);
        glDrawArrays(GL_TRIANGLES,0,_vertex_count);
        glBindVertexArray(0);
    }
    glUseProgram(0);

    glFlush();
}

void VertexColor::resizeGL(int w, int h)
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

void VertexColor::GetVertexData(GLvoid *&vertex_data_ptr, int &size, int &vertex_count)
{
    static VertexData vertex_data[] = {
        {{ 255,   0,   0, 255 }, { -0.90, -0.90 }},  // Triangle 1
        {{   0, 255,   0, 255 }, {  0.85, -0.90 }},
        {{   0,   0, 255, 255 }, { -0.90,  0.85 }},
        {{  10,  10,  10, 255 }, {  0.90, -0.85 }},  // Triangle 2
        {{ 100, 100, 100, 255 }, {  0.90,  0.90 }},
        {{ 255, 255, 255, 255 }, { -0.85,  0.90 }}
    };
    vertex_data_ptr = vertex_data;
    size = sizeof(vertex_data);
    vertex_count = 6;
}



















