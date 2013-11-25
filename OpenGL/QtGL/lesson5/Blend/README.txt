一.混合

混合操作一共分为两步:
第一步:指定如何计算源和目标混合因子
使用glBlendFunc(source,destination);
第二部:指定源和目标的RGBA成分如何混合
使用glBlendEquation(parameter);

混合的结果计算
假定
1.源和目标混合因子分别为(Sr,Sg,Sb,Sa),(Dr,Dg,Db,Da),
2.源和目标颜色分别为(Rs,Gs,Bs,As),(Rd,Gd,Bd,Ad),
那么经过混合最终所得的RGBA值为
(RsSr operator RdDr,
 GsSg operator GdDg,
 BsSb operator BdDb,
 AsSa operator AdDa)
 其中operator表示源和目标的RGBA成分混合方式
Tips:
先绘制的是目标颜色,后绘制的是源颜色.

二.雾

雾在本质上是一种视觉效果模拟应用,用于模拟有限可视性的场合.开启雾以后,远离观察点的物体开始融入
到雾的颜色中.可以控制雾的浓度,它决定了物体随着距离的增加而融入到雾颜色的速度.

雾是在执行了矩阵变换\光照和纹理之后才应用的.在大型的模拟程序中,雾可以提高性能,因为它可以选择
不用绘制那些因为雾的影响看不见的物体.

使用雾
glEnable(GL_FROG)
{
    GLfloat fogColor[4] = {0.5,0.5,0.5,1.0};

    GLint fogMode = GL_EXP;
    glFogi(GL_FOG_MODE,fogMode);
    glFogfv(GL_FOG_COLOR,fogColor);
    glFogf(GL_FOG_DENSITY,0.35);
    glFogf(GL_FOG_START,1.0);
    glFogf(GL_FOG_END,0.5);
    glHint(GL_FOG_HINT,GL_DONT_CARE);
}

三.点参数
点参数根据点和观察点的距离,对点的大小和亮度进行衰减.

四.多边形偏移
多边形偏移增加一个适当的偏移值把重合的z值适当地分开一些,使着重显示的直线和多边形的边缘清晰的
分离开来.
