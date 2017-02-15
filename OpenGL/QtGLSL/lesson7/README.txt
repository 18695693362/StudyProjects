    7 Light and Shadow

一、 Classic Lighting Model
1. 简述
经典的光照模型叠加一组独立光照成分来获得整个光照效果。这些光照成分分别为：ambient、diffuse以及specular。

环境光不是来自于任何特定方向。经典光照模型将它当做一个贯穿整个场景的常量，对于分散在场景中的光形成一个合适的
近似。计算环境光不需要涉及任何对光源方向和观察着方向的分析。它可以是每个光源贡献的值的累计，也可以是一个全局
的常量。

漫反射光是物体表面将特定光源的光向所有方向均等地反射的光。即使表面没有将光源直接反射到你的眼睛，因为漫反射的
存在，你依然可以看到表面被点亮。眼睛的方向是无所谓的，但是光源的方向会影响到漫反射。表面越直接面对光源，表面
会越明亮，正对光源的表面比测对光源的表面收集了更多的光。漫反射光的计算依赖于表面的法向量以及光源的方向，以及
表面的颜色，但是不会用到观察者的方向。

环境高光是由表面直接反射的光。高亮程度指的是表面材质表现的有多么像一面镜子。一个高度磨光的金属球反射了非常尖
锐的、亮的镜面高光，然而一个磨的钝的会反射一个巨大的、衰减的镜面高光。一个布料球实质上几乎没有反射任何镜面高光。
这个特定角度的效果强度被称为光滑度。计算镜面高光需要知道直接反射光源的光到眼睛，需要表面朝向多近，因此需要知道
表面的法线，光源的方向以及眼睛的方向。

2. Fragment Shaders for Different Light Styles
(1) No Lighting
----------------------- Vertex Shader -------------------------
// Vertex shader with no lighting
#version 330 core
uniform mat4 MVPMatrix; // model-view-projection transform
in vec4 VertexColor;    // sent from the application, includes alpha
in vec4 VertexPosition; // pre-transformed position
out vec4 Color;         // sent to the rasterizer for interpolation
void main()
{
    Color = VertexColor;
    gl_Position = MVPMatrix * VertexPosition;
}
---------------------- Fragment Shader ------------------------
// Fragment shader with no lighting
#version 330 core
in vec4 Color;          // interpolated between vertices
out vec4 FragColor;     // color result for this fragment
void main()
{
    FragColor = Color;
}

(2) Ambient Light
光自身也可以有颜色而不只是亮度。光的颜色会和被照亮的物体表面的颜色相互作用。这种交互作用可以通过乘法来模拟。
用0.0表示纯黑，用1.0表示满强度开启乘法来模拟这种交互作用。
光的颜色可以比1.0高，特别是我们将多个光源的光进行叠加。我们会使用min()来使光饱和到白色。输出到framebuffer
的颜色值需要应用min(),计算过程中的中间值不需要。
如果物体颜色中包含alpha成分，而且不希望光照修改它的alpha。可以将片段着色器输出颜色的alpha成分设置为物体颜色
的alpha。
光照计算也可以放在顶点着色器中进行，片段着色器中会获得插值后的结果。因为顶点着色器通常处理的顶点要比片段着色器
处理的片段少很多，所以顶点着色器中计算光照会更加高效。但是，对于很多光照技术，插值的结果会不同，基于每个片段的
光照计算要比基于每个顶点的光照计算质量更高。
--------------------------- Vertex Shader -----------------------------
// Vertex shader for ambient light
#version 330 core
uniform mat4 MVPMatrix;
in vec4 VertexColor;
in vec4 VertexPosition;
out vec4 Color;
void main()
{
     Color = VertexColor;
     gl_Position = MVPMatrix * VertexPosition;
}
-------------------------- Fragment Shader ----------------------------
 // Fragment shader for global ambient lighting
