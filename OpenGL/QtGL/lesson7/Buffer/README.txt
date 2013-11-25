第一部分-----缓冲区
一. 关于缓冲区
(1)当每个像素的数据按照统一的方式存储时,存储所有像素的存储空间就叫做缓冲区.
(2)不同的缓冲区可能为每个像素存储的数据量是不同的.但是在一个特定的缓冲区内,为每个像素存储的数据量是相同的.
(3)为每个像素存储了一位信息的缓冲区又叫做位平面(bitplane).
(4)颜色缓冲区用于保存屏幕上所显示的颜色信息,它是用于存储像素信息的许多缓冲区之一.例如:深度缓冲区存储了每个
像素的深度信息.系统的帧缓冲区是由所有这些缓冲区组成的.除了颜色缓冲区之外,其他缓冲区都无法直接查看,它们用于
实现诸如隐藏表面消除\场景抗锯齿\模板测试\绘制平滑的运动图像等功能.

二. 缓冲区及其用途
OpenGL系统可以对如下缓冲区进行操作:
(1)颜色缓冲区:前-左,前-右,后-左,后-右以及任何数量的辅助颜色缓冲区.
(2)深度缓冲区.
(3)模板缓冲区.
(4)累积缓冲区.
具体使用的OpenGL实现决定了可以使用哪些缓冲区,并决定了每个缓冲区为每个像素保留多少位.另外,应用程序可能具有
多种画面(或窗口类型),它们分别具有不同的缓冲区.

1. 各类缓冲区介绍
(1) 颜色缓冲区
颜色缓冲区是通常用于绘图的缓冲区.它们包含了颜色索引或RGB颜色数据,还可能包含alpha数据.支持立体画面的OpenGL
实现提供了左右颜色缓冲区,分别包含了左右立体图像.如果OpenGL实现不支持立体图像,那就只使用左缓冲区.类似地,双
缓冲区系统提供了前后缓冲区,而单缓冲区系统只提供了前缓冲区.另外,OpenGL实现还可能支持不可显示的辅助颜色缓冲区.
OpenGL并没用指定这类缓冲区的特定用途,因此可以按照自己的想法定义和使用它们.
(2) 深度缓冲区
深度缓冲区存储每个像素的深度值.深度通常是根据物体和观察点的距离来测量的,因此具有较大深度值的像素有可能会被具
有较小深度值的像素覆盖.
(3) 模板缓冲区
模板缓冲区的用途之一就是把绘图限制在屏幕中的某个区域,就像使用纸板和喷漆实现精确的绘图一样.
(4) 累积缓冲区
与RGBA模式下的颜色缓冲区一样,累积缓冲区也用于存储RGBA颜色数据.累积缓冲区通常用于把一系列的图像合称为一副图像.
通过这种方法,可以对图像进行超量采样,然后对样本求平均值,并且将结果写入到颜色缓冲区中,从而实现场景的抗锯齿处理.
不能把数据直接写入到累积缓冲区,累积操作总是以矩形块为单位对数据进行操作,通常是把数据移入或移出颜色缓冲区.

2. 清除缓冲区
首先, 指定需要写入到每个将要清除的缓冲区的值
然后, 发布一条命令执行清除操作.在这个命令中,需要传递将要清除的缓冲区列表.如果硬件支持同时清除多个缓冲区,这些清除
操作就会同时进行.否则,这些缓冲区就会按顺序逐个清除.

