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
glBindTexture 和 glBindSampler的不同之处： //void glBindTexture(GLenum target, GLuint texture);
--1-- glBindSampler没有target参数。因为sampler对象没有维度一说，所以没必要区别不同类型的sampler对象类型。
--2-- glBindSampler有unit参数，没有对应的glActiveSampler函数。glActiveTexture的参数为GL_TEXTURE0-GLTEXTURi的常数，i的最大值是由实现定义的。
unit是一个无符号整数，允许任意数目的sampler单元。
（3）删除sampler object
void glDeleteSamplers(GLsizei count, const GLuint *samplers );

2. Sampler Parameters
void glSamplerParameter{fi}(GLuint sampler, GLenum pname, Type param );
void glSamplerParameter{fi}v(GLuint sampler, GLenum pname, const Type* param );
void glSamplerParameterI{i ui}v(GLuint sampler, GLenum pname,const Type* param );
下面的函数用来设置贴图关联的默认的sampler object的参数
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
一个贴图被认为在每个维度上占据了从0.0到1.0的区域。如果贴图坐标在[0.0,1.0]范围外，贴图坐标需要被修改使他们回到[0.0,1.0]范围。
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
Cube-Map贴图的贴图坐标为(x,y,z) 一个中心点在原点的单位立方体其表面的点的坐标和Cube-Map的贴图坐标一一对应。
（1）Skybox
（2）Environment Map
（3）无缝Cube-Map
可以使用glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS)来消除立方体各个面连接处明显的接缝

4. Shadow Samplers
在GLSL中提供了一种特殊的采样器即shadow sampler。shadow sampler 在贴图坐标中使用了额外的分量，用来和获取到
的贴图值进行比较。
使用shadow sampler时，从texture()返回的值在[0.0,1.0]范围内，指示了通过比较操作的贴图值的部分。
对于采样只有一个纹理值（使用了GL_NEAREST过滤模式，没有mipmaps，每个贴图图元只有一个采样）的情况下，返回值为
0.0或1.0。0.0表示没有通过比较操作，1.0表示通过了比较操作。
如果多个图元用来构造返回给shader的值（使用了线性过滤模式，或者使用了多重采样贴图），返回值为[0.0,1.0]范围内的
任何值，该值依赖于通过比较操作的贴图图元的数目。
float texture(gsampler1DShadow tex, vec3 P[, float bias]);
float texture(gsampler2DShadow tex, vec3 P[, float bias]);
float texture(gsamplerCubeShadow tex, vec4 P[, float bias]);
float texture(gsampler1DArrayShadow tex, vec3 P[, float bias]);
float texture(gsampler2DArrayShadow tex, vec4 P[, float bias]);
float texture(gsampler2DRectShadow tex, vec3 P);
float texture(gsamplerCubeArrayShadow tex, vecP P, float compare);
开启关闭比较函数
glSamplerParameteri(sampler,GL_TEXTURE_COMPARE_MODE,GL_COMPARE_REF_TO_TEXTURE)
glSamplerParameteri(sampler,GL_TEXTURE_COMPARE_MODE,GL_NONE)
设置比较函数
glSamplerParameteri(sampler,GL_TEXTURE_COMPARE_FUNC,func)
func 为GL_LEQUAL, GL_GEQUAL, GL_LESS, GL_GREATER, GL_EQUAL, GL_NOTEQUAL, GL_ALWAYS, or GL_NEVER

5. Depth-Stencil Textures
贴图除了可以保存图片数据，通过使用GL_DEPTH_STENCIL贴图格式，还可以保存深度和模板值。
默认情况下着色器会读取深度值(GL_DEPTH_COMPONENT)，通过下面函数可以设置着色器来读取模板值(GL_STENCIL_COMPONENTS)
void glTexParameteri(GLenum target​, GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_COMPONENTS);

