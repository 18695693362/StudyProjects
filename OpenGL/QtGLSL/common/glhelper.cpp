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
    }
    return shader_obj;
}

GLuint GLHelper::CreateShaderProgram(const char* vertex_shader_str, const char* fragment_shader_str)
{
    GLuint vertex_shader_obj = CompileShader(GL_VERTEX_SHADER,vertex_shader_str);
    GLuint fragment_shader_obj = CompileShader(GL_FRAGMENT_SHADER,fragment_shader_str);
    GLuint program = glCreateProgram();
    glAttachShader(program,vertex_shader_obj);
    glAttachShader(program,fragment_shader_obj);
    glLinkProgram(program);

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

        //TODO
    }
    return program;
}

GLuint GLHelper::CreateShaderProgramWithFiles(const QString& vert_path, const QString& frag_path)
{
    return CreateShaderProgram(GetShaderTxt(vert_path).toStdString().c_str(),GetShaderTxt(frag_path).toStdString().c_str());
}

QString GLHelper::GetShaderTxt(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return "";

    QTextStream in(&file);
    return in.readAll();
}

