#ifndef GMODEL_H
#define GMODEL_H
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include <functional>
#include <QtOpenGL>

class GModel
{
public:
    GModel(){}
    virtual ~GModel(){}
    virtual void Draw() = 0;

    void SetTranslate(const glm::vec3& translate)
    {
        _translate = translate;
    }
    void SetScale(float scale)
    {
        _scale = scale;
    }
    float GetScale()
    {
        return _scale;
    }
    void SetColor(glm::vec4 color)
    {
        _color = color;
    }
    glm::vec4 GetColor()
    {
        return _color;
    }
    void SetViewMatrixGetter(std::function<void(glm::mat4x4&)> getter)
    {
        _view_matrix_getter = getter;
    }

    void SetProjectionMatrixGetter(std::function<void(glm::mat4x4&)> getter)
    {
        _projection_matrix_getter = getter;
    }

    void SetCameraPosGetter(std::function<const glm::vec3&()> getter)
    {
        _camera_pos_getter = getter;
    }
protected:
    bool _is_inited = false;
    glm::vec3 _translate;
    glm::vec4 _color;
    float     _scale;
    std::function<void(glm::mat4x4&)> _view_matrix_getter;
    std::function<void(glm::mat4x4&)> _projection_matrix_getter;
    std::function<const glm::vec3&()> _camera_pos_getter;
};

#endif // GMODEL_H
