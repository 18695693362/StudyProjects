Tips:
1、OpenGL是主列序存储矩阵的。
[a1,a5,a9 ,a13]
[a2,a6,a10,a14]
[a3,a7,a11,a15]
[a4,a8,a12,a16]

2、下面的代码中模型视图矩阵的变化为：I、N、NM、NML，最后作用于定点的后得到NMLv
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glMultMatrixf(N);
glMultMatrixf(M);
glMultMatrixf(L);
glBegin(GL_POINTS);
glVertex3f(v);
glEnd();

3、视图变换要在模型变换之前，确保先作用于物体的是模型变换。

4、glBegin(XXXXX) glEnd(void) 之间的合法函数有：
glVertex*()
glColor*()
glIndex*()
glSecondaryColor*()
glNormal*()
glMaterial*()
glTexCoord*()
glVertexAttrib*()
glEdgeFlag*()
glArrayElement()
glEvalCoord*(),glEvalPoint*()
glCallList(),glCallLists()
除了这些函数以外，不能在glBegin(XXXXX) glEnd(void) 之间使用其他OpenGL函数。

5、glRotatef(angle,x,y,z)函数的意义：
绕直线（0,0,0-x,y,z）顺时针旋转angle角度

6、如果发现图形显示不全，可能是因为图形被裁减掉了。检查视景体的z值是否设置正确。
