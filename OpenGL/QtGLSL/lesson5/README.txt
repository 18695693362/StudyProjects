    5 Viewing Transformations Clipping and Feedback

一、 Viewing
将三维变为二维用到的关键工具有：视图模型、标准设备坐标的使用、通过矩阵乘运用线性变换、设置视图映射。
1. Camera Model
制作需要的视图所进行的变换处理和用照相机拍照片类似。
拍照片的步骤：
（1）放置照相机
（2）放置模型
（3）选择镜头
OpenGL渲染图片的步骤：
（1）将照相机移动到你想放置的地方，并且将它的方向放置正确。【视图变换】
（2）将被拍摄的物体放到场景中。【模型变换】
（3）选择照相机摄像头调解缩放。【投影变换】
（4）拍照
（5）放大或缩小结果图片到需要的尺寸。【视口变换】
步骤3决定了场景中多少内容被拍摄到。
步骤5决定了被拍摄到的内容放到多大的屏幕上。
2. Viewing Frustum
OpenGL会排除太近或太远的几何体，也就是说在near平面前面的或在far平面后面的物体会被排除。
靠近视景体顶角的物体会非常大，特别是在顶角上时，这会造成问题。物体太远时出于性能原因，以及
深度精度问题，太远的物体会被排除。
3. Frustum Clipping
图元跨越裁剪平面时，OpenGL会裁剪这样的图元。
4. Orthographic Viewing Model
物体正交投影投影后，维持物体实际尺寸以及他们之间的夹角不变。正交投影只是忽略一个维度的坐标。

