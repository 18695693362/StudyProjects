#include "mglwidget.h"
#ifdef Q_OS_WIN
#include <GL/glu.h>
#endif
#ifdef Q_OS_MAC
#include <OpenGL/glu.h>
#endif
#include <iostream>
#include <vector>
#include <string>
#include <QtGui>
using namespace std;

#define kMinWidth   50.0f
#define kMinHeight  50.0f
#define kDefaultX   100.0f
#define kDefaultY   100.0f
#define kDesignSizeW    480.f
#define kDesignSizeH    320.f

struct BlendEffect
{
    void Init(GLenum src1,GLenum dst1,GLenum opt1,GLfloat alph1,
              GLenum src2,GLenum dst2,GLenum opt2,GLfloat alph2,
              const std::string& name)
    {
        src_blendFunc1=src1;
        dst_blendFunc1=dst1;
        opt_blendType1=opt1;
        alpha_obj1=alph1;
        src_blendFunc2=src2;
        dst_blendFunc2=dst2;
        opt_blendType2=opt2;
        alpha_obj2=alph2;
        effect_name = name;
    }
    GLenum src_blendFunc1;
    GLenum dst_blendFunc1;
    GLenum opt_blendType1;
    GLfloat alpha_obj1;
    GLenum src_blendFunc2;
    GLenum dst_blendFunc2;
    GLenum opt_blendType2;
    GLfloat alpha_obj2;
    std::string effect_name;
};
static std::vector<BlendEffect> g_blendEffects;
static int  g_blendEffectIndex = 0;
static bool g_enableBlendEffect = false;
void InitBlendEffects()
{
    BlendEffect temp;
    temp.Init(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_FUNC_ADD,0.5,
              GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_FUNC_ADD,0.5,
              "Both Images are Enable Alpha(0.5)");
    g_blendEffects.push_back(temp);
    temp.Init(GL_ONE,GL_ZERO,GL_FUNC_ADD,1.0,
              GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_FUNC_ADD,0.5,
              "FirstImage0.5+SecondImage0.5");
    g_blendEffects.push_back(temp);
    temp.Init(GL_SRC_ALPHA,GL_ONE,GL_FUNC_ADD,0.3,
              GL_SRC_ALPHA,GL_ONE,GL_FUNC_ADD,0.3,
              "FirstImage0.3+SecondImage0.3");
    g_blendEffects.push_back(temp);
    temp.Init(GL_ONE,GL_ZERO,GL_FUNC_ADD,1.0,
              GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA,GL_FUNC_ADD,0.0,
              "FirstImage0.3+SecondImage0.3");
    g_blendEffects.push_back(temp);
}

void SetBlendEffect(bool increaseCurrenBlendEffectIndex)
{
    if(increaseCurrenBlendEffectIndex)
    {
        g_blendEffectIndex++;
    }
    else
    {
        g_blendEffectIndex--;
    }
    if(g_blendEffectIndex<0)
    {
        g_blendEffectIndex = g_blendEffects.size() - 1;
    }
    if(g_blendEffectIndex==(int)g_blendEffects.size())
    {
        g_blendEffectIndex = 0;
    }
    const BlendEffect& effect = g_blendEffects.at(g_blendEffectIndex);
    cout << "g_blendEffectIndex: "
         << g_blendEffectIndex
         << " effectName:"
         << effect.effect_name << endl;
}
static std::vector<std::string> g_blendFuncName;
void InitBlendFuncName()
{
    g_blendFuncName.push_back("GL_ONE_MINUS_DST_ALPHA");
    g_blendFuncName.push_back("GL_ZERO");
    g_blendFuncName.push_back("GL_ONE");
    g_blendFuncName.push_back("GL_DST_COLOR");
    g_blendFuncName.push_back("GL_ONE_MINUS_DST_COLOR");
    g_blendFuncName.push_back("GL_SRC_ALPHA");
    g_blendFuncName.push_back("GL_ONE_MINUS_SRC_ALPHA");
    g_blendFuncName.push_back("GL_DST_COLOR");
    g_blendFuncName.push_back("GL_SRC_ALPHA_SATURATE");
}
static GLenum g_blendFuncEnum[] = {
    GL_ONE_MINUS_DST_ALPHA,
    GL_ZERO,
    GL_ONE,
    GL_DST_COLOR,
    GL_ONE_MINUS_DST_COLOR,
    GL_SRC_ALPHA,
    GL_ONE_MINUS_SRC_ALPHA,
    GL_DST_ALPHA,
    GL_SRC_ALPHA_SATURATE
};
static int g_src_blendFuncIndex = 0;
static int g_des_blendFuncIndex = 0;

