#include "geometryengine.h"
#include <math.h>

void UnitVector(GLfloat vector[3])
{
    GLfloat length = sqrtf(vector[0]*vector[0]+vector[1]*vector[1]+vector[2]*vector[2]);
    if(length == 0.0f)
        return;
    vector[0] /= length;
    vector[1] /= length;
    vector[2] /= length;
}

void NormalVector(GLfloat vector1[3],GLfloat vector2[3],GLfloat outVector[3])
{
    outVector[0] = vector1[1]*vector2[2]-vector1[2]*vector2[1];
    outVector[1] = vector1[2]*vector2[0]-vector1[0]*vector2[2];
    outVector[2] = vector1[0]*vector2[1]-vector1[1]*vector2[0];
    UnitVector(outVector);
}

static GLfloat m_cubeVertices[] =
{
    -10,10,10,
    -10,-10,10,
    10,-10,10,
    10,10,10,
    10,-10,-10,
    10,10,-10,
    -10,10,-10,
    -10,-10,-10
};
static GLfloat m_cubeColors[] = {
    1.0,0.2,0.2,
    0.2,0.2,1.0,
    0.8,1.0,0.2,
    0.75,0.75,0.75,
    0.35,0.35,0.35,
    0.5,0.5,0.5
};
static GLushort m_cubeFaceFIndices[] = {
    0,1,2,3
};
static GLushort m_cubeFaceLIndices[] = {
    6,7,1,0
};
static GLushort m_cubeFaceBIndices[] = {
    6,5,4,7
};
static GLushort m_cubeFaceUIndices[] = {
    6,0,3,5
};
static GLushort m_cubeFaceRIndices[] = {
    3,2,4,5
};
static GLushort m_cubeFaceDIndices[] = {
    7,4,2,1
};

void DrawCube()
{
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3,GL_FLOAT,0,m_cubeVertices);

    //glEnableClientState(GL_COLOR_ARRAY);
    //glColorPointer(3,GL_FLOAT,0,m_cubeColors);

    glColor3fv(&m_cubeColors[0]);
    glDrawElements(GL_QUADS,4,GL_UNSIGNED_SHORT,m_cubeFaceFIndices);
    glColor3fv(&m_cubeColors[1*3]);
    glDrawElements(GL_QUADS,4,GL_UNSIGNED_SHORT,m_cubeFaceLIndices);
    glColor3fv(&m_cubeColors[2*3]);
    glDrawElements(GL_QUADS,4,GL_UNSIGNED_SHORT,m_cubeFaceBIndices);
    glColor3fv(&m_cubeColors[3*3]);
    glDrawElements(GL_QUADS,4,GL_UNSIGNED_SHORT,m_cubeFaceUIndices);
    glColor3fv(&m_cubeColors[4*3]);
    glDrawElements(GL_QUADS,4,GL_UNSIGNED_SHORT,m_cubeFaceRIndices);
    glColor3fv(&m_cubeColors[5*3]);
    glDrawElements(GL_QUADS,4,GL_UNSIGNED_SHORT,m_cubeFaceDIndices);
}

#define kIcosahedronModelValueX .525731112119133606
#define kIcosahedronModelValueZ .850650808352039932

static GLfloat m_iconsahedronVertices[][3] = {
    {-kIcosahedronModelValueX, 0.0, kIcosahedronModelValueZ},
    {kIcosahedronModelValueX, 0.0, kIcosahedronModelValueZ},
    {-kIcosahedronModelValueX, 0.0, -kIcosahedronModelValueZ},
    {kIcosahedronModelValueX, 0.0, -kIcosahedronModelValueZ},
    {0.0, kIcosahedronModelValueZ, kIcosahedronModelValueX},
    {0.0, kIcosahedronModelValueZ, -kIcosahedronModelValueX},
    {0.0, -kIcosahedronModelValueZ, kIcosahedronModelValueX},
    {0.0, -kIcosahedronModelValueZ, -kIcosahedronModelValueX},
    {kIcosahedronModelValueZ, kIcosahedronModelValueX, 0.0},
    {-kIcosahedronModelValueZ, kIcosahedronModelValueX, 0.0},
    {kIcosahedronModelValueZ, -kIcosahedronModelValueX, 0.0},
    {-kIcosahedronModelValueZ, -kIcosahedronModelValueX, 0.0},
};

