#ifndef GLHELPER_H
#define GLHELPER_H

#include <QtOpenGL>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include <string>

enum LogType{
    kInfo,
    kWarnning,
    kError,
};
class GLHelper
{
public:
    GLHelper();
    ~GLHelper();

    static void Init();

    static GLuint CompileShader(GLuint shader_type, const char* shader_str);
    static GLuint CreateShaderProgram(const char* vertex_shader_str, const char* fragment_shader_str);
    static GLuint CreateShaderProgramWithFiles(const QString& vert_path, const QString& frag_path);
    static QString GetShaderTxt(const QString& filePath);

    static GLint GetUniformLocal(GLuint program, const char* uniform_name);
    static bool  IsGLError();

    static size_t TypeSize(GLenum type);

    static void Log(const std::string log_str,LogType type=LogType::kInfo);

    static glm::mat4 GetScale(float x);
    static glm::mat4 GetScale(float x,float y, float z);
    static glm::mat4 GetRotate(float angle,float x,float y, float z);
    static glm::mat4 GetTranslate(float x, float y, float z);

    static std::string GetGResAbsPath();
    static std::string GetAbsPathRelativeGResPath(const std::string &relative_path);

    static long GetTickCount();

private:
    static QElapsedTimer _start_timer;
};

class GTriangle
{
public:
    void Init(GLfloat* vertex_data, int size, int count, attrib_local);
    void Draw();

private:
    int    _count;
    GLuint _vaobject;
    GLuint _vabuffer;
};

#endif // GLHELPER_H
