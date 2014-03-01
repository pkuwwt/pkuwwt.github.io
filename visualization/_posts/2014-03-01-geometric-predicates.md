---
layout: blog
comments: true
title: 几种基本几何预测
---

  - [马克斯·普朗克计算机科学研究所](http://www.mpi-inf.mpg.de/)的[计算几何和几何计算](http://www.mpi-inf.mpg.de/departments/d1/teaching/ws09_10/CGGC/)课程。
  - [原文](http://www.mpi-inf.mpg.de/departments/d1/teaching/ws09_10/CGGC/Exercises/Ex01.pdf)

本文讨论几种主要的几何预测(geometric predicates)。

## 方向(orientation)预测
令$$p=(p_x,p_y)$$, $$q=(q_x,q_y)$$，$$r=(r_x,r_y)$$，是平面上的3个点。我们已经证明了

$$
2\cdot area(\Delta(p,q,r)) = det\begin{pmatrix}
1 & p_x & p_y \\
1 & q_x & q_y \\
1 & r_x & r_y 
\end{pmatrix}
$$

是三角形$$\Delta pqr$$的有向面积的2倍。本文是为了给出另外一种证明。图1显出了一个黄色平行四边形$$P$$。用大正方形减去长方形$$R$$，及三角形$$T_1$$和$$T_2$$，可以得到$$P$$的有向面积为$$bc'-b'c$$。那这与方向预测有啥关系? 

![](../img/parallelogram-area.png)

图1. 由矢量$$(b,b')$$,$$(c,c')$$确定的平行

其实，你以点$$p$$为局部坐标系的原点，则另外两点在此坐标系中的坐标分别为$$(b,b')=(q_x-p_x, q_y-p_y)$$，$$(c,c')=(r_x-p_x,r_y-p_y)$$，上面的行列式中用第二行和第三行送去第一行，显然，结果刚好就等于$$bc'-b'c$$。

$$
2\cdot area(\Delta(p,q,r)) = det\begin{pmatrix}
1 & p_x & p_y \\
0 & q_x-p_x & q_y-p_y \\
0 & r_x-p_x & r_y-p_y 
\end{pmatrix} = det\begin{pmatrix}
1 & p_x & p_y \\
0 & b & b' \\
0 & c & c'
\end{pmatrix}
$$

有向面积值为正，表示三角形是逆时针，否则表示顺时针。如果为0则三点共线。

## 圆内外(side of circle)预测

令$$p=(p_x,p_y)$$, $$q=(q_x,q_y)$$，$$r=(r_x,r_y)$$，$$s=(s_x,s_y)$$是平面上的4个点。头3个点定义了一个有向圆(从$$p$$经过$$q$$到达$$r$$)。我们希望判定$$s$$在圆的左边还是右边。如果圆有逆时针方向，左对应内部，右对应着外部。本文的目的在于显示下面的公式可用于预测圆内外问题(side-of-circle)。

$$
C(p,q,r,s) = det\begin{pmatrix}
1 & p_x & p_y & p_x^2+p_y^2 \\
1 & q_x & q_y & q_x^2+q_y^2 \\
1 & r_x & r_y & r_x^2+r_y^2 \\
1 & s_x & s_y & s_x^2+s_y^2 
\end{pmatrix}
$$

如果4点共线，则上式为0，因为只需要两个点就可以通过仿射变换(系数和为1)表示连线上的所有点，因此上述行列式至少有两行的前3项可以通过行变换变成0，显然这样的行列式值为0。

现在，假定4点不共线，且$$p$$, $$q$$和$$r$$可以定义一个正常的三角形。对于平面上的点$$v=(v_x,v_y)$$来说，令$$\ell(v)=(v_x,v_y,v_x^2+v_y^2)$$为$$v$$对于抛物面$$z=x^2+y^2$$的"提升"。

首先假定$$\Delta(p,q,r)$$的外接圆的中心位于原点。则矩阵第4列是各点离原点的距离的平方，且$$p,q,r$$三点至原点距离相等，设为$$R$$，而$$s$$离原点的距离设为$$L$$，则行列式变成

$$
C(p,q,r,s) = det\begin{pmatrix}
1 & p_x & p_y & R^2 \\
1 & q_x & q_y & R^2 \\
1 & r_x & r_y & R^2 \\
1 & s_x & s_y & L^2 
\end{pmatrix}
$$

显然，点$$s$$可以由其它3个点的仿射组合而得到，即存在$$\lambda_p$$,$$\lambda_q$$和$$\lambda_r$$满足

$$
(1,s_x,s_y) = \lambda_p(1,p_x,p_y) + \lambda_q(1,q_x,q_y) + \lambda_r(1,r_x,r_y)
$$

使用上述公式可以简化矩阵的第4行。 在第4行上加上第一行的$$-\lambda_p$$，第二行的$$-\lambda_q$$，和第三行的$$-\lambda_r$$，则第4行的前3项变成0，剩下最后一项为

$$
L^2 - (\lambda_p+\lambda_q+\lambda_r)R^2 = L^2 - R^2
$$

现在，可以得到上述行列式的值为
  
$$2\cdot area(\Delta(p,q,r))\cdot(L^2-R^2)$$

其中$$R$$是$$\Delta$$的外接圆的半径，而$$L$$是$$s$$离原点的距离。

由上式可知，行列式是可以用于圆内外(side-of-circle)的预测的。**如果$$p,q,r$$是逆时针的，则行列式$$C(p,q,r,s)$$为正说明$$s$$在圆外，为负说明在圆内，为0说明共圆(或者共线)**。

此过程可以推广到原点不在$$\Delta$$外接圆圆心的情况。令原点为$$o$$，$$\Delta(p,q,r)$$的外接圆的原心为$$c$$，则$$\vert\vec{cp}\vert=\vert\vec{cq}\vert=\vert\vec{cr}\vert=R$$，而$$\vert\vec{cs}\vert=L$$。

$$\lambda_p,\lambda_q,\lambda_r$$仍然是由$$p,q,r$$到$$s$$的仿射变换的系数。且易知

$$
\begin{array}{rcl}
\lambda_p + \lambda_q + \lambda_r &=& 1 \\
(\vec{op},\vec{oq},\vec{or},\vec{os}) &=& ((p_x,p_y),(q_x,q_y),(r_x,r_y),(s_x,s_y)) \\
\vec{os} &=& \lambda_p\vec{op}+\lambda_q\vec{oq}+\lambda_r\vec{or} \\
\vec{cs} &=& \lambda_p\vec{cp}+\lambda_q\vec{cq}+\lambda_r\vec{cr}
\end{array}
$$

与前面的推理一样，消除第4行的前3项，最后一项变成

$$
\begin{array}{cl}
&\vert\vec{cs}\vert^2 - \lambda_p\vert\vec{cp}\vert^2 - \lambda_q\vert\vec{cq}\vert^2 - \lambda_r\vert\vec{cr}\vert^2 \\
=& (\vec{oc}+\vec{cs})^2 - \lambda_p(\vec{oc}+\vec{cs})^2 - \cdots \\
=& (\vert\vec{oc}\vert^2 - \lambda_p\vert\vec{oc}\vert^2 - \lambda_q\vert\vec{oc}\vert^2 - \lambda_r\vert\vec{oc}\vert^2) + \\
 & 2\vec{oc}\cdot(\vec{cs} - \lambda_p\vec{cp} - \lambda_q\vec{cq} - \lambda_r\vec{cr}) + \\
 & (\vert\vec{cs}\vert^2 - \lambda_p\vert\vec{cp}\vert^2 - \lambda_q\vert\vec{cq}\vert^2 - \lambda_r\vert\vec{cr}\vert^2) \\
=& 0 + 2\cdot 0 + (L^2 - R^2)
\end{array}
$$

如果$$p,q,r$$是共线的，上述行列式不一定为0，但是$$\Delta(p,q,r)$$的有向面积却为0。可以考虑极限情况，将其视为是无穷大的圆，由此相当于是判定$$s$$在直线的哪一边。