6. Buffer Textures
buffer textures是一种特殊的贴图类型，它可以让着色器访问一个buffer对象，将这个buffer对象当做一个很大的一维贴图。
buffer textures通过glTexParameteri()设置参数，它没有内置的才采样器并且采样对象对于它是无效的。
buffer textures和一维贴图的主要区别为：
（1）一维贴图的尺寸限制为GL_MAX_ TEXTURE_SIZE，而buffer textures的尺寸限制为GL_MAX_TEXTURE_BUFFER_SIZE。
（2）一维贴图支持过滤、mipmaps、纹理坐标包装以及其他的采样器参数。而buffer textures都不支持。
（3）一维贴图的贴图坐标是标准化的浮点值，而buffer textures使用非标准化的整数贴图坐标。

关联buffer对象和贴图对象
oid glTexBuffer(GLenum target, GLenum internalFormat, GLuint buffer);
void glTexBufferRange(GLenum target, GLenum internalFormat, GLuint buffer, GLintptr offset,
GLsizeiptr size);

在着色器中访问buffer textures
vec4 texelFetch(samplerBuffer s, int coord);
ivec4 texelFetch(isamplerBuffer s, int coord);
uvec4 texelFetch(usamplerBuffer s, int coord);

e.g:
// Buffer to be used as the data store
 GLuint buf;
 // Texture to be used as a buffer texture
 GLuint tex;
// Data is located somewhere else in this program extern const GLvoid* data;
 // Generate, bind, and initialize a buffer object
 // using the GL_TEXTURE_BUFFER binding. Assume we’re
 // going to use one megabyte of data here.
 glGenBuffers(1, &buf);
 glBindBuffer(GL_TEXTURE_BUFFER,  buf);
 glBufferData(GL_TEXTURE_BUFFER,  1024 * 1024,
              data, GL_STATIC_DRAW);
 // Now create the buffer texture and associate it
 // with the buffer object.
 glGenTextures(1, &tex);
 glBindTexture(GL_TEXTURE_BUFFER, tex);
 glTexBuffer(GL_TEXTURE_BUFFER, GL_R32F, buf);

#version 330 core
uniform samplerBuffer buf
in int buf_tex_coord;
layout (location = 0) out vec4 color;
void main(void)
{
     color = texelFetch(buf, tex_coord);
}

九、 Texture Views
OpenGL允许多个贴图公用一个数据存储。
首先 创建一个贴图将其初始化为大小不可变的。
其次 创建一个贴图的贴图视图。
void glTextureView(GLuint texture, GLenum target,GLuint origTexture, GLenum internalFormat,
GLuint minLevel, GLuint numLevels, GLuint minLayer, GLuint numLayers);
target 和 origTexture必须匹配
Original Target(GL_TEXTURE*)        Compatible Targets(GL_TEXTURE*)
1D                                  1D,1D_ARRAY
2D                                  2D,2D_ARRAY
.......
internalFormat 也必须和 origTexture的internalFormat匹配
OriginalTarget          CompatibleTargets
128-bit                 GL_RGBA32F,GL_RGBA32UI,GL_RGBA32I
......

创建了贴图的视图以后，可以在任何可以使用贴图的地方使用贴图视图，包括图片加载和存储或者帧缓存附件，还可以创建
贴图视图的贴图视图，每个视图都会保存一个到原始数据存储的引用。删除原始的贴图也是合法的。只要有一个数据的视图
存在，真实的数据就不会被删除。

e.g 1: Creating a Texture View with a New Format
// Create two texture names - one will be our parent,
 // one will be the view
 GLuint tex[2];
 glGenTextures(2, &tex);
 // Bind the first texture and initialize its data store
 // Here, the store will be 1024 x 1024 2D texture with
 // mipmaps and the format will be GL_RGB8 - 8-bits per
 // component RGB, unsigned normalized
 glBindTexture(GL_TEXTURE_2D, tex[0]);
 glTexStorage2D(GL_TEXTURE_2D, 10, GL_RGB8, 1024, 1024);
