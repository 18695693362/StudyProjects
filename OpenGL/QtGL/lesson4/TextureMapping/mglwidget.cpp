#include "mglwidget.h"
#ifdef Q_OS_WIN
#include <GL/glu.h>
#endif
#ifdef Q_OS_MAC
#include <OpenGL/glu.h>
#endif
#include <QtMath>
#include <QtGui>
#include <iostream>
using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

#define kTimerInterval  1000.0f/60.0f

#define kDistanceBetweenSunAndEarth     100
#define kDistanceBetweenMoonAndEarth    40

#define kSunRadiusFactor        3
#define kEarthRadiusFactor      2
#define kMoonRadiusFactor       1

//太阳自转            30秒
//地球公转            360秒
//地球自转            10秒
//月球自转公转          30秒
#define kSunRotateSpeed                 360.0f/30000.0f
#define kEarthRelativeSunRotateSpeed    360.0f/360000.0f
#define kEarthRotateSpeed               360.0f/10000.0f
#define kMoonRotateSpeed                360.0f/30000.0f

#define kCheckImageWidth    64
#define kCheckImageHeight   64
static GLubyte check_image[kCheckImageWidth][kCheckImageHeight][4];
static GLuint texture_name1;
static GLuint texture_name2; //when load texture,compress texture

GLdouble g_left_bottom_pos[]={0.0,0.0};
GLdouble g_left_top_pos[]={0.0,kDesignSizeH};
GLdouble g_right_bottom_pos[]={kDesignSizeW,0.0};
GLdouble g_right_top_pos[]={kDesignSizeW,kDesignSizeH};
GLdouble g_middle_pos[]={kDesignSizeW/2,kDesignSizeH/2};

GLfloat g_whiteColor[] = {1.0,1.0f,1.0,1.0};
GLfloat g_blackColor[] = {0.0,0.0f,0.0,1.0};
GLfloat g_lightBlackColor[] = {0.1,0.1,0.1,1.0};
GLfloat g_redColor[] = {1.0,0.0f,0.0,1.0};
GLfloat g_greenColor[] = {0.0,0.0f,1.0,1.0};
GLfloat g_blueColor[] = {0.0,0.0f,1.0,1.0};
GLfloat g_lightBlueColor[] = {65.0/225.0,105.0/225.0,1.0,1.0};
GLfloat g_yellowColor[] = {1.0,215.0f/255.0f,0.0,1.0};
GLfloat g_grayColor[] = {70.0f/255.0f,70.0f/255.0f,70.0f/255.0f,1.0f};

void MakeCheckImage()
{
    int c;
    for(int i=0; i<kCheckImageWidth; i++)
    {
        for(int j=0; j<kCheckImageHeight; j++)
        {
            c = (((i&0x8)==0) ^ ((j&0x8)==0)) * 255;
            check_image[i][j][0] = c;
            check_image[i][j][1] = c;
            check_image[i][j][2] = c;
            check_image[i][j][3] = 255;
        }
    }
}

void AdjustRotateAngle(GLfloat& angle)
{
    if(angle>360.0f)
    {
        angle -= 360.0f;
    }
    else if(angle<-360.0f)
    {
        angle += 360.0f;
    }
}

MGLWidget::MGLWidget(QWidget *parent, const char* name, bool full_screen) :
    QGLWidget(parent)
{
    setGeometry( kDefaultX, kDefaultY, kDesignSizeW, kDesignSizeH );
    setMinimumSize(kMinWidth, kMinHeight);
    window_width_ = kDesignSizeW;
    window_height_= kDesignSizeH;

    setWindowTitle(name);

    is_full_screen_ = full_screen;
    if(is_full_screen_)
        showFullScreen();

    rotate_angle_x_ = 0.0f;
    rotate_angle_y_ = 0.0f;
    rotate_angle_z_ = 0.0f;

    sun_rotate_angle_x_ = 0.0f;
    sun_rotate_angle_y_ = 0.0f;
    sun_rotate_angle_z_ = 0.0f;

    earth_rotate_angle_x_ = 0.0f;
    earth_rotate_angle_y_ = 0.0f;
    earth_rotate_angle_z_ = 0.0f;

    earth_relative_sun_rotate_angle_x_ = 0.0f;
    earth_relative_sun_rotate_angle_y_ = 0.0f;
    earth_relative_sun_rotate_angle_z_ = 0.0f;

    moon_rotate_angle_x_ = 0.0f;
    moon_rotate_angle_y_ = 0.0f;
    moon_rotate_angle_z_ = 0.0f;

    moon_ralative_earth_rotate_angle_x_ = 0.0f;
    moon_ralative_earth_rotate_angle_y_ = 0.0f;
    moon_ralative_earth_rotate_angle_z_ = 0.0f;

    m_geometryEngine.init();
}


