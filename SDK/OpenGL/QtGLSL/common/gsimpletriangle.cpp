#include "gsimpletriangle.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <QImage>
using namespace std;

GSimpleTriangle::GSimpleTriangle(bool is_vertex_ccw)
{
    _is_inited = false;
    _is_vertex_ccw = is_vertex_ccw;

    _kPosAttribLocal = 0;
    _kColorAttribLocal = 1;
    _scale = 1.0f;
    _color = glm::vec4(1.0,1.0,1.0,1.0);
}

void GSimpleTriangle::GetVertexData(GLfloat*& vertex_data,int& size, int& count, int& pos_comp_count, int& color_comp_count)
{
    // 顺时针
    static GLfloat cw_vertex_data[] = {
        //  ------ 位置 -------  ---- 颜色 ----
        -1.0, -1.0,  0.0,  1.0,  1.0, 0.0, 0.0, 1.0,
         0.0,  1.0,  0.0,  1.0,  0.0, 1.0, 0.0, 1.0,
         1.0, -1.0,  0.0,  1.0,  0.0, 0.0, 1.0, 1.0,
    };
    // 逆时针
    static GLfloat ccw_vertex_data[] = {
        //  ------ 位置 -------  ---- 颜色 ----
        -1.0, -1.0,  0.0,  1.0,  1.0, 0.0, 0.0, 1.0,
         1.0, -1.0,  0.0,  1.0,  0.0, 0.0, 1.0, 1.0,
         0.0,  1.0,  0.0,  1.0,  0.0, 1.0, 0.0, 1.0,
    };
    vertex_data = _is_vertex_ccw ? ccw_vertex_data : cw_vertex_data;
    size = sizeof(cw_vertex_data);
    count = 3;
    pos_comp_count = 4;
    color_comp_count = 4;
}

void GSimpleTriangle::Init(GLfloat *pos_data, int size, int count)
{
    _is_inited = true;

    int pos_component_count = 4;
    int color_comp_count = 4;
    if(!pos_data)
    {
        GetVertexData(pos_data, _size, _count, pos_component_count, color_comp_count);
    }
    else
    {
        _count = count;
        _size  = size;
        pos_component_count = _size / _count / sizeof(GLfloat);
        color_comp_count = 0;
    }
    int total_comp_count = pos_component_count + color_comp_count;

    const char vs[] =
            "#version 410\n"
            "layout (location = 0) in vec4 vi_position;\n"
            "layout (location = 1) in vec4 vi_color;\n"
            "uniform float scale;\n"
            "uniform vec3  translate;\n"
            "uniform vec4  color;\n"
            "out vec4 vo_f_color;\n"
            "void main(void)\n"
            "{\n"
            "    mat4 scale_mat = mat4(scale);\n"
            "    scale_mat[3].w = 1.0f;\n"
            "    gl_Position = scale_mat*vi_position+vec4(translate,0.0);\n"
            "    vo_f_color = color*vi_color;\n"
            "}\n";
    const char fs[] =
            "#version 410\n"
            "in vec4 vo_f_color;\n"
            "out vec4 fo_color;\n"
            "void main(void)\n"
            "{\n"
            "    fo_color = vo_f_color;\n"
            "}\n";
    _program = GLHelper::CreateShaderProgram(vs,fs);
    glUseProgram(_program);
    {
        glGenVertexArrays(1,&_vaobject);
        glBindVertexArray(_vaobject);

        glGenBuffers(1,&_vbobject);
        glBindBuffer(GL_ARRAY_BUFFER,_vbobject);
        glBufferData(GL_ARRAY_BUFFER, _size, pos_data, GL_STATIC_DRAW);
        glVertexAttribPointer(_kPosAttribLocal,pos_component_count,GL_FLOAT,GL_FALSE,total_comp_count*sizeof(GLfloat),BUFF_OFFSET(0));
        glEnableVertexAttribArray(_kPosAttribLocal);
        if(color_comp_count)
        {
            int offset = pos_component_count*sizeof(GLfloat);
            glVertexAttribPointer(_kColorAttribLocal,color_comp_count,GL_FLOAT,GL_FALSE,total_comp_count*sizeof(GLfloat),BUFF_OFFSET(offset));
            glEnableVertexAttribArray(_kColorAttribLocal);
        }



        _scaleUniformLocal = GLHelper::GetUniformLocal(_program,"scale");
        _colorUniformLocal = GLHelper::GetUniformLocal(_program,"color");
        _translateUniformLocal = GLHelper::GetUniformLocal(_program,"translate");

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    }
    glUseProgram(0);
}

void GSimpleTriangle::SetScale(float scale)
{
    _scale = scale;
}

void GSimpleTriangle::SetColor(glm::vec4 color)
{
    _color = color;
}

void GSimpleTriangle::Draw()
{
    if(_is_inited)
    {
        glUseProgram(_program);
        {
            glUniform1f(_scaleUniformLocal,_scale);
            glUniform4fv(_colorUniformLocal,1,glm::value_ptr(_color));
            glUniform3fv(_translateUniformLocal,1,glm::value_ptr(_translate));

            glBindVertexArray(_vaobject);
            glDrawArrays(GL_TRIANGLES,0,_count);
            glBindVertexArray(0);
        }
        glUseProgram(0);
    }
}
