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

    _layout = new QHBoxLayout;
    setLayout(_layout);

    is_full_screen_ = full_screen;
    if(is_full_screen_)
        showFullScreen();

    GTimerMgr::GetInstance().Schedule(this,[this](float delta){
        this->update();
    },GTimerMgr::REPEAT_FOREVER,33);
}

GOGLWidget::~GOGLWidget()
{
    for(int light_index=0; light_index<_kCubesCount; light_index++)
    {
        delete _lights[light_index];
        _lights[light_index] = nullptr;
    }
}

void GOGLWidget::OnSelectedLight()
{
    for(int light_idx=0; light_idx<_kLightsCount; light_idx++)
    {
        if(sender() == _lights_switchers[light_idx])
        {
            if(_lights_switchers[light_idx]->isChecked())
            {
                _lights[light_idx]->property.enable = true;
            }
            else
            {
                _lights[light_idx]->property.enable = false;
            }
            return;
        }
    }
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
    InitLights();
    InitCubes();
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
    },(GModel*)&_skybox,(GModel*)&_cube,(GModel*)&_cube_light);

    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glClearDepth(100.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;
}

void GOGLWidget::paintGL()
{
    //glEnable(GL_CULL_FACE);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _triangle.Draw();
    _cube.Draw();
    _cube_light.Draw();
    for(int cube_index=0; cube_index<_kCubesCount; cube_index++)
    {
        _cubes[cube_index].Draw();
    }
    for(int light_index=0; light_index<_kCubesCount; light_index++)
    {
        _lights[light_index]->Draw();
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

void GOGLWidget::InitLights()
{
    glm::vec3 pos_arr[_kLightsCount] = {
        {1.3,1.3,1.3},
        {1.3,1.3,-1.3},
        {-1.3,1.3,-1.3}
    };
    glm::vec3 dir_arr[_kLightsCount] = {
        {-1.0,-1.0,-1.0},
        {-1.0,-1.0,0.0},
        {1.0,-1.0,1.0}
    };
    InitLight(_cube_light,0);
    _cube_light.SetColor(glm::vec4(1.0,1.0,1.0,1.0)); // color
    _cube_light.SetTranslate(glm::vec3(1.3,1.3,1.3)); // pos
    for(int i=0; i<_kLightsCount; i++)
    {
        GCubeLight* light = new GCubeLight();
        light->property.enable      = i==1 ? true : false;
        light->property.type        = (GLightType)i;
        light->property.dir         = dir_arr[i];

        if(i==0)
        {
            light->SetColor(glm::vec4(1.0,0.0,0.0,1.0));
        }
        else if(i==1)
        {
            light->SetColor(glm::vec4(0.0,1.0,0.0,1.0));
        }
        else
        {
            light->SetColor(glm::vec4(0.0,0.0,1.0,1.0));
        }
        light->property.color       = glm::vec3(1.0,1.0,1.0);
        light->SetTranslate(pos_arr[i]);                        // pos

        light->property.ambient     = glm::vec3(0.1,0.1,0.1);
        light->property.shininess   = (float)32.0f;
        light->property.strengthen  = (float)1.0f;
        light->property.attenuation = (float)1.0f;
        light->property.linear_attenuation      = (float)0.09f;
        light->property.quadratic_attenuation   = (float)0.032f;
        light->property.spot_inner_cutoff       = (float)12.50f;
        light->property.spot_outer_cutoff       = (float)30.00f;

        _lights[i] = light;

        QCheckBox* check_box = new QCheckBox();
        check_box->setText(GLightBase::GetLightTypeName((GLightType)i).c_str());
        if(light->property.enable)
        {
            check_box->setCheckState(Qt::CheckState::Checked);
        }
        else
        {
            check_box->setCheckState(Qt::CheckState::Unchecked);
        }
        check_box->setStyleSheet("QCheckBox:unchecked{ color: white; }QCheckBox:checked{ color: red; }");
        _layout->addWidget(check_box);
        _lights_switchers[i] = check_box;
        connect(check_box,SIGNAL(clicked(bool)),this,SLOT(OnSelectedLight()));

        InitLight(*light, i);
    }
}

void GOGLWidget::InitLight(GLightBase &light, int index)
{
    GUniformType uniform_types[] = {
        GUniformType::kTranslate,
        GUniformType::kScale,
        GUniformType::kColor,
        GUniformType::kViewMatrix,
        GUniformType::kProjectionMatrix,
    };

    int uniform_count = sizeof(uniform_types) / sizeof(GUniformType);
    light.Init(":0_light_obj.vert",
              ":0_light_obj.frag",
              uniform_types,
              uniform_count);

    light.SetScale(0.3);
    light.SetCameraGetter([this](){
        return &(this->_camera);
    });
}

void GOGLWidget::InitCubes()
{
    for(int cube_index=0; cube_index<_kCubesCount; cube_index++)
    {
        InitCube(_cubes[cube_index],cube_index);
    }
}

void GOGLWidget::InitCube(GCubeForLight &cube, int index)
{
    for(int i=0; i<_kLightsCount; i++)
    {
        cube.AddLight(_lights[i]);
    }

    GUniformType uniform_types[] = {
        GUniformType::kTranslate,
        GUniformType::kViewMatrix,
        GUniformType::kProjectionMatrix,
        GUniformType::kNormalMatrix,
        GUniformType::kEyeDir,
    };
    int uniform_count = sizeof(uniform_types) / sizeof(GUniformType);
    cube.Init(":5_multi_light.vert",
              ":5_multi_light.frag",
              uniform_types,
              uniform_count);

    int offset_x = index%2;
    int offset_z = index / 2;
    glm::vec3 translate = glm::vec3(offset_x*1.4,0,-offset_z*1.4);
    cube.SetTranslate(translate);
    cube.SetCameraGetter([this](){
        return &(this->_camera);
    });
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
        GUniformType::kLight0_Dir,
        GUniformType::kLight0_Shininess,
        GUniformType::kLight0_Strengthen,
        GUniformType::kLight0_Attenuation,
        GUniformType::kLight0_LinearAttenuation,
        GUniformType::kLight0_QuadraticAttenuation,
        GUniformType::kLight0_SpotInnerCutoff,
        GUniformType::kLight0_SpotOuterCutoff,
        GUniformType::kLight0_SpotExponent
    };

    int uniform_count = sizeof(uniform_types) / sizeof(GUniformType);
    cube.Init(":4_spot_light.vert",
              ":4_spot_light.frag",
              uniform_types,
              uniform_count);

    int offset_x = index%2;
    int offset_z = index / 2;
    glm::vec3 translate = glm::vec3(offset_x*1.4,0,-offset_z*1.4);
    cube.SetTranslate(translate);

    auto* ambient = new GUniformData<glm::vec4>();
    ambient->SetData(new glm::vec4(0.1,0.1,0.1,1.0));
    cube.SetUniformData(GUniformType::kAmbient,ambient);

    auto* light0_type = new GUniformData<GLightType>();
    light0_type->SetData(new int(GLightType::kSpotLight));
    cube.SetUniformData(GUniformType::kLight0_Type,light0_type);

    auto* light0_color = new GUniformData<glm::vec3>();
    light0_color->SetData(new glm::vec3(light.GetColor()));
    cube.SetUniformData(GUniformType::kLight0_Color,light0_color);

    auto* light0_pos = new GUniformData<glm::vec3>();
    light0_pos->SetData(new glm::vec3(light.GetTranslate()));
    cube.SetUniformData(GUniformType::kLight0_Pos,light0_pos);

    auto* light0_dir = new GUniformData<glm::vec3>();
    light0_dir->SetData(new glm::vec3(-1.0f, -1.0f, -1.0f));
    cube.SetUniformData(GUniformType::kLight0_Dir,light0_dir);

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

    auto* light0_spot_inner_cutoff = new GUniformData<float>();
    light0_spot_inner_cutoff->SetData(new float(12.5f));
    cube.SetUniformData(GUniformType::kLight0_SpotInnerCutoff,light0_spot_inner_cutoff);

    auto* light0_spot_outer_cutoff = new GUniformData<float>();
    light0_spot_outer_cutoff->SetData(new float(30.0f));
    cube.SetUniformData(GUniformType::kLight0_SpotOuterCutoff,light0_spot_outer_cutoff);

    auto* light0_spot_exponent = new GUniformData<float>();
    light0_spot_exponent->SetData(new float(32));
    cube.SetUniformData(GUniformType::kLight0_SpotExponent,light0_spot_exponent);

    cube.SetCameraGetter([this](){
        return &(this->_camera);
    });
}



















