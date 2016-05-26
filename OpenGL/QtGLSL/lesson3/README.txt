    Drawing with OpenGL

一、 OpenGL Graphics Primitives
1. Points
在程序中用glPointSize(GLfloat size)来固定点的大小
在shader中用gl_PointSize来设置点的大小（只有GL_PROGRAM_POINT_SIZE为GL_TRUE才可用）
以点为中心以点的大小为边长的正方形包含的像素会被覆盖

2. Point Sprites
在渲染点的时候，gl_PointCoord变量可以在fragment shader中使用

3. Lines, Strips, and Loops
多条线按顺序连接不闭合 被称作 line strip
多条线按顺序连接闭合   被称作 line loop
光栅化线的规则被称为钻石退出规则
glLineWidth用来设置线的宽度
反锯齿开启后，线被当做长方体，其长度和线长度相同，宽度和线宽度相同。

4. Triangles Strips Fans
Triangles Strips 某个三角形会公用前一个三角形后面两个顶点
Triangles Fans 所有三角形公用第一个顶点

5. Rendering Polygons As Points, Outlines, or Solids
void glPolygonMode(GLenum face, GLenum mode);

6. Reversing and Culling Polygon Faces
void glFrontFace(GLenum mode);
//GL_CCW counterclockwise
//GL_CW  clockwise
指定剔除的面
void glCullFace(GLenum mode)
// GL_FRONT GL_BACK GL_FRONT_AND_BACK
glEnable(GL_CULL_FACE)

二、 Data in OpenGL Buffers
1. Creating and allocating buffers
调用glGenBuffers生成buffer object的名称。
void glGenBuffers(GLsizei n, GLuint *buffers);

---Buffer Binding Targets(points)---
Target                          Uses
GL_ARRAY_BUFFER                 用于通过glVertexAttribPointer设置顶点数组数据指针
GL_COPY_READ/WRITE_BUFFER       用于buffer之间copy数据
GL_DRAW_INDIRECT_BUFFER         用于indirect绘制时保存绘制命令的参数
GL_ELEMENT_ARRAY_BUFFER         用于保存顶点的索引，执行索引绘制命令glDrawElements
GL_PIXEL_PACK_BUFFER            用于保存从图片对象(textures/framebuffer)读取的数据 glGetTexImage glReadPixels
GL_PIXEL_UNPACK_BUFFER          用于指定glTexImage2D的来源数据
GL_TEXTURE_BUFFER               将buffer绑定到texture对象上，这样就可以在shader中获取其数据了
GL_TRANSFORM_FEEDBACK_BUFFER    用于保存变换后的顶点属性
GL_UNIFORM_BUFFER

//指定当前绑定的target类的buffer对象 或者 创建target类的buffer对象
glBindBuffer(GLenum target, GLuint buffer);

2. Getting Data into and out of Buffers
glBufferData(GLenum target,GLsizeiptr size,const GLvoid* data,GLenum usage)
glBufferSubData(GLenum target,GLintptr offset,GLsizeiptr size,const GLvoid* data);
glClearBufferData(GLenum target,GLenum internalfamat,GLenum format,GLenum type,const void* data)
glClearSubBufferData(GLenum target,GLenum internalfamat,GLintptr offset,GLintptr size,GLenum format,GLenum type,const void* data)
glCopyBufferSubData(GLenum readtarget,GLenum writetarget,GLintptr readoffset,GLintptr writeoffset,GLsizeiptr size)

3. Reading the contents of a buffer
void glGetBufferSubData(GLenum target,GLintptr offset,GLsizeiptr size,GLvoid* data);

4. Accessing the Content of Buffers
void* glMapBuffer(GLenum target,GLenum access)
---Access Modes---
GL_READ_ONLY
GL_WRITE_ONLY
GL_READ_WRITE
void glUnmapBuffer(GLenum target)

5. Asynchronous and explicit mapping
void* glMapBufferRange(GLenum target,GLintptr offset,GLsizeiptr length,GLbitfield access)
--- Access ---
GL_MAP_INVALIDATE_RANGE_BIT         指定范围的数据被忽略成为invalid数据，不能和GL_MAP_READ_BIT同时使用
GL_MAP_INVALIDATE_BUFFER_BIT        整个范围的数据被忽略成为invalid数据，不能和GL_MAP_READ_BIT同时使用
GL_MAP_FLUSH_EXPLICIT_BIT           指定更新数据的范围，和GL_MAP_WRITE_BIT同时使用
GL_MAP_UNSYNCHRONIZED_BIT           未指定该参数时，在返回关联的范围之前，OpenGL会等待所有访问该buffer的操作完成