MGLWidget::MGLWidget(QWidget *parent, const char* name, bool full_screen) :
    QGLWidget(parent)
{
    InitBlendFuncName();
    InitBlendEffects();

    setGeometry( kDefaultX, kDefaultY, kDesignSizeW, kDesignSizeH );
    setMinimumSize(kMinWidth, kMinHeight);
    window_width_ = kDesignSizeW;
    window_height_= kDesignSizeH;

    setWindowTitle(name);

    is_full_screen_ = full_screen;
    if(is_full_screen_)
        showFullScreen();
}


void MGLWidget::initializeGL()
{
    glClearColor(0.0f,0.0f,1.0f,1.0f);
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_FLAT); //GL_SMOOTH GL_FLAT
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glEnable(GL_BLEND);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, kDesignSizeW, 0.0, kDesignSizeH, -1000, 1000);
}

void MGLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt(0.0,0.0,0.0,    0.0,0.0,-100.0,    0.0,1.0,0.0 ); //this is default value
    gluLookAt(0.0,0.0,10.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );

    GLfloat alphaValue = 1.0f;

    glTranslatef(kDesignSizeW/2,kDesignSizeH/2,0.0);
    glPushMatrix();
    {
        if(g_enableBlendEffect)
        {
            const BlendEffect& effect = g_blendEffects.at(g_blendEffectIndex);
            glBlendFunc(effect.src_blendFunc1,
                        effect.dst_blendFunc1);
            glBlendEquation(effect.opt_blendType1);
            alphaValue = effect.alpha_obj1;
        }
        glTranslatef(80,80,0.0);
        glScalef(100.0,100.0,1.0);
        glBegin(GL_QUADS);
        {
            glColor4f(0.0,1.0,0.0,alphaValue);
            glVertex2f(-1.0,-1.0);
            glVertex2f(1.0,-1.0);
            glVertex2f(1.0,1.0);
            glVertex2f(-1.0,1.0);
        }
        glEnd();
    }
    glPopMatrix();

    glPushMatrix();
    {
        if(g_enableBlendEffect)
        {
            const BlendEffect& effect = g_blendEffects.at(g_blendEffectIndex);
            glBlendFunc(effect.src_blendFunc2,
                        effect.dst_blendFunc2);
            glBlendEquation(effect.opt_blendType2);
            alphaValue = effect.alpha_obj2;
        }
        glScalef(50.0,50.0,1.0);
        glBegin(GL_QUADS);
        {
            glColor4f(1.0,0.0,0.0,alphaValue);
            glVertex2f(-1.0,-1.0);
            glVertex2f(1.0,-1.0);
            glVertex2f(1.0,1.0);
            glVertex2f(-1.0,1.0);
        }
        glEnd();
    }
    glPopMatrix();
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
}

void MGLWidget::keyReleaseEvent(QKeyEvent *key)
{
    g_enableBlendEffect = false;
    switch (key->key())
    {
    case 'a':
    case 'A':
    {
        glBlendEquation(GL_FUNC_ADD);
        break;
    }
    case 's':
    case 'S':
    {
        glBlendEquation(GL_FUNC_SUBTRACT);
        break;
    }
    case 'r':
    case 'R':
    {
        glBlendEquation(GL_FUNC_REVERSE_SUBTRACT);
        break;
    }
    case 'n':
    case 'N':
    {
        glBlendEquation(GL_MIN);
        break;
    }
    case 'x':
    case 'X':
    {
        glBlendEquation(GL_MAX);
        break;
    }
    case '+':
    case '=':
    {
        g_enableBlendEffect = true;
        SetBlendEffect(true);
        break;
    }
    case '_':
    case '-':
    {
        g_enableBlendEffect = true;
        SetBlendEffect(false);
        break;
    }
    default:
        break;
    }

    updateGL();
}

void MGLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    switch (event->button()) {
    case Qt::LeftButton:
    {
        g_src_blendFuncIndex++;
        if(g_src_blendFuncIndex == sizeof(g_blendFuncEnum)/sizeof(GLenum))
        {
            g_src_blendFuncIndex = 0;
        }
        break;
    }
    case Qt::RightButton:
    {
        g_des_blendFuncIndex++;
        if(g_des_blendFuncIndex == sizeof(g_blendFuncEnum)/sizeof(GLenum))
        {
            g_des_blendFuncIndex = 0;
        }
        break;
    }
    default:
        break;
    }
    cout << "g_src_blendFuncIndex: " << g_blendFuncName[g_src_blendFuncIndex];
    cout << " g_des_blendFuncIndex: " << g_blendFuncName[g_des_blendFuncIndex];
    cout << endl;

    g_enableBlendEffect = false;
    glBlendFunc(g_blendFuncEnum[g_src_blendFuncIndex],
                g_blendFuncEnum[g_des_blendFuncIndex]);

    updateGL();
}
















