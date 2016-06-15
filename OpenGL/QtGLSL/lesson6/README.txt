    6 Texture

    通常来讲，计算机图形的目的是为了确定组成图像各个部分的颜色。尽管可以通过一个高级的渲染算法来计算像素的颜色，通常这个复杂的渲染器是不实用的。
我们依赖于贴图（大块的图片数据）来绘制物体的表面，让物体更加真实。

一、 Texture Mapping
贴图是由贴图元素组成的。
使用贴图映射的步骤
（1）创建texture object并加载贴图数据到其中
（2）在顶点中包含贴图坐标
（3）在渲染器中，将每个你想要使用的贴图地图和一个texture sampler关联
（4）在渲染器中，通过texture sampler来获取贴图值

二、 Basic Texture Types
（1）OpenGL提供了很多类型的贴图对象，他们有各种各样的维度以及布局。
每个贴图对象包含了一组图片来组成完整的贴图。每个图片可以是一维、二维、三维的图元数组，并且多个图片可以堆叠形成mipmap金字塔。
贴图数组可以包含一维或二维切片。正方体映射是一种特殊的贴图数组，它包含六个切片。
（2）贴图可用于实现表面多重采样。
（3）贴图通过texture units绑定到OpenGL上下文。用GL_TEXTURE0、GL_TEXTUREi来表示绑定点。
（4）绑定到OpenGL上下文的贴图可以通过sampler variables来访问。
下表为贴图类型和采样变量类型的对应关系
Target GL_TEXTURE*          Sampleler Type          Dimensionality
1D                          sampler1D               1D
1D_ARRAY                    sampler1DArray          1D array
2D                          sampler2D               2D
2D_ARRAY                    sampler2DArray          2D array
2D_MULTISAMPLE              sampler2DMS             2D multisample
2D_MULTISAMPLE_ARRAY        sampler2DMSArray        2D multisample array
3D                          sampler3D               3D
CUBE                        samplerCube             cube-map texture
ARRAY                       samplerCubeArray        cube-map array
RECTANGLE                   samplerRect             2D rectangle
BUFFER                      samplerBuffer           1D buffer

三、 Creating and Initializing Textures
（1）生成贴图对象名称
void glGenTextures(GLsizei n, GLuint *textures);
（2）创建/绑定贴图对象到激活的纹理单元
void glBindTexture(GLenum target, GLuint texture);
target GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_RECTANGLE,
GL_TEXTURE_BUFFER, GL_TEXTURE_CUBE_MAP, GL_TEXTURE_CUBE_MAP_ARRAY, GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_2D_MULTISAMPLE_ARRAY
判断纹理名称是否为纹理对象
GLboolean glIsTexture(GLuint texture);
（3）选择激活的纹理绑定点
默认激活的纹理绑定点为GL_TEXTURE0
void glActiveTexture(GLenum texture);
texture GL_TEXTURE0-GL_TEXTUREi
GL_MAX_COMBINED_ TEXTURE_IMAGE_UNITS 用来查询支持的最大纹理单元数目
（4）删除纹理对象
void glDeleteTextures(GLsizei n, const GLuint *textures);
（5）为纹理对象指定存储空间和数据
void glTexStorage1D(GLenum target, GLsizei levels,GLenum internalFormat, GLsizei width);
    target 必须为 GL_TEXTURE_1D
    internalFormat 为 OpenGL用于存储内部贴图数据的格式
