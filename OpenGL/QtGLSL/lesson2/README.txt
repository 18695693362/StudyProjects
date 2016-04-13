=1= Shaders and OpenGL
从3.1版本开始，固定函数管线从CoreProfile中移除了，shaders成为强制要求的。
=2= OpenGL's Programmable pipline
==1== 4.3版本的图形管线包含4个阶段：
(1) vertex shading stage.       [mandatory]
接收vertex-buffer对象指定的顶点数据，分别处理每个顶点。
(2) tessellation shading stage  [optional]
在OpenGL管线中生成额外的几何图元。激活该阶段时，它将从顶点着色阶段接收数据，并做进一步处理。
(3) geometry shading stage      [optional]
可以修改OpenGL管线中的几何图元，分别处理每个几何图元（修改、忽略几何图元）。
(4) fragment shading stage      [mandatory]
该阶段处理由光栅化程序产生的fragments，在这个阶段片段的颜色和深度值被计算。
(5) compute shading stage
该阶段不是图形管线的一部分。
==2== 数据传输
shader  通过in/out(输入/输出)变量来进行数据传递。
uniform 为OpenGL应用程序定义变量，在shader中只能读不能修改。
=3= Shading Language
==1== 类型转换
隐式类型转换
int -> uint
int,uint -> float
int,uint,float -> double
显式类型转换
float f=10.0;
int ten=int(f);
==2== 聚集类型
BaseType    2D vec      3D vec      4D vec      MatrixTypes
float       vec2        vec3        vec4        mat2    mat3    mat4
                                                mat2x2  mat2x3  mat2x4
                                                mat3x2  mat3x3  mat3x4
                                                mat4x2  mat4x3  mat4x4
double      dvec2       dvec3       dvec4       dmat2   dmat3   dmat4
                                                dmat2x2 dmat2x3 dmat2x4
                                                dmat3x2 dmat3x3 dmat3x4
                                                dmat4x2 dmat4x3 dmat4x4
int         ivec2       ivec3       ivec4       X
uint        uvec2       uvec3       uvec4       X
bool        bvec2       bvec3       bvec4       X
==3== Structrues
struct Particle {
    float lifetime;
    vec3  position;
    vec3  velocity;
};
==4== Array
float coeff[3] = float[3](1.0,2.0,3.0);
float[3] coeff = float[3](1.0,2.0,3.0);
coeff.length();     // =3
float coeff[3][5];
coeff[2].length();  // =5
==5== Storage Qualifiers
-TypeModifier-      -Description-
const               标记变量为只读
=in                 输入变量
=out                输出变量
=uniform            从App传到shader的变量，shader中只读
buffer              和App共享的读写内存
shared              computer shader使用。
==6== Function
returnType functionName([accessModifier] type1 variable1,[accessModifier] type2 variable2)
{
    // function body
    return returnValue;
}
-AccessModifier-    -Description-
in                  值被copy到函数
const in            只读的copy到函数的值
out                 值被copy到函数外
inout               值被copy到函数内、外
==7== 计算不变性
invariant 和 precise 可以保证shader中的计算不变性。
invariant 用于任何shader的输出变量。如果两个shader使用同一个表达式计算该输出变量，那么结果是相同的
precise   用于任何函数返回值或任何计算变量。也可用于内置变量，用户变量。
precise gl_Position;
precise out vec3 Location;
precise vec3 subdivide(vec3 P1, vec3 P2)
{
    // .....
}
=4= Interface Blocks
=5= Compiling Shaders
=6= Shader Subroutines
=7= Separate Shader Objects


























