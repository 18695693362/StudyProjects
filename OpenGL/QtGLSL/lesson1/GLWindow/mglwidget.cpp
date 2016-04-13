#include "mglwidget.h"
//#include <glu.h>
#include <iostream>
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

GLuint CompileShader(GLuint shader_type, const char* shader_str)
{
    GLuint shader_obj = glCreateShader(shader_type);
    glShaderSource(shader_obj,1,&shader_str,NULL);
    glCompileShader(shader_obj);

    GLint status;
    glGetShaderiv(shader_obj,GL_COMPILE_STATUS,&status);
    if(status != GL_TRUE)
    {
        GLint log_size;
        glGetShaderiv(shader_obj,GL_INFO_LOG_LENGTH,&log_size);
        char* log = new char[log_size];
        memset(log,0,log_size);
        glGetShaderInfoLog(shader_obj,log_size,&log_size,log);
        cout << log << endl;

        //TODO
    }
    return shader_obj;
}

GLuint CreateShaderProgram(const char* vertex_shader_str, const char* fragment_shader_str)
{
    GLuint vertex_shader_obj = CompileShader(GL_VERTEX_SHADER,vertex_shader_str);
    GLuint fragment_shader_obj = CompileShader(GL_FRAGMENT_SHADER,fragment_shader_str);
    GLuint program = glCreateProgram();
    glAttachShader(program,vertex_shader_obj);
    glAttachShader(program,fragment_shader_obj);
    glLinkProgram(program);

    GLint status;
    glGetProgramiv(program,GL_LINK_STATUS,&status);
    if(status != GL_TRUE)
    {
        GLint log_size;
        glGetProgramiv(program,GL_INFO_LOG_LENGTH,&log_size);
        char* log = new char[log_size];
        memset(log,0,log_size);
        glGetProgramInfoLog(program,log_size,&log_size,log);
        cout << log << endl;

        //TODO
    }
    return program;
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
}


void MGLWidget::initializeGL()
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

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

    QString vertex_shader = "\
        #version 410 core \
        layout(location = 0) in vec4 vPosition; \
        void main() { \
            gl_Position = vPosition; \
        }";
    QString fragment_shader = "\
        #version 410 core \
        out vec4 fColor; \
        void main() {\
            fColor = vec4(1.0, 1.0, 0.0, 1.0);\
        }";

    GLint program = CreateShaderProgram(vertex_shader.toStdString().c_str(),fragment_shader.toStdString().c_str());
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



















