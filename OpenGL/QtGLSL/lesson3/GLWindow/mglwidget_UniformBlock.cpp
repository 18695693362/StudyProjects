#include "mglwidget_UniformBlock.h"
#include <iostream>
#include "../../common/glhelper.h"

using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

#define BUFF_OFFSET(offset) ((void*)(offset))

enum VAO_IDs {
    Triangles,
    NumVAOs
};
enum Buffer_IDs {
    ArrayBuffer,
    NumBuffers
};
enum Attrib_IDs {
    vPos = 1
};
GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
const GLuint NumVertices = 6;

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

    GLint program = GLHelper::CreateShaderProgramWithFiles(":/vertex_UniformBlock.vert",":/fragment_UniformBlock.frag");
    glUseProgram(program);

    GLuint uboIndex;
    GLint  uboSize;
    GLuint ubo;
    GLvoid *buffer;

    uboIndex = glGetUniformBlockIndex(program, "Uniforms");
    glGetActiveUniformBlockiv(program, uboIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &uboSize);

    buffer = malloc(uboSize);

    if(buffer == NULL)
    {
        fprintf(stderr, "Unable to allocate buffer\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        enum {Translation, Scale, Rotation, Enabled, NumUniforms};
        GLfloat scale = 0.5;
        GLfloat translation[] = {0.1, 0.1, 0.0};
        GLfloat rotation[] = {90, 0.0, 0.0, 1.0};
        GLboolean enabled = GL_TRUE;

        const char* names[NumUniforms] = {
            "translation",
            "scale",
            "rotation",
            "enabled"
        };

        GLuint indices[NumUniforms];
        GLint  size[NumUniforms];
        GLint  offset[NumUniforms];
        GLint  type[NumUniforms];

        glGetUniformIndices(program,NumUniforms, names, indices);
        glGetActiveUniformsiv(program,NumUniforms,indices,GL_UNIFORM_OFFSET, offset);
        glGetActiveUniformsiv(program,NumUniforms,indices,GL_UNIFORM_SIZE, size);
        glGetActiveUniformsiv(program,NumUniforms,indices,GL_UNIFORM_TYPE, type);

        memcpy( (GLchar*)buffer + offset[Translation], &translation, size[Scale] * GLHelper::TypeSize(type[Translation]) );
        memcpy( (GLchar*)buffer + offset[Scale],       &scale,       size[Scale] * GLHelper::TypeSize(type[Scale]) );
        memcpy( (GLchar*)buffer + offset[Rotation],    &rotation,    size[Rotation] * GLHelper::TypeSize(type[Rotation]) );
        memcpy( (GLchar*)buffer + offset[Enabled],     &enabled,     size[Enabled] * GLHelper::TypeSize(type[Enabled]) );

        glGenBuffers(1, &ubo);
        glBindBuffer(GL_UNIFORM_BUFFER, ubo);
        glBufferData(GL_UNIFORM_BUFFER, uboSize, buffer, GL_STATIC_DRAW);
        glBindBufferBase(GL_UNIFORM_BUFFER, uboIndex, ubo);

        glGenVertexArrays(NumVAOs, VAOs);
        glBindVertexArray(VAOs[Triangles]);
        GLfloat vertices[NumVertices][2] = {
            {-0.90, -0.90},
            { 0.85, -0.90},
            {-0.90,  0.85},
            { 0.90, -0.85},
            { 0.90,  0.90},
            {-0.85,  0.90},
        };

        glGenBuffers(NumBuffers,Buffers);
        glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(vPos,2,GL_FLOAT,GL_FALSE,0,BUFF_OFFSET(0));
        glEnableVertexAttribArray(vPos);
    }
}

void MGLWidgetUniformBlock::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAOs[Triangles]);
    glDrawArrays(GL_TRIANGLES, 0, NumVertices);

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



















