#include "gmodel.h"
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include "glight.h"

using namespace std;
string GModel::GetUniformName(GUniformType type)
{
    switch (type)
    {
    case GUniformType::kTranslate:
    {
        return "trans_vec";
    }
    case GUniformType::kScale:
    {
        return "scale";
    }
    case GUniformType::kColor:
    {
        return "color";
    }
    case GUniformType::kViewMatrix:
    {
        return "view_matrix";
    }
    case GUniformType::kProjectionMatrix:
    {
        return "projection_matrix";
    }
    case GUniformType::kNormalMatrix:
    {
        return "normal_matrix";
    }
    case GUniformType::kEyePos:
    {
        return "eye_pos";
    }
    case GUniformType::kEyeDir:
    {
        return "eye_dir";
    }
    case GUniformType::kAmbient:
    {
        return "ambient";
    }
    case GUniformType::kLight0_Type:
    {
        return "light0_type";
    }
    case GUniformType::kLight0_Color:
    {
        return "light0_color";
    }
    case GUniformType::kLight0_Pos:
    {
        return "light0_pos";
    }
    case GUniformType::kLight0_Dir:
    {
        return "light0_dir";
    }
    case GUniformType::kLight0_Shininess:
    {
        return "light0_shininess";
    }
    case GUniformType::kLight0_Strengthen:
    {
        return "light0_strengthen";
    }
    case GUniformType::kLight0_Attenuation:
    {
        return "light0_attenuation";
    }
    case GUniformType::kLight0_LinearAttenuation:
    {
        return "light0_linear_attenuation";
    }
    case GUniformType::kLight0_QuadraticAttenuation:
    {
        return "light0_quadratic_attenuation";
    }
    case GUniformType::kLight0_SpotInnerCutoff:
    {
        return "light0_spot_inner_cutoff";
    }
    case GUniformType::kLight0_SpotOuterCutoff:
    {
        return "light0_spot_outer_cutoff";
    }
    case GUniformType::kLight0_SpotExponent:
    {
        return "light0_spot_exponent";
    }
    default:
        break;
    }
    return "";
}

void GModel::AddLight(GLightBase *light)
{
    if(!light)
    {
        return;
    }
    for(auto iter=_lights.begin(); iter!=_lights.end(); iter++)
    {
        if(*iter == light)
        {
            return;
        }
    }
    _lights.push_back(light);
}

void GModel::RemoveLight(GLightBase *light)
{
    if(!light)
    {
        return;
    }
    for(auto iter=_lights.begin(); iter!=_lights.end(); )
    {
        if(*iter == light)
        {
            iter = _lights.erase(iter);
        }
        else
        {
            iter++;
        }
    }
}

