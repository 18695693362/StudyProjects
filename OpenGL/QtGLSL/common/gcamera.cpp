#include "gcamera.h"
#include "glhelper.h"

GCamera::GCamera(const glm::vec3 &pos, const glm::vec3 &target, const glm::vec3 &up)
{
    _position = pos;
    _target = target;
    _U = glm::normalize(up);

    _W = glm::normalize(pos - target);
    _V = glm::cross(_U,_W);
}

void GCamera::GetViewMatrix(glm::mat4x4 &view_matrix)
{
    glm::mat4x4 move_matrix = GLHelper::GetTranslate(_position.x,_position.y,_position.z);
    glm::mat4x4 w_to_v_matrix;

    w_to_v_matrix[0][0] = _U.x; w_to_v_matrix[0][1] = _U.y; w_to_v_matrix[0][2] = _U.z; w_to_v_matrix[0][3] = 0.0;
    w_to_v_matrix[1][0] = _V.x; w_to_v_matrix[1][1] = _V.y; w_to_v_matrix[1][2] = _V.z; w_to_v_matrix[1][3] = 0.0;
    w_to_v_matrix[2][0] = _W.x; w_to_v_matrix[2][1] = _W.y; w_to_v_matrix[2][2] = _W.z; w_to_v_matrix[2][3] = 0.0;
    w_to_v_matrix[3] = glm::vec4(0); w_to_v_matrix[3][3] = 1.0;

    view_matrix = w_to_v_matrix * move_matrix;
}

void GCamera::MoveInX(float step)
{
    _position.x += step;
}

void GCamera::MoveInY(float step)
{
    _position.y += step;
}

void GCamera::MoveInZ(float step)
{
    _position.z += step;
}

void GCamera::MoveLeft(float step)
{
    _position.x -= step;
}

void GCamera::MoveRight(float step)
{
    _position.x += step;
}

void GCamera::MoveForward(float step)
{
    _position.z -= step;
}

void GCamera::MoveBackward(float step)
{
    _position.z += step;
}

void GCamera::MoveUp(float step)
{
    _position.y += step;
}

void GCamera::MoveDown(float step)
{
    _position.y -= step;
}
