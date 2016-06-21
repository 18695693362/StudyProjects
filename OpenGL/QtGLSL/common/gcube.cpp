#include "gcube.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GCube::GCube()
{
    _kPosAttribLocal = 0;
    _kColorAttribLocal = 1;
    _is_inited = false;
    _scale = 1.0f;
    _color = glm::vec4(1.0,0.0,0.0,1.0);
}

void GCube::Init()
{
    _is_inited = true;

    const char vs[] =
            "#version 410\n"
            "layout (location = 0) in vec3 vi_position;\n"
            "layout (location = 1) in vec3 vi_color;\n"
            "uniform float  scale;\n"
            "uniform vec4   color;\n"
            "uniform mat4x4 view_matrix;\n"
            "uniform mat4x4 projection_matrix;\n"
            "out vec4 vo_color;\n"
            "void main(void)\n"
            "{\n"
            "    mat4 scale_mat = mat4(scale);"
            "    scale_mat[3].w = 1.0f;"
            "    //gl_Position = scale_mat*vec4(vi_position,1.0);\n"
            "    //gl_Position = view_matrix*scale_mat*vec4(vi_position,1.0);\n"
            "    //gl_Position = projection_matrix*scale_mat*vec4(vi_position,1.0);\n"
            "    gl_Position = projection_matrix*view_matrix*scale_mat*vec4(vi_position,1.0);\n"
            "    //vo_color = color;\n"
            "    vo_color = vec4(vi_color,1.0);\n"
            "}\n";
    const char fs[] =
            "#version 410\n"
            "in vec4 vo_color;\n"
            "out vec4 fo_color;\n"
            "void main(void)\n"
            "{\n"
            "    fo_color = vo_color;\n"
            "}\n";
    _program = GLHelper::CreateShaderProgram(vs,fs);
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

        _scaleUniformLocal = GLHelper::GetUniformLocal(_program,"scale");
        _colorUniformLocal = GLHelper::GetUniformLocal(_program,"color");
        _viewMatrixUniformLocal = GLHelper::GetUniformLocal(_program,"view_matrix");
        _projectionMatrixUniformLocal = GLHelper::GetUniformLocal(_program,"projection_matrix");

        glVertexAttribPointer(_kPosAttribLocal,vertex_pos_comp_count,GL_FLOAT,GL_FALSE,
                              0,BUFF_OFFSET(0));
        glEnableVertexAttribArray(_kPosAttribLocal);
        glVertexAttribPointer(_kColorAttribLocal,vertex_color_comp_count,GL_FLOAT,GL_FALSE,
                              0,BUFF_OFFSET(vertex_data_size));
        glEnableVertexAttribArray(_kColorAttribLocal);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
    glUseProgram(0);
}

void GCube::GetVertexData(GLfloat*& vertex_data,GLuint*& vertex_index_data,GLfloat*& vertex_color_data,
                          int& vertex_data_size,int& index_data_size,int& color_data_size,
                          int& vertex_pos_comp_count,int& vertex_color_comp_count)
{
    static GLfloat v_data[] = {
        -0.5, -0.5,  0.0, //0 front-left-down
        -0.5,  0.5,  0.0, //1 front-left-up
         0.5,  0.5,  0.0, //2 front-right-up
         0.5, -0.5,  0.0, //3 front-right-down
        -0.5, -0.5, -1.0, //4 back-left-down
        -0.5,  0.5, -1.0, //5 back-left-up
         0.5,  0.5, -1.0, //6 back-right-up
         0.5, -0.5, -1.0, //7 back-right-down
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
//        0,1,2,  2,3,0, // front
//        0,4,7,  7,3,0, // down
//        0,4,1,  1,4,5, // left
//        5,4,7,  7,6,5, // back
//        5,6,2,  2,1,5, // up
//        2,6,7,  7,3,2  // right
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

void GCube::Draw()
{
    if(_is_inited)
    {
        glUseProgram(_program);
        {
            glUniform1f(_scaleUniformLocal,_scale);
            glUniform4fv(_colorUniformLocal,1,glm::value_ptr(_color));
            if(_view_matrix_getter && _viewMatrixUniformLocal!=-1)
            {
                glm::mat4x4 view_matrix;
                _view_matrix_getter(view_matrix);
                glUniformMatrix4fv(_viewMatrixUniformLocal,1,GL_FALSE,glm::value_ptr(view_matrix));
            }
            if(_projection_matrix_getter && _projectionMatrixUniformLocal!=-1)
            {
                glm::mat4x4 projection_matrix;
                _projection_matrix_getter(projection_matrix);
                glUniformMatrix4fv(_projectionMatrixUniformLocal,1,GL_FALSE,glm::value_ptr(projection_matrix));
            }

            glBindVertexArray(_vertex_arr_obj);
            //glDrawElements(GL_TRIANGLES,16,GL_UNSIGNED_INT,BUFF_OFFSET(0));
            glDrawElements(GL_TRIANGLE_STRIP,8,GL_UNSIGNED_INT,BUFF_OFFSET(0));
            glDrawElements(GL_TRIANGLE_STRIP,8,GL_UNSIGNED_INT,BUFF_OFFSET(9*sizeof(GLuint)));
            glBindVertexArray(0);
        }
        glUseProgram(0);
    }
}
