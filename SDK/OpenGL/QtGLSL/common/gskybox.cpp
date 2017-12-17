#include "gskybox.h"
#include "glhelper.h"
#include <glm/gtc/type_ptr.hpp>

GSkybox::GSkybox()
{
    _kPosAttribLocal = 0;
    _kColorAttribLocal = 1;
    _is_inited = false;
    _scale = 1.0f;
    _translate = glm::vec3(0.0,0.0,0.0);
    _color = glm::vec4(1.0,0.0,0.0,1.0);
}

void GSkybox::Init(const char *pos_x, const char *neg_x, const char *pos_y, const char *neg_y, const char *pos_z, const char *neg_z, QImage::Format img_format)
{
    _is_inited = true;
    //QImage::Format::Format_RGB888
    _cube_tex_obj.Load(pos_x,neg_x,pos_y,neg_y,pos_z,neg_z,img_format);

    const char vs[] =
            "#version 410\n"
            "layout (location = 0) in vec3 vi_position;\n"
            "layout (location = 1) in vec3 vi_color;\n"
            "uniform vec3   move;\n"
            "uniform float  scale;\n"
            "uniform vec4   color;\n"
            "uniform mat4x4 view_matrix;\n"
            "uniform mat4x4 projection_matrix;\n"
            "out vec3 vo_tex_pos;\n"
            "out vec4 vo_color;\n"
            "void main(void)\n"
            "{\n"
            "    mat4 scale_mat = mat4(scale);"
            "    scale_mat[3].w = 1.0f;"
            "    //gl_Position = scale_mat*vec4(vi_position+move,1.0);\n"
            "    //gl_Position = view_matrix*scale_mat*vec4(vi_position+move,1.0);\n"
            "    //gl_Position = projection_matrix*scale_mat*vec4(vi_position+move,1.0);\n"
            "    gl_Position = projection_matrix*view_matrix*scale_mat*vec4(vi_position+move,1.0);\n"
            "    gl_Position = gl_Position.xyww;\n"
            "    //vo_color = color;\n"
            "    vo_color = vec4(vi_color,1.0);\n"
            "    vo_tex_pos = vi_position;\n"
            "}\n";
    const char fs[] =
            "#version 410\n"
            "in vec3 vo_tex_pos;\n"
            "in vec4 vo_color;\n"
            "out vec4 fo_color;\n"
            "uniform samplerCube cube_tex;\n"
            "void main(void)\n"
            "{\n"
            "    //fo_color = vo_color;\n"
            "    fo_color = texture(cube_tex,vo_tex_pos);\n"
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
        _moveUniformLocal  = GLHelper::GetUniformLocal(_program,"move");
        _cubeSamplerVarUniformLocal = GLHelper::GetUniformLocal(_program,"cube_tex");

        _viewMatrixUniformLocal = GLHelper::GetUniformLocal(_program,"view_matrix");
        _projectionMatrixUniformLocal = GLHelper::GetUniformLocal(_program,"projection_matrix");

        glVertexAttribPointer(_kPosAttribLocal,vertex_pos_comp_count,GL_FLOAT,GL_FALSE,
                              0,BUFF_OFFSET(0));
        glEnableVertexAttribArray(_kPosAttribLocal);
        glVertexAttribPointer(_kColorAttribLocal,vertex_color_comp_count,GL_FLOAT,GL_FALSE,
                              0,BUFF_OFFSET(vertex_data_size));
        glEnableVertexAttribArray(_kColorAttribLocal);

        glUniform1i(_cubeSamplerVarUniformLocal,0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER,0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
    }
    glUseProgram(0);
}

void GSkybox::GetVertexData(GLfloat*& vertex_data,GLuint*& vertex_index_data,GLfloat*& vertex_color_data,
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
    static GLuint v_index_data[] =
    {
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

void GSkybox::Draw()
{
    if(_is_inited)
    {
        if(_camera_pos_getter)
        {
            SetTranslate(_camera_pos_getter());
        }

        GLint OldCullFaceMode;
        glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
        GLint OldDepthFuncMode;
        glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

        glCullFace(GL_FRONT);
        glDepthFunc(GL_LEQUAL);

        glUseProgram(_program);
        {
            _cube_tex_obj.Bind(GL_TEXTURE0);

            glUniform1f(_scaleUniformLocal,_scale);
            glUniform4fv(_colorUniformLocal,1,glm::value_ptr(_color));
            glUniform3fv(_moveUniformLocal,1,glm::value_ptr(_translate));
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

        glCullFace(OldCullFaceMode);
        glDepthFunc(OldDepthFuncMode);
    }
}

