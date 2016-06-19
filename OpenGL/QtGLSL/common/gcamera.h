#ifndef GCAMERA_H
#define GCAMERA_H

#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

class GCamera
{
public:
    GCamera(const glm::vec3& pos=glm::vec3(0.0,0.0,1.0),
            const glm::vec3& target=glm::vec3(0.0,0.0,0.0),
            const glm::vec3& up=glm::vec3(0.0,1.0,0.0));

    enum ProjectionType{
        kOrtho,
        kPerspective
    };
    void SetOrthoMatrix( float left, float right,
                         float bottom, float top,
                         float near, float far, bool is_active);
    void GetOrhtoMatrix(glm::mat4x4& matrix)
    {
        matrix = _ortho;
    }

    void SetPerspectiveMatrix(float fovy, float aspect, float zNear,
                              float zFar, bool is_active);
    void GetPerspectiveMatrix(glm::mat4x4& matrix)
    {
        matrix = _perspective;
    }

    void SetCurProjectionType(ProjectionType type)
    {
        _cur_projection_type = type;
    }

    void GetViewMatrix(glm::mat4x4& view_matrix);
    void GetProjectionMatrix();

    void Move(glm::vec3 step);
    void MoveInX(float step);
    void MoveInY(float step);
    void MoveInZ(float step);
    void MoveLeft(float step=1.0f);
    void MoveRight(float step=1.0f);
    void MoveForward(float step=1.0f);
    void MoveBackward(float step=1.0f);
    void MoveUp(float step=1.0f);
    void MoveDown(float step=1.0f);

    void RotateAroundTarget(bool is_stop);

    enum InfoType{
        kAll,
        kPos    = 1,
        kTarget = 2,
        kPosTarget = 3,
        kR = 4,
        kU = 8,
        kD = 16,
        kRUD = 28,
    };
    void PrintCameraInfo(unsigned int type);
private:
    void UpdateCamera();
    bool  _is_camera_changed;
    float _change_step;

    bool    _is_rotate_by_target;

    ProjectionType  _cur_projection_type;
    glm::mat4x4     _ortho;
    glm::mat4x4     _perspective;

    glm::vec3 _position;
    glm::vec3 _target;

    glm::vec3 _R;
    glm::vec3 _U;
    glm::vec3 _D;
};

#endif // GCAMERA_H
