#ifndef GCUBEMAPTEXTURE_H
#define GCUBEMAPTEXTURE_H
#include <QtOpenGL>
#include <string>
#include <QImage>

class GCubemapTexture
{
public:
    bool Load(const char* pos_x, const char* neg_x, const char* pos_y, const char* neg_y,
              const char* pos_z, const char* neg_z, QImage::Format format);

    void Bind(GLenum texture_unit);

    enum FaceType{
        kPosX,
        kNegX,
        kPosY,
        kNegY,
        kPosZ,
        kNegZ,
        kFaceNums
    };
private:
    bool            _is_loaded = false;
    GLuint          _texture_obj;

    std::string     _files[kFaceNums];
    QImage::Format  _img_format;
};

#endif // GCUBEMAPTEXTURE_H
