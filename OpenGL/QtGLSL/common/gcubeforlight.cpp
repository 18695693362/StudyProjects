#include "gcubeforlight.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include "glight.h"

using namespace std;

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
            GCubeDataHelper::GetVertexData(vertex_data, data_size, pos_comp_count, color_comp_count, normal_comp_count);
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

            string struct_name;
            string prop_name;
            GLint  prop_local;
            for(int idx=0; idx<_lights.size(); idx++)
            {
                struct_name = string("lights[") + to_string(idx) + "].";
                for(GLightPropType prop_type = kLightPropType_Enable;
                    prop_type<kLightPropType_TypeNumbs; )
                {
                    prop_name = struct_name + GLightBase::GetLightPropName(prop_type);
                    prop_local = GLHelper::GetUniformLocal(_program,prop_name.c_str());
                    _lights[idx]->SetPropertyLocal(prop_type,prop_local);

                    prop_type = (GLightPropType)((int)prop_type+1);
                }
            }

            glVertexAttribPointer(GAttribType::kAttribType_Pos,pos_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(0));
            glVertexAttribPointer(GAttribType::kAttribType_Color,color_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(sizeof(GLfloat)*pos_comp_count));
            glVertexAttribPointer(GAttribType::kAttribType_Normal,normal_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(sizeof(GLfloat)*(pos_comp_count+color_comp_count)));
            glEnableVertexAttribArray(GAttribType::kAttribType_Pos);
            glEnableVertexAttribArray(GAttribType::kAttribType_Color);
            glEnableVertexAttribArray(GAttribType::kAttribType_Normal);

            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER,0);
            glBindBuffer(GL_UNIFORM_BUFFER, 0);
        }
        glUseProgram(0);
    }
}

void GCubeForLight::Draw()
{
    if(_is_inited)
    {
        glUseProgram(_program);
        {
            SetUniformInDraw();
            SetLightInDraw();

            glBindVertexArray(_vertex_arr_obj);
            glDrawArrays(GL_TRIANGLES,0,36);
            glBindVertexArray(0);
        }
        glUseProgram(0);
    }
}

void GCubeForLight::SetLightInDraw()
{
    GCamera* camera = nullptr;
    if(_camera_getter)
    {
        camera = _camera_getter();
    }

    for(int idx=0; idx<_lights.size(); idx++)
    {
        for(GLightPropType prop_type = kLightPropType_Enable;
            prop_type<kLightPropType_TypeNumbs; )
        {
            //_lights[idx]->SetPropertyLocal(prop_type,prop_local);
            _lights[idx]->UploadProperty(prop_type,camera);

            prop_type = (GLightPropType)((int)prop_type+1);
        }
    }
}


