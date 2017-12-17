#include "glhelper.h"
#include <QFile>
#include <iostream>
#include <string>
#include <QElapsedTimer>
#include "../libs/glm/glm/gtx/norm.hpp"
using namespace std;

bool GLHelper::_is_delete_shader = true;
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

void GLHelper::SetDeleteShader(bool is_delete_shader)
{
    _is_delete_shader = is_delete_shader;
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

GLuint GLHelper::CreateShaderProgram(const char* vertex_shader_str, const char* fragment_shader_str, const char *geom_shader_str)
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
    GLuint geom_shader_obj = 0;
    if (geom_shader_str!=nullptr)
    {
        geom_shader_obj = CompileShader(GL_GEOMETRY_SHADER, geom_shader_str);
    }
    GLuint program = glCreateProgram();
    glAttachShader(program,vertex_shader_obj);
    glAttachShader(program,fragment_shader_obj);
    if(geom_shader_obj!=0)
    {
        glAttachShader(program,geom_shader_obj);
    }
    glLinkProgram(program);

    if(_is_delete_shader)
    {
        if(vertex_shader_obj)
        {
            glDeleteShader(vertex_shader_obj);
        }
        if(fragment_shader_obj)
        {
            glDeleteShader(fragment_shader_obj);
        }
        if(geom_shader_obj)
        {
            glDeleteShader(geom_shader_obj);
        }
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

GLuint GLHelper::CreateShaderProgramWithFiles(const QString& vert_path, const QString& frag_path,const QString& geom_path)
{
    const char* geom_shader_txt = nullptr;
    string geom_shader_str;
    if(!geom_path.isEmpty())
    {
        geom_shader_str = GetShaderTxt(geom_path).toStdString();
        geom_shader_txt = geom_shader_str.c_str();
    }
    GLuint program = CreateShaderProgram(GetShaderTxt(vert_path).toStdString().c_str(),GetShaderTxt(frag_path).toStdString().c_str(),geom_shader_txt);
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

bool  GLHelper::IsGLError(string error_msg)
{
    GLenum error = glGetError();
    if(error!=GL_NO_ERROR)
    {
        if(GL_INVALID_OPERATION == error)
        {
            Log("error GL_INVALID_OPERATION = "+to_string(error)+" "+error_msg);
        }
        else if(GL_INVALID_VALUE == error)
        {
            Log("error GL_INVALID_VALUE = "+to_string(error)+" "+error_msg);
        }
        else
        {
            Log(string("error = ")+to_string(error)+" "+error_msg);
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

glm::quat GLHelper::GetRotateBetweenVec(const glm::vec3 &start, const glm::vec3 &end)
{
    glm::vec3 t_start = glm::normalize(start);
    glm::vec3 t_end   = glm::normalize(end);

    float cos_theta = glm::dot(t_start, t_end);
    glm::vec3 rotation_axis;

    if (cos_theta < -1 + 0.001f)
    {
        // special case when vectors in opposite directions:
        // there is no "ideal" rotation axis
        // So guess one; any will do as long as it's perpendicular to start
        rotation_axis = glm::cross(glm::vec3(0.0f, 0.0f, 1.0f), t_start);
        if(glm::length2(rotation_axis) < 0.01)
        {
            rotation_axis = cross(glm::vec3(1.0f, 0.0f, 1.0f), t_start);
        }
        rotation_axis = glm::normalize(rotation_axis);
        return glm::angleAxis(180.0f, rotation_axis);
    }

    rotation_axis = glm::cross(t_start, t_end);

    float s = sqrt( (1+cos_theta)*2 );
    float invs = 1 / s;

    return glm::normalize(glm::quat(
                              s * 0.5f,
                              rotation_axis.x * invs,
                              rotation_axis.y * invs,
                              rotation_axis.z * invs
                              ));
}

glm::quat GLHelper::GetRotateBetweenVec(const glm::quat &start, const glm::quat &end, float max_angle)
{
    glm::quat t_start(start);
    glm::quat t_end(end);

    if( max_angle < 0.001f ){
        // No rotation allowed. Prevent dividing by 0 later.
        return t_start;
    }

    float cos_theta = glm::dot(start, end);

    // q1 and q2 are already equal.
    // Force q2 just to be sure
    if(cos_theta > 0.9999f){
        return t_end;
    }

    // Avoid taking the long path around the sphere
    if (cos_theta < 0){
        //start = start * -1.0f;
        t_start = glm::inverse(t_start);

        cos_theta *= -1.0f;
    }

    float angle = acos(cos_theta);

    // If there is only a 2° difference, and we are allowed 5°,
    // then we arrived.
    if (angle < max_angle){
        return t_end;
    }

    // This is just like slerp(), but with a custom t
    float t = max_angle / angle;
    angle = max_angle;

    glm::quat res = (sin((1.0f - t) * angle) * t_start + sin(t * angle) * t_end) / sin(angle);
    res = normalize(res);
    return res;
}
string GLHelper::GetGResAbsPath()
{
    QDir temp_dir;
    QString res_path = QCoreApplication::applicationDirPath() + "/../res";
    //const char* res_relative_path = "./../../../res";
    if(temp_dir.exists(res_path))
    {
        return temp_dir.absoluteFilePath(res_path).toStdString();
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

void GLHelper::LoadTexture(GLuint &texture_obj,GLenum texture_target,GLenum* sampler_param_name,GLenum* sampler_param_value,
                           int sampler_param_count,QImage::Format format,bool is_gen_mipmap,const char* image_path)
{
    glGenTextures(1,&texture_obj);
    glBindTexture(texture_target, texture_obj);
    for(int param_index=0; param_index<sampler_param_count; param_index++)
    {
        glTexParameteri(texture_target, sampler_param_name[param_index], sampler_param_value[param_index]);
    }
    QImage temp(GLHelper::GetAbsPathRelativeGResPath(image_path).c_str());
    QImage image = temp.convertToFormat(format);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),
                 0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());
    if(is_gen_mipmap)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    glBindTexture(texture_target, 0);
}

long GLHelper::GetTickCount()
{
    return _start_timer.elapsed();
}







