#ifndef GRANDOMTEXTURE_H
#define GRANDOMTEXTURE_H
#include<QtOpenGL>

class GRandomTexture
{
public:
    GRandomTexture();
    ~GRandomTexture();

    void Init(unsigned int size);

    void Bind(GLenum tex_unit_enum);
private:
    GLuint _tex_obj;
};

#endif // GRANDOMTEXTURE_H
