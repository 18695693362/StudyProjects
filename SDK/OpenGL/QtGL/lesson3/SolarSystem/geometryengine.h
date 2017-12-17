#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QtOpenGL>

enum EGeometryType
{
    kCube,
    kIcosahedron,
    kBall1,
    kGeometryType_MaxInvalid
};

class GeometryEngine
{
public:
    GeometryEngine();
    ~GeometryEngine();

    void init();
    void drawGeometry();
    void SetGeometryType(EGeometryType type)
    {
        m_geometryType = type;
    }
    EGeometryType GetGeometryType()
    {
        return m_geometryType;
    }
private:

    void initCubeGeometry();
    EGeometryType m_geometryType;
};

#endif // GEOMETRYENGINE_H