void MGLWidget::initializeGL()
{
    glClearColor(0.0f,0.8f,0.8f,1.0f);
    glClearDepth(1.0f);

    MakeCheckImage();

    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_NORMALIZE);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);
    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT,g_lightBlackColor);
    //glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
    //glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
    //glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
    glShadeModel(GL_FLAT);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glGenTextures(1,&texture_name1);
    glBindTexture(GL_TEXTURE_2D,texture_name1);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,kCheckImageWidth,kCheckImageHeight,
                 0,GL_RGBA,GL_UNSIGNED_BYTE,check_image);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    glGenTextures(1,&texture_name2);
    glBindTexture(GL_TEXTURE_2D,texture_name2);

    glTexImage2D(GL_TEXTURE_2D,0,GL_COMPRESSED_RGBA,kCheckImageWidth,kCheckImageHeight,
                 0,GL_RGBA,GL_UNSIGNED_BYTE,check_image);
    GLint is_compressed;
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED, &is_compressed);
    if(is_compressed)
    {
        GLint compressed_format = 0;

        cout << "(GL_RGBA=" << GL_RGBA << ")" << endl;
        cout << "(GL_COMPRESSED_RGBA=" << GL_COMPRESSED_RGBA << ")" << endl;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &compressed_format);
        cout << "Texture is compressed to " << compressed_format << endl;

        GLsizei compressed_size=0;
        glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_COMPRESSED_IMAGE_SIZE, &compressed_size);
        cout << "Compressed texture size is " << compressed_size << endl;
    }

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

    memset(check_image,0,sizeof(check_image)/sizeof(GLubyte));

    //glLightfv(GL_LIGHT0,GL_AMBIENT,g_yellowColor);
    //glLightfv(GL_LIGHT0,GL_SPECULAR,g_yellowColor);
    //glLightfv(GL_LIGHT0,GL_DIFFUSE,g_yellowColor);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, kDesignSizeW, 0.0, kDesignSizeH, -1000, 1000);

    // record current projection matrix
    glGetDoublev(GL_PROJECTION_MATRIX,m_curProjectionMatrix);

    m_timer.start(kTimerInterval,this);
}

void MGLWidget::timerEvent(QTimerEvent *e)
{
    sun_rotate_angle_y_ += kSunRotateSpeed*kTimerInterval;
    earth_rotate_angle_y_ += kEarthRotateSpeed*kTimerInterval;
    earth_relative_sun_rotate_angle_y_ += kEarthRelativeSunRotateSpeed*kTimerInterval;
    moon_rotate_angle_y_ += kMoonRotateSpeed*kTimerInterval;
    moon_ralative_earth_rotate_angle_y_ += kMoonRotateSpeed*kTimerInterval;

    AdjustRotateAngle(sun_rotate_angle_y_);
    AdjustRotateAngle(earth_rotate_angle_y_);
    AdjustRotateAngle(earth_relative_sun_rotate_angle_y_);
    AdjustRotateAngle(moon_rotate_angle_y_);
    AdjustRotateAngle(moon_ralative_earth_rotate_angle_y_);

    updateGL();
}

void MGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 ); //this is default value
    gluLookAt(0.0,0.0,100.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );

    glRotatef(rotate_angle_x_,1,0,0);
    glRotatef(rotate_angle_y_,0,1,0);
    glRotatef(rotate_angle_z_,0,0,1);

    glTranslatef(kDesignSizeW/2,kDesignSizeH/2,0.0);
    glScalef(50.0,50.0,50.0);
    glBegin(GL_QUADS);
    {
        glBindTexture(GL_TEXTURE_2D,texture_name1);
        glTexCoord2f(0.0,0.0);glVertex3f(-2.0,-1.0,0.0);
        glTexCoord2f(0.0,1.0);glVertex3f(-2.0,1.0,0.0);
        glTexCoord2f(1.0,1.0);glVertex3f(0.0,1.0,0.0);
        glTexCoord2f(1.0,0.0);glVertex3f(0.0,-1.0,0.0);

        glBindTexture(GL_TEXTURE_2D,texture_name2);
        glTexCoord2f(0.0,0.0);glVertex3f(1.0,-1.0,0.0);
        glTexCoord2f(0.0,1.0);glVertex3f(1.0,1.0,0.0);
        glTexCoord2f(1.0,1.0);glVertex3f(2.41421,1.0,-1.41421);
        glTexCoord2f(1.0,0.0);glVertex3f(2.41421,-1.0,-1.41421);
    }
    glEnd();
    glFlush();
    glDisable(GL_TEXTURE_2D);
}

void MGLWidget::resizeGL(int w, int h)
{
    if(w < kMinWidth || h < kMinHeight)
    {
        w = kMinWidth;
        h = kMinHeight;
    }
    window_width_ = w;
    window_height_= h;

    glViewport(0,0,window_width_,window_height_);

    // record current viewport
    glGetIntegerv(GL_VIEWPORT,m_curViewPort);
}

void MGLWidget::DrawGeometry()
{
    m_geometryEngine.drawGeometry();
}

void MGLWidget::mousePressEvent(QMouseEvent *e)
{
    m_mousePressPos = e->localPos();
}

void MGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QPointF mouseReleasePos = event->localPos();
    GLdouble posX,posY,posZ;
    int result =
    gluUnProject(mouseReleasePos.x(),
                 window_height_ - mouseReleasePos.y(),
                 0,
                 m_curModleViewMatrix,
                 m_curProjectionMatrix,
                 m_curViewPort,
                 &posX,&posY,&posZ);
    if(result == GL_TRUE)
    {
        cout << endl;
        cout << " viewportPosX:" << mouseReleasePos.x();
        cout << " viewportPosY:" << window_height_ - mouseReleasePos.y();
        cout << " posX:" << posX;
        cout << " posY:" << posY;
        cout << " posZ:" << posZ;
    }

    unsigned int type = m_geometryEngine.GetGeometryType();
    type += 1;
    type %= kGeometryType_MaxInvalid;
    //m_geometryEngine.SetGeometryType((EGeometryType)type);
    updateGL();
}

void MGLWidget::keyReleaseEvent(QKeyEvent *key)
{
    //initializeGL();
    switch (key->key())
    {
    case Qt::Key_0:
    {
        break;
    }
    case Qt::Key_Left:
    {
        rotate_angle_y_ += 15.0f;
        break;
    }
    case Qt::Key_Up:
    {
        rotate_angle_x_ += 15.0f;
        break;
    }
    case Qt::Key_Right:
    {
        rotate_angle_y_ -= 15.0f;
        break;
    }
    case Qt::Key_Down:
    {
        rotate_angle_x_ -= 15.0f;
        break;
    }
    default:
        break;
    }
    updateGL();
}








