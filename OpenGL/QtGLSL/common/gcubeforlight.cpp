#include "gcubeforlight.h"
#include "glhelper.h"

GCubeForLight::GCubeForLight()
{

}

void GCubeForLight::Init(const char *v_shader, const char *f_shader, GUniformInfo *uniform_infos, int count)
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

            if(uniform_infos)
            {
                for(auto iter=0; iter<count; iter++)
                {
                    uniform_infos[iter].local = GLHelper::GetUniformLocal(_program,uniform_infos[iter].name.c_str());
                    _uniform_infos.push_back(uniform_infos[iter]);
                }
            }

            glVertexAttribPointer(GAttribType::kPos,sizeof(GLfloat)*pos_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(0));
            glVertexAttribPointer(GAttribType::kColor,sizeof(GLfloat)*color_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(sizeof(GLfloat)*pos_comp_count));
            glVertexAttribPointer(GAttribType::kNormal,sizeof(GLfloat)*normal_comp_count,GL_FLOAT,GL_FALSE,stride,BUFF_OFFSET(sizeof(GLfloat)*(pos_comp_count+color_comp_count)));
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
    GLfloat vertices[] =
    {
        //----pos----------/ /----color-------/   /----normal------/
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f, -1.0f,//1
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f,  1.0f,//2
         0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0, -1.0f,  0.0f,  0.0f,//3
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0, -1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f,//4
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f, -1.0f,  0.0f,//5
         0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f, -1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  1.0f,  0.0f,//6
         0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, 1.0, 1.0, 1.0, 1.0,  0.0f,  1.0f,  0.0f
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
            glBindVertexArray(_vertex_arr_obj);
            glDrawArrays(GL_TRIANGLES,0,36);
            glBindVertexArray(0);
        }
        glUseProgram(0);
    }
}
