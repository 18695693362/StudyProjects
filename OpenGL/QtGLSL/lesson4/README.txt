    Color,Pixels and Framebuffers

一、 Basic Color Theory
1. 物理世界的颜色
在物理世界中，光是由光子组成的，用最简单的术语讲，光子是沿直线传播的离子，它拥有自己的“颜色”（其表示了波长或频率）。
可见光的波长范围为390nm-720nm，其中包含了7种颜色：violet indigo blue green yellow orange red。
人眼可以看到不止7种颜色，其实是不同波长光子混合而形成的唯一的颜色。
2. 计算机中的颜色
大部分显示设备只能显示一小部分可见光谱。他们使用主要的三种颜色（红、绿、蓝）来生成可以显示光谱。

二、 Buffers and Their Uses
1. 简述
在OpenGL中可以使用下面几种buffer：Color buffers\ Depth buffer\ Stencil buffer，所有这些buffer组合起来形成
framebuffer。
当应用程序启动时，使用的是default framebuffer.其总是包含一个Color buffer.
(1) Color Buffers
通常绘画到颜色缓冲区中，其中包含了RGB或sRGB颜色数据，以及每个像素的alpha值。一个framebuffer中可能包含多个颜色缓冲区。
default framebuffer的主颜色缓冲区是特殊的颜色缓冲区，它和屏幕上的窗口相关联，将图片显示在屏幕上，其他颜色缓冲区都是离
屏渲染的。
颜色缓存区中的每个像素可以存储一个颜色，或者将该像素分为多个子像素，来执行多重采样反锯齿。
(2) Depth Buffer
深度缓冲区为每个像素保存了深度值，用来决定物体在3维空间中的可见性。
深度值是通过测量到眼睛距离来得到的，拥有更小深度值的像素会覆盖更大生深度的像素。
(3) Stencil Buffer
模板缓冲区用来将绘制限定在特定的区域内。
2. Clearing Buffers
(1) 设置清除缓存的值
void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
void glClearDepth(GLclampd depth);
void glClearDepthf(GLclampf depth);
void glClearStencil(GLint s);
(2) 清除缓存
void glClear(GLbitfield mask);
3. Masking Buffers
OpenGL写数据到开启的颜色、深度、模板缓冲区之前，会在数据上执行掩码操作。
void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
void glColorMaski(GLuint buffer, GLboolean red, GLboolean green, GLboolean blue,GLboolean alpha);
指定某个颜色分量是否可以被写入颜色缓冲区
void glDepthMask(GLboolean flag);
如果flag为GL_TRUE，则深度缓冲区可以写入，否则不可写入。
void glStencilMask(GLuint mask);
void glStencilMaskSeparate(GLenum face, GLuint mask)
指定一个位掩码控制模板缓存区的各个位平面的写入。mask的初始值为全1。

三、 Color and OpenGL
1. 简述
为片段指定颜色的工作是由片段着色器来做的，有很多种方式来做这件事情：
(1) 片段着色器不使用任何额外的数据来生成片段颜色。
(2) 附加的颜色数据被提供给每个顶点，这些数据可能会被顶点着色器修改，然后传递给片段着色器。
片段着色器依据此颜色数据来生成片段颜色
(3) 附加的数据（但不是特定颜色数据）被提供给片段着色器，并且通过计算来生成颜色。
(4) 额外的数据，例如数字图片，在片段着色器中被引用用来查询颜色数据。
2. Color Representation and OpenGL
默认情况下片段着色器接收到的值被当作浮点值，这些值的范围为[0.0,1.0](即标准化的值)，
但这些值被写入到帧缓冲区时会被映射到帧缓存区支持的值的范围。
可以通过glVertexAttribPointer()来指定值是否被标准化。
3. Vertex Color
顶点颜色数据的使用
vertexcolor.h
vertexcolor.cpp
4. Rasterization
光栅化用来决定屏幕上的哪些区域被特定的几何图元覆盖，其结合输入的顶点数据线性插值产生片段着色器中的每个变量。
应用在颜色数据上的线性插值被称作Gouraud shading

四、 Multisampling
1. 简述
多重采样是一种平滑化几何图元边缘的一种技术。通过对每个几何图元的每个像素进行多次采样，对每个像素保存多个样本，
对所有样本进行处理来确定像素的最终颜色。
glGetIntegerv(GL_SAMPLE_BUFFERS)用来检查是否支持多重采样。
glEnable(GL_MULTISAMPLE)开启多重采样
glGetIntegerv(GL_SAMPLES)获取样本的数量
void glGetMultisamplefv(GL_SAMPLE_POSITION, GLuint index, GLfloat *val);
获取索引值为index的样本的地址，该地址的范围为[0,1],表示了样本相对于像素左下角的偏移。与shader中gl_SamplePosition值相同。
在着色器中的使用sample关键字，可以使被修饰的变量依据每个样本的不同地址有对应的细微差别。
2. Sample Shading
glEnable(GL_SAMPLE_SHADING) 可以使片段着色器中的in变量自动依据样本地址插值。
void glMinSampleShading(GLfloat value)
value的范围为[0,1]。1表示每个样本都需要独立被渲染，0表示忽略样本渲染率。

