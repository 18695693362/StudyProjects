#include "gcamera.h"
#include "glhelper.h"
#include "gtimermgr.h"

#include <string>
using namespace std;

#define CHANGE_POS(comp,value) do{\
    _position.comp += (value);\
    RotateAroundTarget(true);\
    _is_camera_changed=true;\
}while(0);

GCamera::GCamera(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up)
    :_is_camera_changed(true)
    ,_cur_projection_type(ProjectionType::kOrtho)
{
    _position = pos;
    _target = target;
    _U = glm::normalize(up);

    //_ortho          = glm::ortho(0.0f, 400.0f, 0.0f, 400.0f, 0.1f, 100.0f);
    //_ortho          = glm::ortho(-10.0f,10.0f,-10.0f,10.0f,0.1f,100.0f);
    _ortho          = glm::ortho(-4.0f,4.0f,-4.0f,4.0f,-100.0f,100.0f);
    _perspective    = glm::perspective(45.0f,1.0f,0.1f,100.0f);
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
    if(_is_camera_changed)
    {
        UpdateCamera();
        PrintCameraInfo(InfoType::kPosTarget);
    }

    glm::mat4x4 move_matrix = GLHelper::GetTranslate(-_position.x,-_position.y,-_position.z);
    glm::mat4x4 w_to_v_matrix;

    w_to_v_matrix[0][0] = _R.x; w_to_v_matrix[0][1] = _R.y; w_to_v_matrix[0][2] = _R.z; w_to_v_matrix[0][3] = 0.0;
    w_to_v_matrix[1][0] = _U.x; w_to_v_matrix[1][1] = _U.y; w_to_v_matrix[1][2] = _U.z; w_to_v_matrix[1][3] = 0.0;
    w_to_v_matrix[2][0] = _D.x; w_to_v_matrix[2][1] = _D.y; w_to_v_matrix[2][2] = _D.z; w_to_v_matrix[2][3] = 0.0;
    w_to_v_matrix[3] = glm::vec4(0); w_to_v_matrix[3][3] = 1.0;

    view_matrix = w_to_v_matrix * move_matrix;

//    view_matrix = glm::lookAt(_position,
//                              glm::vec3(0.0, 0.0, 0.0),
//                              glm::vec3(0.0, 1.0, 0.0));
    //view_matrix = glm::lookAt(_position,_target,_U);
}

void GCamera::Move(glm::vec3 step)
{
    _position += step;
    RotateAroundTarget(true);
    _is_camera_changed=true;
}

void GCamera::MoveInX(float step)
{
    CHANGE_POS(x,step)
}

void GCamera::MoveInY(float step)
{
    CHANGE_POS(y,step)
}

void GCamera::MoveInZ(float step)
{
    CHANGE_POS(z,step)
}

void GCamera::MoveLeft(float step)
{
    CHANGE_POS(x,-step)
}

void GCamera::MoveRight(float step)
{
    CHANGE_POS(x,step)
}

void GCamera::MoveForward(float step)
{
    CHANGE_POS(z,-step)
}

void GCamera::MoveBackward(float step)
{
    CHANGE_POS(z,step)
}

void GCamera::MoveUp(float step)
{
    CHANGE_POS(y,step)
}

void GCamera::MoveDown(float step)
{
    CHANGE_POS(y,-step)
}

void GCamera::RotateAroundTarget(bool is_stop)
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
            float angle = 3.1415925/4000*33;
            GTimerMgr::GetInstance().Schedule(this,[this,angle](float dt)
            {
                glm::mat4x4 move_mat = GLHelper::GetTranslate(this->_target.x-this->_position.x,
                                                              this->_target.y-this->_position.y,
                                                              this->_target.z-this->_position.z);
                glm::vec4 axis = move_mat*glm::vec4(this->_U,1.0);
                glm::vec4 new_pos = GLHelper::GetRotate(angle,axis.x,axis.y,axis.z) *
                        glm::vec4(this->_position,1.0);
                this->_position.x = new_pos.x;
                this->_position.y = new_pos.y;
                this->_position.z = new_pos.z;

                this->_is_camera_changed = true;
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
    if(type&InfoType::kTarget || type==0)
    {
        GLHelper::Log(string("tar.x  = ")+to_string(_target.x));
        GLHelper::Log(string("tar.y  = ")+to_string(_target.y));
        GLHelper::Log(string("tar.z  = ")+to_string(_target.z));
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

void GCamera::UpdateCamera()
{
    if(_is_camera_changed)
    {
        _R = glm::cross(_U,_D);
        _D = glm::normalize(_position - _target);
    }
    _is_camera_changed = false;
}
