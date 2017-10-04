#include "mglwidget_DrawElements.h"
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

#define BUFF_OFFSET(offset) ((void*)(offset))

static const GLfloat vertex_positions[] = {
    -1.0f, -1.0f,  0.0f,  1.0f,
     1.0f, -1.0f,  0.0f,  1.0f,
    -1.0f,  1.0f,  0.0f,  1.0f,
     1.0f,  1.0f,  0.0f,  1.0f,
     0.0f,  1.8f,  0.0f,  1.0f,
};

static const GLfloat vertex_colors[] = {
    1.0f, 1.0f,  1.0f,  1.0f,
    1.0f, 1.0f,  0.0f,  1.0f,
    1.0f, 0.0f,  1.0f,  1.0f,
    1.0f, 0.0f,  0.0f,  1.0f,
    0.0f, 0.0f,  0.0f,  1.0f,
    0.0f, 0.0f,  1.0f,  1.0f,
    0.0f, 1.0f,  0.0f,  1.0f,
    0.0f, 1.0f,  1.0f,  1.0f,
};

// count;
// primCount;
// firstIndex;
// baseVertex;
// baseInstance;
GLuint draw_elem_cmd_args[] = {
    3,  // count
    1,  // primcount
    0,  // first
    0,  // baseVertex
    0,  // baseInstance
};

enum BOType {
    kVBO,
    kEBO,
    kDrawElemCMDBO,
    kBONums
};
GLuint buffer_objs[BOType::kBONums];
enum VAOType {
    kDrawElementsShaderVAO,
    kVAONums
};
GLuint va_objs[VAOType::kVAONums];

enum TestType{
    kTestDrawElementsBaseVertex,
    kTestDrawRangeElements,
    kTestDrawElementsIndirect,
};
//TestType g_curTestType = (TestType)0;
//TestType g_curTestType = (TestType)1;
//TestType g_curTestType = (TestType)2;
TestType g_curTestType = (TestType)2;

static const GLushort vertex_indices[] = {0,1,2,1,3};
GLint  program;

MGLWidgetDrawElements::MGLWidgetDrawElements(QWidget *parent, const char* name, bool full_screen) :
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

void MGLWidgetDrawElements::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepthf(100.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glDisable(GL_CULL_FACE);
    //glFrontFace(GL_CW);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    program = GLHelper::CreateShaderProgramWithFiles(":/DrawElements.vert",":/DrawElements.frag");
    glUseProgram(program);

    glGenBuffers(BOType::kBONums, buffer_objs);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_objs[BOType::kEBO]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, buffer_objs[BOType::kDrawElemCMDBO]);
    glBufferData(GL_DRAW_INDIRECT_BUFFER, sizeof(draw_elem_cmd_args),draw_elem_cmd_args,GL_STATIC_DRAW);

    glGenVertexArrays(VAOType::kVAONums, va_objs);
    glBindVertexArray(va_objs[VAOType::kDrawElementsShaderVAO]);

    glBindBuffer(GL_ARRAY_BUFFER,buffer_objs[BOType::kVBO]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_positions)+sizeof(vertex_colors),NULL,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertex_positions),vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertex_positions),sizeof(vertex_colors),vertex_colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFF_OFFSET(NULL));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFF_OFFSET(sizeof(vertex_positions)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
}

void MGLWidgetDrawElements::paintGL()
{
    //glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    glBindVertexArray(va_objs[VAOType::kDrawElementsShaderVAO]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_objs[BOType::kEBO]);

    switch(g_curTestType)
    {
    case TestType::kTestDrawElementsBaseVertex:
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);
        glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 2);
        break;
    case TestType::kTestDrawRangeElements:
        // start - end 超出范围也没什么影响
        glDrawRangeElements(GL_TRIANGLES, 3, 5, 3, GL_UNSIGNED_SHORT, NULL);
        GLHelper::IsGLError("DrawRangeElements");
    case TestType::kTestDrawElementsIndirect:
        glDrawElementsIndirect(GL_TRIANGLES, GL_UNSIGNED_SHORT, NULL);
        GLHelper::IsGLError("DrawElementsIndirect");
        break;
    }
}

void MGLWidgetDrawElements::resizeGL(int w, int h)
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



