五、 Testing and Operating on Fragments
1. 简述
片段着色器处理片段之后还会进过下面的处理：
（1）Scissor test
（2）Multisample fragment operations
（3）Stencil test
（4）Depth test
（5）Blending
（6）Dithering
（7）Logical operations
2. Scissor Test
void glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
glEnable(GL_SCISSOR_TEST) glDisable(GL_SCISSOR_TEST) 裁剪测试开启控制
3. Multisample Fragment Operations
下面链接详细描述了多重采样的原理
http://learnopengl.com/#!Advanced-OpenGL/Anti-Aliasing
https://learnopengl-cn.readthedocs.io/zh/latest/04%20Advanced%20OpenGL/11%20Anti%20Aliasing/
4. Stencil Test
模板测试需要模板缓冲区，如果不存在模板缓冲区，模板测试则总是通过。
// TODO 实现一个描边效果
5. Depth Test
深度缓存区保存了视点到物体的距离。
（1）Polygon Offset
多边形偏移可用于 渲染固体的高亮边缘、表面贴花、隐藏线移除
glEnable(GL_POLYGON_OFFSET_FILL)
void glPolygonOffset(GLfloat factor, GLfloat units);
开启多边形偏移后，在执行深度测试之前，每个片段的深度值会被添加一个偏移值。偏移值安装下面方法计算：
offset = m * factor + r * units
6. Blending
（1）Blending Factors
Sr,Sg,Sb,Sa表示源混合因子
Dr,Dg,Db,Da表示目标混合因子
Rs,Gs,Bs,As表示源颜色
Rd,Gd,Bd,Ad表示目标颜色
最终的颜色为 SrRs+DrRd, SgGs+DgGd, SbBs+DbBd, SaAs+DaAd
7. Dithering
抖动可以让系统表示更多的颜色。
8. Logical Operations
将输入的片段值（source）和已经存储在颜色缓存区中的片段值（destination）进行逻辑运算。
9. Occlusion Query
深度缓冲区确定了每个像素的可见性。出于性能考虑，如果可以确定一个几何体在渲染之前可以确定它是否可见非常有意义。
遮挡查询可以让你确定一个特定的几何在执行深度测试后是否可见。
使用遮挡查询的步骤：
（1）为你需要的每一个遮挡查询生成一个查询id。
void glGenQueries(GLsizei n,GLuint* ids);
（2）调用glBeginQuery()指定开始遮挡查询
（3）渲染做遮挡测试的几何体
（4）调用glEndQuery()指定遮挡查询完成
（5）获取通过深度测试的片段数据
void glGetQueryObjectiv(GLenum id,GLenum pname,GLint* params)
void glGetQueryObjectuiv(GLenum id, GLenum pname, GLuint *params);
（6）清除遮挡查询对象
void glDeleteQueries(GLsizei n, const GLuint *ids);
10. Conditional Rendering
遮挡查询的一个问题是它需要OpenGL暂停处理几何体和片段，记录深度缓冲区中受影响的片段的数目，
并将改值返回给应用程序。以这种方式停止图形硬件，在性能敏感的应用程序中，会影响到性能。
为了消除暂停OpenGL的操作，条件渲染允许图形硬件来决定是否遮挡查询放弃任何片段，以及期间的渲染命令。
void glBeginConditionalRender(GLuint id, GLenum mode);
id 为遮挡查询对象id
mode 为下列选项之一,用来指定GPU在继续渲染之前，是否等待遮挡查询结果
GL_QUERY_WAIT
GL_QUERY_NO_WAIT
GL_QUERY_BY_REGION_WAIT
GL_QUERY_BY_REGION_WAIT
void glEndConditionalRender(void);

六、 Per-Primitive Antialiasing
1. 简述
可以使用下面的方法来控制图片显示质量和速度的平衡。
void glHint(GLenum target, GLenum hint);
2. Antialiasing Lines
glEnable(GL_LINE_SMOOTH);
glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glHint(GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
3. Antialiasing Polygon
七、 Framebuffer Objects
八、 Writing to Multiple Renderbuffers Simultaneously
九、 Reading and Copying Pixel Data
十、 Copying Pixel Rectangles






















