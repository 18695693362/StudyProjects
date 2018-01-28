#ifndef GINSTANCEARRAY_H
#define GINSTANCEARRAY_H

#include <QOpenGLWidget>
#include <QOpenGLExtraFunctions>
#include "glm/gtc/matrix_transform.hpp"
#include "../../../common/vbm.h"
#include "../../../common/gdebug.h"
#include "../../../common/gtriangle.h"

class GInstanceArray : public QOpenGLWidget, protected QOpenGLExtraFunctions
{
    Q_OBJECT
public:
    explicit GInstanceArray(QWidget *parent = 0, const char* name="", bool full_screen=false);

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int w, int h);

private:
    void GetVertexData(GLfloat *&vertex_data_ptr, int &size, int &vertex_count);
    void GetOffsetData(GLfloat *&offset_data, int &size);

    bool    is_full_screen_;
    float   window_width_;
    float   window_height_;

    enum AttribLocal
    {
        kPosAttribLocal,
        kColorAttribLocal,
        kOffsetAttribLocal
    };
    GLuint  _vabuffer;
    GLuint  _instance_a_buffer;
    GLuint  _vaobject;

    GLint  program;
    VBObject vbobject;
    GDebug   _gldebuger;
    GTriangle _triangle;
    static const int _kInstanceCount;
};

#endif // GINSTANCEARRAY_H