static GLushort m_iconsahedronIndecies[20][3] = {
    {1,4,0},{4,9,0},{4,5,9},{8,5,4},{1,8,4},
    {1,10,8},{10,3,8},{8,3,5},{3,2,5},{3,7,2},
    {3,10,7},{10,6,7},{6,11,7},{6,0,11},{6,1,0},
    {10,1,6},{11,0,9},{2,11,9},{5,2,9},{11,2,7}
};

void DrawIcosahedron()
{
    glScalef(10.0f,10.0f,10.0f);
    glBegin(GL_TRIANGLES);
    GLfloat* colorPointer = m_cubeColors;
    unsigned int colorIterator = 0;
    for(int i=0; i<20; i++)
    {
        glColor3fv(colorPointer+colorIterator*3);
        glNormal3fv(&m_iconsahedronVertices[m_iconsahedronIndecies[i][0]][0]);
        glVertex3fv(&m_iconsahedronVertices[m_iconsahedronIndecies[i][0]][0]);

        glNormal3fv(&m_iconsahedronVertices[m_iconsahedronIndecies[i][1]][0]);
        glVertex3fv(&m_iconsahedronVertices[m_iconsahedronIndecies[i][1]][0]);

        glNormal3fv(&m_iconsahedronVertices[m_iconsahedronIndecies[i][2]][0]);
        glVertex3fv(&m_iconsahedronVertices[m_iconsahedronIndecies[i][2]][0]);
        colorIterator += 1;
        if(colorIterator > sizeof(m_cubeColors)/sizeof(GLfloat))
            colorIterator = 0;
    }
    glEnd();
}

void DrawTriangle(GLfloat* v1,GLfloat* v2,GLfloat* v3)
{
    glBegin(GL_TRIANGLES);
    {
        glNormal3fv(v1);
        glVertex3fv(v1);

        glNormal3fv(v2);
        glVertex3fv(v2);

        glNormal3fv(v3);
        glVertex3fv(v3);
    }
    glEnd();
}

void SubDivide(GLfloat* v1,GLfloat* v2,GLfloat* v3,int depth)
{
    GLfloat v12[3],v23[3],v31[3];
    if(depth == 0)
    {
        DrawTriangle(v1,v2,v3);
        return;
    }
    for(int i=0;i<3;i++)
    {
        v12[i] = (v1[i]+v2[i])/2.0;
        v23[i] = (v2[i]+v3[i])/2.0;
        v31[i] = (v3[i]+v1[i])/2.0;
    }
    UnitVector(v12);
    UnitVector(v23);
    UnitVector(v31);
    SubDivide(v1,v12,v31,depth-1);
    SubDivide(v2,v23,v12,depth-1);
    SubDivide(v3,v31,v23,depth-1);
    SubDivide(v12,v23,v31,depth-1);
}

void DrawBall1()
{
    glScalef(10.0f,10.0f,10.0f);
    for(int i=0; i<20; i++)
    {
        SubDivide(&m_iconsahedronVertices[m_iconsahedronIndecies[i][0]][0],
                  &m_iconsahedronVertices[m_iconsahedronIndecies[i][1]][0],
                  &m_iconsahedronVertices[m_iconsahedronIndecies[i][2]][0],
                  5);
    }
}

GeometryEngine::GeometryEngine()
    :m_geometryType(kCube)
{
}

GeometryEngine::~GeometryEngine()
{
}

void GeometryEngine::init()
{
    initCubeGeometry();
}

void GeometryEngine::initCubeGeometry()
{
}

void GeometryEngine::drawGeometry()
{
    switch(m_geometryType)
    {
    case kCube:
    {
        DrawCube();
        break;
    }
    case kIcosahedron:
    {
        DrawIcosahedron();
        break;
    }
    case kBall1:
    {
        glColor4f(0.0,0.0,0.0,0.0);
        DrawBall1();
        break;
    }
    default:
        break;
    }
}