(1)设置每个缓冲区的清除值
glClearColor(red,green,blue,alpha);
glClearIndex(index)
glClearDepth(depth)
glClearStencil(s)
glClearAccum(red,green,blue,alpha)
(2)清除指定的缓冲区
glClear(mask)
mask的值是GL_COLOR_BUEFFER_BIT,GL_DEPTH_BUFFER_BIT,GL_STENCIL_BUFFER_BIT和GL_ACCUM_BUFFER_BIT的一些
逻辑OR操作的组合结果.
Tips:
OpenGL 3.0引入了glClearBuffer*()函数使用传递给它的值直接清除绑定的绘制缓冲区
glClearBuffer{fiui}v(buffer,drawbuffer,value)
(1) buffer--drawbuffer--value
GL_COLOR -- drawbuffer为一个特定绘制缓冲区指定了索引 -- value是包含清除颜色的一个四元素数组
(2) buffer--drawbuffer--value
GL_DEPTH GL_STENCIL -- 0 -- 单元素数组

3. 选择用于读取和写入的颜色缓冲区
绘图和读取操作的目标都可以是任何颜色缓冲区,以及任何辅助缓冲区.可以选择一个单独的缓冲区作为绘图或读
取操作的目标.对于绘图操作,还可以通过设置把绘图结果同时写入到多个缓冲区.可以使用glDrawBuffer()函
数选择需要写入的缓冲区,也可以使用glReadBuffer()函数选择用于读取的缓冲区,作为glReadPixels()\
glCopyPixels()\glCopyTexImage*()和glCopyTexSubImage*()的数据来源.
如果使用的是双缓冲系统,通常只想在后缓冲区中进行绘图(并在完成绘图后交换前后缓冲区).在有些情况下,我
们可能想把双缓冲区系统当作单缓冲系统一样使用.glDrawBuffer可以设置同时在前后两个缓冲区中进行绘图.
glDrawBuffer还可以选择渲染立体图像的缓冲区,也可以选择渲染到辅助缓冲区.

(1) glDrawBuffer(monde)
mode的值是
GL_FRONT    GL_FRONT_LEFT   GL_AUXi
GL_BACK     GL_FRONT_RIGHT  GL_FRONT_AND_BACK
GL_LEFT     GL_BACK_LEFT    GL_NONE
GL_RIGHT    GL_BACK_RIGHT   GL_COLOR_ATTACHMENTi
其中省略了LEFT或RIGHT的参数表示同时包括左右立体缓冲区.类似地,省略了FRONT和BACK的参数表示同时包
括前后缓冲区.
(2) glDrawBuffers(num,buffers)
该函数制定了用于接收颜色值的多个颜色缓冲区.
buffers 是缓冲区枚举值的数组,这个数组只运行包含GL_NONE GL_FRONT_LEFT GL_FRONT_RIGHT
GL_BACK_LEFT GL_BACK_RIGHT GL_AUXi.OpenGL3.0 添加了帧缓冲区对象,当OpenGL绑定到一个用户定
义的帧缓冲区对象的时候,增加了GL_COLOR_ATTACHMENTi来指定那个颜色渲染缓冲区是绘制目标.
Tips: 如果利用固定功能的管线来生成片断的颜色,每个指定的缓存区都会接收相同的颜色值.如果使用了片断着
色器并指定输出到多个缓冲区,那么每个缓冲区将写入这个着色器的输出所指定的颜色值.
(3) glReadBuffer(mode)
mode的值是
GL_FRONT    GL_FRONT_LEFT   GL_AUXi
GL_BACK     GL_FRONT_RIGHT  GL_COLOR_ATTACHMENTi
GL_LEFT     GL_BACK_LEFT
GL_RIGHT    GL_BACK_RIGHT

