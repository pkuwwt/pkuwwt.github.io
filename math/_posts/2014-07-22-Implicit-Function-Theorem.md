---
layout: blog
comments: true
math: true
title: 隐函数定理
---

## 隐函数定理表述
令$f:\mathbf{R}^n\times\mathbf{R}^m\to\mathbf{R}^m$为连续可微函数。$f(x,y)=c$确定了一个区域$D\subset\mathbf{R}^{n+m}$。
对于任意$(a,b)\in\mathbf{R}^n\times\mathbf{R}^m$，若方阵$\left(\frac{\partial f}{\partial y}\right)(a,b)$可逆，则存在包含$a$的开集$U\subset\mathbf{R}^{n}$，和包含$b$的开集$V\subset\mathbf{R}^m$，以及连续可微函数$g:U\to V$，满足

$$
\{(x,g(x)): x\in U\} = \{(x,y)\in U\times V: f(x,y)=c\}
$$

对$f$求微分
$$
df = \left[\frac{\partial f}{\partial x}|\frac{\partial f}{\partial y}\right] = [X|Y] = 0
$$
其中$X$是$m\times n$矩阵，$Y$是$m\times m$方阵，$Y$在$(a,b)$处是否可逆是判断$(a,b)$邻域内是否存在隐函数的依据。

## 理解
假设隐函数存在，则$f(x,y)=f(x,g(x))$，对$x_j$求微分得

$$
\begin{array}{rcl}
\frac{\partial f}{\partial x_j} &=& \frac{\partial f}{\partial x_j}(x,g(x)) + \frac{\partial f}{\partial y}(x,g(x)) \frac{\partial g}{\partial x_j}(x,g(x)) \\
0 &=& X + Yg_{x_j} \\
g_{x_j} &=& -Y^{-1}X
\end{array}
$$

显然，$Y$必须是可逆矩阵。

## 示例
以单位圆$f(x,y)=x^2+y^2=1$为例，$1\times1$方阵$\partial f/\partial y$为$2y$，因此，在$(\pm1,0)$处，无隐函数存在，这是符合实际情况的。

## 参考文献

  * [Wikipedia:Implicit function theorem](http://en.wikipedia.org/wiki/Implicit_function_theorem)

