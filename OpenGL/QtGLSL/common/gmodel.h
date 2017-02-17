#ifndef GMODEL_H
#define GMODEL_H
#include "glhelper.h"
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include <functional>
#include <QtOpenGL>
#include "gcamera.h"

// shader helper
enum GUniformType
{
    kTranslate,
    kScale,
    kColor,
    kModelMatrix,
    kViewMatrix,
    kProjectionMatrix,
    kNormalMatrix,
    kAmbient,
    kEyePos, //eye-coordinate eye-pos always (0,0,0)
    kEyeDir,
    kLight0_Type,
    kLight0_Color,
    kLight0_Pos,
    kLight0_Dir,
    kLight0_Shininess,
    kLight0_Strengthen,
    kLight0_Attenuation,
    kLight0_LinearAttenuation,
    kLight0_QuadraticAttenuation,
    kLight0_SpotInnerCutoff,
    kLight0_SpotOuterCutoff,
    kLight0_SpotExponent,
};

class GUniformDataBase
{
public:
    virtual ~GUniformDataBase(){}
    virtual void* GetData() const = 0;
    virtual void SetData(void* value) = 0;
};

template<typename DataType>
class GUniformData: public GUniformDataBase
{
public:
    GUniformData(){}
    GUniformData(const GUniformData& src)
    {
        DataType* temp = (DataType*)src.GetData();
        DataType* new_data = new DataType(*temp);
        SetData(new_data);
    }
    GUniformData& operator=(const GUniformData& src)
    {
        DataType* temp = (DataType*)src.GetData();
        DataType* new_data = new DataType(*temp);
        SetData(new_data);
    }
    ~GUniformData()
    {
        if(data)
        {
            delete data;
        }
        data = nullptr;
    }

    void* GetData() const
    {
        return (void*)data;
    }
    void SetData(void* value)
    {
        if(data)
        {
            delete data;
        }
        data = (DataType*)value;
    }
private:
    DataType* data = nullptr;
};

class GUniformInfo
{
public:
    ~GUniformInfo()
    {
        if(data)
        {
            delete data;
        }
        data = nullptr;
    }

    GUniformType        type;
    int                 local;
    std::string         name;
    GUniformDataBase*   data = nullptr;
};

enum GAttribType
{
    kAttribType_Pos = 0,
    kAttribType_Color,
    kAttribType_Normal,
    kAttribType_Nums
};

struct GMaterialProp
{

};

class GLightBase;
class GModel:public QOpenGLExtraFunctions
{
public:
    static std::string GetUniformName(GUniformType type);

    GModel(){}
    virtual ~GModel(){}
    virtual void Draw() = 0;

    void SetTranslate(const glm::vec3& translate)
    {
        _translate = translate;
    }
    glm::vec3 GetTranslate()
    {
        return _translate;
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
    void GetModelMatrix(glm::mat4x4& out_mm);
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

    void SetCameraGetter(std::function<GCamera*(void)> getter)
    {
        _camera_getter = getter;
    }

    template<typename DataType>
    void AddUniformData(GUniformType type, DataType* data)
    {
        GUniformInfo* info_ptr = GetUniformInfo(type);
        if(info_ptr)
        {
            GLHelper::Log(std::string("Error: exist uniform type = ")+GModel::GetUniformName(type));
            return;
        }
        else
        {
            do
            {
                GUniformInfo info;
                info.type = type;
                _uniform_infos.push_back(info);
            }while(0);
            SetUniformData(type,data);
        }
    }
    template<typename DataType>
    void SetUniformData(GUniformType type, DataType* data)
    {
        GUniformInfo* info = GetUniformInfo(type);
        if(info)
        {
            info->data = data;
        }
        else
        {
            GLHelper::Log(std::string("Error: not exist uniform type = ")+GetUniformName(type));
        }
    }

    void AddLight(GLightBase* light);
    void RemoveLight(GLightBase* light);
protected:
    void SetUniformInDraw();
    GUniformInfo* GetUniformInfo(GUniformType type);
    GLint GetUniformLocal(GUniformType type);
    std::vector<GUniformInfo>           _uniform_infos;

    virtual void SetLightInDraw() {}
    std::vector<GLightBase*>            _lights;

    bool _is_inited = false;
    glm::vec3 _translate;
    glm::vec4 _color;
    float     _scale;
    std::function<void(glm::mat4x4&)> _view_matrix_getter;
    std::function<void(glm::mat4x4&)> _projection_matrix_getter;
    std::function<const glm::vec3&()> _camera_pos_getter;
    std::function<GCamera*()>         _camera_getter;
};

class GCubeDataHelper
{
public:
    static void GetVertexData(GLfloat *&vertex_data, int &data_size, int& pos_comp_count, int& color_comp_count, int& normal_comp_count);
};
#endif // GMODEL_H