4. 缓冲区的屏蔽
OpenGL把数据写入到颜色(启用的,即glDrawBuffer指定的)\深度或模板缓冲区之前,它首先会对数据执行屏蔽
操作.数据和掩码通过逻辑AND操作进行组合,然后再写入.
glIndexMask(GLuint mask)
颜色索引模式下,mask中出现了1,颜色索引缓冲区对应的位允许数据写入;mask中出现了0,颜色索引缓冲区对应的位
不允许数据写入
glColorMask(GLboolean red,GLboolean green,GLboolean blue,GLboolean alpha)
RBGA颜色模式下,对应的颜色成分是否写入.GL_TRUE表示写入.
glColorMaski(GLuint buf,GLboolean red,GLboolean green,GLboolean blue,GLboolean alpha)
OpenGL3.0 允许在渲染到多个缓冲区时,为不同的缓冲区指定不同的mask.
glDepthMask(GLboolean flag)
flag=GL_TRUE 深度缓冲区允许写入数据,flag=GL_FLASE 深度缓冲区不允许写入数据
glStencilMask(GLuint mask)
mask=1 模板缓冲区允许数据写入,mask=0 模板缓冲区不允许数据写入
glStencilMaskSeparate(GLenum face,GLuint mask)
允许对正面和背面使用不同的mask.

三. 片断测试和操作
在OpenGL确定了每个片断是否应该生成以及应该使用什么颜色之后,这个片断仍然需要经历一些处理阶段,这些操
作控制是否需要这个片段以及如何把它写入到帧缓冲区中.片断在进入帧缓冲区之前必须经历的所有测试,以及当
片段写入到帧缓冲区时可能对它进行的最终操作是按照下面的顺序进行的.如果片段在其中某个测试中被排除,后
面的测试或操作就不在进行.
(1)裁剪测试
(2)alpha测试
(3)模板测试
(4)深度测试
(5)混合
(6)抖动
(7)逻辑操作

1. 裁剪测试
glScissor(x,y,width,height)
在窗口中定义一个矩形区域,并把绘图限制在这个区域之内.如果一个片段位于这个区域的内部,那么它就能够通
过裁剪测试.默认不开启裁剪测试,默认 x=0 y=0 width=当前窗口的宽度 height=当前窗口的高度.通常需
要在窗口大小改变以后重新调用glScissor

glEnable(GL_SCISSOR_TEST) glDisable(GL_SCISSOR_TEST)
启用和禁用裁剪测试
Tips: 裁剪测试只是模板测试的一个版本,它使用的是屏幕上得一个矩形区域.

2. alpha测试
在RGBA模式下,alpha测试允许根据一个片段的alpha值接受或拒绝它.可以通过向glEnable()和glDisable()
函数传递GL_ALPHA_TEST,分别启用和禁用alpha测试.alpha测试被启用以后,它就把源片段的alpha值与一个
参考值进行比较,并根据比较结果接受或拒绝这个片段.
glAlphaFunc(GLenum func,GLclampf ref)
设置用于alpha测试的参考值和比较函数.参考值ref的范围被限定在0-1之间.
func:
GL_NEVER GL_ALWAYS GL_LESS GL_LEQUAL GL_EQUAL GL_GEQUAL GL_GREATER GL_NOTEQUEL

Tips:alpha片断测试在OpenGL3.0中废弃了,并且在OpenGL3.1中,替代为通过使用discard操作在片段着色
器中丢弃片段.

3. 模板测试
模板测试只有在存在模板缓冲区的情况下才会执行.模板测试把像素存储在模板缓冲区的值与一个参考值进行比较.
根据测试结果,对模板缓冲区中得这个值进行相应地修改.
(1)启用禁用模板测试
glEnable(GL_STENCIL_TEST) glDisable(GL_STENCIL_TEST)
(2)指定比较函数和参考值
glStencilFunc(GLenum func,GLint ref,GLuint mask)
glStencilFuncSeparate(GLenum face,GLenum func,GLint ref,GLuint mask)
这个函数根据比较函数把参考值与模板缓冲区中的值进行比较,但比较只在那些对应的掩码设置为1的位上进行.
mask指定了哪些位平面需要被模板函数考虑.
(3)指定对模板缓冲区执行的修改操作
glStencilOp(GLenum fail,GLenum zfail,GLenum zpass)
glStencilOpSeparate(GLenum face,GLenum fail,GLenum zfail,GLenum zpass)
fail, zfail, zpass:
GL_KEEP 保持当前值
GL_ZERO 使用零值替换
GL_REPLACE      用参数值替换当前值
GL_INCR         在使用饱和的情况下当前值加1
GL_INCR_WRAP    在不使用饱和的情况下当前值加1
GL_DECR         在使用饱和的情况下当前值减1
GL_DECR_WRAP    在不使用饱和的情况下当前值减1
GL_INVERT
(4)使用方法举例
首先 将模板掩码设置为全0
其次 在模板缓冲区中用1绘制所需要的形状,即定义模板区域.
最后 设置参考值 设置比较函数 设置模板缓冲区修改操作.
Tips: 在绘制过程中不要修改模板平面的内容.