二、 User Transformations
1. Matrix Multiply Refresher
C(B(Av)) = (CBA)v
可以利用上面的原理来优化性能
2. Homogeneous Coordinates
将三维坐标转化为四维齐次坐标有两个好处：
（1）可以进行透视投影
（2）可以通过线性变换来表示平移
3. 线性变换和矩阵
（1）平移
x,y,z 都平移2.5
⎡1.0 0.0 0.0 2.5⎤   ⎡x⎤   ⎡x+2.5⎤
⎥0.0 1.0 0.0 2.5⎥ * ⎥y⎥ = ⎥y+2.5⎥
⎥0.0 0.0 1.0 2.5⎥   ⎥z⎥   ⎥z+2.5⎥
⎣0.0 0.0 0.0 1.0⎦   ⎣1⎦   ⎣1    ⎦
（2）缩放
x,y,z 都缩放3倍
⎡3.0 0.0 0.0 0.0⎤   ⎡x⎤   ⎡3x⎤
⎥0.0 3.0 0.0 0.0⎥ * ⎥y⎥ = ⎥3y⎥
⎥0.0 0.0 3.0 0.0⎥   ⎥z⎥   ⎥3z⎥
⎣0.0 0.0 0.0 1.0⎦   ⎣1⎦   ⎣1 ⎦
（3）Rotation
沿x轴旋转50度
⎡ 1.0  0.0    0.0   0.0⎤   ⎡x⎤   ⎡   x            ⎤
⎥ 0.0  cos50 -sin50 0.0⎥   ⎥y⎥   ⎥ cos50*y-sin50*z⎥
⎥ 0.0  sin50  cos50 0.0⎥ * ⎥z⎥ = ⎥ sin50*y+cos50*z⎥
⎣ 0.0  0.0    0.0   1.0⎦   ⎣1⎦   ⎣   1            ⎦
沿y轴旋转50度
⎡ cos50  0.0   sin50 0.0⎤   ⎡x⎤   ⎡ cos50*x+sin50*z⎤
⎥ 0.0    1.0   0.0   0.0⎥   ⎥y⎥   ⎥   y            ⎥
⎥-sin50  0.0   cos50 0.0⎥ * ⎥z⎥ = ⎥-sin50*x+cos50*z⎥
⎣ 0.0    0.0   0.0   1.0⎦   ⎣1⎦   ⎣   1            ⎦
沿z轴旋转50度
⎡ cos50  -sin50 0.0 0.0⎤   ⎡x⎤   ⎡cos50*x-sin50*y⎤
⎥ sin50   cos50 0.0 0.0⎥ * ⎥y⎥ = ⎥sin50*x+cos50*y⎥
⎥ 0.0     0.0   1.0 0.0⎥   ⎥z⎥   ⎥   z           ⎥
⎣ 0.0     0.0   0.0 1.0⎦   ⎣1⎦   ⎣   1           ⎦
沿任意轴(Rx,Ry,Rz)旋转o度
（4）Shearing 切变
⎡ 1 s ⎤ * ⎡ x ⎤ = ⎡ x+sy ⎤
⎣ 0 1 ⎦   ⎣ y ⎦   ⎣  y   ⎦
4. Perspective Projection / Orthographic Projection
构造透视投影矩阵和正交投影矩阵
http://www.songho.ca/opengl/gl_projectionmatrix.html
5. 法线变换
法线向量只用了三维，没有用齐次坐标。因为：
（1）平移物体不会修改它的法线，所以法线不需要考虑平移问题
（2）法线向量用来进行光照计算，其在透视投影之前进行，所以法线向量不需要透视投影。
需要注意的是法线向量的变换公用物体的变换。
n′ = M(−1)Tn
6. OpenGL Matrices
为了优化性能，将对于每个顶点都相同的矩阵运算放在应用程序中进行，计算完毕后传递给顶点着色器。
（1）OpenGL中的矩阵行列
opengl中矩阵是列主序的
mat3x4 m;
vec4 v = m[1]; // v 是矩阵m的第二列向量
三、 OpenGL Transformations
1. 在OpenGL中指定最近和最远的裁剪平面
void glDepthRange(GLclampd near, GLclampd far);
void glDepthRangef(GLclampf near, GLclampf far);
2. 在OpenGL中指定显示区域
void glViewport(GLint x, GLint y, GLint width, GLint height);
3. 多个视口
4. z的精度
使用浮点数来做计算会有精度限制。所以数值上不同的深度坐标最后会有相同的z浮点值。这会造成错误的隐藏物体。
使用透视除法后，z的精度会更加糟糕。随着变换后的深度坐标远离近裁剪平面，它的精度会变小。
下面的链接中，通过图示直观地说明了这个问题。
http://www.songho.ca/opengl/gl_projectionmatrix.html
5. User Clipping
用户裁切是指添加额外的裁切平面。
glEnable(GL_CLIP_PLANE0);
开启第0个裁剪平面
gl_ClipDistance用来指定定点和平面的关系。距离=0表示定点在裁剪平面上，距离>0表示顶点在裁剪平面内
(顶点不会被裁剪)，距离<0表示顶点在裁剪平面外(顶点被裁剪)；
四、 Transform Feedback
1. 简述
Transform feedback是在顶点处理结束以后，在图元装配和光栅化之前。当顶点数据组合为图元时，Transform
feedback捕获这些顶点数据并且可以将他们的属性记录到缓冲区对象中。
2. Transform feedback Objects
transform feedback object封装了实现transform feedback的状态。这些状态包括：
用于保存捕获到的顶点数据的缓冲区、计数索引每个缓冲区有多少满；
标示transform feedback是否是当前激活的。
（1）创建transform feedback 对象名称
void glGenTransformFeedbacks(GLsizei n, GLuint * ids);
（2）创建/绑定transform feedback 对象
void glBindTransformFeedback(GLenum target, GLuint id);
GLboolean glIsTransformFeedback(GLenum id);
（3）删除transform feedback
void glDeleteTransformFeedbacks(GLsizei n, const GLuint ids);
3. Transform Feedback Buffers
void glBindBufferBase(GLenum target, GLuint index, GLuint buffer);
void glBindBufferRange(GLenum target, GLuint index, GLuint buffer, GLintptr offset,GLsizeiptr size);
target GL_TRANSFORM_FEEDBACK_BUFFER
4. Configuring Transform Feedback Varyings
在transform feedback阶段,指定哪些变量会被记录,以及被记录到哪个buffer中
void glTransformFeedbackVaryings(GLuint program, GLsizei count,const GLchar ** varyings, GLenum bufferMode);
bufferMode
GL_INTERLEAVED_ATTRIBS
GL_SEPARATE_ATTRIBS
注意上面的代码需要在glLinkProgram()之前调用。
gl_SkipComponents1, gl_SkipComponents2, gl_SkipComponents3, gl_SkipComponents4, and gl_NextBuffer.
5. 开始、停止Transform Feedback
void glBeginTransformFeedback(GLenum primitiveMode);
void glPauseTransformFeedback(void);
void glResumeTransformFeedback(void);
void glEndTransformFeedback(void);
6. 离子系统
实现离子系统




















