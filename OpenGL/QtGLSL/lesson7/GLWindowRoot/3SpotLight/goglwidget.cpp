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

GOGLWidget::GOGLWidget(QWidget *parent, const char* name, bool full_screen) :
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

    GTimerMgr::GetInstance().Schedule(this,[this](float delta){
        this->update();
    },GTimerMgr::REPEAT_FOREVER,33);
}

void GOGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    _camera.SetCurProjectionType(GCamera::kPerspective);
    _camera.Translate(0.0,0.0,3.0);
//    _triangle.Init(nullptr);
//    _cube.Init();
//    _cube.SetScale(0.3);
//    _skybox.Init("skybox_2/right.jpg",
//                 "skybox_2/left.jpg",
//                 "skybox_2/top.jpg",
//                 "skybox_2/bottom.jpg",
//                 "skybox_2/front.jpg",
//                 "skybox_2/back.jpg",
//                 QImage::Format::Format_RGB888);
    //_skybox.SetScale(10);
    _point_light.Init();
    _point_light.SetColor(glm::vec4(1.0,1.0,1.0,1.0));
    _point_light.SetTranslate(glm::vec3(1.3,1.3,1.3));
    _point_light.SetScale(0.3);
    for(int cube_index=0; cube_index<_kCubesCount; cube_index++)
    {
        InitCubeForLight(_cubes[cube_index],cube_index,_point_light);
    }
    GLHelper::Foreach([this](GModel* model){
        model->SetViewMatrixGetter([this](glm::mat4x4& view_matrix){
            this->_camera.GetViewMatrix(view_matrix);
        });
        model->SetProjectionMatrixGetter([this](glm::mat4x4& projection_matrix){
            this->_camera.GetCurProjectionMatrix(projection_matrix);
        });
        model->SetCameraPosGetter([this](){
            return this->_camera.GetPosition();
        });
        model->SetCameraGetter([this](){
            return &(this->_camera);
        });
    },(GModel*)&_skybox,(GModel*)&_cube,(GModel*)&_point_light);

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepth(100.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;
}

void GOGLWidget::paintGL()
{
    //glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _triangle.Draw();
    _cube.Draw();
    _point_light.Draw();
    for(int cube_index=0; cube_index<_kCubesCount; cube_index++)
    {
        _cubes[cube_index].Draw();
    }

    _skybox.Draw();

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

void GOGLWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        static const float rotSpeed   = 0.5f;
        this->_mouse_pos = QCursor::pos();

        _mouse_timer = GTimerMgr::GetInstance().Schedule(this,[this](float dt){
            QPoint delta = QCursor::pos() - this->_mouse_pos;
            this->_mouse_pos = QCursor::pos();

            this->_camera.Rotate(delta.x()*-rotSpeed,_camera.GetUp());
            this->_camera.Rotate(delta.y()*-rotSpeed,_camera.GetRight());
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

void GOGLWidget::InitCubeForLight(GCubeForLight& cube, int index, GLightBase& light)
{
    GUniformType uniform_types[] = {
        GUniformType::kTranslate,
        GUniformType::kViewMatrix,
        GUniformType::kProjectionMatrix,
        GUniformType::kNormalMatrix,
        GUniformType::kAmbient,
        GUniformType::kEyeDir,
        GUniformType::kLight0_Type,
        GUniformType::kLight0_Color,
        GUniformType::kLight0_Pos,
        //GUniformType::kLight0_Dir,
        GUniformType::kLight0_Shininess,
        GUniformType::kLight0_Strengthen,
        GUniformType::kLight0_Attenuation,
        GUniformType::kLight0_LinearAttenuation,
        GUniformType::kLight0_QuadraticAttenuation
    };
    int uniform_count = sizeof(uniform_types) / sizeof(GUniformType);
    cube.Init(":0_point_light.vert",
              ":0_point_light.frag",
              uniform_types,
              uniform_count);

    int offset_x = index%2;
    int offset_z = index / 2;
    glm::vec3 translate = glm::vec3(offset_x*1.4,0,-offset_z*1.4);
    cube.SetTranslate(translate);

    auto* ambient = new GUniformData<glm::vec4>();
    ambient->SetData(new glm::vec4(0.1,0.1,0.1,1.0));
    cube.SetUniformData(GUniformType::kAmbient,ambient);

    auto* light0_type = new GUniformData<glm::vec3>();
    light0_type->SetData(new int(GLightType::kPointLight));
    cube.SetUniformData(GUniformType::kLight0_Type,light0_type);

    auto* light0_color = new GUniformData<glm::vec3>();
    light0_color->SetData(new glm::vec3(light.GetColor()));
    cube.SetUniformData(GUniformType::kLight0_Color,light0_color);

    auto* light0_pos = new GUniformData<glm::vec3>();
    light0_pos->SetData(new glm::vec3(light.GetTranslate()));
    cube.SetUniformData(GUniformType::kLight0_Pos,light0_pos);

//    auto* light0_dir = new GUniformData<glm::vec3>();
//    light0_dir->SetData(new glm::vec3(-1.0f, -1.0f, -1.0f));
//    _cube_for_light.SetUniformData(GUniformType::kLight0_Dir,light0_dir);

    auto* light0_shininess = new GUniformData<float>();
    light0_shininess->SetData(new float(32.0f));
    cube.SetUniformData(GUniformType::kLight0_Shininess,light0_shininess);

    auto* light0_strenghen = new GUniformData<float>();
    light0_strenghen->SetData(new float(1.0f));
    cube.SetUniformData(GUniformType::kLight0_Strengthen,light0_strenghen);

    auto* light0_attenuation = new GUniformData<float>();
    light0_attenuation->SetData(new float(1.0f));
    cube.SetUniformData(GUniformType::kLight0_Attenuation,light0_attenuation);

    auto* light0_linear_attenuation = new GUniformData<float>();
    light0_linear_attenuation->SetData(new float(0.09f));
    cube.SetUniformData(GUniformType::kLight0_LinearAttenuation,light0_linear_attenuation);

    auto* light0_quadratic_attenuation = new GUniformData<float>();
    light0_quadratic_attenuation->SetData(new float(0.032f));
    cube.SetUniformData(GUniformType::kLight0_QuadraticAttenuation,light0_quadratic_attenuation);

    cube.SetCameraGetter([this](){
        return &(this->_camera);
    });
}



















