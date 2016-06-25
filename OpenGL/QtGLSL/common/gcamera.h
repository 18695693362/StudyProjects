#ifndef GCAMERA_H
#define GCAMERA_H

#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include "../libs/glm/glm/gtc/quaternion.hpp"
#include <functional>
class GCamera
{
public:
    // Constants
    static const glm::vec3 LocalForward;
    static const glm::vec3 LocalUp;
    static const glm::vec3 LocalRight;

    GCamera(const glm::vec3& pos=glm::vec3(0.0f));

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
    void GetCurProjectionMatrix(glm::mat4x4& matrix)
    {
        if(_cur_projection_type==kOrtho)
        {
            matrix = _ortho;
        }
        else
        {
            matrix = _perspective;
        }
    }
    void GetProjectionMatrix();

    void ResetPosAndOrient();

    const glm::vec3& GetPosition() const
    {
        return _position;
    }
    glm::vec3 GetForward() const
    {
        return _D;
    }
    glm::vec3 GetUp() const
    {
        return _U;
    }
    glm::vec3 GetRight() const
    {
        return _R;
    }

    void Translate(const glm::vec3 &step);
    void Translate(float dx, float dy, float dz);
    void Rotate(const glm::quat &dr);
    void Rotate(float angle, const glm::vec3 &axis);
    void Rotate(float angle, float ax, float ay, float az);
    void GetViewMatrix(glm::mat4x4& view_matrix);

    void StopAllMove();
    void RotateAroundTarget(bool is_stop, const glm::vec3 &target_pos=glm::vec3(0.0f,0.0f,0.0f));
    void FaceToTarget(bool is_stop, const glm::vec3 &target_pos=glm::vec3(0.0f,0.0f,0.0f), std::function<void(void)> cb=nullptr);
    enum InfoType{
        kAll,
        kPos = 1,
        kPosTarget = 3,
        kR = 4,
        kU = 8,
        kD = 16,
        kRUD = 28,
    };
    void PrintCameraInfo(unsigned int type);
private:
    bool _is_pos_changed;
    bool _is_orien_changed;
    bool _is_camera_changed;

    bool _is_rotate_by_target;
    bool _is_face_to_target;

    ProjectionType  _cur_projection_type;
    glm::mat4x4     _ortho;
    glm::mat4x4     _perspective;

    glm::vec3 _original_pos;
    glm::vec3 _position;
    glm::vec3 _U;
    glm::vec3 _D;
    glm::vec3 _R;
};

#endif // GCAMERA_H
