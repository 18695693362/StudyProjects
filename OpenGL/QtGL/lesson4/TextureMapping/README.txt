一、使用纹理贴图的步骤：
1、创建纹理对象，并为他指定一个纹理。
2、确定纹理如何应用到每个像素上。
3、启用纹理贴图功能。
4、绘制场景，提供纹理坐标和几何图形坐标。

步骤1. 创建纹理对象，指定一个纹理
1、关于纹理
纹理通常是二维的（即一副常见的图片），但是纹理也可以是1维、3维。

步骤2. 确定纹理如何应用到每个像素上。即根据片断颜色和纹理图像来计算最终的RGBA值。
1、简单的使用纹理颜色作为最终的颜色，这种方式被称为替换模式。
2、用纹理来调整片断的颜色。
3、更具纹理值，用一种常量颜色和片断颜色进行组合。

步骤3. 启用纹理贴图
glEnable(parameter)
glDisable(parameter)
parameter:GL_TEXTURE_1D\GL_TEXTURE_2D\GL_TEXTURE_3D\GL_TEXTURE_MAP\

步骤4. 绘制场景提供纹理坐标和几何坐标
确定纹理在进行“粘贴”之前应该如何根据它所应用的片断进行排列。


二. 指定纹理
1. 定义纹理
(1) glTexImage2D用于定义一个二维纹理或者一个一维纹理数组。
glTexImage2D(target,level,internalFormat,width,height,border,format,type,texels);
target 指定定义的纹理类型
level 如果使用了多种分辨率的纹理图像可以使用该参数，若只提供了一种纹理图像则level=0
internalFormat 确定哪些成分（RGBA、深度、亮度或强度）被选定为图像的纹理单元。
width,height,border 纹理图像的宽度高度和边框。
format,type 参数描述了纹理图像数据的格式和数据类型。
texels 包含了纹理图像数据。
Tips: glPixelStore*() 和 glPixelTransfer*() 会影响format,type参数设置的状态。

(2) glCopyTexImage2D从缓冲区读取一块矩形像素，并且把它作为一个新纹理的纹理单元
glCopyTexImage2D(target,level,internalFormat,x,y,width,height,border)
纹理数组是从屏幕对齐的像素矩形读取的，它的左下角坐标为(x,y).

2. 纹理代理
纹理代理是一种特殊的占位符，它允许更精确地查询OpenGL是否可以容纳某种内部格式的纹理图像。
(1) 创建纹理代理
glTexImage2D(GL_PROXY_TEXTURE_2D,level,internalFormat,width,height,border,format,type,NULL);
(2) 查询纹理状态变量的值（如果没有足够的资源容纳纹理代理指定的纹理图像，表示宽度、高度、边框宽度
以及成分分辨率的纹理状态变量都被设置为0）
glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D,level,pname,params)
例如：
GLint width;
glGetTexLevelParameteriv(GL_PROXY_TEXTURE_2D,level,GL_TEXTURE_WIDTH,&width);

3. 替换纹理的全部或一部分
(1) glTexSubImage2D(target,level,internalFormat,xoffset,yoffset,width,height,format,type,texels);
xoffset,yoffset 指定了x和y方向上纹理单元的偏移量
width,height 指定了子区域的宽度和高度
(2) glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height)
子图像纹理数组取自一个屏幕对齐的像素矩形，它的左下角为(x,y)参数所指定的坐标。

4. 一维、三维纹理
glTexImage1D
glCopyTexImage1D
glTexSubImage1D
glCopyTexSubImage1D

glTexImage3D
glCopyTexImage3D
glTexSubImage3D
glCopyTexSubImage3D

5.压缩纹理图像
(1) 在加载时压缩纹理图像
为了让OpenGL在加载纹理图像的时候对它进行压缩,可以把internalFormat参数设置为其中一种GL_COMPRESSED_*枚举.

(2) 加载经过压缩的纹理图像
glCompressedTexImage1D(target,level,internalFormat,width,border,imageSize,texels)
glCompressedTexImage2D(target,level,internalFormat,width,height,border,imageSize,texels)
glCompressedTexImage3D(target,level,internalFormat,width,height,depth,border,imageSize,texels)