4. 深度测试
深度缓冲区一般用于隐藏表面的消除.如果像素出现了一种新的候选颜色,只有当对应的新物体比原来的物体更
靠近观察点时,它才会被绘制.最初,深度缓冲区的清除值表示一个与观察点尽可能远的距离,因此任何物体的深
度值都要小于它.
glDepthFunc(GLenum func)
func:GL_NEVER GL_ALWAYS GL_LESS GL_LEQUAL GL_EQUAL GL_GEQUAL GL_GREATER GL_NOTEQUAL

5. 遮挡查询
为了提高性能,在渲染几何物体之前判断它是否可见是一个不错的思路(如果不可见就不用绘制它).遮挡查询可以
判断一组几何图形在进行了深度测试之后是否可见.
为了使用遮挡查询,需要执行下面的步骤:
第一步 为每个需要的遮挡查询生成一个查询ID(可选)
第二步 调用glBeginQuery(),表示开始一个遮挡查询.
第三步 渲染需要进行遮挡查询的几何图形.
第四步 调用glEndQuery(),表示已经完成了遮挡查询.
第五步 提取通过了遮挡查询的样本数量
Tips:为了使遮挡查询的处理尽量保持高效,可以禁用所有可能增加渲染时间但不会影响像素可见性的渲染模式.
(1) 生成查询对象
glGenQueries(GLsizei num, GLuint* ids)
0是被保留的遮挡查询名称,不会由glGenQueries返回.
GLboolean glIsQuery(GLuint id)
如果id是一个遮挡查询对象的名称,这个函数返回GL_TRUE.如果id是0或者它不是一个遮挡查询对象的名称,这个
函数返回GL_FALSE.
(2) 对遮挡查询对象进行初始化
glBeginQuery(GLenum target,GLuint id)
指定一次遮挡查询操作的开始.target必须是GL_SAMPLES_PASSED,id是一个无符号整数标识符,标识了这个遮
挡查询操作.
glEndQuery(GLenum target)
结束一次遮挡查询操作.target必须是GL_SAMPLES_PASSED
Tips:在使用遮挡查询时,可以使用除了glGenQueries()和glDeleteQueries()之外,几乎所有的OpenGL操作.
(3) 判断遮挡查询的结果
glGetQueryObjectiv(id, pname, params)
glGetQueryObjectuiv(id, pname, params)
id: 遮挡查询对象的标识符
pname -- params:
GL_QUERY_RESULT -- 通过了深度测试的片段或样本的数量.如果为0表示对象完全被遮挡.
GL_QUERY_RESULT_AVAILABLE -- GL_TRUE GL_FALSE
Tips:在完成遮挡查询操作时可能会产生延迟,可以令pname=GL_QUERY_RESULT_AVAILABLE来查看是否遮挡查询
操作真正的完成了.
(4) 清除遮挡查询对象
glDeleteQueries(n, ids)

6. 条件渲染
条件渲染允许图像服务器判断一个遮挡查询是否产生任何片段以及是否渲染所涉及到的命令.
glBeginConditionalRender(GLuint id,GLenum mode)
glEndConditionalRender(void)
将那些根据遮挡查询对象id的结果可能丢弃的一系列OpenGL渲染命令删除掉.mode指定了OpenGL实现如何使用遮挡
查询的结果.
mode:
GL_QUERY_WAIT
GL_QUERY_NO_WAIT
GL_QUERY_BY_REGION_WAIT
GL_QUERY_BY_REGION_NO_WAIT

