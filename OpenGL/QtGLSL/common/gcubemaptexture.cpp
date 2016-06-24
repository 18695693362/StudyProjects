#include "gcubemaptexture.h"
#include <QtOpenGL>
#include "glhelper.h"

bool GCubemapTexture::Load(const char *pos_x, const char *neg_x, const char *pos_y, const char *neg_y, const char *pos_z, const char *neg_z, QImage::Format format)
{
    if(!_is_loaded)
    {
        _files[kPosX]   = pos_x;
        _files[kNegX]   = neg_x;
        _files[kPosY]   = pos_y;
        _files[kNegY]   = neg_y;
        _files[kPosZ]   = pos_z;
        _files[kNegZ]   = neg_z;

        _img_format = format;

        glGenTextures(1, &_texture_obj);
        glBindTexture(GL_TEXTURE_CUBE_MAP, _texture_obj);
        GLenum texture_targets[] = {
            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
        };
        for(int face_index=0; face_index<kFaceNums; face_index++)
        {
            QImage temp(GLHelper::GetAbsPathRelativeGResPath(_files[face_index]).c_str());
            QImage image = temp.convertToFormat(_img_format);
            glTexImage2D(texture_targets[face_index],0,GL_RGB,image.width(),image.height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image.bits());
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        }
    }
    return true;
}

void GCubemapTexture::Bind(GLenum texture_unit)
{
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_CUBE_MAP,_texture_obj);
}