glCompressedTexSubImage1D(target,level,xoffset,width,imageSize,texels)
glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,imageSize,texels)
glCompressedTexSubImage3Dtarget,level,xoffset,yoffset,zoffset,width,height,depth,imageSize,texels)

三. 过滤
纹理图像是长方形或正方形的,但是当他们映射到多边形的表面并转换为屏幕坐标之后,纹理图像中得单个纹理单元很少与最终
的像素形成一一对应关系.有时候一个像素对应一个纹理单元的一部分(纹理被放大了),有时候则是一个像素对应多个纹理单元
(纹理被缩小了).很难确定最终的颜色是使用了哪些纹理值匀和或插值的.不过OpenGL允许指定几种过滤选项,这些选项提供了
速度和图像质量之间的权衡.
GL_NEAREST最靠近像素中心的那个纹理单元将用于放大或缩小,计算量小于GL_LINEAR.
GL_LINEAR被称为双线性采样,因为它是在一个2*2纹理数组中进行采样的.
GL_LINEAR_MIPMAP_LINEAR被称为三线性采样,因为它是对两个双线性采样的mipmap进行线性匀和.
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);

四. 纹理对象
1. 命名纹理对象
任何非零的无符号整数都可以用来表示纹理对象的名称，为了避免意外的重名，应该使用glGenTextures(num,names)
来提供使用的纹理名称。
GLboolean glIsTexture(name);可以用来判断一个纹理名称是否处于实际可用中。
2. 创建和使用纹理对象
glBindTexture()可以创建和使用纹理对象。
(1)当一个纹理名称初次绑定时，OpenGL会创建一个新的纹理对象，并把纹理图像和纹理属性设置为默认值。
glTexImage*() glTexSubImage*() glCopyTexImage*() glCopyTexSubImage*() glTexParameter*()和
glPrioritizeTextures()函数的后续调用会把数据存储在这个纹理对象中。
纹理对象可以包含一副纹理图像以及相关的mipmap图像，并包括相关的数据，例如宽度、高度、边框宽度、内部格式、成分的
分辨率和纹理属性（缩小和放大过滤器、环绕模式、边框颜色和纹理优先级）等。
(2)当一个纹理对象再次绑定时，它的数据就成为当前的纹理状态。
3. 清除纹理对象
glDeleteTextures(num,textures)
4. 常驻纹理工作集
查看纹理是否在常驻纹理工作集中
glAreTexturesResident(num, texture_names, residences)
设置纹理的优先级
glPrioritizeTextures(num, texture_names, priorities) priorities的取值范围为[0,1]

五. 纹理函数
纹理函数以及基本内部格式的组合决定了纹理的每个成分是如何应用的。纹理函数是在被选择的纹理成分以及片断的颜色值上进行的操作。
Tips: 纹理成分的选择是在应用了像素传输函数后进行的。
glTexEnv{if}(target, pname, param)
glTexEnv{if}v(target, pname, param)
target -> pname -> param
(GL_TEXTURE_FILTER_CONTROL -> GL_TEXTURE_LOD_BIAS -> mipmapParam [mipmap细节层参数的偏移值])
(GL_TEXTURE_ENV -> GL_TEXTURE_ENV_MODE -> GL_REPLACE    [纹理值 直接替换 片断颜色值]
                                          GL_MODULATE   [片断颜色值 依据 纹理值 进行调整]
                                          GL_DECAL      [纹理 贴到 片断上]
                                          GL_BLEND      [纹理 片断 GL_TEXTURE_ENV_COLOR指定的颜色 混合]
                                          GL_ADD        [纹理颜色 和 片断颜色值 相加]
                                          GL_COMBINE)   [纹理颜色 和 片断颜色值 进行组合]
(GL_TEXTURE_ENV -> GL_TEXTURE_ENV_COLOR -> colorv )
(GL_POINT_SPRITE -> GL_COORD_REPLACE -> GL_TRUE GL_FALSE)


