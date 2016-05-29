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

const int kInstanceCount = 1;//100;

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

    program = GLHelper::CreateShaderProgramWithFiles(":/vertex_DrawInstanced.vert",":/fragment_DrawInstanced.frag");
    glUseProgram(program);

    const char* uniform_names[UniformNum] = {"view_matrix","projection_matrix","color_tbo","model_matrix_tbo"};
    for(int i=ViewMatrixUniform; i<UniformNum; i++)
    {
        uniform_var_locals[i] = glGetUniformLocation(program,uniform_names[i]);
    }

    glUniform1i(uniform_var_locals[ColorTBO],0);
    glUniform1i(uniform_var_locals[ModelMatrixTBO],1);

    GLHelper::Log(QDir::currentPath().toStdString());

    string vbm_path = GLHelper::GetAbsPathRelativeGResPath("armadillo_low.vbm");
    vbobject.LoadFromVBM(vbm_path.c_str(),0,1,2);

    glGenTextures(TBONum,textures);
    glGenBuffers(BufferNum,buffers);

    // color
    glBindTexture(GL_TEXTURE_BUFFER, textures[ColorTBO]);
    glm::vec4 colors[kInstanceCount];
    for(int i=0; i<kInstanceCount; i++)
    {
        float a=float(i)/4.0f;
        float b=float(i)/5.0f;
        float c=float(i)/6.0f;
        colors[i][0] = 0.5f * (sinf(a+1.0f)+1.0f);
        colors[i][1] = 0.5f * (sinf(b+2.0f)+1.0f);
        colors[i][2] = 0.5f * (sinf(c+3.0f)+1.0f);
        colors[i][3] = 1.0f;
    }
    glBindBuffer(GL_TEXTURE_BUFFER, buffers[ColorBuffer]);
    glBufferData(GL_TEXTURE_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA32F,buffers[ColorBuffer]);


    // model matrix
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_BUFFER,textures[ModelMatrixTBO]);
    glBindBuffer(GL_TEXTURE_BUFFER, buffers[ModelMatrixBuffer]);
    glBufferData(GL_TEXTURE_BUFFER,kInstanceCount*sizeof(glm::mat4),NULL,GL_DYNAMIC_DRAW);
    glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA32F,buffers[ModelMatrixBuffer]);

    glActiveTexture(GL_TEXTURE0);
}

void MGLWidgetDrawInstanced::paintGL()
{
    float t = float(GLHelper::GetTickCount() & 0x1FFF) / float(0x1FFF);;

    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glm::mat4 model_matrix[kInstanceCount];
    for(int i=0; i<kInstanceCount; i++)
    {
        float a = 50.0f * float(i) / 4.0f;
        float b = 50.0f * float(i) / 4.0f;
        float c = 50.0f * float(i) / 4.0f;
        model_matrix[i] = GLHelper::GetRotate(a+t*360.0f,1.0f,0.0f,0.0f) *
                          GLHelper::GetRotate(b+t*360.0f,0.0f,1.0f,0.0f) *
                          GLHelper::GetRotate(c+t*360.0f,0.0f,0.0f,1.0f) *
                          GLHelper::GetTranslate(10.0f+a,40.0f+b,50.0f+c);
    }
    glBindBuffer(GL_TEXTURE_BUFFER,buffers[ModelMatrixBuffer]);
    glBufferData(GL_TEXTURE_BUFFER,sizeof(model_matrix),model_matrix,GL_DYNAMIC_DRAW);

    glm::mat4 view_matrix = GLHelper::GetTranslate(0.0f,0.0f,-1500.0f) *
            GLHelper::GetRotate(t*360.0f*2.0f,0.0f,1.0f,0.0f);
    GLfloat aspect = window_width_ / window_height_;
    glm::mat4 projection_matrix = glm::frustum(-1.0f,1.0f,-aspect,aspect,1.0f,5000.0f);
    glUniformMatrix4fv(uniform_var_locals[ViewMatrixUniform],1,GL_FALSE,glm::value_ptr(view_matrix));
    glUniformMatrix4fv(uniform_var_locals[ProjectionMatrixUniform],1,GL_FALSE,glm::value_ptr(projection_matrix));

    vbobject.Render(0,kInstanceCount);
    glFlush();
}

void MGLWidgetDrawInstanced::_UpdateTransformMatrix(unsigned int type,glm::mat4 matrix)
{
//    GLsizei data_size = ubo_size[type]*GLHelper::TypeSize(ubo_type[type]);
//    glBindBuffer(GL_UNIFORM_BUFFER, MyBuffers[UniformBuffer]);
//    glBufferSubData(GL_UNIFORM_BUFFER,ubo_offset[type],data_size,&matrix);
//    glBindBufferRange(GL_UNIFORM_BUFFER,ubo_index,MyBuffers[UniformBuffer],ubo_offset[type],data_size);
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



















