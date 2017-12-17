#include "glight.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <QOpenGLFunctions>
#include <string>

using namespace std;

GLightBase::GLightBase()
{
    memset(_property_local,-1,sizeof(_property_local));
}

const std::string GLightBase::GetLightTypeName(GLightType type)
{
    switch(type)
    {
    case GLightType::kDirectionLight:
        return "dir_light";
    case GLightType::kPointLight:
        return "point_light";
    case GLightType::kSpotLight:
        return "spot_light";
    default:
        break;
    }
    return "error_light";
}

const std::string GLightBase::GetLightPropName(GLightPropType type)
{
    if(type >= 0 && type < GLightPropType::kLightPropType_TypeNumbs)
    {
        const char** names = GetLightPropNameArr();
        return names[type];
    }
    return "error_type";
}

const char **GLightBase::GetLightPropNameArr()
{
    static const char* names[] = {
        "enable",
        "type",
        "color",
        "dir",
        "pos",
        "ambient",
        "shininess",
        "strengthen",
        "attenuation",
        "linear_attenuation",
        "quadratic_attenuation",
        "spot_inner_cutoff",
        "spot_outer_cutoff"
    };
    return names;
}

void GLightBase::SetPropertyLocal(GLightPropType type, GLint local)
{
    if(type >= 0 && type < GLightPropType::kLightPropType_TypeNumbs)
    {
        _property_local[type] = local;
    }
}

GLint GLightBase::GetPropertyLocal(GLightPropType type)
{
    if(type >= 0 && type < GLightPropType::kLightPropType_TypeNumbs)
    {
        return _property_local[type];
    }
    return -1;
}

void GLightBase::UploadProperty(GLightPropType type, GCamera *camera)
{
    GLint local = GetPropertyLocal(type);
    if(local > -1)
    {
        switch (type)
        {
        case kLightPropType_Enable:
        {
            int enable = (int)property.enable;
            glUniform1i(local,enable);
            break;
        }
        case kLightPropType_Type:
        {
            glUniform1i(local,property.type);
            break;
        }
        case kLightPropType_Color:
        {
            glUniform3fv(local,1,glm::value_ptr(property.color));
            break;
        }
        case kLightPropType_Dir:
        {
            if(camera)
            {
                glm::mat4x4 view_matrix;
                camera->GetViewMatrix(view_matrix);
                glm::mat3x3 normal_mat = glm::transpose(glm::inverse(glm::mat3x3(view_matrix)));
                glm::vec3 dir = normal_mat * (property.dir);
                dir = glm::normalize(dir);
                glUniform3fv(local,1,glm::value_ptr(dir));
            }
            //glUniform3fv(local,1,glm::value_ptr(property.dir));
            break;
        }
        case kLightPropType_Pos:
        {
            if(camera)
            {
                property.pos = GetTranslate();

                glm::mat4x4 view_matrix;
                camera->GetViewMatrix(view_matrix);
                glm::vec4 pos = glm::vec4(property.pos,1.0);
                pos = view_matrix * pos;
                glm::vec3 final_pos = glm::vec3(pos.x,pos.y,pos.z);
                glUniform3fv(local,1,glm::value_ptr(final_pos));
            }
            //glUniform3fv(local,1,glm::value_ptr(property.pos));
            break;
        }
        case kLightPropType_Ambient:
        {
            glUniform3fv(local,1,glm::value_ptr(property.ambient));
            break;
        }
        case kLightPropType_Shininess:
        {
            glUniform1f(local,property.shininess);
            break;
        }
        case kLightPropType_Strengthen:
        {
            glUniform1f(local,property.strengthen);
            break;
        }
        case kLightPropType_Attenuation:
        {
            glUniform1f(local,property.attenuation);
            break;
        }
        case kLightPropType_Linear_attenuation:
        {
            glUniform1f(local,property.linear_attenuation);
            break;
        }
        case kLightPropType_Quadratic_attenuation:
        {
            glUniform1f(local,property.linear_attenuation);
            break;
        }
        case kLightPropType_Spot_inner_cutoff:
        {
            glUniform1f(local,property.spot_inner_cutoff);
            break;
        }
        case kLightPropType_Spot_outer_cutoff:
        {
            glUniform1f(local,property.spot_outer_cutoff);
            break;
        }
        default:
            break;
        }
    }
    else
    {
        GLHelper::Log(string("Error GLightBase::UploadProperty type = ")+GetLightPropName(type));
    }
}