六. 分配纹理坐标
纹理坐标决定了纹理图像中的哪个纹理单元分配给这个顶点。就像着色多边形和直线中两个顶点之间的插值匀和一样，顶点之间的纹理坐标
也会进行插值匀和。
纹理坐标可以由1个、2个、3个或者4个坐标组成。它们常用s,t,r,q表示，区别于物体坐标(x,y,z)和求职器坐标(u,v);
glTexCoord{1234}{sifd}(coords)
glTexCoord{1234}{sifd}v(coords)
Tips:
(1)在进行任何纹理贴图之前,纹理坐标值和一个4*4的纹理矩阵相乘.
(2)整型的纹理坐标是直接使用的,而不像普通的坐标一样被映射到[-1,1]范围内使用.

1. 计算正确的纹理坐标
纹理坐标映射到物体模型.

2. 重复和截取纹理
可以分配[0,1]范围以外的纹理坐标,并且在纹理图像中对它们进行截取或重复.
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP)
GL_REPEAT: 贴图重复
GL_MIRRORED_REPEAT: 贴图镜像重复
GL_CLAMP: 贴图截取,使用边框颜色用于纹理计算来确定[0,1]范围外的颜色.
GL_CLAMP_TO_EDGE: 截取到边界(边框颜色始终被忽略),使用靠近边界和边界上得颜色用于纹理计算来确定[0,1]范围外的颜色.
GL_CLAMP_TO_BORDER: 截取到边框,[0,1]范围外只用边框颜色作为纹理.
GL_MIRROR_CLAMP_TO_EDGE: 镜像截取到边界

七. 纹理坐标自动生成
glTexGen{ifd}(coord, pname, param)
glTexGen{ifd}v(coord, pname, param)
coord: GL_S GL_T GL_R GL_Q (分别表示需要自动生成s t r q纹理坐标)
pname -> param1:(param1 指定了使用哪种函数生成纹理坐标)
(GL_TEXTURE_GEN_MODE -> GL_OBJECT_LINEAR
                        GL_EYE_LINEAR
                        GL_SPHERE_MAP
                        GL_REFLECTION_MAP
                        GL_NORMAL_MAP)
pname -> param2:(param2 指定了纹理坐标生成函数的参数)
(GL_OBJECT_PLANE GL_EYE_PLANE -> coordV)

1. 创建纹理轮廓线
parameter = {p1,p2,p3,p4}
glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
glTexGeni(GL_S, GL_OBJECT_PLANE, parameter);
glEnable(GL_TEXTURE_GEN_S);
GL_OBJECT_LINEAR: g = p1 * xo + p2 * yo + p3 * zo + p4 * wo   (xo,yo,zo,wo为物体坐标)

2. 球体纹理
glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
glEnable(GL_TEXTURE_GEN_S);
glEnable(GL_TEXTURE_GEN_T);

3. 立方图纹理
glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_NORMAL_MAP);
glEnable(GL_TEXTURE_GEN_S);
glEnable(GL_TEXTURE_GEN_T);
glEnable(GL_TEXTURE_GEN_R);

八. 多重纹理
在进行标准的纹理处理时,一次把一副图应用到一个多边形上.多重纹理允许应用多个纹理图片,在纹理操作管线中把
它们逐个应用到同一个多边形上.多重纹理存在一系列的纹理单位,每个纹理单位执行各自的纹理操作,并把结果传递
给下一个纹理单位,直到所有的纹理单位均完成为止.
1. 多重纹理使用步骤
(1)对每个纹理单位，建立相关的纹理状态，包括纹理图像、过滤器、纹理环境、纹理坐标生成和纹理矩阵等。
glActiveTexture()                           更改当前的纹理单位
glGetIntegerv(GL_MAX_TEXTURE_UNITS,...)     查询OpenGL支持的最大纹理单位数目
(2)指定顶点时，使用glMultiTexCoord*()函数为每个顶点指定多个纹理坐标，分别用于不同的纹理单位。

2. 指定纹理坐标的其他方法

3. 恢复使用单个纹理单位
禁用除0以外的纹理单位，启用纹理单位0.
glActiveTexture(GL_TEXTURE1)
glDisable(GL_TEXTURE_2D)
glActiveTexture(GL_TEXTURE2)
glDisable(GL_TEXTURE_2D)
......
glActiveTexture(GL_TEXTURE0)
glEnable(GL_TEXTURE_2D)

九. 纹理组合器函数


