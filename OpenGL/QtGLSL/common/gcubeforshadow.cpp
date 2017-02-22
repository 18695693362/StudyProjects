#include "gcubeforshadow.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include "glight.h"
//#include "goglwidget.h"

using namespace std;

GCubeForShadow::GCubeForShadow()
{

}

void GCubeForShadow::Init(const char *v_shader, const char *f_shader, GUniformType *uniform_types, int count)
{
    if(!_is_inited)
    {
        _is_inited = true;
        glGenVertexArrays(1,&_vertex_arr_obj);
        glGenBuffers(1, &_vertex_buffer);

        GLuint program = GLHelper::CreateShaderProgramWithFiles(v_shader,f_shader);
        _program[GDrawState::kDraw-1] = program;
        glUseProgram(program);
        {
            glBindVertexArray(_vertex_arr_obj);

            GLfloat* vertex_data;
            int data_size, pos_comp_count, color_comp_count, normal_comp_count, stride;
            GCubeDataHelper::GetVertexData(vertex_data, data_size, pos_comp_count, color_comp_count, normal_comp_count);
            stride = sizeof(GLfloat)*(pos_comp_count+color_comp_count+normal_comp_count);

            glBindBuffer(GL_ARRAY_BUFFER, _vertex_buffer);
            glBufferData(GL_ARRAY_BUFFER,data_size,vertex_data,GL_STATIC_DRAW);

            if(uniform_types)
            {
                for(auto iter=0; iter<count; iter++)
                {
                    GUniformInfo info;
                    info.type = uniform_types[iter];
                    info.name = GModel::GetUniformName(info.type);
                    info.local = GLHelper::GetUniformLocal(program,info.name.c_str());
                    _uniform_infos.push_back(info);
                }
            }
            else
            {
                for(auto iter=_uniform_infos.begin(); iter!=_uniform_infos.end(); iter++)
                {
                    iter->local = GLHelper::GetUniformLocal(program,iter->name.c_str());
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
                    prop_local = GLHelper::GetUniformLocal(program,prop_name.c_str());
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

        InitShodowShader();
    }
}

void GCubeForShadow::InitShodowShader()
{
    GLuint program = GLHelper::CreateShaderProgramWithFiles(":shadow_gen.vert",":shadow_gen.frag");
    _program[GDrawState::kDrawForShadow-1] = program;
    // draw for shadow not calc light

    // config depth texture object
    glGenTextures(1,&_depth_tex_obj);
    glBindTexture(GL_TEXTURE_2D,_depth_tex_obj);
    glTexImage2D(GL_TEXTURE_2D,0,GL_DEPTH_COMPONENT32,1024,1024,0,GL_DEPTH_COMPONENT32,GL_FLOAT,NULL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_COMPARE_FUNC,GL_LEQUAL);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D,0);

    // config framebuffer
    GLuint temp,temp1;
    glGenFramebuffers(1,&temp);
    glGenFramebuffers(1,&temp1);
    glGenFramebuffers(1,&_depth_fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, _depth_fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER,GL_DEPTH_STENCIL_ATTACHMENT,GL_TEXTURE_2D,_depth_tex_obj, 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void GCubeForShadow::Draw()
{
    if(_is_inited)
    {
        GDrawState state = GDrawState::kDrawForShadow;
        glBindFramebuffer(GL_FRAMEBUFFER, _depth_fbo);
        DrawHelper(state);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        state = GDrawState::kDraw;
        DrawHelper(state);
    }
}

void GCubeForShadow::DrawHelper(GDrawState state)
{
    glUseProgram(_program[state-1]);
    {
        SetUniformInDraw(state);
        if(state==GDrawState::kDraw)
            SetLightInDraw();

        glBindVertexArray(_vertex_arr_obj);
        glDrawArrays(GL_TRIANGLES,0,36);
        glBindVertexArray(0);
    }
    glUseProgram(0);
}


void GCubeForShadow::SetUniformInDraw(GDrawState state)
{
    if(state == GDrawState::kDraw)
    {
        GModel::SetUniformInDraw();
    }
    else
    {
        if (_lights.size()>0)
        {
            // light model matrix is obj view matrix
            auto local = GLHelper::GetUniformLocal(_program[state-1],GetUniformName(GUniformType::kViewMatrix).c_str());
            glm::mat4x4 mm;
            _lights[0]->GetModelMatrix(mm);
            glUniformMatrix4fv(local,1,GL_FALSE,glm::value_ptr(mm));
        }

        auto local = GLHelper::GetUniformLocal(_program[state-1],GetUniformName(GUniformType::kProjectionMatrix).c_str());
        glm::mat4x4 pm;
        GCamera* camera = nullptr;
        if(_camera_getter)
        {
            camera = _camera_getter();
        }
        if(camera)
        {
            camera->GetCurProjectionMatrix(pm);
        }
        else if(_projection_matrix_getter)
        {
            _projection_matrix_getter(pm);
        }
        glUniformMatrix4fv(local,1,GL_FALSE,glm::value_ptr(pm));
    }
}

void GCubeForShadow::SetLightInDraw()
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