// Now,.create a view of the texture, this time using // GL_RGB8UI so as to receive the raw data from the texture
glTextureView(tex[1],           // New texture view
              GL_TEXTURE_2D,    // Target for the new view
              tex[0],           // Original texture
              GL_RGB8UI,        // New format
              0, 10,            // All mipmaps
              0, 1);            // Only one layer

e.g 2: Creating a Texture View with a New Target
// Create two texture names - one will be our parent,
 // one will be the view
 GLuint tex[2];
 glGenTextures(2, &tex);
// Bind the first texture and initialize its data store
// We are going to create a 2D array texture with a layer
// size of 256x256 texels and 100 layers.
glBindTexture(GL_TEXTURE_2D_ARRAY, tex[0]);
glTexStorage3D(GL_TEXTURE_2D_ARRAY, 8, GL_RGAB32F, 256, 256, 100);
 // Now,.create a GL_TEXTURE_2D view of the texture,
 // extracting a single slice from the middle of the array
glTextureView(tex[1],           // New texture view
              GL_TEXTURE_2D,    // Target for the new view
              tex[0],           // Original texture
              GL_RGBA32F,       // Same format as original texture
              0, 8,             // All mipmaps
              50, 1);           // Only one layer

十、 Compressed Textures
有两种方法可以将压缩数据放入OpenGL。
第一种方法是让OpenGL为你压缩数据。这种情况下你提供非压缩数据，但是指定一种
压缩类型的内部格式。OpenGL实现会获取原始未压缩数据然后对其进行压缩。因为这是实时的过程，所以OpenGL通常会实
现一个比较简单的算法从而可以快速压缩数据，导致压缩图片质量比较低。
第二种方法是离线压缩数据，然后将压缩过的数据直接传递给OpenGL。使用这种方法，你可以花足够的时间来达到想要的图
片质量而不牺牲运行时性能。
有很多种压缩算法和压缩格式，并且不同的硬件和OpenGL实现会支持不同的格式。为了确定你的OpenGL实现支持哪些格式，
你需要检查扩展的实现列表。
OpenGL会保证支持两种家族格式。RGTC(Red-Green贴图压缩格式)和BPTC(Block Partitioned贴图压缩格式)。两种
格式都是基于块的并且将图元以4x4的图元块为单位存储，每一个都独立压缩。这样的数据块很容易被硬件解压。

使用离线压缩图片时，可使用下面的方法指定可变的存储
void glCompressedTexImage1D(GLenum target, GLint level, GLenum internalFormat,
GLsizei width, GLint border, GLsizei imageSize, const void *data);
......

使用离线压缩图片时，更新压缩贴图的部分数据
void glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width,
GLenum format, GLsizei imageSize, const void *data);
......

十一、 Filtering
1. 简述
贴图映射可以是直线、正方形、矩形甚至是3，贴图被映射到一个多边形或表面并且被转换为屏幕坐标后，贴图的每个独立的图元
很少会直接对应屏幕图片的每个独立的像素。依赖于使用的变换以及应用的贴图映射，屏幕上的一个像素可能对应一个贴图图元的
一小部分，或者一组图元的集合。

2. Linear Filtering
只要贴图的采样率相对于图片的尖峰数据足够高，线性重建的图片依然会有相当高的质量。
OpenGL获得你传递给它的贴图坐标，并且查找两个最靠近的样本。依据到这两个点的距离为这两个样本创建权值，然后使用它们的
权值来创建一个平均权值。
线性过滤不仅可用于1D 2D 3D贴图，它还可用于邻接的mipmap。
GL_TEXTURE_MAG_FILTER和GL_TEXTURE_MIN_FILTER这两个参数控制OpenGL如何过滤贴图。
贴图被放大时使用GL_TEXTURE_MAG_FILTER参数的配置。需求的贴图分辨率比最高分辨率的mipmap(level0)高.
贴图被缩小是使用GL_TEXTURE_MIN_FILTER参数的配置。

