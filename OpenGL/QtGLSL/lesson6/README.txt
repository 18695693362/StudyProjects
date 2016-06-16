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
（3）选择激活的纹理绑定点（纹理单元）
默认激活的纹理绑定点为GL_TEXTURE0
void glActiveTexture(GLenum texture);
texture GL_TEXTURE0-GL_TEXTUREi
GL_MAX_COMBINED_ TEXTURE_IMAGE_UNITS 用来查询支持的最大纹理单元数目
同一个纹理对象可以同步绑定到多个纹理绑定点。
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
使用QImage可以加载图片。
QImage temp(GLHelper::GetAbsPathRelativeGResPath("wall.jpg").c_str());
QImage image = temp.convertToFormat(QImage::Format_RGB888);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(),0, GL_RGB, GL_UNSIGNED_BYTE, image.bits());

5. Retrieving Texture Data
可以将贴图中的数据读到应用程序内存或一个buffer对象。
void glGetTexImage(GLenum target, GLint lod, GLenum format, GLenum type, GLvoid* image);
target - GL_TEXTURE_1D, GL_TEXTURE_2D, GL_TEXTURE_3D, GL_TEXTURE_1D_ARRAY, GL_TEXTURE_2D_ARRAY, GL_TEXTURE_CUBE_MAP_ARRAY,
GL_TEXTURE_RECTANGLE. GL_TEXTURE_CUBE_MAP_POSITIVE_X, GL_TEXTURE_CUBE_MAP_NEGATIVE_X, GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, GL_TEXTURE_CUBE_MAP_POSITIVE_Z, and GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
读入image中的数据大小是由target、format和type决定的。
通常来讲将数据读入应用程序不是高效的操作，如果必须要读取贴图数据，应该讲数据读到buffer对象中，然后将buffer映射到应用程序中。

6. Texture Data Layout
大多数情况图片数据是从左到右，从上到下在内存贴图图元之间紧密排列。
可以通过下面的函数来指定图片数据的排列方式：
void glPixelStorei(GLenum pname, GLint param);
void glPixelStoref(GLenum pname, GLfloat param);
pname - GL_UNPACK_ROW_LENGTH, GL_UNPACK_SWAP_BYTES, GL_UNPACK_SKIP_PIXELS, GL_UNPACK_SKIP_ROWS, GL_UNPACK_SKIP_IMAGES,
GL_UNPACK_ALIGNMENT, GL_UNPACK_IMAGE_HEIGHT, or GL_UNPACK_LSB_FIRST
GL_PACK_ROW_LENGTH, GL_PACK_SWAP_BYTES, GL_PACK_SKIP_PIXELS, GL_PACK_SKIP_ROWS, GL_PACK_SKIP_IMAGES,
GL_PACK_ALIGNMENT, GL_PACK_IMAGE_HEIGHT, or GL_PACK_LSB_FIRST
unpack  参数用来指定OpenGL如何从应用程序内存或绑定到GL_PIXEL_UNPACK_BUFFER的缓冲区读取数据（glTexSubImage2D）。
packing 参数用来指定OpenGL如何将贴图数据写入内存（glGetTexImage）.

六、 Sampler Objects
1. 简述
贴图可以通过关联到贴图单元的一个sampler变量来读取，并运用GLSL内置的函数从贴图图片来获取贴图图元。
sampler对象中保存了获取图元方式的相关参数。sampler对象被绑定到sampler单元。
贴图对象包含一个内置的sampler对象，如果没有sampler对象绑定到对应的sampler单元，则该默认sampler对象用来贴图数据读取。
（1）创建sampler对象名称
void glGenSamplers(GLsizei count, GLuint *samplers);
（2）创建/绑定sampler对象到sampler单元
void glBindSampler(GLuint unit, GLuint sampler);
unit为sampler单元的索引。如果sampler为0，则清除sampler单元上绑定的所有sampler对象
GLboolean glIsSampler(GLenum id);
glBindTexture 和 glBindSampler的不同之处：
--1-- glBindSampler没有target参数。因为sampler对象没有维度一说，所以没必要区别不同类型的sampler对象类型。
--2-- glBindSampler有unit参数，没有对应的glActiveSampler函数。glActiveTexture的参数为GL_TEXTURE0-GLTEXTURi的常数，i的最大值是由实现定义的。
unit是一个无符号整数，允许任意数目的sampler单元。
（3）删除sampler object
void glDeleteSamplers(GLsizei count, const GLuint *samplers );

2. Sampler Parameters
void glSamplerParameter{fi}(GLuint sampler, GLenum pname, Type param );
void glSamplerParameter{fi}v(GLuint sampler, GLenum pname, const Type* param );
void glSamplerParameterI{i ui}v(GLuint sampler, GLenum pname,const Type* param );
下面的函数用来设置贴图当前关联的sampler object的参数
void glTexParameter{fi}(GLenum target, GLenum pname, Type param );
void glTexParameter{fi}v(GLenum target, GLenum pname, const Type *param );
void glTexParameterI{i ui}v(GLenum target, GLenum pname, const Type *param );

