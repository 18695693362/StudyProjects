#include "gmodel.h"
#include <string>
using namespace std;
string GModel::GetUniformName(GUniformType type)
{
    switch (type)
    {
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
    default:
        break;
    }
    return "";
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
