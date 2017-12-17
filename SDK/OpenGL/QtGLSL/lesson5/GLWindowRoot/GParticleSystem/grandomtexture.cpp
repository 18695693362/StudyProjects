#include "grandomtexture.h"
#include "glm/glm.hpp"
#include "cstdlib"
#include "../../common/glfuncdefine.h"

GRandomTexture::GRandomTexture()
{
    _tex_obj = 0;
}

GRandomTexture::~GRandomTexture()
{
    if(_tex_obj!=0)
        glDeleteTextures(1, &_tex_obj);
}

void GRandomTexture::Init(unsigned int size)
{
    glm::vec3* random_data = new glm::vec3[size];
    for (int i=0; i<size; i++)
    {
        random_data[i].x = (rand()%255)/255;
        random_data[i].y = (rand()%255)/255;
        random_data[i].z = (rand()%255)/255;
    }
    glGenTextures(1, &_tex_obj);
    glBindTexture(GL_TEXTURE_1D, _tex_obj);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, size, 0, GL_RGB, GL_FLOAT, random_data);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_REPEAT);

    delete []random_data;
}

void GRandomTexture::Bind(GLenum tex_unit_enum)
{
    glActiveTexture(tex_unit_enum);
    glBindTexture(GL_TEXTURE_1D, _tex_obj);
}
