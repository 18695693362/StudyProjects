#include "glhelper.h"
#include <QFile>
#include <iostream>
using namespace std;

GLHelper::GLHelper()
{

}

GLHelper::~GLHelper()
{

}

GLuint GLHelper::CompileShader(GLuint shader_type, const char* shader_str)
{
    GLuint shader_obj = glCreateShader(shader_type);
    glShaderSource(shader_obj,1,&shader_str,NULL);
    glCompileShader(shader_obj);

    GLint status;
    glGetShaderiv(shader_obj,GL_COMPILE_STATUS,&status);
    if(status != GL_TRUE)
    {
        GLint log_size;
        glGetShaderiv(shader_obj,GL_INFO_LOG_LENGTH,&log_size);
        char* log = new char[log_size];
        memset(log,0,log_size);
        glGetShaderInfoLog(shader_obj,log_size,&log_size,log);
        cout << log << endl;

        //TODO
        return 0;
    }
    return shader_obj;
}

GLuint GLHelper::CreateShaderProgram(const char* vertex_shader_str, const char* fragment_shader_str)
{
    GLuint vertex_shader_obj = CompileShader(GL_VERTEX_SHADER,vertex_shader_str);
    if(!vertex_shader_obj)
    {
        return ~(GLuint)0 - 1;
    }
    GLuint fragment_shader_obj = CompileShader(GL_FRAGMENT_SHADER,fragment_shader_str);
    if(!fragment_shader_obj)
    {
        return ~(GLuint)0 - 2;
    }
    GLuint program = glCreateProgram();
    glAttachShader(program,vertex_shader_obj);
    glAttachShader(program,fragment_shader_obj);
    glLinkProgram(program);

    if(vertex_shader_obj)
    {
        glDeleteShader(vertex_shader_obj);
    }
    if(fragment_shader_obj)
    {
        glDeleteShader(fragment_shader_obj);
    }

    GLint status;
    glGetProgramiv(program,GL_LINK_STATUS,&status);
    if(status != GL_TRUE)
    {
        GLint log_size;
        glGetProgramiv(program,GL_INFO_LOG_LENGTH,&log_size);
        char* log = new char[log_size];
        memset(log,0,log_size);
        glGetProgramInfoLog(program,log_size,&log_size,log);
        cout << log << endl;

        return 0;
    }
    return program;
}

GLuint GLHelper::CreateShaderProgramWithFiles(const QString& vert_path, const QString& frag_path)
{
    GLuint program = CreateShaderProgram(GetShaderTxt(vert_path).toStdString().c_str(),GetShaderTxt(frag_path).toStdString().c_str());
    if(program == (~(GLuint)0 - 1))
    {
        cout << "vert error = " << vert_path.toStdString() << endl;
    }
    else if(program == (~(GLuint)0 - 2))
    {
        cout << "frag error = " << frag_path.toStdString() << endl;
    }
    else if(program == 0)
    {
        cout << "program link error!" << endl;
    }
    cout << "program = " << program << endl;
    return program;
}

QString GLHelper::GetShaderTxt(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

size_t GLHelper::TypeSize(GLenum type)
{
    size_t size;
#define CASE(Enum, Count, Type) \
    case Enum: size = Count*sizeof(Type); break

    switch (type) {
        CASE(GL_FLOAT, 1, GLfloat);
        CASE(GL_FLOAT_VEC2, 2, GLfloat);
        CASE(GL_FLOAT_VEC3, 3, GLfloat);
        CASE(GL_FLOAT_VEC4, 4, GLfloat);
        CASE(GL_INT, 1, GLint);
        CASE(GL_INT_VEC2, 2, GLint);
        CASE(GL_INT_VEC3, 3, GLint);
        CASE(GL_INT_VEC4, 4, GLint);
        CASE(GL_UNSIGNED_INT, 1, GLuint);
        CASE(GL_UNSIGNED_INT_VEC2, 2, GLuint);
        CASE(GL_UNSIGNED_INT_VEC3, 3, GLuint);
        CASE(GL_UNSIGNED_INT_VEC4, 4, GLuint);
        CASE(GL_BOOL, 1, GLboolean);
        CASE(GL_BOOL_VEC2, 2, GLboolean);
        CASE(GL_BOOL_VEC3, 3, GLboolean);
        CASE(GL_BOOL_VEC4, 4, GLboolean);
        CASE(GL_FLOAT_MAT2, 4, GLfloat);
        CASE(GL_FLOAT_MAT2x3, 6, GLfloat);
        CASE(GL_FLOAT_MAT2x4, 8, GLfloat);
        CASE(GL_FLOAT_MAT3, 9, GLfloat);
        CASE(GL_FLOAT_MAT3x2, 6, GLfloat);
        CASE(GL_FLOAT_MAT3x4, 12, GLfloat);
        CASE(GL_FLOAT_MAT4, 16, GLfloat);
        CASE(GL_FLOAT_MAT4x2, 8, GLfloat);
        CASE(GL_FLOAT_MAT4x3, 12, GLfloat);
#undef CASE
        default:
            fprintf(stderr, "Unknown type: 0x%x\n", type);
            exit(EXIT_FAILURE);
            break;
    }
    return size;
}





















