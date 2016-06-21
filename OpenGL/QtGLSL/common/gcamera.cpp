#include "gcamera.h"
#include "glhelper.h"
#include "gtimermgr.h"

#include <string>
using namespace std;

#define CHANGE_POS(comp,value) do{\
    _position.comp += (value);\
    RotateAroundTarget(true);\
    _is_pos_changed = true;\
}while(0);

const glm::vec3 GCamera::LocalForward(0.0f, 0.0f, -1.0f);
const glm::vec3 GCamera::LocalUp(0.0f, 1.0f, 0.0f);
const glm::vec3 GCamera::LocalRight(1.0f, 0.0f, 0.0f);

GCamera::GCamera()
    :_is_camera_changed(true)
    ,_cur_projection_type(ProjectionType::kOrtho)
    ,_position(0.0,0.0,0.0)
    ,_U(LocalUp)
    ,_D(LocalForward)
    ,_R(LocalRight)
{
    //_ortho          = glm::ortho(0.0f, 400.0f, 0.0f, 400.0f, 0.1f, 100.0f);
    //_ortho          = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.1f,100.0f);
    _ortho          = glm::ortho(-4.0f,4.0f,-4.0f,4.0f,-100.0f,100.0f);
    _perspective    = glm::perspective(45.0f,1.0f,-1.0f,8.0f);
}

void GCamera::SetOrthoMatrix(float left, float right, float bottom, float top, float near, float far, bool is_active)
{
    _ortho = glm::ortho(left,right,bottom,top,near,far);

    if(is_active)
    {
        _cur_projection_type = ProjectionType::kOrtho;
    }
}

void GCamera::SetPerspectiveMatrix(float fovy, float aspect, float zNear, float zFar, bool is_active)
{
    _perspective = glm::perspective(fovy, aspect, zNear, zFar);

    if(is_active)
    {
        _cur_projection_type = ProjectionType::kPerspective;
    }
}

void GCamera::GetViewMatrix(glm::mat4x4 &view_matrix)
{
    if(_is_pos_changed)
    {
        PrintCameraInfo(InfoType::kPos);
        _is_pos_changed = false;
    }
    if(_is_orien_changed)
    {
        PrintCameraInfo(InfoType::kRUD);
        _is_orien_changed = false;
    }

//#define G_USE_SELF_MATRIX
#ifdef G_USE_SELF_MATRIX
    glm::mat4x4 move_matrix = GLHelper::GetTranslate(-_position.x,-_position.y,-_position.z);
    glm::mat4x4 w_to_v_matrix;

    w_to_v_matrix[0][0] = _R.x; w_to_v_matrix[0][1] = _R.y; w_to_v_matrix[0][2] = _R.z; w_to_v_matrix[0][3] = 0.0;
    w_to_v_matrix[1][0] = _U.x; w_to_v_matrix[1][1] = _U.y; w_to_v_matrix[1][2] = _U.z; w_to_v_matrix[1][3] = 0.0;
    w_to_v_matrix[2][0] = _D.x; w_to_v_matrix[2][1] = _D.y; w_to_v_matrix[2][2] = _D.z; w_to_v_matrix[2][3] = 0.0;
    w_to_v_matrix[3] = glm::vec4(0); w_to_v_matrix[3][3] = 1.0;

    view_matrix = w_to_v_matrix * move_matrix;
#else
    view_matrix = glm::lookAt(_position,_position+_D,_U);
#endif
}

void GCamera::Translate(const glm::vec3 &step)
{
    CHANGE_POS(x,step.x);
    CHANGE_POS(y,step.y);
    CHANGE_POS(z,step.z);
}

void GCamera::Translate(float dx, float dy, float dz)
{
    CHANGE_POS(x,dx);
    CHANGE_POS(y,dy);
    CHANGE_POS(z,dz);
}

void GCamera::Rotate(const glm::quat &dr)
{
    glm::quat quat_D = glm::quat(0.0,_D.x,_D.y,_D.z);
    quat_D = dr*quat_D*glm::inverse(dr);
    _D.x = quat_D.x;
    _D.y = quat_D.y;
    _D.z = quat_D.z;

    glm::quat quat_U = glm::quat(0.0,_U.x,_U.y,_U.z);
    quat_U = dr*quat_U*glm::inverse(dr);
    _U.x = quat_U.x;
    _U.y = quat_U.y;
    _U.z = quat_U.z;

    _R = glm::cross(_U,_D);

    _is_orien_changed = true;
}

void GCamera::Rotate(float angle, const glm::vec3 &axis)
{
    angle = (angle / 2.0f) * M_PI / 180.0f;
    float s = std::sin(angle);
    float c = std::cos(angle);
    glm::vec3 ax = glm::normalize(axis);
    glm::quat rotate_quat = glm::normalize(glm::quat(c,  ax.x * s, ax.y* s, ax.z * s));
    Rotate(rotate_quat);
}

void GCamera::Rotate(float angle, float ax, float ay, float az)
{
    Rotate(angle,glm::vec3(ax,ay,az));
}

void GCamera::RotateAroundTarget(bool is_stop,const glm::vec3& target_pos)
{
    if(is_stop)
    {
        _is_rotate_by_target = false;
        GTimerMgr::GetInstance().Unschedule(this);
    }
    else
    {
        if(!_is_rotate_by_target)
        {
            _is_rotate_by_target = true;
            float angle = 180/4000*33;
            GTimerMgr::GetInstance().Schedule(this,[this,angle,target_pos](float dt)
            {
                glm::mat4x4 move_mat = GLHelper::GetTranslate(target_pos.x-this->_position.x,
                                                              target_pos.y-this->_position.y,
                                                              target_pos.z-this->_position.z);
                glm::vec4 axis = move_mat*glm::vec4(this->_U,1.0);
                this->Rotate(angle,axis.x,axis.y,axis.z);
            },GTimerMgr::REPEAT_FOREVER,33);
        }
    }
}

void GCamera::PrintCameraInfo(unsigned int type)
{
    GLHelper::Log("+++++++++++++++++++++++++");
    GLHelper::Log(string("camera = ")+to_string((uint64_t)this));

    if(type&InfoType::kPos || type==0)
    {
        GLHelper::Log(string("pos.x  = ")+to_string(_position.x));
        GLHelper::Log(string("pos.y  = ")+to_string(_position.y));
        GLHelper::Log(string("pos.z  = ")+to_string(_position.z));
    }
    if(type&InfoType::kU || type==0)
    {
        GLHelper::Log(string("U.x    = ")+to_string(_U.x));
        GLHelper::Log(string("U.y    = ")+to_string(_U.y));
        GLHelper::Log(string("U.z    = ")+to_string(_U.z));
    }
    if(type&InfoType::kR || type==0)
    {
        GLHelper::Log(string("R.x    = ")+to_string(_R.x));
        GLHelper::Log(string("R.y    = ")+to_string(_R.y));
        GLHelper::Log(string("R.z    = ")+to_string(_R.z));
    }
    if(type&InfoType::kD || type==0)
    {
        GLHelper::Log(string("D.x    = ")+to_string(_D.x));
        GLHelper::Log(string("D.y    = ")+to_string(_D.y));
        GLHelper::Log(string("D.z    = ")+to_string(_D.z));
    }
}