3. Using and Generating Mipmaps
GL_TEXTURE_MIN_FILTER参数控制着，当mipmap level比0大时，贴图图元如何创建。
GL_NEAREST和GL_LINEAR设置会关闭mipmapping，OpenGL只会使用level0贴图。
GL_NEAREST_MIPMAP_NEAREST、GL_NEAREST_MIPMAP_LINEAR、GL_LINEAR_MIPMAP_NEAREST、GL_LINEAR_MIPMAP_LINEAR设
置会启用mipmapping。GL_A_MIPMAP_B,A控制如何创建每个level-mipmap的图元。NEAREST表示取最近的图元，LINEAR表示线性插值
获得图元；B控制如何将这些样本混合。NEAREST表示只使用最近level的mipmap，LINEAR表示取两个最近的mipmap进行线性插值。
Tips:
GL_TEXTURE_MAG_FILTER的默认值为GL_LINEAR，GL_TEXTURE_MIN_FILTER的默认值为GL_LINEAR_MIPMAP_LINEAR。所以默认情况
下回启用mipmapping。使用mipmapping要求完整的mipmap集合，即所有level的mipmap都必须存在，如果没有完整的mipmap，shader
中会返回无用的贴图数据。

为了使用mipmapping，你必须提供所有2的幂尺寸的贴图，这些2的幂尺寸的贴图尺寸范围为1x1到贴图最大尺寸。
如果你不想使用mipmapping一直到1x1大小的贴图，你可以设置GL_TEXTURE_MAX_LEVEL来指定你提供的最大level。
如果最高分辨率level的贴图不是正方形，在生成mipmap时，尺寸小的那个维度将比另一个维度在尺寸上先变为1.此时会继续生成mipmap，
直到另一维度的尺寸也变为1.例如：最高分辨率的图片为64x16,会生成32x8,16x4,8x2,4x1,2x1,1x1尺寸的mipmap。

OpenGL支持自动生成mipmap，但是该实现被设计为效率优先于质量，而且不同的实现之间有很大不同。所以当需要高质量，结果一致的时候
最好自己生成mipmap。
void glGenerateMipmap(GLenum target);

4. Calculating the Mipmap Level

λbase (x, y) = log2 [ρ (x, y)]
λ′ (x, y) = λbase + clamp(biastexobj + biasshader)

λ = lodmax,     λ′ > lodmax
λ = λ′,         lodmin ≤ λ′ ≤ lodmax
λ = lodmin,     λ′ < lodmin
λ = undefined,  lodmin > lodmax

lodmin 通过 GL_TEXTURE_MIN_LOD来设置
lodmax 通过 GL_TEXTURE_MAX_LOD来设置

5. Mipmap Level-of-Detail Control
GL_TEXTURE_BASE_LEVEL指定mipmap的最低等级，即指定最高分辨率的mipmap等级
GL_TEXTURE_MAX_LEVEL指定mipmap的最高等级，即指定最低分辨率的mipmap等级

贴图流的使用：
使用贴图流时，存储完整贴图对象的空间是通过glTexStorage2D()来申请的，但是初始化数据没有载入，当应用程序运行时，新的对象出现
时，他的贴图数据以从最低分辨率mipmap到最高分辨率mipmap的顺序进行加载。GL_TEXTURE_BASE_LEVEL的值被设置为到目前为止载入的
最高分辨率的mipmap的level。这样的话当越来越多的贴图数据载入，屏幕上的物体会越来越清晰。

