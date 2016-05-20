#include "mglwidget_DrawCommands.h"
#include <iostream>
#include "../../../common/glhelper.h"
#include "glm/glm.hpp"
#include "glm/fwd.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

#define BUFF_OFFSET(offset) ((void*)(offset))

static const GLfloat vertex_positions[] = {
    -1.0f, -1.0f,  0.0f,  1.0f,
     1.0f, -1.0f,  0.0f,  1.0f,
    -1.0f,  1.0f,  0.0f,  1.0f,
    -1.0f, -1.0f,  0.0f,  1.0f,
};

static const GLfloat vertex_colors[] = {
    1.0f, 1.0f,  1.0f,  1.0f,
    1.0f, 1.0f,  0.0f,  1.0f,
    1.0f, 0.0f,  1.0f,  1.0f,
    0.0f, 1.0f,  1.0f,  1.0f,
};

static const GLushort vertex_indices[] = {1,2,3};

enum VAO_IDs {
    Triangles,
    NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer,
    ElemArrayBuffer,
    UniformBuffer,
    NumBuffers
};
enum Attrib_IDs {
    vPos = 1
};
enum Uniforms{
    Model,
    Projection,
    NumUniforms
};

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 3;
GLuint ubo_index;
GLint  ubo_data_source_size;
GLvoid* ubo_data_source;
GLuint ubo_indices[NumUniforms];
GLint  ubo_size[NumUniforms];
GLint  ubo_offset[NumUniforms];
GLint  ubo_type[NumUniforms];
GLint  program;

bool g_isUseUniformBlock = false;

MGLWidgetUniformBlock::MGLWidgetUniformBlock(QWidget *parent, const char* name, bool full_screen) :
    QGLWidget(parent)
{
    setGeometry( kDefaultX, kDefaultY, kDesignSizeW, kDesignSizeH );
    setMinimumSize(kMinWidth, kMinHeight);
    window_width_ = kDesignSizeW;
    window_height_= kDesignSizeH;

    setWindowTitle(name);

    is_full_screen_ = full_screen;
    if(is_full_screen_)
        showFullScreen();
}


void MGLWidgetUniformBlock::initializeGL()
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    cout << "gl version = " << glGetString(GL_VERSION) << endl;

    const char* vertex_shader_path = NULL;
    if(g_isUseUniformBlock)
    {
        vertex_shader_path = ":/vertex_DrawCMD_UniformBlock.vert";

    }
    else
    {
        vertex_shader_path = ":/vertex_DrawCMD.vert";
    }
    program = GLHelper::CreateShaderProgramWithFiles(vertex_shader_path,":/fragment_DrawCMD.frag");
    glUseProgram(program);

    glGenBuffers(NumBuffers,Buffers);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[ElemArrayBuffer]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(vertex_indices),vertex_indices,GL_STATIC_DRAW);

    glGenVertexArrays(NumVAOs,VAOs);
    glBindVertexArray(VAOs[Triangles]);

    glBindBuffer(GL_ARRAY_BUFFER,Buffers[ArrayBuffer]);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertex_positions)+sizeof(vertex_colors),NULL,GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(vertex_positions),vertex_positions);
    glBufferSubData(GL_ARRAY_BUFFER,sizeof(vertex_positions),sizeof(vertex_colors),vertex_colors);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, NULL);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, BUFF_OFFSET(sizeof(vertex_positions)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    const char* names[NumUniforms] = {"model_matirx","projection_matrix"};
    if(g_isUseUniformBlock)
    {
        ubo_index = glGetUniformBlockIndex(program,"Uniforms");
        glGetActiveUniformBlockiv(program, ubo_index, GL_UNIFORM_BLOCK_DATA_SIZE, &ubo_data_source_size);
        ubo_data_source = malloc(ubo_data_source_size);
        if(ubo_data_source == NULL)
        {
            perror("error malloc failed!");
        }
        else
        {
            glGetUniformIndices(program,NumUniforms,names,ubo_indices);
            glGetActiveUniformBlockiv(program,NumUniforms,GL_UNIFORM_OFFSET,ubo_offset);
            glGetActiveUniformBlockiv(program,NumUniforms,GL_UNIFORM_SIZE,ubo_size);
            glGetActiveUniformBlockiv(program,NumUniforms,GL_UNIFORM_TYPE,ubo_type);

            glBindBuffer(GL_UNIFORM_BUFFER, Buffers[UniformBuffer]);
            glBufferData(GL_UNIFORM_BUFFER,ubo_data_source_size,NULL,GL_DYNAMIC_DRAW);
        }
    }
    else
    {
        for(int i=0; i<NumUniforms; i++)
        {
            ubo_indices[i] = glGetUniformLocation(program,names[i]);
        }
    }
}

void MGLWidgetUniformBlock::paintGL()
{
    glEnable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);

    glm::mat4 model_matrix;
    //glm::mat4 projection_matrix = glm::perspective(45.0f, window_width_ / window_height_, 0.1f, 100.0f);
    glm::mat4 projection_matrix = glm::ortho(0.0f, window_width_, 0.0f, window_height_);
    glUniformMatrix4fv(ubo_indices[Projection],1,GL_FALSE,glm::value_ptr(projection_matrix));

    // Draw arrays
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f, 0.0f, -5.0f));
    if(g_isUseUniformBlock)
    {
        memcpy((GLchar*)ubo_data_source+ubo_offset[Model],&model_matrix,ubo_size[Model]*GLHelper::TypeSize(ubo_type[Model]));
        memcpy((GLchar*)ubo_data_source+ubo_offset[Projection],&projection_matrix,ubo_size[Projection]*GLHelper::TypeSize(ubo_type[Projection]));
        glBindBuffer(GL_UNIFORM_BUFFER, Buffers[UniformBuffer]);
        glBufferSubData(GL_UNIFORM_BUFFER,0,ubo_data_source_size,ubo_data_source);
    }
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],4,GL_FALSE,glm::value_ptr(model_matrix));
    }
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

    //set up glDrawElements
    glBindVertexArray(VAOs[Triangles]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Buffers[ElemArrayBuffer]);
    // Draw elem
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, -5.0f));
    if(g_isUseUniformBlock)
    {}
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],4,GL_FALSE,glm::value_ptr(model_matrix));
    }
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL);

    // DrawElementsBaseVertex
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, -5.0f));
    if(g_isUseUniformBlock)
    {}
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],4,GL_FALSE,glm::value_ptr(model_matrix));
    }
    glDrawElementsBaseVertex(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, NULL, 1);

    // DrawArraysInstanced
    model_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(3.0f, 0.0f, -5.0f));
    if(g_isUseUniformBlock)
    {}
    else
    {
        glUniformMatrix4fv(ubo_indices[Model],4,GL_FALSE,glm::value_ptr(model_matrix));
    }
    glDrawArraysInstanced(GL_TRIANGLES, 0, 3, 1);

    glFlush();
}

void MGLWidgetUniformBlock::resizeGL(int w, int h)
{
    if(w < kMinWidth || h < kMinHeight)
    {
        w = kMinWidth;
        h = kMinHeight;
    }
    window_width_ = w;
    window_height_= h;

    glViewport(0,0,window_width_,window_height_);
}



