void GCubeLight::Init(const char *v_shader, const char *f_shader, GUniformType* uniform_types, int count)
{
    if(!_is_inited)
    {
        _is_inited = true;

        _program = GLHelper::CreateShaderProgramWithFiles(v_shader,f_shader);
        glUseProgram(_program);
        {
            glGenVertexArrays(1,&_vertex_arr_obj);
            glBindVertexArray(_vertex_arr_obj);

            GLfloat* vertex_data = NULL;
            GLint    vertex_data_size;
            GLfloat* vertex_color_data = NULL;
            GLint    vertex_color_data_size;
            GLuint*  vertex_index_data = NULL;
            GLint    vertex_index_data_size;
            GLint    vertex_pos_comp_count;
            GLint    vertex_color_comp_count;

            GetVertexData(vertex_data,vertex_index_data,vertex_color_data,
                          vertex_data_size,vertex_index_data_size,vertex_color_data_size,
                          vertex_pos_comp_count,vertex_color_comp_count);

            glGenBuffers(1,&_vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER,_vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER,vertex_data_size+vertex_color_data_size,NULL,GL_STATIC_DRAW);
            glBufferSubData(GL_ARRAY_BUFFER,0,vertex_data_size,vertex_data);
            glBufferSubData(GL_ARRAY_BUFFER,vertex_data_size,vertex_color_data_size,vertex_color_data);

            glGenBuffers(1,&_vertex_index_buffer);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_vertex_index_buffer);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER,vertex_index_data_size,vertex_index_data,GL_STATIC_DRAW);

            if(uniform_types)
            {
                for(auto iter=0; iter<count; iter++)
                {
                    GUniformInfo info;
                    info.type = uniform_types[iter];
                    info.name = GModel::GetUniformName(info.type);
                    info.local = GLHelper::GetUniformLocal(_program,info.name.c_str());
                    _uniform_infos.push_back(info);
                }
            }
            else
            {
                for(auto iter=_uniform_infos.begin(); iter!=_uniform_infos.end(); iter++)
                {
                    iter->local = GLHelper::GetUniformLocal(_program,iter->name.c_str());
                }
            }

            glVertexAttribPointer(GAttribType::kAttribType_Pos,vertex_pos_comp_count,GL_FLOAT,GL_FALSE,
                                  0,BUFF_OFFSET(0));
            glVertexAttribPointer(GAttribType::kAttribType_Color,vertex_color_comp_count,GL_FLOAT,GL_FALSE,
                                  0,BUFF_OFFSET(vertex_data_size));
            glEnableVertexAttribArray(GAttribType::kAttribType_Pos);
            glEnableVertexAttribArray(GAttribType::kAttribType_Color);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
        }
        glUseProgram(0);
    }
}

void GCubeLight::GetVertexData(GLfloat*& vertex_data,GLuint*& vertex_index_data,GLfloat*& vertex_color_data,
                          int& vertex_data_size,int& index_data_size,int& color_data_size,
                          int& vertex_pos_comp_count,int& vertex_color_comp_count)
{
    static GLfloat v_data[] = {
        -0.5, -0.5,  0.5, //0 front-left-down
        -0.5,  0.5,  0.5, //1 front-left-up
         0.5,  0.5,  0.5, //2 front-right-up
         0.5, -0.5,  0.5, //3 front-right-down
        -0.5, -0.5, -0.5, //4 back-left-down
        -0.5,  0.5, -0.5, //5 back-left-up
         0.5,  0.5, -0.5, //6 back-right-up
         0.5, -0.5, -0.5, //7 back-right-down
    };
    static GLfloat v_color[] = {
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 1.0, 0.0,
    };
    static GLuint v_index_data[] = {
        0, 1, 3, 2, 7, 6, 4, 5,
        0xFFFF,
        2, 6, 1, 5, 0, 4, 3, 7
    };

    vertex_data = v_data;
    vertex_data_size = sizeof(v_data);

    vertex_color_data = v_color;
    color_data_size = sizeof(v_color);

    vertex_index_data = v_index_data;
    index_data_size = sizeof(v_index_data);

    vertex_pos_comp_count = 3;
    vertex_color_comp_count = 3;
}

void GCubeLight::Draw()
{
    if(_is_inited)
    {
        glUseProgram(_program);
        {
            SetUniformInDraw();

            glBindVertexArray(_vertex_arr_obj);
            glDrawElements(GL_TRIANGLE_STRIP,8,GL_UNSIGNED_INT,BUFF_OFFSET(0));
            glDrawElements(GL_TRIANGLE_STRIP,8,GL_UNSIGNED_INT,BUFF_OFFSET(9*sizeof(GLuint)));
            glBindVertexArray(0);
        }
        glUseProgram(0);
    }
}
