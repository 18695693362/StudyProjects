说明：
该项目实现一个太阳系的模型。画出3个天体：太阳、地球、月亮。
太阳在赤道处的自转周期是24.47天，约为25天；
地球的自转是1天，公转是356天；
月亮的自转公转都是28天；
太阳半径696000千米
地球半径6400千米
月球半径1738.2千米
太阳：地球：月亮 = 350:3:1
太阳地球距离：1.4亿千米
地球月球距离：384000千米

程序里的数据：
太阳自转            30秒
地球公转            360秒
地球自转            10秒
月球自转公转          30秒
太阳地球距离      100
地球月球距离      40
太阳半径        30
地球半径        20
月亮半径        10

一、使用顶点数组对几何图形进行渲染需要下面3个步骤：
1、激活（启用）最多可达8个数组，每个数组用于存储不同类型的数据：顶点坐标、
表面法线、RGBA颜色、辅助颜色、颜色索引、雾坐标、纹理坐标以及多边形的边界标志。

2、把数据放入数组中。这些数组是通过他们的内存位置的地址（即指针）访问的。
在客户机-服务器模型中，这些数组存储在客户机的地址空间中，除非选择使用缓冲区对象，
这时候，数组存储在服务器内存中。

3、用这些数据绘制几何图形。OpenGL通过指针从所有的被激活数组中获取数据。

二、glPushMatrix() glPosMatrix()
可以使用上面的函数来限制某些矩阵变换只作用在特定的顶点数据上。

三、在正二十面体基础上，使用递归法画球体
1、将正二十面体的每个三角形面细分为4个三角形面。
2、将细分出来的面的顶点进行单位化。（这样就可以保证顶点是在球体表面上的）
3、以单位化后的顶点为新的顶点数据，绘制三角形。

四、光源的属性
1、环境强度
2、散射强度
3、镜面强度
4、位置 glLightfv(GL_LIGHT0,GL_POSITION,pos);
（1）pos是观察点和光源的相对位置。
（2）pos是一个四维顶点（x,y,z,w）。
w的值为0.0f表示，光源是方向性光源，光源位于无限远处，(x,y,z)表示光的方向。
w的值不为0.0f表示，光源是位置性光源，(x,y,z)表示光源的位置。
（3）光源的位置会受到模型视图矩阵变换的影响。其实，光源就好像一个具有光属性的顶点。
5、聚光灯参数
6、常量衰减因子、线性衰减因子、二次衰减因子

五、光照模型
1、全局环境光强度
glLightModelfv(GL_LIGHT_MODEL_AMBIENT,g_lightBlackColor);
2、观察点的位置
glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
3、双面光照
glLightModelf(GL_LIGHT_MODEL_TWO_SIDE,GL_TRUE);
4、镜面颜色是否从环境颜色和散射颜色中分离出来，在纹理操作之后应用。
glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SEPARATE_SPECULAR_COLOR);
glLightModelf(GL_LIGHT_MODEL_COLOR_CONTROL,GL_SINGLE_COLOR);

六、材料属性
1、材料的环境颜色、散射颜色、镜面颜色、发射颜色、镜面指数
glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,g_lightBlueColor);
glMaterialfv(GL_FRONT,GL_EMISSION,g_blackColor);
2、颜色材料模式
glEnable(GL_COLOR_MATERIAL)
glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE)



