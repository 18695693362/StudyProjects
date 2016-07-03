#include "gcubeforlight.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include "glight.h"

GCubeForLight::GCubeForLight()
{

}

void GCubeForLight::Init(const char *v_shader, const char *f_shader, GUniformType* uniform_types, int count)
{
    if(!_is_inited)
    {
        _is_inited = true;

        _program = GLHelper::CreateShaderProgramWithFiles(v_shader,f_shader);
        glUseProgram(_program);
        {
            glGenVertexArrays(1,&_vertex_arr_obj);
            glBindVertexArray(_vertex_arr_obj);

            GLfloat* vertex_data;
            int data_size, pos_comp_count, color_comp_count, normal_comp_count, stride;
            GetVertexData(vertex_data, data_size, pos_comp_count, color_comp_count, normal_comp_count);
            stride = sizeof(GLfloat)*(pos_comp_count+color_comp_count+normal_comp_count);

            glGenBuffers(1, &_vertex_buffer);
            glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER,data_size,vertex_data,GL_STATIC_DRAW);

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

            glVertexAttribPointer(GAttribType::kPos,pos_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(0));
            glVertexAttribPointer(GAttribType::kColor,color_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(sizeof(GLfloat)*pos_comp_count));
            glVertexAttribPointer(GAttribType::kNormal,normal_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(sizeof(GLfloat)*(pos_comp_count+color_comp_count)));
            glEnableVertexAttribArray(GAttribType::kPos);
            glEnableVertexAttribArray(GAttribType::kColor);
            glEnableVertexAttribArray(GAttribType::kNormal);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER,0);
        }
        glUseProgram(0);
    }
}

void GCubeForLight::GetVertexData(GLfloat *&vertex_data, int& data_size, int &pos_comp_count, int &color_comp_count, int &normal_comp_count)
{
    static GLfloat vertices[] =
    {
        //----pos----------/ /----color-------/   /----normal------/
        -0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f, -1.0f,//1
         0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f,  1.0f,//2
         0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0, -1.0f,  0.0f,  0.0f,//3
        -0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0, -1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  1.0f,  0.0f,  0.0f,//4
         0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f, -1.0f,  0.0f,//5
         0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f, -1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  1.0f,  0.0f,//6
         0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 0.5, 0.31, 1.0,  0.0f,  1.0f,  0.0f
    };
    vertex_data = vertices;
    data_size = sizeof(vertices);
    pos_comp_count = 3;
    color_comp_count = 4;
    normal_comp_count = 3;
}

void GCubeForLight::Draw()
{
    if(_is_inited)
    {
        glUseProgram(_program);
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

            auto info = GetUniformInfo(GUniformType::kNormalMatrix);
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

            glBindVertexArray(_vertex_arr_obj);
            glDrawArrays(GL_TRIANGLES,0,36);
            glBindVertexArray(0);
        }
        glUseProgram(0);
    }
}


