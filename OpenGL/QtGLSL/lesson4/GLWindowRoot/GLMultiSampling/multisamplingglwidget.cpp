#include "multisamplingglwidget.h"
#include "../../common/glhelper.h"
using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f
MultiSamplingGLWidget::MultiSamplingGLWidget(QWidget *parent, const char* name, bool full_screen):
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

void MultiSamplingGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    GLint result;
    glGetIntegerv(GL_SAMPLE_BUFFERS, &result);
    GLHelper::Log(string("sample buffer count = ") + to_string(result));

    _triangle1.Init();
    _triangle1.SetScale(0.5);
    _triangle1.SetTranslate(glm::vec3(-0.5,0,0));
    _triangle2.Init();
    _triangle2.SetScale(0.5);
    _triangle2.SetTranslate(glm::vec3(0.5,0,0));
}

void MultiSamplingGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE);
    _triangle1.Draw();
    glDisable(GL_MULTISAMPLE);
    _triangle2.Draw();
}

void MultiSamplingGLWidget::resizeGL(int w, int h)
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