七、 Using Textures
在shader中通过有维度类型的sampler变量来表示的。每个sampler变量由贴图对象和sampler对象组成，贴图对象包含了一组图片数据，
sampler对象包含了一组采样参数。贴图对象被绑定到贴图单元，sampler对象被绑定到对应的sampler单元。使用GLSL的内置函数texture
可以通过贴图对象和sampler对象来访问贴图数据。
gvec4 texture(gsampler1D tex, float P[, float bias]);
gvec4 texture(gsampler2D tex, vec2 P[, float bias]);
gvec4 texture(gsampler3D tex, vec3 P[, float bias]);
gvec4 texture(gsamplerCube tex, vec3 P[, float bias]);
gvec4 texture(gsampler1DArray tex, vec2 P[, float bias]);
gvec4 texture(gsampler2DArray tex, vec3 P[, float bias]);
gvec4 texture(gsampler2DRect tex, vec2 P);
gvec4 texture(gsamplerCubeArray tex, vec4 P[, float bias]);
gvec4 为vec4, ivec4, or uvec4
gsampler2D 为sampler2D, isampler2D

1. Texture Coordinates
一个贴图被认为在每个维度上占据了从0。0到1.0的区域。如果贴图坐标在[0.0,1.0]范围外，贴图坐标需要被修改使他们回到[0.0,1.0]范围。
OpenGL通过下面的采样参数来控制修改贴图坐标的行为：
GL_TEXTURE_WRAP_S 控制s轴数据的修改
GL_TEXTURE_WRAP_T 控制t轴数据的修改
GL_TEXTURE_WRAP_R 控制r轴数据的修改
下面的参数指定了具体修改方式：
GL_CLAMP_TO_EDGE
GL_CLAMP_TO_BORDER
GL_REPEAT
GL_MIRRORED_REPEAT
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

2. Arranging Texture Data
static const GLenum abgr_swizzle[] =
{
     GL_ALPHA, GL_RED, GL_GREEN, GL_BLUE
};
// Bind the ABGR texture
glBindTexture(GL_TEXTURE_2D, abgr_texture);
// Set all four swizzle parameters in one call to glTexParameteriv
glTexParameteriv( GL_TEXTURE_2D,
                  GL_TEXTURE_SWIZZLE_RGBA,
                  abgr_swizzle);
// Now bind the RGBx texture
glBindTexture(GL_TEXTURE_2D, rgbx_texture);
// We’re only setting the GL_TEXTURE_SWIZZLE_A parameter here
// because the R, G, and B swizzles can be left as their default values.
glTexParameteri( GL_TEXTURE_2D,
                 GL_TEXTURE_SWIZZLE_A,
                 GL_ONE);

3. Using Multiple Textures
为了使用多个纹理，需要在shader中声明多个uniform sampler变量。每个变量会索引不同的纹理单元。
通过glGetUniformLocation()可以获得uniform sampler变量
使用glUniform1i()可以修改uniform sampler变量的值。
使用多个纹理的步骤：
（1）激活每个使用的纹理单元，并将纹理对象绑定到该纹理单元
glActiveTexture()
glBindTexture()
（2）设置sampler变量的值为纹理单元的索引
glUniform1i()
e.g:
 glUseProgram(prog);
 // For the first texture, we will use texture unit 0...
 // Get the uniform location
 GLint tex1_uniform_loc = glGetUniformLocation(prog, "tex1");
 // Set it to 0
 glUniform1i(tex1_uniform_loc, 0);
 // Select texture unit 0
 glActiveTexture(GL_TEXTURE0);
 // Bind a texture to it
 glBindTexture(GL_TEXTURE_2D, tex1);
 // Repeat the above process for texture unit 1
 GLint tex2_uniform_loc = glGetUniformLocation(prog, "tex2");
 glUniform1i(tex2_uniform_loc, 1);
 glActiveTexture(GL_TEXTURE1);
 glBindTexture(GL_TEXTURE_2D, tex2);

八、 Complex Texture Types
贴图通常为一维或二维图片，但是还有一些其他类型的贴图。例如：3D贴图、贴图数组、立方体映射、阴影、深度-模板以及缓冲区贴图。
1. 3D Textures
3D贴图可以认为是在3D网格中排列的体素。
3D贴图典型应用是在医学图片或流体模拟中的体渲染。

2. Array Textures
有时候需要在一次渲染中访问多个贴图，例如你需要使用一个角色的漫反射贴图、法线贴图、镜面光贴图以及其他的一些属性。如果为每个
贴图使用glBindTexture()会造成性能影响。贴图数组允许你组合一组一维或二维的贴图，他们拥有相同的大小和格式。

3. Cube-Map Textures
立方体映射贴图用于环境贴图。它包含一组图片，并且将他们当做立方体的每个面。正方体的六个面由六个子贴图表示，他们必须是大小相
同的正方形。
Cube-Map贴图的贴图坐标为


九、 Texture Views
十、 Compressed Textures
十一、 Filtering
十二、 Advanced Texture Lookup Functions
十三、 Point Sprites
十四、 Rendering to Texture Maps





















