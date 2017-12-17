#include "goglwidget.h"
#include <QApplication>
#include <QGLFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setVersion(4,1);
    QSurfaceFormat::setDefaultFormat(format);

    GOGLWidget widget(NULL,"TestCamera",false);
    widget.show();
    
    return a.exec();
}

//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtx/quaternion.hpp"
//#include "glm/gtx/vector_angle.hpp"
//#include <iostream>
//using namespace std;
//#define Print(pos) do{\
//    cout << #pos <<".x " << pos.x << "\n";\
//    cout << #pos <<".y " << pos.y << "\n";\
//    cout << #pos <<".z " << pos.z << "\n";\
//}while(0);

//int main()
//{
//    //glm::quat quat_1(1.f,0.f,0.f,0.f);
//    //glm::quat quat_1(0.7f,0.7f,0.f,0.0f);
//    float angle = asin(0.8);
//    glm::quat quat_1 = glm::angleAxis(angle,glm::vec3(0.0,1.0,0.0));
//    glm::vec3 pos_1(5.0f,0.0,0.0);
//    glm::vec3 pos_2 = quat_1 * pos_1;
//    //dr*quat_D*glm::conjugate(dr);
//    glm::quat quat_t = glm::quat(0.0,pos_1.x,pos_1.y,pos_1.z);
//    glm::quat pos_3 = quat_1*quat_t*glm::conjugate(quat_1);
//    Print(quat_1);
//    Print(pos_2);
//    Print(pos_3);
//    return 0;
//}