7. 混合抖动和逻辑操作
当一个源片断通过了上面所描述的所有测试之后,它就可以按照不同的方式与颜色缓冲区的当前内容进行组合.最简单
地方式就是覆盖原先的值.另外,如果使用的RGBA模式,并且想对片段进行半透明或抗锯齿处理,可以把它的值与缓冲
区中已有的值求平均(混合).在可用颜色数量较少的系统中,可能需要对颜色值进行抖动,在适当损失颜色质量的情况
下增加可使用的颜色数量.最后,可以使用各种位操作符,对源片段和已经写入的片段进行组合.
(1) 混合
混合操作把源片段的RGB和alpha值与已经存储在这个位置的像素的对应值进行组合.
(2) 抖动
在那些只有少量颜色位平面的系统,可以通过对图像中得颜色进行抖动,来增加可用颜色的数量.
(3) 逻辑操作
片段执行的最后一种操作是逻辑操作,例如OR\XOR或INVERT,它们作用于源片断值和(或)颜色缓冲区中的目标片段.
XOR可以实现一种可撤销的方式来绘制图像.简单地对同一副图像连续执行两次XOR操作,所得到的结果就是最初的图
像.
可以向glEnable()glDisable()函数传递GL_INDEX_LOGIC_OP或GL_COLOR_LOGIC_OP参数,分别在颜色索引
模式和RGBA模式下启用和禁用逻辑操作.
glLogicOp(GLenum opcode)

四. 累积缓冲区
OpenGL的图像操作并不是直接写入到累积缓冲区.一般情况下,OpenGL在一个标准颜色缓冲区中产生一系列的图像,
然后以每次一副的方式把它们累积到累积缓冲区中.在累积操作完成后,再把结果复制到颜色缓冲区中以便查看.为了
减少舍入误差,累积缓冲区的精度(每种颜色成分的位数)可能比标准的颜色缓冲区更高.
glAccum(GLenum op,GLfloat value)
op:
GL_ACCUM
GL_LOAD
GL_RETURN
GL_ADD
GL_MULT
Tips:OpenGL3.1中已经废弃累积缓冲区.

第二部分-----缓冲区对象
缓冲区对象允许应用程序显示地指定哪些数据存储在图形服务器中。

1. 创建缓冲区对象
glGenBuffers(num, buffers)
glIsBuffer(buffer)
如果buffer是一个绑定的缓冲区对象的名称，而且还没有删除，则返回TRUE。否则返回FALSE。
Tips:
零是一个保留的缓冲区对象名称，从来不会被glGenBuffers()当做缓冲区对象返回。

2. 激活缓冲区对象
glBindBuffer(target,buffer)
target:
GL_ARRAY_BUFFER
GL_ELEMENT_ARRAY_BUFFER
GL_PIXEL_PACK_BUFFER
GL_PIXEL_UNPACK_BUFFER
GL_COPY_READ_BUFFER
GL_COPY_WRITE_BUFFER
GL_TRANSFORM_FEEDBACK_BUFFER
GL_UNIFORM_BUFFER

glBindBuffer完成3个任务
(1)当buffer是一个首次使用的非零无符号整数时，它就创建一个新的缓冲区对象，并把buffer分配给这个缓冲
区对象，作为它的名称。
(2)当绑定到一个以前创建的缓冲区对象时，这个缓冲区对象便成为当前活动的缓冲区对象。
(3)当绑定到一个值为0的缓冲区对象时，OpenGL就会停止使用缓冲区对象。

