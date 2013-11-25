Qt框架中和OpenGL相关的函数有：
（1）virtual void initializeGL();             初始化OpenGL的一些参数
（2）virtual void paintGL();                  在该函数内进行绘制
（3）virtual void resizeGL(int w, int h);     当窗口发生改变时，调用该函数。

使用OpenGL的一般方式：
1、放置摄像机。将摄像机放在指定的位置，旋转摄像机到指定方向。（视图变换）
Tips:视图变换和模型变换互逆，他们操作的都是模型矩阵
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(0.0,0.0,10.0,    0.0,0.0,-10.0,    0.0,1.0,0.0 );

2、设置摄像机视野模式（投影变换）
（1）设置视景体；
（2）设置投影方式；
glMatrixMode(GL_PROJECTION);
glLoadIdentity();

glOrtho(left, right, bottom, top, -near, -far); //Tips:此处设置的是相反数
gluPerspective(fovy,aspect,zNear,zFar);
glFrustum(left,right,bottom,top,zNear,zFar);

3、指定投影到胶片的区域（设置视口）
glViewport(0,0,window_width_,window_height_);

4、在场景中放置物体（模型变换）
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glBegin(GL_LINES); //Tips:此处参数不能为GL_LINE
{
}
glEnd();

