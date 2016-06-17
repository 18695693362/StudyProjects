#ifndef GLHELPER_H
#define GLHELPER_H

#include <QtOpenGL>
#include <QImage>
#include "../libs/glm/glm/glm.hpp"
#include "../libs/glm/glm/gtc/matrix_transform.hpp"
#include <string>
#include "gtriangle.h"

#define BUFF_OFFSET(offset) ((void*)(offset))

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

    static void LoadTexture(GLuint& texture_obj, GLenum texture_target, GLenum *sampler_param_name, GLenum *sampler_param_value, int sampler_param_count, QImage::Format format, bool is_gen_mipmap, const char *image_path);

    static long GetTickCount();

    template<typename T, typename... U>
    static size_t GetFuncAddr(std::function<T(U...)> f)
    {
        typedef T(fnType)(U...);
        fnType ** fnPointer = f.template target<fnType*>();
        return (size_t) *fnPointer;
    }
private:
    static QElapsedTimer _start_timer;
};

#endif // GLHELPER_H
