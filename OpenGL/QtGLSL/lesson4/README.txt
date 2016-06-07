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
光栅化用来决定

四、 Multisampling
五、 Testing and Operating on Fragments
六、 Per-Primitive Antialiasing
七、 Framebuffer Objects
八、 Writing to Multiple Renderbuffers Simultaneously
九、 Reading and Copying Pixel Data
十、 Copying Pixel Rectangles
