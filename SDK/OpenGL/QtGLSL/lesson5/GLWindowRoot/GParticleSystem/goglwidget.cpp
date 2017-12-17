#include "goglwidget.h"
#include <iostream>
#include "../../../common/glfuncdefine.h"
#include "../../../common/glhelper.h"
#include "../../../common/gtimermgr.h"
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

GOGLWidget::GOGLWidget(QWidget *parent, const char* name, bool full_screen) :
    QOpenGLWidget(parent),
    _triangle("fire_red.jpg")
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

void GOGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepth(100.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    _camera.SetCurProjectionType(GCamera::kPerspective);
    _ps.Init(glm::vec3(0,0,0));
    //_triangle.Init(nullptr);

    GTimerMgr::GetInstance().Schedule(this,[this](float delta){
        this->update();
    },GTimerMgr::REPEAT_FOREVER,33);
}

void GOGLWidget::paintGL()
{
    //glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glStencilMask(0xFF);
    //_triangle.Draw();
    _ps.Draw(&_camera);

    glFlush();
}

void GOGLWidget::resizeGL(int w, int h)
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

void GOGLWidget::keyPressEvent(QKeyEvent *event)
{
    static float step_factor = 0.1;
    glm::vec3 step(0);
    switch (event->key())
    {
        case Qt::Key_A:
        {
            step = -_camera.GetRight();
            break;
        }
        case Qt::Key_D:
        {
            step = _camera.GetRight();
            break;
        }
        case Qt::Key_Q:
        {
            step = -_camera.GetUp();
            break;
        }
        case Qt::Key_E:
        {
            step = _camera.GetUp();
            break;
        }
        case Qt::Key_W:
        {
            step = -_camera.GetForward();
            break;
        }
        case Qt::Key_S:
        {
            step = _camera.GetForward();
            break;
        }
        default:
            break;
    }
    GLHelper::Log("move key "+to_string(event->key()));
    _camera.Translate(step*step_factor);

    update();
}

void GOGLWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
        case Qt::Key_R:
        {
            _camera.RotateAroundTarget(false);
            break;
        }
        case Qt::Key_F:
        {
            _camera.FaceToTarget(false,glm::vec3(0.0,0.0,-4.0));
            break;
        }
        case Qt::Key_Escape:
        {
            _camera.ResetPosAndOrient();
            break;
        }
        case Qt::Key_Space:
        {
            _camera.StopAllMove();
            break;
        }
        default:
            break;
    }
}


















