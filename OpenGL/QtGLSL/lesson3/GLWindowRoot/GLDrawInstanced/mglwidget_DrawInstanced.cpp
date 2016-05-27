#include "mglwidget_DrawInstanced.h"
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

enum InVarType{
    PositionInVar,
    NormalInVar,
    ColorInVar,
    InVarNum
};
enum UniformType
{
    ViewMatrixUniform,
    ProjectionMatrixUniform,
    ColorTBOUniform,
    ModelMatrixTBOUniform,
    UniformNum
};
enum Buffer_IDs {
    ColorBuffer,
    ModelMatrixBuffer,
    BufferNum
};
enum Attrib_IDs {
    PosAttrib,
    NormalAttrib,
    ColorAttrib,
    ModelMatrixAttrib,
    AttribNum
};
enum TBOType
{
    ColorTBO,
    ModelMatrixTBO,
    TBONum
};

GLint  program;
GLint  uniform_var_locals[UniformNum];
GLint  in_var_locals[InVarNum];
GLuint buffers[BufferNum];
GLuint textures[TBONum];

const int kInstanceCount = 100;

MGLWidgetDrawInstanced::MGLWidgetDrawInstanced(QWidget *parent, const char* name, bool full_screen) :
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

void MGLWidgetDrawInstanced::_InitOpenGLLogging()
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

void MGLWidgetDrawInstanced::messageLogged(const QOpenGLDebugMessage &msg)
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

void MGLWidgetDrawInstanced::initializeGL()
{
    initializeOpenGLFunctions();
    _InitOpenGLLogging();

    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    program = GLHelper::CreateShaderProgramWithFiles(":/vertex_DrawInstanced.vert",":/fragment_DrawCMD.frag");
    glUseProgram(program);

    const char* uniform_names[UniformNum] = {"view_matrix","projection_matrix"};
    for(int i=ViewMatrixUniform; i<UniformNum; i++)
    {
        uniform_var_locals[i] = glGetUniformLocation(program,uniform_names[i]);
    }

    glUniform1i(uniform_var_locals[ColorTBO],0);
    glUniform1i(uniform_var_locals[ModelMatrixTBO],1);

    vbobject.LoadFromVBM(":armadillo_low.vbm",0,1,2);
    vbobject.BindVertexArray();

    glGenTextures(TBONum,textures);
    glBindTexture(GL_TEXTURE_BUFFER, textures[ColorTBO]);

    glm::vec4 colors[kInstanceCount];
    for(int i=0; i<kInstanceCount; i++)
    {
        float a=float(n)/4.0f;
        float b=float(n)/5.0f;
        float c=float(n)/6.0f;
        colors[n][0] = 0.5f * (sinf(a+1.0f)+1.0f);
        colors[n][1] = 0.5f * (sinf(b+2.0f)+1.0f);
        colors[n][2] = 0.5f * (sinf(c+3.0f)+1.0f);
        colors[n][3] = 1.0f;
    }
    //weight
    glGenBuffers(BufferNum,buffers);
    glBindBuffer(GL_ARRAY_BUFFER, buffers[WeightBuffer]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(colors),colors,GL_DYNAMIC_DRAW);

    glVertexAttribDivisor(ModelMatrixAttrib,1);
    glVertexAttribPointer(ModelMatrixAttrib,4,GL_FLOAT,GL_FALSE,0,NULL);
    glEnableVertexAttribArray(ModelMatrixAttrib);

    // color
    glBindBuffer(GL_ARRAY_BUFFER, buffers[ColorBuffer]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribDivisor(ColorAttrib,1);
    glVertexAttribPointer(ColorAttrib,4,GL_FLOAT,GL_FALSE,0,NULL);
    glEnableVertexAttribArray(4);

    glBindVertexArray(0);
}

void MGLWidgetDrawInstanced::paintGL()
{
    float t = 0.1;
    glm::vec4 weights[kInstanceCount];
    for(int i=0; i<kInstanceCount; i++)
    {
        float a = float(i)/4.0f;
        float b = float(i)/5.0f;
        float c = float(i)/6.0f;

        weights[i][0] = 0.5f * (sinf(t*6.28318531f*8.0f+a)+1.0f);
        weights[i][1] = 0.5f * (sinf(t*6.28318531f*8.0f+b)+1.0f);
        weights[i][2] = 0.5f * (sinf(t*6.28318531f*8.0f+c)+1.0f);
        weights[i][3] = 0.5f * (sinf(t*6.28318531f*8.0f+a+b)+1.0f);
    }

    glBindBuffer(GL_ARRAY_BUFFER, buffers[WeightBuffer]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(weights),weights,GL_DYNAMIC_DRAW);

    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glm::mat4 model_matrix[4];
    for(int i=0; i<kInstanceCount; i++)
    {
        model_matrix[n] = (GLHelper::GetScale(0.5)*
                           GLHelper::GetRotate(t*360.0f*40.0f+float(i+1)*29.0f,0.0f,1.0f,0.0f) *
                           GLHelper::GetRotate(t*360.0f*20.0f+float(i+1)*35.0f,0.0f,0.0f,1.0f) *
                           GLHelper::GetRotate(t*360.0f*30.0f+float(i+1)*67.0f,0.0f,1.0f,0.0f) *
                           GLHelper::GetTranslate((float)i*10.0f-15.0f,0.0f,0.0f) *
                           GLHelper::GetScale(0.01f));
    }
    glUniformMatrix4fv(uniform_var_locals[ViewMatrixUniform]);
    glFlush();
}

void MGLWidgetDrawInstanced::_UpdateTransformMatrix(unsigned int type,glm::mat4 matrix)
{
    GLsizei data_size = ubo_size[type]*GLHelper::TypeSize(ubo_type[type]);
    glBindBuffer(GL_UNIFORM_BUFFER, MyBuffers[UniformBuffer]);
    glBufferSubData(GL_UNIFORM_BUFFER,ubo_offset[type],data_size,&matrix);
    glBindBufferRange(GL_UNIFORM_BUFFER,ubo_index,MyBuffers[UniformBuffer],ubo_offset[type],data_size);
}

void MGLWidgetDrawInstanced::resizeGL(int w, int h)
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



















