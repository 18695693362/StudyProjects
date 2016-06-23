#include "goglwidget.h"
#include <iostream>
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
#define kDesignSizeH    480.f

GOGLWidget::GOGLWidget(QWidget *parent, const char* name, bool full_screen)
    :QOpenGLWidget(parent)
    ,_camera(glm::vec3(0.0,0.0,5.0f))
{
    setGeometry( kDefaultX, kDefaultY, kDesignSizeW, kDesignSizeH );
    setMinimumSize(kMinWidth, kMinHeight);
    window_width_ = kDesignSizeW;
    window_height_= kDesignSizeH;

    setWindowTitle(name);

    is_full_screen_ = full_screen;
    if(is_full_screen_)
        showFullScreen();

    GTimerMgr::GetInstance().Schedule(this,[this](float delta){
        this->update();
    },GTimerMgr::REPEAT_FOREVER,33);
}

GOGLWidget::~GOGLWidget()
{
    GTimerMgr::GetInstance().Unschedule(this);
}

void GOGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    _camera.SetCurProjectionType(GCamera::kPerspective);
    for(int i=0; i<_kCubesCount; i++)
    {
        _cubes[i].Init();
        _cubes[i].SetViewMatrixGetter([this](glm::mat4x4& view_matrix){
            this->_camera.GetViewMatrix(view_matrix);
        });
        _cubes[i].SetProjectionMatrixGetter([this](glm::mat4x4& projection_matrix){
            this->_camera.GetCurProjectionMatrix(projection_matrix);
        });
        _cubes[i].SetTranslate(glm::vec3(0.0,0.0,i*-1*2));
    }
    //_cubes[_kCubesCount-1].SetScale(2.f);

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepth(100.0f);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;
}

void GOGLWidget::paintGL()
{
    static int counter = 0;
    counter++;
    //glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(int i=0; i<_kCubesCount; i++)
    {
        _cubes[i].Draw();
    }

    //GLHelper::Log("counter = "+to_string(counter));
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
    static float step_value = 0.1;
    glm::vec3 step(0);
    switch (event->key())
    {
        case Qt::Key_A:
        {
            step.x = -step_value;
            break;
        }
        case Qt::Key_D:
        {
            step.x = step_value;
            break;
        }
        case Qt::Key_Q:
        {
            step.y = -step_value;
            break;
        }
        case Qt::Key_E:
        {
            step.y = step_value;
            break;
        }
        case Qt::Key_W:
        {
            step.z = step_value;
            break;
        }
        case Qt::Key_S:
        {
            step.z = -step_value;
            break;
        }
        default:
            break;
    }
    GLHelper::Log("move key "+to_string(event->key()));
    _camera.Translate(step);

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

void GOGLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        static const float rotSpeed   = 0.5f;
        this->_mouse_pos = QCursor::pos();

        _mouse_timer = GTimerMgr::GetInstance().Schedule(this,[this](float dt){
            QPoint delta = QCursor::pos() - this->_mouse_pos;
            this->_mouse_pos = QCursor::pos();

            this->_camera.Rotate(delta.x()*rotSpeed,_camera.GetUp());
            this->_camera.Rotate(delta.y()*rotSpeed,_camera.GetRight());
        },GTimerMgr::REPEAT_FOREVER,33);
    }
    else
    {
        this->_mouse_pos = QCursor::pos();

        _mouse_timer = GTimerMgr::GetInstance().Schedule(this,[this](float dt){
            QPoint delta = QCursor::pos() - this->_mouse_pos;
            this->_mouse_pos = QCursor::pos();
            GLHelper::Log(string("delta x = ")+to_string(delta.x()));
            GLHelper::Log(string("delta y = ")+to_string(delta.y()));
        },GTimerMgr::REPEAT_FOREVER,33);
    }
}

void GOGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        GTimerMgr::GetInstance().Unschedule(this,_mouse_timer);
    }
    else
    {
        GTimerMgr::GetInstance().Unschedule(this,_mouse_timer);
    }
}

