void glTexStorage2D(GLenum target, GLsizei levels,GLenum internalFormat, GLsizei width, GLsizei height);
void glTexStorage3D(GLenum target, GLsizei levels,GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth)
void glTexStorage2DMultisample(GLenum target, GLsizei samples,GLenum internalFormat,
GLsizei width, GLsizei height, GLboolean fixedsamplelocations);
void glTexStorage3DMultisample(GLenum target, GLsizei samples,GLenum internalFormat,
GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
尽管最好的实践是声明不变的贴图存储，但是允许贴图对象改变尺寸以及格式是可以支持的。
下面的方法指定了可变的纹理
void glTexImage1D(GLenum target, GLint level,GLint internalFormat, GLsizei width,GLint border, GLenum format, GLenum type,
const void *data);
    format 为 应用程序提供的数据的格式
void glTexImage2D(GLenum target, GLint level,GLint internalFormat, GLsizei width,GLsizei height, GLint border, GLenum format,
GLenum type, const void *data);
void glTexImage3D(GLenum target, GLint level,GLint internalFormat, GLsizei width,GLsizei height, GLsizei depth, GLint border,
GLenum format, GLenum type, const void *data);
void glTexImage2DMultisample(GLenum target, GLenum samples,GLint internalFormat,GLsizei width, GLsizei height,
GLboolean fixedsamplelocations);
void glTexImage3DMultisample(GLenum target, GLenum samples,GLint internalFormat,GLsizei width, GLsizei height, GLsizei depth,
GLboolean fixedsamplelocations);
￼
因为多重采样贴图的数据不能被初始化，glTexSubImage2D()也不能用来更新多重采样贴图的内容。将数据载入多重采样贴图的唯一方法是将多重采样贴图和一个
framebuffer对象相关联，然后将数据渲染到其中。
（6）Texture Formats
internal format 为 OpenGL用于存储内部贴图数据的格式。应用程序提供的数据会被转化为这种类型。
Sized Internal Format       Base Internal Format        R Bits          G Bits          B Bits          A Bits
GL_R8                       GL_RED                      8
GL_R8_SNORM                 GL_RED                      s8
GL_R16                      GL_RED                      16
GL_R16_SNORM                GL_RG                       s16
GL_RG8                      GL_RG                       8               8
....
external format 为 应用程序提供的数据的格式。
Format                  Components Present
GL_RED                  Red
GL_GREEN                Green
GL_BLUE                 Blue
GL_RG                   Red, Green
GL_RGB                  Red, Green, Blue
GL_RGBA                 Red, Green, Blue, Alpha
....

四、 Proxy Textures
每一类纹理类型都有与之对应的代理纹理。代理纹理用来测试OpenGL实现的能力。

五、 Specifying Texture Data
1. Explicitly Setting Texture Data
void glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format,GLenum type, const void *data);
void glTexSubImage2D(GLenum target, GLint level, GLint xoffset,GLint yoffset, GLsizei width, GLsizei height, GLenum format,
GLenum type, const void *data);
void glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset,GLsizei width, GLsizei height,
GLsizei depth, GLenum format, GLenum type, const void *data);
￼
2. Using Pixel Unpack Buffers
当没有buffer对象绑定到GL_PIXEL_UNPACK_BUFFER时，glTexSubImage**()函数的data参数指定了数据的地址。
当有buffer对象绑定到GL_PIXEL_UNPACK_BUFFER时，glTexSubImage**()函数的data参数指定了绑定到GL_PIXEL_UNPACK_BUFFER的buffer的偏移量。
使用buffer对象来指定贴图数据的优势是，传递数据到贴图不需要立即执行，直到在渲染器中访问数据。这样数据的传输就可以和应用程序的运行同步进行了。
3. Copying Data from the Frambuffer
可以读取frambuffer的部分数据到贴图对象。
void glCopyTexImage1D(GLenum target, GLint level,GLint internalFormat, GLint x, GLint y,GLsizei width, GLint border);
void glCopyTexImage2D(GLenum target, GLint level,GLint internalFormat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
void glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y,GLsizei width);
void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset,GLint x, GLint y, GLsizei width,GLsizei height);
void glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset,GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height);
虽然可以将framebuffer的数据读取到贴图对象，但是更高效的方式是直接将数据渲染到贴图对象中。
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
void glFramebufferTexture1D(GLenum target, GLenum attachment,GLenum texturetarget,GLuint texture, GLint level);
void glFramebufferTexture2D(GLenum target,GLenum attachment, GLenum texturetarget, GLuint texture, GLint level);
void glFramebufferTexture3D(GLenum target, GLenum attachment,GLenum texturetarget, GLuint texture, GLint level, GLint layer);
4. Loading Images from Files

六、 Sampler Objects
七、 Using Textures
八、 Complex Texture Types
九、 Texture Views
十、 Compressed Textures
十一、 Filtering
十二、 Advanced Texture Lookup Functions
十三、 Point Sprites
十四、 Rendering to Texture Maps





















