#ifndef GLHELPER_H
#define GLHELPER_H

#include <QtOpenGL>

class GLHelper
{
public:
    GLHelper();
    ~GLHelper();

    static GLuint CompileShader(GLuint shader_type, const char* shader_str);
    static GLuint CreateShaderProgram(const char* vertex_shader_str, const char* fragment_shader_str);
    static GLuint CreateShaderProgramWithFiles(const QString& vert_path, const QString& frag_path);
    static QString GetShaderTxt(const QString& filePath);

    static size_t TypeSize(GLenum type);
};

#endif // GLHELPER_H