3. 用数据分配和初始化缓冲区对象
glBufferData(target,size,data,usage)
分配size个存储单位的OpenGL服务器内存，用于存储顶点数据或索引。以前所有与当前绑定的缓冲区对象相关联
的数据都将删除。
target:
GL_ARRAY_BUFFER             表示顶点数据
GL_ELEMENT_ARRAY_BUFFER     表示索引数据
GL_PIXEL_PACK_BUFFER        表示传递给OpenGL的像素数据
GL_PIXEL_UNPACK_BUFFER      表示从OpenGL获取的像素数据
GL_COPY_READ_BUFFER             表示在缓冲区直接传递数据
GL_COPY_WRITE_BUFFER            表示在缓冲区直接传递数据
GL_TEXTURE_BUFFER               表示作为纹理缓冲区存储的纹理数据
GL_TRANSFORM_FEEDBACK_BUFFER    表示执行一个变换反馈着色器的结果
GL_UNIFORM_BUFFER               表示统一变量值
size: 存储相关数据需要的内存数量。
data:
OpenGL客户端的一个有效内存地址  ---将客户端内存中的size个数据copy到服务器。
NULL  ---服务器保留size个单位的存储空间供以后使用，但不进行初始化。
usage:

4. 更新缓冲区对象的数据值
void        glBufferSubData(target,offset,size,data)
GLvoid*     glMapBuffer(target,access)
GLboolean   glUnmapBuffer(target)
GLvoid*     glMapBufferRange(target,offset,length,access)
GLboolean   glFlushMappedBufferRange(target,offset,length)

5. 在缓冲区对象之间复制数据
glCopyBufferSubData(readbuffer,writebuffer,readoffset,writeoffset,size)

6. 清除缓冲区对象
glDeleteBuffers(num,buffers)

第三部分-----帧缓冲区对象

一. 关于帧缓冲区对象
帧缓冲区对象支持下面一些功能:执行离屏渲染\更新纹理图像\进行缓冲区ping-pong(GPGPU中用到的一种数据
传输技术)
1. 帧缓冲区对象和窗口系统提供的帧缓冲区的不同
(1)窗口系统所提供的帧缓冲区是图形服务器的显示系统可用的唯一的帧缓冲区,也就是说,它是你在自己的屏幕上可以
看到的唯一的帧缓冲区.应用程序创建的帧缓冲区不能在显示器上显示,它们只支持离屏渲染.
(2)当窗口创建的适合,窗口系统管理的那些缓冲区就分配它们的缓冲区(颜色\深度\模板和累积等).当创建应用管理
的帧缓冲区对象的时候,需要创建与所创建的帧缓冲区对象相关的其他渲染缓冲区.
(3)带有窗口系统提供的缓冲区的那些缓冲区,不能与应用程序创建的缓冲区对象相关联,反之亦然.

2. 生成帧缓冲区对象名字
glGenFramebuffers(GLsize num,GLuint* ids)
分配一个帧缓冲区对象名字并不会真正地创建帧缓冲区对象或者为其分配任何存储空间.

3. 激活帧缓冲区对象
glBindFramebuffer(GLenum target,GLuint framebuffer)
target:
GL_DRAW_FRAMEBUFFER 表示framebuffer指定了帧缓冲区渲染的目标
GL_READ_FRAMEBUFFER 表示framebuffer指定了读取操作的源
framebuffer:
framebuffer为0表示把target绑定为默认值(窗口系统默认帧缓冲区)
framebuffer为调用glGenFramebuffers()所产生的一个帧缓冲区对象.

4. 删除帧缓冲区对象
glDeleteFramebuffers(num, ids)
回收与ids所提供的名字相关的num个帧缓冲区对象.如果一个帧缓冲区对象是当前绑定的并且被删除了,帧缓冲区
目标立即绑定到id=0(窗口系统提供的帧缓冲区),并且帧缓冲区对象将释放.
glIsFramebuffer(framebuffer)

二. 渲染缓冲区
渲染缓冲区是OpenGL管理的有效内存,其中包含了格式化的图像数据.

