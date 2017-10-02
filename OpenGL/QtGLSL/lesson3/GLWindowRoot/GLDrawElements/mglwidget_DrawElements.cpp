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
    //0.0f,  1.0f,  0.0f,  1.0f,
    -1.0f,  1.0f,  0.0f,  1.0f,
    -1.0f, -1.0f,  0.0f,  1.0f,
};

static const GLfloat vertex_colors[] = {
    1.0f, 1.0f,  1.0f,  1.0f,
    1.0f, 1.0f,  0.0f,  1.0f,
    1.0f, 0.0f,  1.0f,  1.0f,
    0.0f, 1.0f,  1.0f,  1.0f,
};

//static const GLushort vertex_indices[] = {0,1,2};
static const GLushort vertex_indices[] = {1,2,3};

enum VAO_IDs {
    Triangles,
    NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer,
    ElemArrayBuffer,
    UniformBuffer,
    NumBuffers
};
enum Attrib_IDs {
    vPos = 1
};
enum Uniforms{
    Model,
    Projection,
    NumUniforms
};

GLuint VAOs[NumVAOs];
GLuint MyBuffers[NumBuffers];
const GLuint NumVertices = 3;
GLuint ubo_index;
GLint  ubo_data_source_size;
GLvoid* ubo_data_source;
GLuint ubo_indices[NumUniforms];
GLint  ubo_size[NumUniforms];
GLint  ubo_offset[NumUniforms];
GLint  ubo_type[NumUniforms];
GLint  program;

//bool g_isUseUniformBlock = false;
bool g_isUseUniformBlock = true;

MGLWidgetDrawElements::MGLWidgetDrawElements(QWidget *parent, const char* name, bool full_screen) :
    QOpenGLWidget(parent)
{
    setGeometry( kDefaultX, kDefaultY, kDesignSizeW, kDesignSizeH );
    setMinimumSize(kMinWidth, kMinHeight);
    window_width_ = kDesignSizeW;
    window_height_= kDesignSizeH;

    gl_logger_ = NULL;

    setWindowTitle(name);

    is_full_screen_ = full_screen;
    if(is_full_screen_)
        showFullScreen();
}

void MGLWidgetDrawElements::_InitOpenGLLogging()
{
    //QOpenGLContext *ctx = QOpenGLContext::currentContext();
    gl_logger_ = new QOpenGLDebugLogger(this);
    if(gl_logger_->initialize())
    {
        qDebug() << "GL_DEBUG Debug Logger" << gl_logger_ << "\n";

        connect(gl_logger_, SIGNAL(messageLogged(QOpenGLDebugMessage)),this,SLOT(messageLogged(QOpenGLDebugMessage)));
        gl_logger_->startLogging();
    }
    else
    {
        qDebug() << "GL_DEBUG Debug Logger (NONE)\n";
    }
}

void MGLWidgetDrawElements::messageLogged(const QOpenGLDebugMessage &msg)
{
  QString error;

  // Format based on severity
  switch (msg.severity())
  {
  case QOpenGLDebugMessage::NotificationSeverity:
    error += "--";
    break;
  case QOpenGLDebugMessage::HighSeverity:
    error += "!!";
    break;
  case QOpenGLDebugMessage::MediumSeverity:
    error += "!~";
    break;
  case QOpenGLDebugMessage::LowSeverity:
    error += "~~";
    break;
  }

  error += " (";

  // Format based on source
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
  switch (msg.source())
  {
    CASE(APISource);
    CASE(WindowSystemSource);
    CASE(ShaderCompilerSource);
    CASE(ThirdPartySource);
    CASE(ApplicationSource);
    CASE(OtherSource);
    CASE(InvalidSource);
  }
#undef CASE

  error += " : ";

  // Format based on type
#define CASE(c) case QOpenGLDebugMessage::c: error += #c; break
  switch (msg.type())
  {
    CASE(ErrorType);
    CASE(DeprecatedBehaviorType);
    CASE(UndefinedBehaviorType);
    CASE(PortabilityType);
    CASE(PerformanceType);
    CASE(OtherType);
    CASE(MarkerType);
    CASE(GroupPushType);
    CASE(GroupPopType);
  }
#undef CASE

  error += ")";
  qDebug() << qPrintable(error) << "\n" << qPrintable(msg.message()) << "\n";
}