void GModel::SetUniformInDraw()
{
    GCamera* camera = nullptr;
    if(_camera_getter)
    {
        camera = _camera_getter();
    }
    auto local = GetUniformLocal(GUniformType::kTranslate);
    if(local!=-1)
    {
        glm::vec3 transe = GetTranslate();
        glUniform3fv(local,1,glm::value_ptr(transe));
    }
    auto info = GetUniformInfo(GUniformType::kScale);
    if(info)
    {
        float scale = GetScale();
        glUniform1f(info->local,scale);
    }
    info = GetUniformInfo(GUniformType::kColor);
    if(info)
    {
        glm::vec4 color = GetColor();
        glUniform4fv(info->local,1,glm::value_ptr(color));
    }

    local = GetUniformLocal(GUniformType::kViewMatrix);
    if(local!=-1)
    {
        glm::mat4x4 view_matrix;
        if(camera)
        {
            camera->GetViewMatrix(view_matrix);
        }
        else if(_view_matrix_getter)
        {
            _view_matrix_getter(view_matrix);
        }
        glUniformMatrix4fv(local,1,GL_FALSE,glm::value_ptr(view_matrix));
    }

    local = GetUniformLocal(GUniformType::kProjectionMatrix);
    if(local!=-1)
    {
        glm::mat4x4 projection_matrix;
        if(camera)
        {
            camera->GetCurProjectionMatrix(projection_matrix);
        }
        else if(_projection_matrix_getter)
        {
            _projection_matrix_getter(projection_matrix);
        }
        glUniformMatrix4fv(local,1,GL_FALSE,glm::value_ptr(projection_matrix));
    }

    info = GetUniformInfo(GUniformType::kNormalMatrix);
    if(info && camera)
    {
        glm::mat4x4 view_matrix;
        camera->GetViewMatrix(view_matrix);
        glm::mat3x3 normal_mat = glm::transpose(glm::inverse(glm::mat3x3(view_matrix)));
        glUniformMatrix3fv(info->local,1,GL_FALSE,glm::value_ptr(normal_mat));
    }
    info = GetUniformInfo(GUniformType::kAmbient);
    if(info)
    {
        glm::vec4* ambient = (glm::vec4*)info->data->GetData();
        glUniform4fv(info->local,1,glm::value_ptr(*ambient));
    }
    info = GetUniformInfo(GUniformType::kEyePos);
    if(info && camera) // world-space
    {
        glUniform3fv(info->local,1,glm::value_ptr(camera->GetPosition()));
    }
    info = GetUniformInfo(GUniformType::kEyeDir);
    if(info) //eye-space
    {
        glm::vec3 dir = -camera->GetForward();
        dir = glm::normalize(dir);
        glUniform3fv(info->local,1,glm::value_ptr(dir));
    }
    auto light0_type_info = GetUniformInfo(GUniformType::kLight0_Type);
    auto light0_type = GLightType::kDirectionLight;
    if(light0_type_info)
    {
        light0_type = *((GLightType*)light0_type_info->data->GetData());
        glUniform1i(light0_type_info->local,light0_type);
    }
    info = GetUniformInfo(GUniformType::kLight0_Color);
    if(info)
    {
        glm::vec3* light0_color = (glm::vec3*)info->data->GetData();
        glUniform3fv(info->local,1,glm::value_ptr(*light0_color));
    }
    info = GetUniformInfo(GUniformType::kLight0_Pos);
    if(info && camera) // world-space
    {
        glm::vec3* light0_pos = (glm::vec3*)info->data->GetData();
        glm::mat4x4 view_matrix;
        camera->GetViewMatrix(view_matrix);
        glm::vec4 pos = glm::vec4(*light0_pos,1.0);
        pos = view_matrix * pos;
        glm::vec3 final_pos = glm::vec3(pos.x,pos.y,pos.z);
        glUniform3fv(info->local,1,glm::value_ptr(final_pos));
    }
    info = GetUniformInfo(GUniformType::kLight0_Dir);
    if(info && camera) // world-space
    {
        glm::vec3* light0_dir = (glm::vec3*)info->data->GetData();
        glm::mat4x4 view_matrix;
        camera->GetViewMatrix(view_matrix);
        glm::mat3x3 normal_mat = glm::transpose(glm::inverse(glm::mat3x3(view_matrix)));
        glm::vec3 dir = normal_mat * (*light0_dir);
        dir = glm::normalize(dir);
        glUniform3fv(info->local,1,glm::value_ptr(dir));
    }
    info = GetUniformInfo(GUniformType::kLight0_Shininess);
    if(info)
    {
        float* light0_shininess = (float*)info->data->GetData();
        glUniform1f(info->local,*light0_shininess);
    }
    info = GetUniformInfo(GUniformType::kLight0_Strengthen);
    if(info)
    {
        float* light0_strenghten = (float*)info->data->GetData();
        glUniform1f(info->local,*light0_strenghten);
    }
    info = GetUniformInfo(GUniformType::kLight0_Attenuation);
    if(info)
    {
        float* light0_attenuation = (float*)info->data->GetData();
        glUniform1f(info->local,*light0_attenuation);
    }
    info = GetUniformInfo(GUniformType::kLight0_LinearAttenuation);
    if(info)
    {
        float* light0_linear_attenuation = (float*)info->data->GetData();
        glUniform1f(info->local,*light0_linear_attenuation);
    }
    info = GetUniformInfo(GUniformType::kLight0_QuadraticAttenuation);
    if(info)
    {
        float* light0_quadratic_attenuation = (float*)info->data->GetData();
        glUniform1f(info->local,*light0_quadratic_attenuation);
    }
    info = GetUniformInfo(GUniformType::kLight0_SpotInnerCutoff);
    if(info)
    {
        float* cutoff_degree = (float*)info->data->GetData();
        float light0_spot_cos_cutoff = glm::cos(glm::radians(*cutoff_degree));
        glUniform1f(info->local,light0_spot_cos_cutoff);
    }
    info = GetUniformInfo(GUniformType::kLight0_SpotOuterCutoff);
    if(info)
    {
        float* out_cutoff_degree = (float*)info->data->GetData();
        float light0_spot_outer_cutoff = glm::cos(glm::radians(*out_cutoff_degree));
        glUniform1f(info->local,light0_spot_outer_cutoff);
    }
    info = GetUniformInfo(GUniformType::kLight0_SpotExponent);
    if(info)
    {
        float* light0_spot_exponent = (float*)info->data->GetData();
        glUniform1f(info->local,*light0_spot_exponent);
    }
}

GUniformInfo *GModel::GetUniformInfo(GUniformType type)
{
    for(auto iter=_uniform_infos.begin(); iter!=_uniform_infos.end(); iter++)
    {
        if(iter->type == type)
        {
            return &(*iter);
        }
    }
    return nullptr;
}

GLint GModel::GetUniformLocal(GUniformType type)
{
    GUniformInfo* info = GetUniformInfo(type);
    if(info)
    {
        return info->local;
    }
    return -1;
}
