#include "mglwidget_PolygonMode.h"
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

MGLWidgetPolygonMode::MGLWidgetPolygonMode(QWidget *parent, const char* name, bool full_screen) :
    QOpenGLWidget(parent),
    _triangle_b(false)
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

void MGLWidgetPolygonMode::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepthf(100.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    //glFrontFace(GL_CW);
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    _triangle_a.Init(nullptr);
    _triangle_b.Init(nullptr);
    _triangle_a.SetScale(0.4);
    _triangle_b.SetScale(0.4);
    _triangle_a.SetTranslate(glm::vec3(-0.5,0,0));
    _triangle_b.SetTranslate(glm::vec3(0.5,0,0));
}

void MGLWidgetPolygonMode::paintGL()
{
    //glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    _triangle_a.Draw();
    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    _triangle_b.Draw();
}

void MGLWidgetPolygonMode::resizeGL(int w, int h)
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



