void glFlushMappedBufferRange(GLenum target,GLintptr offset,GLsizeiptr length);

6. Discarding Buffer Data
glInvalidateBufferData(GLuint buffer)
glInvalidateBufferSubData(GLuint buffer,GLintptr offset,GLsizeptr length)


三、 Vertex Specification
1. VertexAttibPointer in Depth
void glVertexAttribPointer(GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei stride,const GLvoid* pointer)
e.g:
glVertexAttribPointer(index,size,GL_INT,GL_TRUE,stride,pointer)
数据被标准化的方法 result = source/(pow(32)-1)
glVertexAttribPointer(index,size,GL_UNSIGNED_BYTE,GL_TRUE,stride,pointer)
数据被标准化的方法 result = (2*source+1)/(pow(8)-1)

2. Integer Vertex Attributes
void glVertexAttribIPointer(GLuint index,GLint size,GLenum type,GLsizei stride,const GLvoid* pointer)
type -- GL_BYPTE,GL_UNSIGNED_BYTE,GL_SHORT,GL_UNSIGNED_SHORT,GL_INT,GL_UNSIGNED_INT

3. Double-Precision Vertex Attributes
void glVertexAttribLPointer(GLuint index,GLint size,GLenum type,GLsizei stride,const GLvoid* pointer)
type -- GL_DOUBLE

4. Packed Data Formats for Vertex Attributes
GL_INT_2_10_10_10_REV
GL_UNSIGNED_INT_2_10_10_10_REV

5. Static Vertex-Attribute Specification
静态顶点属性是顶点属性的默认值。
void glVertexAttrib{1234}{fds}(GLuint index,TYPE values);
void glVertexAttrib{1234}{fds}v(GLuint index,const TYPE* values);
void glVertexAttrib4{bsifd ub us ui}v(GLuint index,const TYPE* values);

void glVertexAttrib4Nub(GLuint index,GLubyte x,GLubyte y,GLubyte z,GLubyte w);
void glVertexAttrib4N{bsi ub us ui}v(GLuint index,const TYPE* v);

void glVertexAttribI{1234}{i ui}(GLuint index, TYPE values);
void glVertexAttribI{123}{i ui}v(GLuint index,const TYPE *values);
void glVertexAttribI4{bsi ub us ui}v(GLuint index,const TYPE *values);

void glVertexAttribL{1234}(GLuint index, TYPE values);
void glVertexAttribL{1234}v(GLuint index, const TYPE *values);

四、 OpenGL Drawing Commands
1. 绘图命令
Open的绘图命令可以粗略的分为两类：基于索引的和非索引的
void glDrawArrays(GLenum mode,GLint first, GLsizei count);
void glDrawElements(GLenum mode,GLsizei count,GLenum type,const GLvoid* indices);
void glDrawElementsBaseVertex(GLenum mode, GLsizei count, GLenum type,const GLvoid *indices, GLint basevertex);
void glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count,GLenum type,const GLvoid *indices);
void glDrawRangeElementsBaseVertex(GLenum mode,GLuint start, GLuint end,GLsizei count, GLenum type,const GLvoid *indices, GLint basevertex);
void glDrawArraysIndirect(GLenum mode,const GLvoid *indirect);
void glDrawElementsIndirect(GLenum mode, GLenum type, const GLvoid * indirect);

void glMultiDrawArrays(GLenum mode, const GLint * first, const GLint * count, GLsizei primcount);
void glMultiDrawElements(GLenum mode, const GLint * count, GLenum type,const GLvoid * const * indices, GLsizei primcount);
void glMultiDrawElementsBaseVertex(GLenum mode, const GLint * count,GLenum type,const GLvoid * const * indices, GLsizei primcount,const GLint * baseVertex);
void glMultiDrawArraysIndirect(GLenum mode, const void * indirect,GLsizei drawcount, GLsizei stride);
void glMultiDrawElementsIndirect(GLenum mode, GLenum type,const void * indirect, GLsizei drawcount, GLsizei stride);

2. Restarting Primitives
void glPrimitiveRestartIndex(GLuint index);
设置primitive_restart_index,使用glDrawElements系列的绘图命令时，当获取顶点的索引和primitive_restart_index相等时，会忽略当前索引，并且以下一个索引为新图元的第一个顶点。

五、 Instanced Rendering



