#version 330 core
uniform vec4 Ambient; // sets lighting level, same across many vertices
in vec4 Color;
out vec4 FragColor;
void main()
{
//    vec4 scatteredLight = Ambient; // this is the only light
//    // modulate surface color with light, but saturate at white
//    FragColor = min(Color * scatteredLight, vec4(1.0));
    vec3 scatteredLight = vec3(Ambient);
    vec3 rgb = min(Color.rgb*scatteredLight,vec3(1.0));
    FragColor = vec4(rgb,Color.a);
}
(3) Directional Light
如果光非常的远，可以近似地认为物体表面上每点的光的方向都是相同的。将这种光称为方向光。类似的，当观察者非常远时，
可以近似地认为物体表面上每点的眼睛的方向都是相同的。这种简化让方向光的代码实现很简单并且运行速度比其他类型的光照
更快。这种类型的光对于模拟像太阳这样的光源很有用。
就像环境光一样，方向光也有自己的颜色，我们将依据漫反射的分散，用光的颜色来调整物体表面的颜色。镜面成分的贡献会被
分开计算，这样镜面高亮就是光源的颜色，而不是物体表面颜色的调整。
镜面高光的反光度是通过一个指数来测量，用来加快直接反射方向的角度的减少。
Directional Light Source Lighting
--------------------------- Vertex Shader -----------------------------
// Vertex shader for a directional light computed in the fragment shader
#version 330 core
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix; // to transform normals, pre-perspective
in vec4 VertexColor;
in vec3 VertexNormal;
in vec4 VertexPosition;
out vec4 Color;
out vec3 Normal;
void main() {
    Color = VertexColor;
    // we now need a surface normal
    // interpolate the normalized surface normal
    // transform the normal, without perspective, and normalize it
    Normal = normalize(NormalMatrix * VertexNormal);
    gl_Position = MVPMatrix * VertexPosition;
}
-------------------------- Fragment Shader ----------------------------
// Fragment shader computing lighting for a directional light
#version 330 core
uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec3 LightDirection; // direction toward the light
uniform vec3 HalfVector;
uniform float Shininess;
uniform float Strength;
// surface orientation for shiniest spots
// exponent for sharping highlights
// extra factor to adjust shininess
in vec4 Color;
in vec3 Normal; // surface normal, interpolated between vertices
out vec4 FragColor;
void main()
{
    // compute cosine of the directions, using dot products,
    // to see how much light would be reflected
    float diffuse = max(0.0, dot(Normal, LightDirection));
    float specular = max(0.0, dot(Normal, HalfVector));
    // surfaces facing away from the light (negative dot products)
    // won’t be lit by the directional light
    if (diffuse == 0.0)
    {
        specular = 0.0;
    }
    else
    {
        specular = pow(specular, Shininess); // sharpen the highlight
    }
    vec3 scatteredLight = Ambient + LightColor * diffuse;
    vec3 reflectedLight = LightColor * specular * Strength;
￼     // don’t modulate the underlying color with reflected light,
     // only with scattered light
    vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
(4) Point Lights
点光模拟靠近场景或者是场景内的光，例如灯光或者天花板灯光或者街道上的灯光。点光源和方向光源之间主要有两个不同点：
首先：对于物体表面上的每个点来说，点光源的方向是不同的。
其次：物体表面接收到的光会随着和点光源的距离增加而减弱。
Point-Light Source Lighting
--------------------------- Vertex Shader -----------------------------
// Vertex shader for a point-light (local) source, with computation
// done in the fragment shader.
#version 330 core
uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform mat3 NormalMatrix;
in vec4 VertexColor;
in vec3 VertexNormal;
in vec4 VertexPosition;
// now need the transform, minus perspective
out vec4 Color;
out vec3 Normal;
out vec4 Position; // adding position, so we know where we are
void main() {
    Color = VertexColor;
    Normal = normalize(NormalMatrix * VertexNormal);
    Position = MVMatrix * VertexPosition;     // pre-perspective space
    gl_Position = MVPMatrix * VertexPosition; // includes perspective
}
-------------------------- Fragment Shader ----------------------------
// Fragment shader computing a point-light (local) source lighting.
#version 330 core
uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform float Shininess;
uniform float Strength;
// location of the light, eye space
uniform vec3 EyeDirection;
uniform float ConstantAttenuation; // attenuation coefficients
uniform float LinearAttenuation;
uniform float QuadraticAttenuation;
in vec4 Color;
in vec3 Normal;
in vec4 Position;
out vec4 FragColor;
void main()
{
    // find the direction and distance of the light,
    // which changes fragment to fragment for a local light
    vec3 lightDirection = LightPosition - vec3(Position);
    float lightDistance = length(lightDirection);
    // normalize the light direction vector, so
    // that a dot products give cosines
    lightDirection = lightDirection / lightDistance;
    // model how much light is available for this fragment
    float attenuation = 1.0 / (ConstantAttenuation + LinearAttenuation * lightDistance +
    QuadraticAttenuation * lightDistance * lightDistance);
     // the direction of maximum highlight also changes per fragment
    vec3 halfVector = normalize(lightDirection + EyeDirection);
    float diffuse = max(0.0, dot(Normal, lightDirection));
    float specular = max(0.0, dot(Normal, halfVector));
    if (diffuse == 0.0)
    {
        specular = 0.0;
    }
    else
    {
        specular = pow(specular, Shininess) * Strength;
    }
    vec3 scatteredLight = Ambient + LightColor * diffuse * attenuation;
    vec3 reflectedLight = LightColor * specular * attenuation;
    vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}
(5) Spotlights
在剧场或影院，聚光灯投射一个巨大的光，照亮一个指定的区域。OpenGL限制产生一个在某个特定方向上的光锥来模拟聚光
灯。聚光灯的方向和聚光灯光锥对准的方向是不同的，除非你从聚光灯的中心看。
Spotlight Lighting
--------------------------- Vertex Shader -----------------------------
// Vertex shader for spotlight computed in the fragment shader
#version 330 core
uniform mat4 MVPMatrix;
uniform mat4 MVMatrix;
uniform mat3 NormalMatrix;
in vec4 VertexColor;
in vec3 VertexNormal;
in vec4 VertexPosition;
out vec4 Color;
out vec3 Normal;
out vec4 Position;
void main() {
    Color = VertexColor;
    Normal = normalize(NormalMatrix * VertexNormal);
    Position = MVMatrix * VertexPosition;
    gl_Position = MVPMatrix * VertexPosition;
}
-------------------------- Fragment Shader ----------------------------
// Fragment shader computing a spotlight’s effect
#version 330 core
uniform vec3 Ambient;
uniform vec3 LightColor;
uniform vec3 LightPosition;
uniform float Shininess;
uniform float Strength;
uniform vec3 EyeDirection;
uniform float ConstantAttenuation;
uniform float LinearAttenuation;
uniform float QuadraticAttenuation;
uniform vec3 ConeDirection;
uniform float SpotCosCutoff;
uniform float SpotExponent;
in vec4 Color;
in vec3 Normal;
in vec4 Position;
out vec4 FragColor;
void main()
{
    // adding spotlight attributes
    // how wide the spot is, as a cosine
    // control light fall-off in the spot
    vec3 lightDirection = LightPosition - vec3(Position);
    float lightDistance = length(lightDirection);
    lightDirection = lightDirection / lightDistance;
    float attenuation = 1.0 / (ConstantAttenuation + LinearAttenuation * lightDistance +
    QuadraticAttenuation * lightDistance * lightDistance);
    // how close are we to being in the spot?
    float spotCos = dot(lightDirection, -ConeDirection);
    // attenuate more, based on spot-relative position
    if (spotCos < SpotCosCutoff)
    {
        attenuation = 0.0;
    }
    else
    {
        attenuation *= pow(spotCos, SpotExponent);
    }

    vec3 halfVector = normalize(lightDirection + EyeDirection);
    float diffuse = max(0.0, dot(Normal, lightDirection));
    float specular = max(0.0, dot(Normal, halfVector));
    if (diffuse == 0.0)
    {
        specular = 0.0;
    }
    else
    {
        specular = pow(specular, Shininess) * Strength;
    }
    vec3 scatteredLight = Ambient + LightColor * diffuse * attenuation;
    vec3 reflectedLight = LightColor * specular * attenuation;
    vec3 rgb = min(Color.rgb * scatteredLight + reflectedLight, vec3(1.0));
    FragColor = vec4(rgb, Color.a);
}

3. Moving Calculations to the Vertex Shader
没有关于在哪儿进行光照计算的规则。通过实验来发现对于你的物体表面的更好方式。极端情况下，颜色可以完全在顶点着色器中计算
然后在插值。这本质上就是Gouraud渲染。尽管从计算角度来看是很节省，但是它会造成光照锯齿。

4. Multiple Lights and Materials
通常一个场景中有很多个光源，以及很多种材质。通常一次只会渲染一个材质，但是会有很多个光源照亮这个材质。
（1）光照属性
将光的特性组成一个结构体，创建一个结构体的数组进行处理。
struct LightProperties {
bool isEnabled; // true to apply this light in this invocation
bool isLocal;   // true for a point light or a spotlight, false for a positional light
bool isSpot;    // true if the light is a spotlight
vec3 ambient;   // light’s contribution to ambient light
vec3 color;     // color of light
vec3 position;  // location of light, if is Local is true, otherwise the direction toward the light
vec3 halfVector;        // direction of highlights for directional light vec3 coneDirection;
float spotCosCutoff;    // spotlight attributes
float spotExponent;
float constantAttenuation; // local light attenuation coefficients
float linearAttenuation;
float quadraticAttenuation;
// other properties you may desire
};
（2）材质的属性
struct MaterialProperties {
vec3 emission;  // light produced by the material
vec3 ambient;   // what part of ambient light is reflected
vec3 diffuse;   // what part of diffuse light is scattered
vec3 specular;  // what part of specular light is scattered
float shininess; // exponent for sharpening specular reflection
// other properties you may desire
};
如果应用程序需要经常在不同的材质之间切换，可以使用同一个片段着色器来渲染不同的材质，这样就不需要切换shader或更新uniforms
了。为了达到这样的目的，需要创建一个MaterialProperties数组，其中每个元素表示不同的材质。将材质的索引传入着色器，着色器
会到数组中索引材质，然后对进行合适的渲染。
（3）Two-Sided Lighting
shader中的内置变量gl_FrontFacing用来标记当前正在从正面还是背面观察表面。该变量只能在片段着色器中使用。

5. Lighting Coordinate Systems
所有光照计算用到的法线、方向、位置坐标必须来自同一个坐标系，这样光照计算才会有意义。通常会选择视觉坐标系为光照
坐标系。也就是眼睛的坐标为(0,0,0)并且眼睛朝向z轴负方向。通常提供给光照方程的所有方向和位置都是视觉坐标系，而
光栅化会使用齐次坐标系。
Tips:
使用视觉坐标系来计算光照，世界空间的光的方向需要经过法线矩阵变换。

6. Limitations of the Classic Lighting Model
（1）经典光照模型没有考虑阴影
（2）环境光的衰减不够真实。
（3）一个发热或光亮的物体会有光晕环绕。
（4）一个贴图的表面通常不是非常光滑的，光照必须考虑表面的凹凸，否则表面看起来会不自然的平整。

二、 Advanced Lighting Models
1. Hemisphere Lighting
半球光照背后的理念是使用两个半球来模拟光照。上面的半球代表天空，下面的半球表示地面。物体法线直接指向上方的表面，其所有光
照都来自上半球，物体法线直接指向下方的表面，其所有光照都来自下半球。为两个半球指定合适的颜色，可以让球体上法线指向上方的
被照亮，法线指向下方的在阴影中。
计算表面任何一点的光照：
Color = a * SkyColor + (1 - a) GroundColor
_
| a = 1.0 - (0.5 * sin(x))    x<=90degree
| a = 0.5 * sin(x)            x>90degree
-
or a = 0.5 + 0.5*cos(x)

2. Image-Based Lighting
在基于图片的光照中涉及到以下步骤：
（1）使用光照探针（例如，一个反射球）来抓取发生在现实场景中的照明。抓取到的全方向的，高动态范围的图片被
称作一个光照探针图片
（2）使用光照探针图片来创建环境的表示（例如，环境贴图）
（3）将需要渲染的物体放到环境中
（4）使用步骤（2）生成环境表示来渲染物体
Shaders for Image-based Lighting
--------------------- Vertex Shader ---------------------
// Vertex shader for image-based lighting
#version 330 core
uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;
in vec4 VertexPosition;
in vec3 VertexNormal;
out vec3 ReflectDir;
out vec3 Normal;
void main() {
    Normal = normalize(NormalMatrix * VertexNormal);
    vec4 pos = MVMatrix * VertexPosition;
    vec3 eyeDir = pos.xyz;
    ReflectDir = reflect(eyeDir, Normal);
    gl_Position = MVPMatrix * VertexPosition;
}
 -------------------- Fragment Shader --------------------
 // Fragment shader for image-based lighting
#version 330 core
uniform vec3 BaseColor;
uniform float SpecularPercent;
uniform float DiffusePercent;
uniform samplerCube SpecularEnvMap;
uniform samplerCube DiffuseEnvMap;
in vec3 ReflectDir; in vec3 Normal;
out vec4 FragColor;
void main() {
    // Look up environment map values in cube maps
    vec3 diffuseColor = vec3(texture(DiffuseEnvMap, normalize(Normal)));
    vec3 specularColor = vec3(texture(SpecularEnvMap, normalize(ReflectDir)));
    // Add lighting to base color and mix
    vec3color=mix(BaseColor,diffuseColor*BaseColor,DiffusePercent);
    color = mix(color, specularColor + color, SpecularPercent);
    FragColor = vec4(color, 1.0);
}

3. Lighting with Spherical Harmonics
Spherical Harmonics是用来计算光照漫反射项的方法。这种方法利用光照探针图片可以精确再现漫反射，而不需要在运行时访问光照探针
图片。探针图片被预处理来产生一些系数，在运行时，这些系数可以被用来在数学上表示这个探针图片。
Spherical hamonics表示了一张图片在一个球上的频率空间。这类似于在直线或者是圆上的傅里叶变换。这种图片的表示方法是连续的并且
是旋转不变的。使用这种方式表示一个光照探针图片，你可以只使用9个球谐基函数精确地再现一个表面的漫反射。这9个球谐基函数可以通过
归一化表面法线的常数、线性、二次多项式来获得。
直观上来看，使用少量数目的频率空间上的基函数来模拟漫反射似乎是可以的，因为漫反射在表面的变化很慢。只使用9项参数，对于任何输入
的物理光照分布，在所有朝向的表面上的平均错误要小于3%。使用Debevec的光照探针图片，平均错误还要小于1%，并且对于任意像素的最大
错误要小于5%。
每个球谐基函数有一个基于使用的光照探针图片的系数。这个系数对于不同的颜色通道也不同，所以你可以将每个系数当做一个RGB值。预处理
阶段用来计算光照探针图片的这九个RGB参数。
使用Spherical Harmonics的漫反射公式为：
diffuse = c1 L22 (x^2-y^2) + c3 L20 z^2 + c4 L00 - c5L20 +
          2c1(L2 m2 xy + L21 xz + L2 m1 yz) +
          2c2(L11 x + L1 m1 y + L10z)
c1-c5 为5个常数，L系数是九个基函数系数，他们是通过特定的光照探针图片在预处理阶段计算出来的。x,y,z为被渲染的顶点的归一化的法
线。

因为漫反射变化比较慢，对于没有巨大多边形的场景，我们理当在顶点着色器中计算光照，然后在光栅化阶段进行插值。
// Shaders for Spherical Harmonics Lighting
// --------------------- Vertex Shader ---------------------
// Vertex shader for computing spherical harmonics
#version 330 core
uniform mat4 MVMatrix;
uniform mat4 MVPMatrix;
uniform mat3 NormalMatrix;
uniform float ScaleFactor;
const float C1 = 0.429043;
const float C2 = 0.511664;
const float C3 = 0.743125;
const float C4 = 0.886227;
const float C5 = 0.247708;
// Constants for Old Town Square lighting
const vec3 L00 = vec3( 0.871297, 0.875222, 0.864470);
const vec3 L1m1 = vec3( 0.175058, 0.245335, 0.312891);
const vec3 L10 = vec3( 0.034675, 0.036107, 0.037362);
const vec3 L11 = vec3(-0.004629, -0.029448, -0.048028);
const vec3 L2m2 = vec3(-0.120535, -0.121160, -0.117507);
const vec3 L2m1 = vec3( 0.003242, 0.003624, 0.007511);
const vec3 L20 = vec3(-0.028667, -0.024926, -0.020998);
const vec3 L21 = vec3(-0.077539, -0.086325, -0.091591);
const vec3 L22 = vec3(-0.161784, -0.191783, -0.219152);

in vec4 VertexPosition;
in vec3 VertexNormal;
out vec3 DiffuseColor;
void main()
{
vec3 tnorm = normalize(NormalMatrix * VertexNormal);
DiffuseColor =  C1 * L22 *(tnorm.x * tnorm.x - tnorm.y * tnorm.y) +
                C3 * L20 * tnorm.z * tnorm.z +
                C4 * L00 -
                C5 * L20 +
                2.0 * C1 * L2m2 * tnorm.x * tnorm.y +
                2.0 * C1 * L21 * tnorm.x * tnorm.z +
                2.0 * C1 * L2m1 * tnorm.y * tnorm.z +
                2.0 * C2 * L11 * tnorm.x +
                2.0 * C2 * L1m1 * tnorm.y +
                2.0 * C2 * L10 * tnorm.z;
DiffuseColor *= ScaleFactor;
gl_Position = MVPMatrix * VertexPosition;
}
// -------------------- Fragment Shader --------------------
// Fragment shader for lighting with spherical harmonics
#version 330 core
in vec3 DiffuseColor;
out vec4 FragColor;
void main()
{
FragColor = vec4(DiffuseColor, 1.0);
}

三、 Shadow Mapping
