void MGLWidgetDrawElements::initializeGL()
{
    initializeOpenGLFunctions();
    _InitOpenGLLogging();

    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepthf(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    const char* vertex_shader_path = NULL;
    if(g_isUseUniformBlock)
    {
        vertex_shader_path = ":/vertex_DrawCMD_UniformBlock.vert";

    }
    else
    {
        vertex_shader_path = ":/vertex_DrawCMD.vert";
    }
    program = GLHelper::CreateShaderProgramWithFiles(vertex_shader_path,":/fragment_DrawCMD.frag");
    glUseProgram(program);

    glGenBuffers(NumBuffers,MyBuffers);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MyBuffers[ElemArrayBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);

    glGenVertexArrays(NumVAOs,VAOs);
    glBindVertexArray(VAOs[Triangles]);

    glBindBuffer(GL_ARRAY_BUFFER,MyBuffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_positions)+sizeof(vertex_colors),NULL,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertex_positions),vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertex_positions),sizeof(vertex_colors),vertex_colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, BUFF_OFFSET(NULL));
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFF_OFFSET(sizeof(vertex_positions)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    const char* names[NumUniforms] = {"model_matrix","projection_matrix"};
    if(g_isUseUniformBlock)
    {
        ubo_index = glGetUniformBlockIndex(program,"Uniforms");
        glGetActiveUniformBlockiv(program, ubo_index, GL_UNIFORM_BLOCK_DATA_SIZE, &ubo_data_source_size);
        ubo_data_source = malloc(ubo_data_source_size);
        if(ubo_data_source == NULL)
        {
            perror("error malloc failed!");
        }
        else
        {
            glGetUniformIndices(program,NumUniforms,names,ubo_indices);
            glGetActiveUniformsiv(program,NumUniforms,ubo_indices,GL_UNIFORM_OFFSET,ubo_offset);
            glGetActiveUniformsiv(program,NumUniforms,ubo_indices,GL_UNIFORM_SIZE,ubo_size);
            glGetActiveUniformsiv(program,NumUniforms,ubo_indices,GL_UNIFORM_TYPE,ubo_type);

            glBindBuffer(GL_UNIFORM_BUFFER, MyBuffers[UniformBuffer]);
            glBufferData(GL_UNIFORM_BUFFER,ubo_data_source_size,NULL,GL_DYNAMIC_DRAW);
        }
    }
    else
    {
        for(int i=0; i<NumUniforms; i++)
        {
            ubo_indices[i] = GLHelper::GetUniformLocal(program,names[i]);
        }
    }
}

void MGLWidgetDrawElements::paintGL()
{
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    glm::mat4 model_matrix;
    GLfloat aspect = window_width_ / window_height_;
    //glm::mat4 projection_matrix = glm::frustum(-1.0f, 1.0f,-aspect, aspect, 1.0f, 500.0f);
    glm::mat4 projection_matrix = glm::perspective(45.0f, aspect, 1.0f, 500.0f);
    //glm::mat4 projection_matrix = glm::ortho(0.0f, window_width_, window_height_, 0.0f);
    if(g_isUseUniformBlock)
    {
        _UpdateTransformMatrix(Projection,projection_matrix);
    }
    else
    {
        glUniformMatrix4fv(ubo_indices[Projection],1,GL_FALSE,glm::value_ptr(projection_matrix));
    }

    //set up glDrawElements
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, MyBuffers[ElemArrayBuffer]);

    // Draw arrays
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, -5.0f));
    //model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.0f, -5.0f));
    //model_matrix = glm::scale(glm::mat4(1.0f),glm::vec3(0.3,0.3,0.3));
    if(g_isUseUniformBlock)
    {
        _UpdateTransformMatrix(Model,model_matrix);
    }
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],1,GL_FALSE,glm::value_ptr(model_matrix));
    }
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);
    for(int i=0; i<3; i++)
    {
        glm::vec4 pos(vertex_positions[i*4+0], vertex_positions[i*4+1], vertex_positions[i*4+2], vertex_positions[i*4+3]);
        glm::vec4 tempPos1 =  model_matrix*pos;
        glm::vec4 tempPos2 =  projection_matrix*(model_matrix*pos);
        glm::vec4 tempPos3;
        tempPos3.x =  tempPos2.x / tempPos2.w;
        tempPos3.y =  tempPos2.y / tempPos2.w;
        tempPos3.z =  tempPos2.z / tempPos2.w;
        tempPos3.w =  tempPos2.w / tempPos2.w;

        //qDebug() << "tempPos1 x " << tempPos1.x << " y " << tempPos1.y << " z " << tempPos1.z << " w " << tempPos1.w << "\n";
        //qDebug() << "tempPos2 x " << tempPos2.x << " y " << tempPos2.y << " z " << tempPos2.z << " w " << tempPos2.w << "\n";
        //qDebug() << "tempPos3 x " << tempPos3.x << " y " << tempPos3.y << " z " << tempPos3.z << " w " << tempPos3.w << "\n";
    }

    // Draw elem
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -5.0f));
    //model_matrix = glm::scale(model_matrix,glm::vec3(0.5,0.5,0.5));
    if(g_isUseUniformBlock)
    {
        _UpdateTransformMatrix(Model,model_matrix);
    }
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],1,GL_FALSE,glm::value_ptr(model_matrix));
    }
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

    // DrawElementsBaseVertex
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -5.0f));
    //model_matrix = glm::scale(model_matrix,glm::vec3(0.5,0.5,0.5));
    if(g_isUseUniformBlock)
    {
        _UpdateTransformMatrix(Model,model_matrix);
    }
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],1,GL_FALSE,glm::value_ptr(model_matrix));
    }
    //glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 0);

    // DrawArraysInstanced
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, -5.0f));
    //model_matrix = glm::scale(model_matrix,glm::vec3(0.5,0.5,0.5));
    if(g_isUseUniformBlock)
    {
        _UpdateTransformMatrix(Model,model_matrix);
    }
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],1,GL_FALSE,glm::value_ptr(model_matrix));
    }
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

    glFlush();
}

void MGLWidgetDrawElements::_UpdateTransformMatrix(unsigned int type,glm::mat4 matrix)
{
    GLsizei data_size = ubo_size[type]*GLHelper::TypeSize(ubo_type[type]);
    glBindBuffer(GL_UNIFORM_BUFFER, MyBuffers[UniformBuffer]);
    glBufferSubData(GL_UNIFORM_BUFFER,ubo_offset[type],data_size,&matrix);
    glBindBufferRange(GL_UNIFORM_BUFFER,ubo_index,MyBuffers[UniformBuffer],ubo_offset[type],data_size);
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



















