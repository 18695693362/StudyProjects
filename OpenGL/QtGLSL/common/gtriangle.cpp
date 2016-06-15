#include "gtriangle.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <QImage>
using namespace std;

GTriangle::GTriangle()
{
    _is_inited = false;

    _kPosAttribLocal = 0;
    _kTexCoorAttribLocal = 1;
    _scale = 1.0f;
    _color = glm::vec4(1.0,0.0,0.0,1.0);
}

void GTriangle::GetPosData(GLfloat*& pos_data,int& size, int& count)
{
    static GLfloat default_pos_data[] = {
        //  ------ 位置 -------
        -1.0, -1.0,  0.0,  1.0,
         0.0,  1.0,  0.0,  1.0,
         1.0, -1.0,  0.0,  1.0,
    };
    pos_data = default_pos_data;
    size = sizeof(default_pos_data);
    count = 3;
}

void GTriangle::GetVertexData(GLfloat*& vertex_data,int& size, int& count, int& pos_comp_count, int& tex_coor_comp_count)
{
    static GLfloat default_vertex_data[] = {
        //  ------ 位置 -------  ---- 纹理坐标 ----
        -1.0, -1.0,  0.0,  1.0,  0.0, 0.0, //左下
         0.0,  1.0,  0.0,  1.0,  0.5, 1.0, //中上
         1.0, -1.0,  0.0,  1.0,  1.0, 0.0  //右下
    };
    vertex_data = default_vertex_data;
    size = sizeof(default_vertex_data);
    count = 3;
    pos_comp_count = 4;
    tex_coor_comp_count = 2;
}

void GTriangle::Init(GLfloat *pos_data, int size, int count)
{
    _is_inited = true;

    int pos_component_count = 4;
    int tex_coor_comp_count = 2;
    if(!pos_data)
    {
        GetVertexData(pos_data, _size, _count, pos_component_count, tex_coor_comp_count);
    }
    else
    {
        _count = count;
        _size  = size;
        pos_component_count = _size / _count / sizeof(GLfloat);
        tex_coor_comp_count = 0;
    }
    int total_comp_count = pos_component_count + tex_coor_comp_count;

    const char vs[] =
            "#version 410\n"
            "layout (location = 0) in vec4 vi_position;\n"
            "layout (location = 1) in vec2 vi_tex_pos;\n"
            "uniform float scale;\n"
            "uniform vec4  color;\n"
            "out vec4 vo_f_color;\n"
            "out vec2 vo_tex_pos;\n"
            "void main(void)\n"
            "{\n"
            "    mat4 scale_mat = mat4(scale);"
            "    scale_mat[3].w = 1.0f;"
            "    gl_Position = scale_mat*vi_position;\n"
            "    vo_f_color = color;\n"
            "    vo_tex_pos = vi_tex_pos;\n"
            "}\n";
    const char fs[] =
            "#version 410\n"
            "in vec4 vo_f_color;\n"
            "in vec2 vo_tex_pos;\n"
            "uniform sampler2D tex;\n"
            "out vec4 fo_color;\n"
            "void main(void)\n"
            "{\n"
            "    //fo_color = texture(tex,vo_tex_pos)*vo_f_color;\n"
            "    fo_color = texture(tex,vo_tex_pos);\n"
            "}\n";
    _program = GLHelper::CreateShaderProgram(vs,fs);
    glUseProgram(_program);
    {
        glGenVertexArrays(1,&_vaobject);
        glBindVertexArray(_vaobject);

        glGenBuffers(1,&_vabuffer);
        glBindBuffer(GL_ARRAY_BUFFER,_vabuffer);
        glBufferData(GL_ARRAY_BUFFER, _size, pos_data, GL_STATIC_DRAW);
        glVertexAttribPointer(_kPosAttribLocal,pos_component_count,GL_FLOAT,GL_FALSE,total_comp_count*sizeof(GLfloat),BUFF_OFFSET(0));
        glEnableVertexAttribArray(_kPosAttribLocal);
        if(tex_coor_comp_count)
        {
            int offset = pos_component_count*sizeof(GLfloat);
            glVertexAttribPointer(_kTexCoorAttribLocal,tex_coor_comp_count,GL_FLOAT,GL_FALSE,total_comp_count*sizeof(GLfloat),BUFF_OFFSET(offset));
            glEnableVertexAttribArray(_kTexCoorAttribLocal);
        }

        _scaleUniformLocal = GLHelper::GetUniformLocal(_program,"scale");
        _colorUniformLocal = GLHelper::GetUniformLocal(_program,"color");

        glGenTextures(1,&_texture);
        glBindTexture(GL_TEXTURE_2D, _texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        QImage image(GLHelper::GetAbsPathRelativeGResPath("wall.jpg").c_str());
        //QImage image = temp.mirrored();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
                     0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());
        glGenerateMipmap(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindVertexArray(0);
    }
    glUseProgram(0);
}

void GTriangle::SetScale(float scale)
{
    _scale = scale;
}

void GTriangle::SetColor(glm::vec4 color)
{
    _color = color;
}

void GTriangle::Draw()
{
    if(_is_inited)
    {
        glUseProgram(_program);
        {
            glUniform1f(_scaleUniformLocal,_scale);
            glUniform4fv(_colorUniformLocal,1,glm::value_ptr(_color));

            glBindTexture(GL_TEXTURE_2D, _texture);

            glBindVertexArray(_vaobject);
            glDrawArrays(GL_TRIANGLES,0,_count);
            glBindVertexArray(0);
        }
        glUseProgram(0);
    }
}
