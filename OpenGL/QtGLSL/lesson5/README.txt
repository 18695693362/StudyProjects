    Viewing Transformations Clipping and Feedback

一、 Viewing
将三维变为二维用到的关键工具有：视图模型、标准设备坐标的使用、通过矩阵乘运用线性变换、设置视图映射。
1. Camera Model
制作需要的视图所进行的变换处理和用照相机拍照片类似。
拍照片的步骤：
（1）放置照相机
（2）放置模型
（3）选择镜头
OpenGL渲染图片的步骤：
（1）将照相机移动到你想放置的地方，并且将它的方向放置正确。【视图变换】
（2）将被拍摄的物体放到场景中。【模型变换】
（3）选择照相机摄像头调解缩放。【投影变换】
（4）拍照
（5）放大或缩小结果图片到需要的尺寸。【视口变换】
步骤3决定了场景中多少内容被拍摄到。
步骤5决定了被拍摄到的内容放到多大的屏幕上。
2. Viewing Frustum
OpenGL会排除太近或太远的几何体，也就是说在near平面前面的或在far平面后面的物体会被排除。
靠近视景体顶角的物体会非常大，特别是在顶角上时，这会造成问题。物体太远时出于性能原因，以及
深度精度问题，太远的物体会被排除。
3. Frustum Clipping
图元跨越裁剪平面时，OpenGL会裁剪这样的图元。
4. Orthographic Viewing Model
物体正交投影投影后，维持物体实际尺寸以及他们之间的夹角不变。正交投影只是忽略一个维度的坐标。

二、 User Transformations

三、 OpenGL Transformations
四、 Transform Feedback






















