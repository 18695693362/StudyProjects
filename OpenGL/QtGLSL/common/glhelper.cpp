#include "glhelper.h"
#include <QFile>
#include <iostream>
#include <string>
#include <QElapsedTimer>
using namespace std;

GLHelper::GLHelper()
{

}

GLHelper::~GLHelper()
{

}

QElapsedTimer GLHelper::_start_timer;
void GLHelper::Init()
{
    _start_timer.start();
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
    if(!glIsProgram(program))
    {
        cout << "ERROR: invalid program = " << program << endl;
    }
    return program;
}

QString GLHelper::GetShaderTxt(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Log(string("Error open file failed! file = ")+filePath.toStdString());
        return "";
    }

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

GLint GLHelper::GetUniformLocal(GLuint program, const char* uniform_name)
{
    GLint local = -1;
    if(!glIsProgram(program))
    {
        Log(string("Error invalid program = ")+to_string(program));
    }
    else
    {
        if(uniform_name)
        {
            local = glGetUniformLocation(program,uniform_name);
            if(IsGLError())
            {
               Log(string("Error glGetUniformLocation local = ")+to_string(local));
            }
        }
        else
        {
            Log("Error invalid uniform_name = null");
        }
    }
    return local;
}

void GLHelper::Log(const std::string log_str,LogType type)
{
    cout << log_str << endl;
}

bool  GLHelper::IsGLError()
{
    GLenum error = glGetError();
    if(error!=GL_NO_ERROR)
    {
        if(GL_INVALID_OPERATION == error)
        {
            Log("error GL_INVALID_OPERATION = "+to_string(error));
        }
        else if(GL_INVALID_VALUE == error)
        {
            Log("error GL_INVALID_VALUE = "+to_string(error));
        }
        else
        {
            Log(string("error = ")+to_string(error));
        }
        return true;
    }
    return false;
}

glm::mat4 GLHelper::GetScale(float x)
{
    return glm::scale(glm::mat4(1),glm::vec3(x,x,x));
}
glm::mat4 GLHelper::GetScale(float x,float y, float z)
{
    return glm::scale(glm::mat4(1),glm::vec3(x,y,z));
}
glm::mat4 GLHelper::GetRotate(float angle,float x,float y, float z)
{
    return glm::rotate(glm::mat4(1),angle,glm::vec3(x,y,z));
}
glm::mat4 GLHelper::GetTranslate(float x, float y, float z)
{
    return glm::translate(glm::mat4(1),glm::vec3(x,y,z));
}
string GLHelper::GetGResAbsPath()
{
    QDir temp_dir;
    const char* res_relative_path = "./../../../res";
    if(temp_dir.exists(res_relative_path))
    {
        return temp_dir.absoluteFilePath(res_relative_path).toStdString();
    }
    else
    {
        Log("Error get GResPath failed!");
        return "";
    }
}
std::string GLHelper::GetAbsPathRelativeGResPath(const std::string& relative_path)
{
    QString res_abs_path = GetGResAbsPath().c_str();
    if(!res_abs_path.isEmpty())
    {
        QDir temp_dir(res_abs_path);
        if(!temp_dir.exists(relative_path.c_str()))
        {
            Log(string("Error relative_path not exist. path = ")+relative_path);
            Log(string("full path = ")+temp_dir.absoluteFilePath(relative_path.c_str()).toStdString());
        }
        else
        {
            return temp_dir.absoluteFilePath(relative_path.c_str()).toStdString();
        }
    }
    else
    {
        Log("Error GetAbsPathRelativeGResPath failed!");
    }
    return "";
}

long GLHelper::GetTickCount()
{
    return _start_timer.elapsed();
}

GTriangle::GTriangle()
{
    _kPosAttribLocal = 0;
    _scale = 1.0f;
}

void GTriangle::Init(GLfloat *pos_data, int size, int count)
{
    int pos_component_count = 4;
    if(!pos_data)
    {
        static GLfloat default_pos_data[] = {
            -1.0, -1.0,  0.0,  1.0,
             0.0,  1.0,  0.0,  1.0,
             1.0, -1.0,  0.0,  1.0
        };
        pos_data = default_pos_data;
        _count = 3;
        pos_component_count = 4;
    }
    else
    {
        _count = count;
        pos_component_count = size / count;
    }

    const char vs[] =
            "#version 410\n"
            "layout (location = 0) in vec4 position;\n"
            "uniform float scale;\n"
            "void main(void)\n"
            "{\n"
            "    mat4 scale_mat = mat4("
            "       scale,0,0,0,"
            "       0,scale,0,0,"
            "       0,0,scale,0,"
            "       0,0,0,1);"
            "    gl_Position = scale_mat*position;\n"
            "}\n";
    const char fs[] =
            "#version 410\n"
            "layout (location = 0) out vec4 color;\n"
            "void main(void)\n"
            "{\n"
            "    color = vec4(1.0,0.0,0.0,1.0);\n"
            "}\n";
    _programe = GLHelper::CreateShaderProgram(vs,fs);
    glUseProgram(_programe);
    {
        glGenVertexArrays(1,&_vaobject);
        glBindVertexArray(_vaobject);
        glGenBuffers(1,&_vabuffer);
        glBindBuffer(GL_ARRAY_BUFFER,_vabuffer);
        glBufferData(GL_ARRAY_BUFFER, size, pos_data, GL_STATIC_DRAW);
        glVertexAttribPointer(_kPosAttribLocal,pos_component_count,GL_FLOAT,GL_FALSE,0,pos_data);
        glEnableVertexAttribArray(_kPosAttribLocal);

        _scaleUniformLocal = GLHelper::GetUniformLocal(_programe,"scale");
    }
    glUseProgram(0);
}

void GTriangle::SetScale(float scale)
{
    _scale = scale;
}

void GTriangle::Draw()
{
    glUseProgram(_programe);
    {
        glUniform1f(_scaleUniformLocal,_scale);

        glBindVertexArray(_vaobject);
        glDrawArrays(GL_TRIANGLES,0,_count);
    }
    glUseProgram(0);
}







