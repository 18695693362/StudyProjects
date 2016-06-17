#ifndef GCAMERA_H
#define GCAMERA_H

#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"

class GCamera
{
public:
    GCamera(const glm::vec3& pos,const glm::vec3& target,const glm::vec3& up=glm::vec3(0.0,1.0,0.0));

    void GetViewMatrix(glm::mat4x4& view_matrix);

    void MoveInX(float step);
    void MoveInY(float step);
    void MoveInZ(float step);
    void MoveLeft(float step=1.0f);
    void MoveRight(float step=1.0f);
    void MoveForward(float step=1.0f);
    void MoveBackward(float step=1.0f);
    void MoveUp(float step=1.0f);
    void MoveDown(float step=1.0f);
private:
    float _change_step;

    glm::vec3 _position;
    glm::vec3 _target;

    glm::vec3 _U;
    glm::vec3 _V;
    glm::vec3 _W;
};

#endif // GCAMERA_H
