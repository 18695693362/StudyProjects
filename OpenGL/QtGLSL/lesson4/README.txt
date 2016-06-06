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
2. Color Buffers
通常绘画到颜色缓冲区中，其中包含了RGB或sRGB颜色数据，以及每个像素的alpha值。一个framebuffer中可能包含多个颜色缓冲区。
default framebuffer的主颜色缓冲区是特殊的颜色缓冲区，它和屏幕上的窗口相关联，将图片显示在屏幕上，其他颜色缓冲区都是离
屏渲染的。
颜色缓存区中的每个像素可以存储一个颜色，或者将该像素分为多个子像素，来执行多重采样反锯齿。
3. Depth Buffer
深度缓冲区为每个像素保存了深度值，用来决定物体在3维空间中的可见性。
深度值是通过测量到眼睛距离来得到的，拥有更小深度值的像素会覆盖更大生深度的像素。
4. Stencil Buffer
模板缓冲区用来将绘制限定在特定的区域内。

三、 Color and OpenGL
四、 Multisampling
五、 Testing and Operating on Fragments
六、 Per-Primitive Antialiasing
七、 Framebuffer Objects
八、 Writing to Multiple Renderbuffers Simultaneously
九、 Reading and Copying Pixel Data
十、 Copying Pixel Rectangles
