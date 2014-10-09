---
layout: blog
comments: true
title: Linux下常用工具
---

下面都是我常用的软件。

## 排版工具

  - LaTeX(texlive)
  - pandoc+markdown

## 文本工具

  - 编辑器: vim，键盘控还是不习惯用emacs
  - 文本处理: grep,sed,awk,以及其它常用shell命令

## 影音工具

  - mplayer+smplayer
  - projectM: 音乐可视化软件

## 编程工具

  - GNU工具链: gcc/g++/make/automake
  - 跨平台工程管理: cmake
  - 其它语言: java, python
  - IDE: eclipse

## 图形工具

  - gnuplot: 常见的函数绘图和数据作图
  - oodraw(libreoffice-draw): 画流程图方便
  - gimp: 类似于photoshop的一个软件
  - graphviz: 画graph和网络结构很方便
  - ImageMagick: 图片处理命令行工具
  - dia: 类似于visio，可以画流程图和UML
  - plantuml: 用脚本画UML
  - tikz/pgf: 基本latex的矢量线条图
  - sketch: 基于命令的3维矢量草图
  - openscad: 基于脚本的3维工程制图，语法很简单

## 数学工具

  - R: 统计类软件，在生物信息学应用最多
  - octave: 和matlab语法类同，有些.m脚本可以直接运行
  - matlab: 不多说，迫不得已用一下
  - kdeedu-math: KDE出了不少好软件，这个数学套装里的kmplot和kalgebra是画函数(2D/3D)图的好手。
  - maxima: 符号计算软件，Mathematica的前辈。行列式，(非)线性方程组再也不用手算了。它有wx版本，能更好地显示公式。
  - geogebra: 交互式绘制几何对象，并能自由修改坐标，支持命令输入。最新版支持3维视图。

## 桌面工具

  - 截屏: ksnapshot，这个最好用了
  - 录屏: qt-recordmydesktop,istanbul

## 办工软件

  - office: wps, libreoffice。相较而言，国货虽不开源，但也相当好用了。
  - pdf: evince。如果需要注释功能，用wine+foxit吧。

## 网络软件

  - 浏览器: chrome虽然耗资源，但还是比firefox华丽很多
  - 下载: wget, axel, aria2。BT可用transmission，ed2k可用amule，但是俱往矣，现在有百度云了。wget最好用的功能是扒网站：`wget -mk -w 30 -e robots=off --user-agent="Mozilla/4.5 (X11; U; Linux x86_64; en-US)" http://xxx.xxx.com`或`wget -np -r -l 4 robots=off --user-agent="Mozilla/4.5 (X11; U; Linux x86_64; en-US)" http://xxx.xxx.com`。wget可以续传，但是不能分段下载。aria2和axel既能续传，又能分段。而且aria2居然支持磁力链和种子。axel的续传直接使用`-o`选项即可。

