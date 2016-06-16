#ifndef GCUBEMAPTEXTURE_H
#define GCUBEMAPTEXTURE_H
#include <QtOpenGL>
#include <string>
#include <QImage>

class GCubemapTexture
{
public:
    GCubemapTexture(const char* pos_x, const char* neg_x, const char* pos_y, const char* neg_y,
                    const char* pos_z, const char* neg_z, QImage::Format format);
    ~GCubemapTexture();

    bool Load();
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
    std::string     _files[kFaceNums];
    GLuint          _texture_obj;
    QImage::Format  _img_format;
};

#endif // GCUBEMAPTEXTURE_H
