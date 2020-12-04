# MiniMineCraft
本项目是基于**C++(c11)**、**OpenGL**和**GLFW**实现的模仿我的世界的图形学小Demo。实现了包括随机地形生成，方块消除和放置功能。</br>
前后断断续续用了5天左右的时间开发完成。完成仓促，因此在类结构、功能和性能上都有很多不足的地方，后续有时间会进行重构修改，并记录全过程。</br>
其中方块贴图资源来源于[Craft项目](https://github.com/fogleman/Craft)，噪声函数来源于[noise项目](https://github.com/caseman/noise)。
# 使用方式
## 代码使用方式
项目基于windows开发，项目代码位于MineCraftDemo文件夹中，可以直接使用visual studio 2015加载。
## 全局参数设置
全局参数位于WorldInfo.h&WorldInfo.cpp中，会影响运行性能的参数如下：
参数名|说明|备注
-|-|-
renderChunkRadius|渲染半径|设置的越大可见范围越广，但可能会造成卡顿。默认为2，建议设置为1
useLight|是否开启光照明|默认开启
useFog|是否开启雾效|默认开启
rayTestStepNum|射线检测步数|和rayTestStep共同决定射线检测的精度和距离
rayTestStep|射线检测步长|同rayTestStepNum
waterLevel|水平面|

# 运行效果
![运行效果1](/img/运行示意图1.png)
![运行效果1](/img/运行示意图2.png)
![运行效果1](/img/运行示意图3.jpg)
![运行效果1](/img/运行示意图4.png)

---
+ 感谢[CregskiN](https://github.com/CregskiN)提供的[xcode版本](https://github.com/CregskiN/MiniMineCraft-xcode)