十二、 Advanced Texture Lookup Functions
1. Explicit Level of Detial
下面函数可以对指定level的texture进行采样
gvec4 textureLod(gsampler1D tex, float P, float lod);
gvec4 textureLod(gsampler2D tex, vec2 P, float lod);
gvec4 textureLod(gsampler3D tex, vec3 P, float lod);
gvec4 textureLod(gsamplerCube tex, vec3 P, float lod);
gvec4 textureLod(gsampler1DArray tex, vec2 P, float lod);
gvec4 textureLod(gsampler2DArray tex, vec3 P, float lod);
gvec4 textureLod(gsampler2DRect tex, vec2 P, float lod);
gvec4 textureLod(gsamplerCubeArray tex, vec4 P, float lod);

2. Explicit Gradient Specification
可以通过下面的函数，覆盖mipmapping的level-of-detail计算。
gvec4 textureGrad(gsampler1D tex, float P,float dPdx, float dPdy);
gvec4 textureGrad(gsampler2D tex, vec2 P,vec2 dPdx, vec2 dPdy);
gvec4 textureGrad(gsampler3D tex, vec3 P,vec3 dPdx, vec3 dPdy);
gvec4 textureGrad(gsamplerCube tex, vec3 P,vec3 dPdx,vec3 dPdy);
gvec4 textureGrad(gsampler1DArray tex, vec2 P,float dPdx,float dPdy);
gvec4 textureGrad(gsampler2DArray tex, vec3 P,vec2 dPdx,vec2 dPdy);
gvec4 textureGrad(gsamplerCubeArray tex, vec4 P,vec3 dPdx,vec3 dPdy);

3. Texture Fetch with Offsets
gvec4 textureOffset(gsampler1D tex, float P, int offset, [float bias]);
gvec4 textureOffset(gsampler2D tex, vec2 P, ivec2 offset, [float bias]);
gvec4 textureOffset(gsampler3D tex, vec3 P, ivec3 offset, [float bias]);
gvec4 textureOffset(gsampler1DArray tex, vec2 P, int offset, [float bias]);
gvec4 textureOffset(gsampler2DArray tex, vec3 P, ivec2 offset, [float bias]);
gvec4 textureOffset(gsampler2DRect tex, vec2 P, ivec2 offset, [float bias]);
在执行获取图元之前会偏移offset个图元。