1. 创建新的渲染缓冲区
glGenRenderbuffers(num, ids)
2. 激活渲染缓冲区
glBindRenderbuffer(target,renderbuffer)
target必须为GL_RENDERBUFFER
renderbuffer:
为0表示删除任何绑定的渲染缓冲区
为调用glGenRenderbuffers()所产生的一个名字
3. 删除渲染缓冲区
glDeleteRenderbuffers(num, ids)
如果渲染缓冲区之一是当前绑定,一个到0的绑定会替代在当前帧缓冲区附加点的绑定,并且释放该渲染缓冲区.
glIsRenderbuffer
4. 创建渲染缓冲区存储
当初次针对一个未使用的渲染缓冲区名字调用glBindRenderbuffer()的适合,OpenGL服务器创建一个渲染缓冲区,
其所有状态信息都设置为默认值.在这个配置过程中,并没有分配存储空间来存储像素数据.需要先分配存储空间并指定
其图像格式,然后才可以把渲染缓冲区附加到一个帧缓冲区并向其中渲染.
glRenderbufferStorage(target,internalformat,width,height)
glRenderbufferStorageMultisample(target,samples,internalformat,width,height)
为绑定的渲染缓冲区分配存储空间来存储图像数据
target必须为GL_RENDERBUER
internalformat可以分为颜色渲染缓冲区 深度渲染缓冲区 模板渲染缓冲区 深度-模板渲染缓冲区
width height以像素为单位指定了渲染缓冲区的大小.
samples指定了每个像素多重采样样本的数目
5. 帧缓冲区附加
(1) 将一些渲染缓冲区附加到帧缓冲区对象.
glFramebufferRenderbuffer(target,attachment,renderbuffertarget,renderbuffer)
target必须为GL_READ_FRAMEBUFFER\GL_DRAW_FRAMEBUFFER或者GL_FRAMEBUFFER
attachment:
GL_COLOR_ATTACHMENTi
GL_DEPTH_ATTACHMENT
GL_STENCIL_ATTACHMENT
GL_DEPTH_STENCIL_ATTCHMENT
renderbuffertarget必须为GL_RENDERBUFFER
renderbuffer:
为0表示删除附加点任何渲染缓冲区附加
为调用glGenRenderbuffers()所产生的一个名字
(2) 将纹理对象的一层作为渲染附加到帧缓冲区对象
glFramebufferTexture1D(target,attachment,texturetargt,texture,level)
glFramebufferTexture2D(target,attachment,texturetargt,texture,level)
glFramebufferTexture3D(target,attachment,texturetargt,texture,level,layer)
target必须为GL_READ_FRAMEBUFFER\GL_DRAW_FRAMEBUFFER或者GL_FRAMEBUFFER
GL_COLOR_ATTACHMENTi
GL_DEPTH_ATTACHMENT
GL_STENCIL_ATTACHMENT
GL_DEPTH_STENCIL_ATTCHMENT
texture:
对于glFramebufferTexture1D,如果texture不为0,texturetarget必须为GL_TEXTURE_1D
对于glFramebufferTexture2D,如果texture不为0,texturetarget必须为:
GL_TEXTURE_2D GL_TEXTURE_RECTANGLE GL_TEXTURE_CUBE_MAP_POSITIVE_X
GL_TEXTURE_CUBE_MAP_POSITIVE_Y GL_TEXTURE_CUBE_MAP_POSITIVE_Z
GL_TEXTURE_CUBE_MAP_NEGATIVE_X GL_TEXTURE_CUBE_MAP_NEGATIVE_Y
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
对于glFramebufferTexture3D,如果texture不为0,texturetarget必须为GL_TEXTURE_3D
如果texture为0,表示绑定到附加的任何纹理都释放了,并且没有对附加进行后续的绑定.
level表示作为渲染模板附加的相关纹理图像的mipmap层.
layer表示三维纹理时所使用的纹理的层.




