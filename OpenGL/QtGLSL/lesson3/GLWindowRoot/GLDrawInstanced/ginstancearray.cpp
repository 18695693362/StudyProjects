#include "ginstancearray.h"
#include <iostream>
#include "../../../common/glhelper.h"
#include "glm/glm.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <sstream>

using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

#define BUFF_OFFSET(offset) ((void*)(offset))
const int GInstanceArray::_kInstanceCount = 100;
GInstanceArray::GInstanceArray(QWidget *parent, const char* name, bool full_screen) :
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

void GInstanceArray::initializeGL()
{
    initializeOpenGLFunctions();
    _gldebuger.Init();

    glClearColor(0.0f,0.3f,0.3f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    //_triangle.Init(nullptr);
    _triangle.SetScale(0.3);
    _triangle.SetColor(glm::vec4(0.0,0.3,1.0,1.0));

    program = GLHelper::CreateShaderProgramWithFiles(":/vertex_InstancedArray.vert",":/fragment_InstancedArray.frag");
    glUseProgram(program);
    {
        glGenVertexArrays(1,&_vaobject);
        glBindVertexArray(_vaobject);

        glGenBuffers(1,&_vabuffer);
        glBindBuffer(GL_ARRAY_BUFFER,_vabuffer);
        GLfloat* vertex_data;
        int vertex_data_size;
        int vertex_count;
        GetVertexData(vertex_data,vertex_data_size,vertex_count);
        glBufferData(GL_ARRAY_BUFFER, vertex_data_size, vertex_data, GL_STATIC_DRAW);
        glVertexAttribPointer(kPosAttribLocal,2,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),BUFF_OFFSET(0));
        glEnableVertexAttribArray(kPosAttribLocal);
        glVertexAttribPointer(kColorAttribLocal,3,GL_FLOAT,GL_FALSE,5*sizeof(GLfloat),BUFF_OFFSET(2*sizeof(GLfloat)));
        glEnableVertexAttribArray(kColorAttribLocal);

        GLfloat* offset_data;
        int offset_data_size;
        GetOffsetData(offset_data,offset_data_size);
        glGenBuffers(1,&_instance_a_buffer);
        glBindBuffer(GL_ARRAY_BUFFER,_instance_a_buffer);
        glBufferData(GL_ARRAY_BUFFER,offset_data_size,offset_data,GL_STATIC_DRAW);
        glEnableVertexAttribArray(kOffsetAttribLocal);
        glVertexAttribPointer(kOffsetAttribLocal,2,GL_FLOAT,GL_FALSE,2*sizeof(GLfloat),BUFF_OFFSET(0));
        glVertexAttribDivisor(kOffsetAttribLocal,1);

        glBindVertexArray(0);
    }
    glUseProgram(0);
}

void GInstanceArray::paintGL()
{
    //float t = float(GLHelper::GetTickCount() & 0x1FFF) / float(0x1FFF);

    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    {
        glBindVertexArray(_vaobject);
        glDrawArraysInstanced(GL_TRIANGLES,0,6,_kInstanceCount);
        //glDrawArrays(GL_TRIANGLES,0,6);

        glBindVertexArray(0);
    }
    glUseProgram(0);

    _triangle.Draw();
    glFlush();
}

void GInstanceArray::resizeGL(int w, int h)
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

void GInstanceArray::GetOffsetData(GLfloat*& offset_data,int& size)
{
    static GLfloat translations[_kInstanceCount*2];
    static bool is_init = false;
    float offset = 0.1;
    int index = 0;
    if(!is_init)
    {
        for(int y=-10; y<10; y+=2)
        {
            for(int x=-10; x<10; x+=2)
            {
                translations[index++] = (GLfloat)x/10.0f + offset;
                translations[index++] = (GLfloat)y/10.0f + offset;
            }
        }
        is_init = true;
    }
    offset_data = translations;
    size = sizeof(translations);
}

void GInstanceArray::GetVertexData(GLfloat*& vertex_data_ptr,int& size,int& vertex_count)
{
    static GLfloat vertex_data[] = {
        //  ---位置---   ------颜色-------
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
    };
    vertex_data_ptr = vertex_data;
    size = sizeof(vertex_data);
    vertex_count = 6;
}

