4. Projective Texturing
gvec4 textureProj(gsampler1D tex, vec2 P[, float bias);
gvec4 textureProj(gsampler1D tex, vec4 P[, float bias);
gvec4 textureProj(gsampler2D tex, vec3 P[, float bias);
gvec4 textureProj(gsampler2D tex, vec4 P[, float bias);
gvec4 txtureProj(gsampler3D tex, vec4 P[, float bias);
gvec4 textureProj(gsamplerRect tex, vec3 P);
gvec4 textureProj(gsamplerRect tex, vec4 P);

5. Texture Queries in Shaders
下面的函数返回mipmap信息，返回值为vec2类型，x中保存了被访问的mipmap数组。y返回了mipmap的基础level。
vec2 textureQueryLod(gsampler1D sampler,float P);
vec2 textureQueryLod(gsampler2D sampler,vec2 P);
vec2 textureQueryLod(gsampler3D sampler,vec3 P);
......
下面的函数返回样本包含的mipmap等级数量
int textureQueryLevels(gsampler1D tex);
int textureQueryLevels(gsampler2D tex);
int textureQueryLevels(gsampler3D tex);
......
下面的函数返回贴图的尺寸
int textureSize(gsampler1D tex, int lod);
ivec2 textureSize(gsampler2D tex, int lod);
ivec3 textureSize(gsampler3D tex, int lod);
......

6. Gathering Texels
gvec4 textureGather(gsampler2D tex, vec2 P[, int comp]);
从贴图获取四个贴图图元，comp指定要获取的分量。0，1，2，3分别对应x,y,z,w
textureGather的返回值:
vec4(Sample_i0_j1(P, base).comp,
     Sample_i1_j1(P, base).comp,
     Sample_i1_j0(P, base).comp,
     Sample_i0_j1(P, base).comp);

7. Combining Special Functions
组合多个特性的贴图函数
textureProjLod
textureProjGrad
......

十三、 Point Sprites
点精灵本质上是使用片段着色器渲染OpenGL点，点中的片段坐标可以通过gl_PointCoord获取到。
1. Texutred Point Sprites
-- vertex shader --
uniform mat4 model_matrix;
uniform mat4 projection_matrix;
layout (location = 0) in vec4 position;
void main(void)
{
     vec4 pos = projection_matrix * (model_matrix * position);
     gl_PointSize = (1.0 - pos.z / pos.w) * 64.0;
     gl_Position = pos;
}
-- fragment shader --
uniform sampler2D sprite_texture;
out vec4 color;
void main(void)
{
     color = texture(sprite_texture, gl_PointCoord);
}

2. Analytic Color and Shape
out vec4 color;
void main(void)
{
    const vec4 color1 = vec4(0.6, 0.0, 0.0, 1.0);
    const vec4 color2 = vec4(0.9, 0.7, 1.0, 0.0);
    vec2 temp = gl_PointCoord - vec2(0.5);
    float f = dot(temp, temp);
    if (f > 0.25) discard;
    color = mix(color1, color2, smoothstep(0.1, 0.25, f));
}
3. Controlling the Appearance of Points
可以通过下面的函数控制点的外观
void glPointParameter{if}(GLenum pname, TYPE param);
void glPointParameter{if}v(GLenum pname, const TYPE *param);
pname                           param                               description
GL_POINT_SPRITE_COORD_ORIGIN    GL_LOWER_LEFT GL_UPPER_LEFT         指定点的原点坐标
GL_POINT_FADE_THRESHOLD_SIZE                                        指定fade门槛
当点的尺寸低于门槛值时，OpenGL可以停止真正的反锯齿，而是使用混合将该点淡出为背景色。

十四、 Rendering to Texture Maps
1. 简述
通过下面的方法可以将数据渲染到贴图
void glFramebufferTexture(GLenum target, GLenum attachment, GLuint texture, GLint level);
......
对于三维或一维、二维贴图数组，可以通过下面函数将贴图的单层作为framebuffer附加点。
void glFramebufferTextureLayer(GLenum target, GLenum attachment,
GLuint texture, GLint level, GLint layer);

2. Discading Rendered Data
首要的规则：在开始渲染一帧之前，你必须清除framebuffer。
忽略framebuffer要比清除它更加高效。
如果你确定新的渲染将完全替换framebuffer的内容，你可以通过下面的函数忽略framebuffer中的数据：
void glInvalidateFramebuffer(GLenum target,GLsizei numAttachments,const GLenum * attachments);
void glInvalidateSubFramebuffer(GLenum target,GLsizei numAttachments, const GLenum * attachments,
GLint x, GLint y, GLint width, GLint height);
如果你只想忽略和framebuffer关联的texture的内容，可以使用下面的函数：
void glInvalidateTexImage(GLuint texture, GLint level);
void glInvalidateTexSubImage(GLuint texture, GLint level,GLint xoffset, GLint yoffset,
GLint zoffset, GLint width, GLint height, GLint depth);


十五、贴图最佳实践
1. Immutable Texuture Storage
尽量使用空间不变的贴图，对于空间不变的贴图，OpenGL实现可以对其有效性做一定假设。例如，空间不变的贴图总是完整的。

2. Mipmaps
为贴图创建并初始化mipmap链。允许硬件使用低分辨率的mipmap不仅可以提高程序渲染图片的质量，而且会让图形处理器的
caches使用效率更高。贴图cache是一小片内存用来存储最近使用过的贴图数据。应用程序使用的贴图越小，放入贴图cache
的图片就会越多，应用程序运行速度就越快。

3. Integer Format Textures


Tips:
1 关于 纹理对象、纹理单元、采样器变量、采样器对象、采样器单元的关系可参考一下文档描述。
http://ogldev.atspace.co.uk/www/tutorial16/tutorial16.html


















